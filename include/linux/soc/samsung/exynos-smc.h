/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2018 Samsung Electronics Co., Ltd.
 *	      http://www.samsung.com/
 *
 * Exynos - SMC call
 */

#ifndef __EXYNOS_SMC_H__
#define __EXYNOS_SMC_H__

#include <linux/arm-smccc.h>

/* For Power Management */
#define SMC_CMD_SLEEP			(-3)
#define SMC_CMD_CPU1BOOT		(-4)
#define SMC_CMD_CPU0AFTR		(-5)
#define SMC_CMD_SAVE			(-6)
#define SMC_CMD_SHUTDOWN		(-7)

#define SMC_CMD_CPUMAP			(-10)

/* For Accessing CP15/SFR (General) */
#define SMC_CMD_REG			(-101)

/* For setting memory for debug */
#define SMC_CMD_SET_DEBUG_MEM		(-120)
#define SMC_CMD_GET_LOCKUP_REASON	(-121)
#define SMC_CMD_KERNEL_PANIC_NOTICE	(0x8200007A)
#define SMC_CMD_SET_SEH_ADDRESS		(-123)
#define SMC_CMD_LOCKUP_NOTICE		(0x8200007C)
#define SMC_CMD_GET_SJTAG_STATUS	(0x8200012E)

/* For protecting kernel text area */
#define SMC_CMD_PROTECT_KERNEL_TEXT	(-125)

/* For Security Dump Manager */
#define SMC_CMD_DUMP_SECURE_REGION	(-130)
#define SMC_CMD_FLUSH_SECDRAM		(-131)

/* For D-GPIO/D-TZPC */
#define SMC_CMD_PREPARE_PD_ONOFF	(0x82000410)

/* For accessing privileged registers */
#define SMC_CMD_PRIV_REG		(0x82000504)

/* For FMP/SMU Ctrl */
#define SMC_CMD_FMP_SECURITY		(0xC2001810)
#define SMC_CMD_FMP_DISK_KEY_STORED	(0xC2001820)
#define SMC_CMD_FMP_DISK_KEY_SET	(0xC2001830)
#define SMC_CMD_FMP_DISK_KEY_CLEAR	(0xC2001840)
#define SMC_CMD_SMU			(0xC2001850)
#define SMC_CMD_FMP_SMU_RESUME		(0xC2001860)
#define SMC_CMD_FMP_SMU_DUMP		(0xC2001870)
#define SMC_CMD_UFS_LOG			(0xC2001880)
#define SMC_CMD_FMP_USE_OTP_KEY		(0xC2001890)

/* SMU IDs (third parameter to FMP/SMU Ctrls) */
#define SMU_EMBEDDED			0
#define SMU_UFSCARD			1
#define SMU_SDCARD			2

/* SMU commands (second parameter to SMC_CMD_SMU) */
#define SMU_INIT			0
#define SMU_SET				1
#define SMU_ABORT			2

/* Fourth parameter to SMC_CMD_FMP_SECURITY */
#define CFG_DESCTYPE_3			3

/* Command ID for smc */
#define SMC_PROTECTION_SET		(0x82002010)
#define SMC_DRM_FW_LOADING		(0x82002011)
#define SMC_DCPP_SUPPORT		(0x82002012)
#define SMC_DRM_HISTOGRAM_SEC		(0x82002013)
#define SMC_DRM_HISTOGRAM_BINS_SEC	(0x82002014)
#define SMC_DRM_SECBUF_PROT		(0x82002020)
#define SMC_DRM_SECBUF_UNPROT		(0x82002021)
#define SMC_DRM_SECBUF_CFW_PROT		(0x82002030)
#define SMC_DRM_SECBUF_CFW_UNPROT	(0x82002031)
#define SMC_DRM_DPU_CRC_SEC		(0x82002070)
#define SMC_DRM_PPMP_PROT		(0x82002110)
#define SMC_DRM_PPMP_UNPROT		(0x82002111)
#define SMC_DRM_PPMP_MFCFW_PROT		(0x82002112)
#define SMC_DRM_PPMP_MFCFW_UNPROT	(0x82002113)
#define SMC_DRM_G3D_PPCFW_RESTORE	(0x8200211C)
#define SMC_DRM_G3D_PPCFW_OFF		(0x8200211D)
#define MC_FC_SET_CFW_PROT		(0x82002040)
#define SMC_DRM_SEC_SMMU_INFO		(0x820020D0)
#define MC_FC_DRM_SET_CFW_PROT		(0x10000000)
#define SMC_SRPMB_WSM			(0x82003811)

/* Deprecated */
#define SMC_DRM_MAKE_PGTABLE		(0x81000003)
#define SMC_DRM_CLEAR_PGTABLE		(0x81000004)
#define SMC_MEM_PROT_SET		(0x81000005)
#define SMC_DRM_SECMEM_INFO		(0x81000006)
#define SMC_DRM_VIDEO_PROC		(0x81000007)

