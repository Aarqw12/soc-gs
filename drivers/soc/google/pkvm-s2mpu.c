// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2022 - Google LLC
 * Author: David Brazdil <dbrazdil@google.com>
 */

#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>

#include <linux/io-64-nonatomic-hi-lo.h>
#include <linux/pm_domain.h>
#include <linux/pm_runtime.h>

#include <linux/kvm_host.h>
#include <asm/kvm_s2mpu.h>

#include <soc/google/pkvm-s2mpu.h>

struct s2mpu_data {
	struct device *dev;
	void __iomem *base;
	bool pkvm_registered;
};

static struct platform_device *__of_get_phandle_pdev(struct device *parent,
						     const char *prop, int index)
{
	struct device_node *np;
	struct platform_device *pdev;

	np = of_parse_phandle(parent->of_node, prop, index);
	if (!np)
		return NULL;

	pdev = of_find_device_by_node(np);
	of_node_put(np);
	if (!pdev)
		return ERR_PTR(-EINVAL);

	return pdev;
}

int pkvm_s2mpu_of_link(struct device *parent)
{
	struct platform_device *pdev;
	struct device_link *link;
	int i;

	/* Check that all S2MPUs have been initialized. */
	for (i = 0; (pdev = __of_get_phandle_pdev(parent, "s2mpus", i)); i++) {
		if (IS_ERR(pdev))
			return PTR_ERR(pdev);

		if (!pkvm_s2mpu_ready(&pdev->dev))
			return -EAGAIN;
	}

	/* Link all S2MPUs as suppliers to the parent. */
	for (i = 0; (pdev = __of_get_phandle_pdev(parent, "s2mpus", i)); i++) {
		if (IS_ERR(pdev))
			return PTR_ERR(pdev);

		link = device_link_add(/*consumer=*/parent, /*supplier=*/&pdev->dev,
				       DL_FLAG_AUTOREMOVE_CONSUMER | DL_FLAG_PM_RUNTIME);
		if (!link)
			return -EINVAL;
	}

	return 0;
}
EXPORT_SYMBOL_GPL(pkvm_s2mpu_of_link);

static irqreturn_t s2mpu_irq_handler(int irq, void *ptr)
{
	struct s2mpu_data *data = ptr;
	unsigned int vid;
	u32 vid_bmap, fault_info;
	phys_addr_t fault_pa;
	const char *fault_type;
	irqreturn_t ret = IRQ_NONE;

	while ((vid_bmap = readl_relaxed(data->base + REG_NS_FAULT_STATUS))) {
		WARN_ON_ONCE(vid_bmap & (~ALL_VIDS_BITMAP));
		vid = __ffs(vid_bmap);

		fault_pa = hi_lo_readq_relaxed(data->base + REG_NS_FAULT_PA_HIGH_LOW(vid));
		fault_info = readl_relaxed(data->base + REG_NS_FAULT_INFO(vid));
		WARN_ON(FIELD_GET(FAULT_INFO_VID_MASK, fault_info) != vid);

		switch (FIELD_GET(FAULT_INFO_TYPE_MASK, fault_info)) {
		case FAULT_INFO_TYPE_MPTW:
			fault_type = "MPTW fault";
			break;
		case FAULT_INFO_TYPE_AP:
			fault_type = "access permission fault";
			break;
		case FAULT_INFO_TYPE_CONTEXT:
			fault_type = "context fault";
			break;
		default:
			fault_type = "unknown fault";
			break;
		}

		dev_err(data->dev, "\n"
			"============== S2MPU FAULT DETECTED ==============\n"
			"  PA=%pap, FAULT_INFO=0x%08x\n"
			"  DIRECTION: %s, TYPE: %s\n"
			"  VID=%u, REQ_LENGTH=%lu, REQ_AXI_ID=%lu\n"
			"==================================================\n",
			&fault_pa, fault_info,
			(fault_info & FAULT_INFO_RW_BIT) ? "write" : "read",
			fault_type, vid,
			FIELD_GET(FAULT_INFO_LEN_MASK, fault_info),
			FIELD_GET(FAULT_INFO_ID_MASK, fault_info));

		writel_relaxed(BIT(vid), data->base + REG_NS_INTERRUPT_CLEAR);
		ret = IRQ_HANDLED;
	}

	return ret;
}

