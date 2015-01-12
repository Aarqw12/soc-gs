/**
 * dwc3-pci.c - PCI Specific glue layer
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - http://www.ti.com
 *
 * Authors: Felipe Balbi <balbi@ti.com>,
 *	    Sebastian Andrzej Siewior <bigeasy@linutronix.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2  of
 * the License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/pci.h>
#include <linux/platform_device.h>

#include "platform_data.h"

/* FIXME define these in <linux/pci_ids.h> */
#define PCI_VENDOR_ID_SYNOPSYS		0x16c3
#define PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3	0xabcd
#define PCI_DEVICE_ID_INTEL_BYT		0x0f37
#define PCI_DEVICE_ID_INTEL_MRFLD	0x119e
#define PCI_DEVICE_ID_INTEL_BSW		0x22B7

struct dwc3_pci {
	struct device		*dev;
	struct platform_device	*dwc3;
};

static int dwc3_pci_probe(struct pci_dev *pci,
		const struct pci_device_id *id)
{
	struct resource		res[2];
	struct platform_device	*dwc3;
	struct dwc3_pci		*glue;
	int			ret;
	struct device		*dev = &pci->dev;
	struct dwc3_platform_data dwc3_pdata;

	memset(&dwc3_pdata, 0x00, sizeof(dwc3_pdata));

	glue = devm_kzalloc(dev, sizeof(*glue), GFP_KERNEL);
	if (!glue)
		return -ENOMEM;

	glue->dev = dev;

	ret = pcim_enable_device(pci);
	if (ret) {
		dev_err(dev, "failed to enable pci device\n");
		return -ENODEV;
	}

	pci_set_master(pci);

	dwc3 = platform_device_alloc("dwc3", PLATFORM_DEVID_AUTO);
	if (!dwc3) {
		dev_err(dev, "couldn't allocate dwc3 device\n");
		return -ENOMEM;
	}

	memset(res, 0x00, sizeof(struct resource) * ARRAY_SIZE(res));

	res[0].start	= pci_resource_start(pci, 0);
	res[0].end	= pci_resource_end(pci, 0);
	res[0].name	= "dwc_usb3";
	res[0].flags	= IORESOURCE_MEM;

	res[1].start	= pci->irq;
	res[1].name	= "dwc_usb3";
	res[1].flags	= IORESOURCE_IRQ;

	if (pci->vendor == PCI_VENDOR_ID_AMD &&
			pci->device == PCI_DEVICE_ID_AMD_NL_USB) {
		dwc3_pdata.has_lpm_erratum = true;
		dwc3_pdata.lpm_nyet_threshold = 0xf;

		dwc3_pdata.u2exit_lfps_quirk = true;
		dwc3_pdata.u2ss_inp3_quirk = true;
		dwc3_pdata.req_p1p2p3_quirk = true;
		dwc3_pdata.del_p1p2p3_quirk = true;
		dwc3_pdata.del_phy_power_chg_quirk = true;
		dwc3_pdata.lfps_filter_quirk = true;
		dwc3_pdata.rx_detect_poll_quirk = true;

		dwc3_pdata.tx_de_emphasis_quirk = true;
		dwc3_pdata.tx_de_emphasis = 1;

		/*
		 * FIXME these quirks should be removed when AMD NL
		 * taps out
		 */
		dwc3_pdata.disable_scramble_quirk = true;
		dwc3_pdata.dis_u3_susphy_quirk = true;
		dwc3_pdata.dis_u2_susphy_quirk = true;
	}

	ret = platform_device_add_resources(dwc3, res, ARRAY_SIZE(res));
	if (ret) {
		dev_err(dev, "couldn't add resources to dwc3 device\n");
		return ret;
	}

	pci_set_drvdata(pci, glue);

	ret = platform_device_add_data(dwc3, &dwc3_pdata, sizeof(dwc3_pdata));
	if (ret)
		goto err3;

	dma_set_coherent_mask(&dwc3->dev, dev->coherent_dma_mask);

	dwc3->dev.dma_mask = dev->dma_mask;
	dwc3->dev.dma_parms = dev->dma_parms;
	dwc3->dev.parent = dev;
	glue->dwc3 = dwc3;

	ret = platform_device_add(dwc3);
	if (ret) {
		dev_err(dev, "failed to register dwc3 device\n");
		goto err3;
	}

	return 0;

err3:
	platform_device_put(dwc3);
	return ret;
}

static void dwc3_pci_remove(struct pci_dev *pci)
{
	struct dwc3_pci	*glue = pci_get_drvdata(pci);

	platform_device_unregister(glue->dwc3);
}

static const struct pci_device_id dwc3_pci_id_table[] = {
	{
		PCI_DEVICE(PCI_VENDOR_ID_SYNOPSYS,
				PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3),
	},
	{ PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_BSW), },
	{ PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_BYT), },
	{ PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_MRFLD), },
	{ PCI_DEVICE(PCI_VENDOR_ID_AMD, PCI_DEVICE_ID_AMD_NL_USB), },
	{  }	/* Terminating Entry */
};
MODULE_DEVICE_TABLE(pci, dwc3_pci_id_table);

static struct pci_driver dwc3_pci_driver = {
	.name		= "dwc3-pci",
	.id_table	= dwc3_pci_id_table,
	.probe		= dwc3_pci_probe,
	.remove		= dwc3_pci_remove,
};

MODULE_AUTHOR("Felipe Balbi <balbi@ti.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("DesignWare USB3 PCI Glue Layer");

module_pci_driver(dwc3_pci_driver);