/* Parameter for smc */
#define SMC_PROTECTION_ENABLE		(1)
#define SMC_PROTECTION_DISABLE		(0)

/* For DTRNG Access */
#define SMC_CMD_RANDOM			(0x82001012)

/* For Secure log information */
#define SMC_CMD_SEC_LOG_INFO		(0x82000610)

/* For EL3 debug cmd */
#define SIP_SVD_GS_DEBUG_CMD		(0x82000612)

/* Debug commands */
#define CMD_ASSERT			0x0
#define CMD_PANIC			0x1
#define CMD_ECC				0xecc

/* For PPMPU fail information */
#define SMC_CMD_GET_PPMPU_FAIL_INFO	(0x8200211A)
#define SMC_CMD_CHECK_PPMPU_CH_NUM	(0x8200211B)

/* For MMCache flush */
#define SMC_CMD_MM_CACHE_OPERATION	(0x82000720)

/* MACRO for SMC_CMD_REG */
#define SMC_REG_CLASS_CP15		(0x0 << 30)
#define SMC_REG_CLASS_SFR_W		(0x1 << 30)
#define SMC_REG_CLASS_SFR_R		(0x3 << 30)
#define SMC_REG_CLASS_MASK		(0x3 << 30)
#define SMC_REG_ID_SFR_W(ADDR)		(SMC_REG_CLASS_SFR_W | ((ADDR) >> 2))
#define SMC_REG_ID_SFR_R(ADDR)		(SMC_REG_CLASS_SFR_R | ((ADDR) >> 2))

/* op type for SMC_CMD_SAVE and SMC_CMD_SHUTDOWN */
#define OP_TYPE_CORE			(0x0)
#define OP_TYPE_CLUSTER			(0x1)

/* Power State required for SMC_CMD_SAVE and SMC_CMD_SHUTDOWN */
#define SMC_POWERSTATE_SLEEP		(0x0)
#define SMC_POWERSTATE_IDLE		(0x1)
#define SMC_POWERSTATE_SWITCH		(0x2)

/*
 * For SMC CMD for SRPMB
 */
#define SMC_SRPMB_WSM			(0x82003811)

/* For DTRNG Access */
#define HWRNG_INIT			(0x0)
#define HWRNG_EXIT			(0x1)
#define HWRNG_GET_DATA			(0x2)
#define HWRNG_RESUME			(0x3)

/* For CFW group */
#define CFW_DISP_RW			(3)
#define CFW_VPP0			(5)
#define CFW_VPP1			(6)

#define SMC_TZPC_OK			(2)

#define PROT_MFC			(0)
#define PROT_MSCL0			(1)
#define PROT_MSCL1			(2)

#define PROT_L0				(3)
#define PROT_L1				(4)
#define PROT_L2				(5)
#ifdef CONFIG_SOC_ZUMA
#define PROT_L3				(6)
#define PROT_L4				(7)
#define PROT_L5				(8)
#define PROT_L6				(9)

#define PROT_L8				(25)
#define PROT_L9				(26)
#define PROT_L10			(27)
#define PROT_L11			(28)
#define PROT_L12			(29)
#define PROT_L13			(30)
#define PROT_L14			(31)
#else
#define PROT_L4				(6)
#define PROT_L3				(9)
#define PROT_L5				(10)
#define PROT_L12			(11)
#endif

#define PROT_G3D			(12)
#define PROT_JPEG			(13)
#define PROT_G2D			(14)
#define PROT_MFC1			(23)

#ifndef __ASSEMBLY__
/* secure SysMMU SFR access */
enum sec_sysmmu_sfr_access_t {
	SEC_SMMU_SFR_READ,
	SEC_SMMU_SFR_WRITE,
};

/* Return value from DRM LDFW */
enum drmdrv_result_t {
	DRMDRV_OK				= 0x0000,

	/* Error lists for common driver */
	E_DRMDRV_INVALID			= 0x1001,
	E_DRMDRV_INVALID_ADDR_ALIGN		= 0x1002,
	E_DRMDRV_INVALID_SIZE_ALIGN		= 0x1003,
	E_DRMDRV_INVALID_MEMCPY_LENGTH		= 0x1004,
	E_DRMDRV_ADDR_OUT_OF_DRAM		= 0x1005,
	E_DRMDRV_ADDR_OUT_OF_SECMEM		= 0x1006,
	E_DRMDRV_INVALID_ADDR			= 0x1007,
	E_DRMDRV_INVALID_SIZE			= 0x1008,
	E_DRMDRV_INVALID_CMD			= 0x1009,
	E_DRMDRV_ADDR_OVERFLOWED		= 0x100A,
	E_DRMDRV_ADDR_OVERLAP_SECOS		= 0x100B,