/*
 * Parse interrupt information from DT and if found, register IRQ handler.
 * This is considered optional and will not fail even if the initialization is
 * unsuccessful. In that case the IRQ will remain masked.
 */
static void s2mpu_probe_irq(struct platform_device *pdev, struct s2mpu_data *data)
{
	int ret, irq;

	irq = platform_get_irq_optional(pdev, 0);

	if (irq == -ENXIO)
		return; /* No IRQ specified. */

	if (irq < 0) {
		/* IRQ specified but failed to parse. */
		dev_err(data->dev, "failed to parse IRQ, IRQ not enabled");
		return;
	}

	ret = devm_request_irq(data->dev, irq, s2mpu_irq_handler, 0,
			       dev_name(data->dev), data);
	if (ret) {
		dev_err(&pdev->dev, "failed to register IRQ, IRQ not enabled");
		return;
	}
}

static int s2mpu_suspend(struct device *dev)
{
	struct s2mpu_data *data = platform_get_drvdata(to_platform_device(dev));

	if (data->pkvm_registered)
		return pkvm_iommu_suspend(dev);

	return 0;
}

static int s2mpu_resume(struct device *dev)
{
	struct s2mpu_data *data = platform_get_drvdata(to_platform_device(dev));

	if (data->pkvm_registered)
		return pkvm_iommu_resume(dev);

	writel_relaxed(0, data->base + REG_NS_CTRL0);
	return 0;
}

static int s2mpu_late_suspend(struct device *dev)
{
	if (pm_runtime_status_suspended(dev))
		return 0;

	dev->power.must_resume = true;
	return s2mpu_suspend(dev);
}

static int s2mpu_late_resume(struct device *dev)
{
	if (pm_runtime_status_suspended(dev))
		return 0;

	return s2mpu_resume(dev);
}

static int s2mpu_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = pdev->dev.of_node;
	struct resource *res;
	struct s2mpu_data *data;
	bool always_on, off_at_boot;
	int ret;

	data = devm_kmalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;
	data->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "failed to parse 'reg'");
		return -EINVAL;
	}

	/* devm_ioremap_resource internally calls devm_request_mem_region. */
	data->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(data->base)) {
		dev_err(dev, "could not ioremap resource: %ld", PTR_ERR(data->base));
		return PTR_ERR(data->base);
	}

	always_on = !!of_get_property(np, "always-on", NULL);
	off_at_boot = !!of_get_property(np, "off-at-boot", NULL);

	/*
	 * Try to parse IRQ information. This is optional as it only affects
	 * runtime fault reporting, and therefore errors do not fail the whole
	 * driver initialization.
	 */
	s2mpu_probe_irq(pdev, data);

	ret = pkvm_iommu_s2mpu_register(dev, res->start);
	if (ret && ret != -ENODEV) {
		dev_err(dev, "could not register: %d\n", ret);
		return ret;
	}

	data->pkvm_registered = ret != -ENODEV;
	if (!data->pkvm_registered)
		dev_warn(dev, "pKVM disabled, control from kernel\n");

	platform_set_drvdata(pdev, data);

	/*
	 * Most S2MPUs are in an allow-all state at boot. Call the hypervisor
	 * to initialize the S2MPU to a blocking state. This corresponds to
	 * the state the hypervisor sets on suspend.
	 */
	if (!off_at_boot)
		WARN_ON(s2mpu_suspend(dev));

	pm_runtime_enable(dev);
	if (always_on)
		pm_runtime_get_sync(dev);

	return 0;
}

static const struct dev_pm_ops s2mpu_pm_ops = {
	SET_RUNTIME_PM_OPS(s2mpu_suspend, s2mpu_resume, NULL)
	SET_LATE_SYSTEM_SLEEP_PM_OPS(s2mpu_late_suspend, s2mpu_late_resume)
};

static const struct of_device_id s2mpu_of_match[] = {
	{ .compatible = "google,s2mpu" },
	{},
};

static struct platform_driver s2mpu_driver = {
	.probe = s2mpu_probe,
	.driver = {
		.name = "pkvm-s2mpu",
		.of_match_table = s2mpu_of_match,
		.pm = &s2mpu_pm_ops,
	},
};

module_platform_driver(s2mpu_driver);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("David Brazdil <dbrazdil@google.com>");