	/* Error lists for TZASC driver */
	E_DRMDRV_TZASC_ALIGN_CHECK		= 0x2001,
	E_DRMDRV_TZASC_CONTIG_CHECK		= 0x2002,
	E_DRMDRV_TZASC_GET_ORDER		= 0x2003,
	E_DRMDRV_TZASC_INVALID_INDEX		= 0x2004,
	E_DRMDRV_TZASC_INVALID_ENABLED		= 0x2005,
	E_DRMDRV_TZASC_NOT_PROTECTED		= 0x2006,

	/* Erorr lists for media driver */
	E_DRMDRV_MEDIA_CHECK_POWER		= 0x3001,
	E_DRMDRV_MEDIA_CHECK_CLOCK		= 0x3002,
	E_DRMDRV_MEDIA_CHECK_SMMU_CLOCK		= 0x3003,
	E_DRMDRV_MEDIA_CHECK_SMMU_ENABLED	= 0x3004,
	E_DRMDRV_WB_CHECK_FAILED		= 0x3005,
	E_DRMDRV_HDMI_WITH_NO_HDCP_FAILED	= 0x3006,
	E_DRMDRV_MSCL_LOCAL_PATH_FAILED		= 0x3007,
	E_DRMDRV_HDMI_POWER_OFF			= 0x3008,
	E_DRMDRV_HDMI_CLOCK_OFF			= 0x3009,
	E_DRMDRV_INVALID_REFCOUNT		= 0x300A,

	/* Error lists for g2d driver */
	E_DRMDRV_G2D_INVALID_PARAM		= 0x4001,
	E_DRMDRV_G2D_BLIT_TIMEOUT		= 0x4002,

	/* Error lists for RTC driver */
	E_DRMDRV_GET_RTC_TIME			= 0x5001,
	E_DRMDRV_SET_RTC_TIME			= 0x5002,
	E_DRMDRV_GET_RTC_TICK_TIME		= 0x5003,
	E_DRMDRV_SET_RTC_TICK_TIME		= 0x5004,

	/* Error lists for CFW driver */
	E_DRMDRV_CFW_ERROR			= 0x6001,
	E_DRMDRV_CFW_BUFFER_LIST_FULL		= 0x6002,
	E_DRMDRV_CFW_NOT_PROTECTED_BUFFER	= 0x6003,
	E_DRMDRV_CFW_INVALID_DEV_ARG		= 0x6004,
	E_DRMDRV_CFW_INIT_FAIL			= 0x6005,
	E_DRMDRV_CFW_PROT_FAIL			= 0x6006,
	E_DRMDRV_CFW_ENABLED_ALREADY		= 0x6007,
	E_DRMDRV_CFW_NOT_EXIST_IN_CFW_BUFF_LIST	= 0x6008,
	E_DRMDRV_CFW_DUPLICATED_BUFFER		= 0x6009,
	E_DRMDRV_CFW_BUFFER_IS_OVERLAPPED	= 0x600A,

	/* Error lists for Secure Buffer */
	E_DRMDRV_DUPLICATED_BUFFER		= 0x7001,
	E_DRMDRV_BUFFER_LIST_FULL		= 0x7002,
	E_DRMDRV_NOT_EXIST_IN_SEC_BUFFER_LIST	= 0x7003,
	E_DRMDRV_OVERLAP_RESERVED_ASP_REGION	= 0x7004,
	E_DRMDRV_INVALID_BUFFER_TYPE		= 0x7005,

	/* Error lists for MFC FW */
	E_DRMDRV_MFC_FW_IS_NOT_PROTECTED	= 0x8001,
	E_DRMDRV_MFC_FW_ARG_IS_NULL		= 0x8002,
	E_DRMDRV_MFC_FW_INVALID_SIZE		= 0x8003,
};

static inline unsigned long exynos_smc(unsigned long cmd,
				       unsigned long arg0,
				       unsigned long arg1,
				       unsigned long arg2)
{
	struct arm_smccc_res res;

	arm_smccc_smc(cmd, arg0, arg1, arg2, 0, 0, 0, 0, &res);
	return (unsigned long)res.a0;
}

static inline unsigned long exynos_smc4(unsigned long cmd,
					unsigned long arg0,
					unsigned long arg1,
					unsigned long arg2,
					unsigned long *ret1,
					unsigned long *ret2,
					unsigned long *ret3)
{
	struct arm_smccc_res res;

	arm_smccc_smc(cmd, arg0, arg1, arg2, 0, 0, 0, 0, &res);
	if (ret1)
		*ret1 = (unsigned long)res.a1;
	if (ret2)
		*ret2 = (unsigned long)res.a2;
	if (ret3)
		*ret3 = (unsigned long)res.a3;
	return (unsigned long)res.a0;
}

static inline unsigned long exynos_smc_readsfr(unsigned long addr,
					       unsigned long *val)
{
	struct arm_smccc_res res;

	arm_smccc_smc(SMC_CMD_REG, addr, 0, 0, 0, 0, 0, 0, &res);
	if (res.a0 == 0)
		*val = (unsigned long)res.a2;
	return (unsigned long)res.a0;
}
#endif

#endif	/* __EXYNOS_SMC_H__ */
