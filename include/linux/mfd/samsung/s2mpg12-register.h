/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * s2mpg12-register.h
 *
 * Copyright (C) 2015 Samsung Electronics
 *
 * header file including register information of s2mpg12
 */

#ifndef __LINUX_MFD_S2MPG12_REGISTER_H
#define __LINUX_MFD_S2MPG12_REGISTER_H

#include <linux/i2c.h>
#include "s2mpg1x-register.h"

#define S2MPG12_REG_INVALID	(0xFF)

enum S2MPG12_pmic_rev {
	S2MPG12_EVT0,
	S2MPG12_EVT1,
};

/* Common(0x0) Registers */
enum S2MPG12_COMMON_REG {
	S2MPG12_COMMON_VGPIO0 = 0x0,
	S2MPG12_COMMON_VGPIO1 = 0x1,
	S2MPG12_COMMON_VGPIO2 = 0x2,
	S2MPG12_COMMON_VGPIO3 = 0x3,
	S2MPG12_COMMON_I3C_DAA = 0x4,
	S2MPG12_COMMON_IBI0 = 0x5,
	S2MPG12_COMMON_IBI1 = 0x6,
	S2MPG12_COMMON_IBI2 = 0x7,
	S2MPG12_COMMON_IBI3 = 0x8,
	S2MPG12_COMMON_CHIPID = 0xB,
	S2MPG12_COMMON_I3C_CFG1 = 0xC,
	S2MPG12_COMMON_I3C_CFG2 = 0xD,
	S2MPG12_COMMON_I3C_STA = 0xE,
	S2MPG12_COMMON_IBIM1 = 0xF,
	S2MPG12_COMMON_IBIM2 = 0x10,
};

/* PM(0x1) Registers */
enum S2MPG12_PM_REG {
	S2MPG12_PM_INT1 = 0x0,
	S2MPG12_PM_INT2 = 0x1,
	S2MPG12_PM_INT3 = 0x2,
	S2MPG12_PM_INT4 = 0x3,
	S2MPG12_PM_INT5 = 0x4,
	S2MPG12_PM_INT1M = 0x5,
	S2MPG12_PM_INT2M = 0x6,
	S2MPG12_PM_INT3M = 0x7,
	S2MPG12_PM_INT4M = 0x8,
	S2MPG12_PM_INT5M = 0x9,
	S2MPG12_PM_STATUS1 = 0xA,
	S2MPG12_PM_STATUS2 = 0xB,
	S2MPG12_PM_PWRONSRC = 0xC,
	S2MPG12_PM_OFFSRC1 = 0xD,
	S2MPG12_PM_OFFSRC2 = 0xE,
	S2MPG12_PM_BUCHG = 0xF,
	S2MPG12_PM_RTCBUF = 0x10,
	S2MPG12_PM_CTRL1 = 0x11,
	S2MPG12_PM_CTRL2 = 0x12,
	S2MPG12_PM_CTRL3 = 0x13,
	S2MPG12_PM_CTRL4 = 0x14,
	S2MPG12_PM_CTRL5 = 0x15,
	S2MPG12_PM_SMPL_WARN_CTRL = 0x16,
	S2MPG12_PM_B1M_CTRL = 0x17,
	S2MPG12_PM_B1M_OUT1 = 0x18,
	S2MPG12_PM_B2M_CTRL = 0x19,
	S2MPG12_PM_B2M_OUT1 = 0x1A,
	S2MPG12_PM_B3M_CTRL = 0x1B,
	S2MPG12_PM_B3M_OUT1 = 0x1C,
	S2MPG12_PM_B4M_CTRL = 0x1D,
	S2MPG12_PM_B4M_OUT1 = 0x1E,
	S2MPG12_PM_B5M_CTRL = 0x1F,
	S2MPG12_PM_B5M_OUT1 = 0x20,
	S2MPG12_PM_B6M_CTRL = 0x21,
	S2MPG12_PM_B6M_OUT1 = 0x22,
	S2MPG12_PM_B7M_CTRL = 0x23,
	S2MPG12_PM_B7M_OUT1 = 0x24,
	S2MPG12_PM_B8M_CTRL = 0x25,
	S2MPG12_PM_B8M_OUT1 = 0x26,
	S2MPG12_PM_B9M_CTRL = 0x27,
	S2MPG12_PM_B9M_OUT1 = 0x28,
	S2MPG12_PM_B10M_CTRL = 0x29,
	S2MPG12_PM_B10M_OUT1 = 0x2A,
	S2MPG12_PM_L1M_CTRL = 0x2B,
	S2MPG12_PM_L2M_CTRL = 0x2C,
	S2MPG12_PM_L3M_CTRL = 0x2D,
	S2MPG12_PM_L3M_CTRL2 = 0x2E,
	S2MPG12_PM_L4M_CTRL = 0x2F,
	S2MPG12_PM_L5M_CTRL = 0x30,
	S2MPG12_PM_L6M_CTRL = 0x31,
	S2MPG12_PM_L7M_CTRL = 0x32,
	S2MPG12_PM_L8M_CTRL = 0x33,
	S2MPG12_PM_L9M_CTRL = 0x34,
	S2MPG12_PM_L10M_CTRL = 0x35,
	S2MPG12_PM_L11M_CTRL1 = 0x36,
	S2MPG12_PM_L12M_CTRL1 = 0x37,
	S2MPG12_PM_L13M_CTRL1 = 0x38,
	S2MPG12_PM_L14M_CTRL = 0x39,
	S2MPG12_PM_L15M_CTRL1 = 0x3A,
	S2MPG12_PM_L16M_CTRL = 0x3B,
	S2MPG12_PM_L17M_CTRL = 0x3C,
	S2MPG12_PM_L18M_CTRL = 0x3D,
	S2MPG12_PM_L19M_CTRL = 0x3E,
	S2MPG12_PM_L20M_CTRL = 0x3F,
	S2MPG12_PM_L21M_CTRL = 0x40,
	S2MPG12_PM_L22M_CTRL = 0x41,
	S2MPG12_PM_L23M_CTRL = 0x42,
	S2MPG12_PM_L24M_CTRL = 0x43,
	S2MPG12_PM_L25M_CTRL = 0x44,
	S2MPG12_PM_L26M_CTRL = 0x45,
	S2MPG12_PM_L27M_CTRL = 0x46,
	S2MPG12_PM_L28M_CTRL = 0x47,
	S2MPG12_PM_LDO_CTRL1 = 0x48,
	S2MPG12_PM_LDO_CTRL2 = 0x49,
	S2MPG12_PM_LDO_CTRL3 = 0x4A,
	S2MPG12_PM_LDO_DSCH1 = 0x4B,
	S2MPG12_PM_LDO_DSCH2 = 0x4C,
	S2MPG12_PM_LDO_DSCH3 = 0x4D,
	S2MPG12_PM_LDO_DSCH4 = 0x4E,
	S2MPG12_PM_B7M_HLIMIT = 0x4F,
	S2MPG12_PM_B7M_LLIMIT = 0x50,
	S2MPG12_PM_L21M_HLIMIT = 0x51,
	S2MPG12_PM_L21M_LLIMIT = 0x52,
	S2MPG12_PM_DVS_RAMP1 = 0x53,
	S2MPG12_PM_DVS_RAMP2 = 0x54,
	S2MPG12_PM_DVS_RAMP3 = 0x55,
	S2MPG12_PM_DVS_RAMP4 = 0x56,
	S2MPG12_PM_DVS_RAMP5 = 0x57,
	S2MPG12_PM_DVS_RAMP6 = 0x58,
	S2MPG12_PM_DVS_RAMP7 = 0x59,
	S2MPG12_PM_DVS_RAMP8 = 0x5A,
	S2MPG12_PM_DVS_SYNC_CTRL1 = 0x5B,
	S2MPG12_PM_DVS_SYNC_CTRL2 = 0x5C,
	S2MPG12_PM_DVS_SYNC_CTRL3 = 0x5D,
	S2MPG12_PM_DVS_SYNC_CTRL4 = 0x5E,
	S2MPG12_PM_DVS_SYNC_CTRL5 = 0x5F,
	S2MPG12_PM_DVS_SYNC_CTRL6 = 0x60,
	S2MPG12_PM_DVS_OPTION1 = 0x61,
	S2MPG12_PM_OFF_CTRL1 = 0x62,
	S2MPG12_PM_OFF_CTRL2 = 0x63,
	S2MPG12_PM_OFF_CTRL3 = 0x64,
	S2MPG12_PM_OFF_CTRL4 = 0x65,
	S2MPG12_PM_OFF_CTRL5 = 0x66,
	S2MPG12_PM_OFF_CTRL6 = 0x67,
	S2MPG12_PM_OFF_CTRL7 = 0x68,
    /* ONSEQ1 ~ ONSEQ33 (0x69 ~ 0x89) */
    /* OFFSEQ1 ~ OFFSEQ17 (0x8A ~ 0x9A) */
	S2MPG12_PM_PCTRLSEL1 = 0X9B,
	S2MPG12_PM_PCTRLSEL2 = 0X9C,
	S2MPG12_PM_PCTRLSEL3 = 0X9D,
	S2MPG12_PM_PCTRLSEL4 = 0X9E,
	S2MPG12_PM_PCTRLSEL5 = 0X9F,
	S2MPG12_PM_PCTRLSEL6 = 0XA0,
	S2MPG12_PM_PCTRLSEL7 = 0XA1,
	S2MPG12_PM_PCTRLSEL8 = 0XA2,
	S2MPG12_PM_PCTRLSEL9 = 0XA3,
	S2MPG12_PM_PCTRLSEL10 = 0XA4,
	S2MPG12_PM_PCTRLSEL11 = 0XA5,
	S2MPG12_PM_PCTRLSEL12 = 0XA6,
	S2MPG12_PM_PCTRLSEL13 = 0XA7,
	S2MPG12_PM_PCTRLSEL14 = 0XA8,
	S2MPG12_PM_DCTRLSEL1 = 0xA9,
	S2MPG12_PM_DCTRLSEL2 = 0xAA,
	S2MPG12_PM_DCTRLSEL3 = 0xAB,
	S2MPG12_PM_DCTRLSEL4 = 0xAC,
	S2MPG12_PM_DCTRLSEL5 = 0xAD,
	S2MPG12_PM_DCTRLSEL6 = 0xAE,
	S2MPG12_PM_DCTRLSEL7 = 0xAF,
	S2MPG12_PM_DCTRLSEL8 = 0xB0,
	S2MPG12_PM_DCTRLSEL9 = 0xB1,
	S2MPG12_PM_BUCK_OCP_EN1 = 0xB2,
	S2MPG12_PM_BUCK_OCP_EN2 = 0xB3,
	S2MPG12_PM_BUCK_OCP_PD_EN1 = 0xB4,
	S2MPG12_PM_BUCK_OCP_PD_EN2 = 0xB5,
	S2MPG12_PM_BUCK_OCP_CTRL1 = 0xB6,
	S2MPG12_PM_BUCK_OCP_CTRL2 = 0xB7,
	S2MPG12_PM_BUCK_OCP_CTRL3 = 0xB8,
	S2MPG12_PM_BUCK_OCP_CTRL4 = 0xB9,
	S2MPG12_PM_BUCK_OCP_CTRL5 = 0xBA,
	S2MPG12_PM_PSI_CTRL1 = 0xBB,
	S2MPG12_PM_PSI_CTRL2 = 0xBC,
	S2MPG12_PM_PSI_CTRL3 = 0xBD,
	S2MPG12_PM_PSI_CTRL4 = 0xBE,
	S2MPG12_PM_SEL_HW_VGPIO = 0xBF,
	S2MPG12_PM_B2M_OCP_WARN = 0xC3,
	S2MPG12_PM_B3M_OCP_WARN = 0xC4,
	S2MPG12_PM_B10M_OCP_WARN = 0xC5,
	S2MPG12_PM_B2M_SOFT_OCP_WARN = 0xC6,
	S2MPG12_PM_B3M_SOFT_OCP_WARN = 0xC7,
	S2MPG12_PM_B10M_SOFT_OCP_WARN = 0xC8,
	S2MPG12_PM_B1M_OUT2 = 0xC9,
	S2MPG12_PM_B2M_OUT2 = 0xCA,
	S2MPG12_PM_B3M_OUT2 = 0xCB,
	S2MPG12_PM_B4M_OUT2 = 0xCC,
	S2MPG12_PM_B5M_OUT2 = 0xCD,
	S2MPG12_PM_B6M_OUT2 = 0xCE,
	S2MPG12_PM_B7M_OUT2 = 0xCF,
	S2MPG12_PM_B8M_OUT2 = 0xD0,
	S2MPG12_PM_B9M_OUT2 = 0xD1,
	S2MPG12_PM_B10M_OUT2 = 0xD2,
	S2MPG12_PM_L11M_CTRL2 = 0xD3,
	S2MPG12_PM_L12M_CTRL2 = 0xD4,
	S2MPG12_PM_L13M_CTRL2 = 0xD5,
	S2MPG12_PM_L15M_CTRL2 = 0xD6,
	S2MPG12_PM_L17M_CTRL2 = 0xD7,
	S2MPG12_PM_L19M_CTRL2 = 0xD8,
	S2MPG12_PM_L22M_CTRL2 = 0xD9,
	S2MPG12_PM_BUCK_HRMODE1 = 0xDA,
	S2MPG12_PM_BUCK_HRMODE2 = 0xDB,
	S2MPG12_PM_LDO_SENSE1 = 0xDC,
	S2MPG12_PM_LDO_SENSE2 = 0xDD,
	S2MPG12_PM_LDO_SENSE3 = 0xDE,
	S2MPG12_PM_LDO_SENSE4 = 0xDF,
	S2MPG12_PM_B1M_USONIC = 0xE0,
	S2MPG12_PM_B2M_USONIC = 0xE1,
	S2MPG12_PM_B3M_USONIC = 0xE2,
	S2MPG12_PM_B4M_USONIC = 0xE3,
	S2MPG12_PM_B5M_USONIC = 0xE4,
	S2MPG12_PM_B6M_USONIC = 0xE5,
	S2MPG12_PM_B7M_USONIC = 0xE6,
	S2MPG12_PM_B8M_USONIC = 0xE7,
	S2MPG12_PM_B9M_USONIC = 0xE8,
	S2MPG12_PM_B10M_USONIC = 0xE9,
	S2MPG12_PM_FAULTOUT_CTRL = 0xEA,
	S2MPG12_PM_INT_REG_SEL = 0xEB,
	S2MPG12_PM_SW_RESET = 0xEC,
};

/* Meter(0xA) Registers */
enum S2MPG12_METER_REG {
	S2MPG12_METER_INT1 = 0x0,
	S2MPG12_METER_INT2 = 0x1,
	S2MPG12_METER_INT1M = 0x4,
	S2MPG12_METER_INT2M = 0x5,
	S2MPG12_METER_CTRL1 = 0x8,
	S2MPG12_METER_CTRL2 = 0x9,
	S2MPG12_METER_CTRL4 = 0xB,
	S2MPG12_METER_CTRL5 = 0xC,
	S2MPG12_METER_CTRL6 = 0xD,
	S2MPG12_METER_CTRL7 = 0xE,
	S2MPG12_METER_BUCKEN1 = 0xF,
	S2MPG12_METER_BUCKEN2 = 0x10,
	S2MPG12_METER_MUXSEL0 = 0x11,
	S2MPG12_METER_MUXSEL1 = 0x12,
	S2MPG12_METER_MUXSEL2 = 0x13,
	S2MPG12_METER_MUXSEL3 = 0x14,
	S2MPG12_METER_MUXSEL4 = 0x15,
	S2MPG12_METER_MUXSEL5 = 0x16,
	S2MPG12_METER_MUXSEL6 = 0x17,
	S2MPG12_METER_MUXSEL7 = 0x18,
	S2MPG12_METER_MUXSEL8 = 0x19,
	S2MPG12_METER_MUXSEL9 = 0x1A,
	S2MPG12_METER_MUXSEL10 = 0x1B,
	S2MPG12_METER_MUXSEL11 = 0x1C,
	S2MPG12_METER_LPF_C0_0 = 0x1D,
	S2MPG12_METER_LPF_C0_1 = 0x1E,
	S2MPG12_METER_LPF_C0_2 = 0x1F,
	S2MPG12_METER_LPF_C0_3 = 0x20,
	S2MPG12_METER_LPF_C0_4 = 0x21,
	S2MPG12_METER_LPF_C0_5 = 0x22,
	S2MPG12_METER_LPF_C0_6 = 0x23,
	S2MPG12_METER_LPF_C0_7 = 0x24,
	S2MPG12_METER_LPF_C0_8 = 0x25,
	S2MPG12_METER_LPF_C0_9 = 0x26,
	S2MPG12_METER_LPF_C0_10 = 0x27,
	S2MPG12_METER_LPF_C0_11 = 0x28,
	S2MPG12_METER_PWR_WARN0 = 0x31,
	S2MPG12_METER_PWR_WARN1 = 0x32,
	S2MPG12_METER_PWR_WARN2 = 0x33,
	S2MPG12_METER_PWR_WARN3 = 0x34,
	S2MPG12_METER_PWR_WARN4 = 0x35,
	S2MPG12_METER_PWR_WARN5 = 0x36,
	S2MPG12_METER_PWR_WARN6 = 0x37,
	S2MPG12_METER_PWR_WARN7 = 0x38,
	S2MPG12_METER_PWR_WARN8 = 0x39,
	S2MPG12_METER_PWR_WARN9 = 0x3A,
	S2MPG12_METER_PWR_WARN10 = 0x3B,
	S2MPG12_METER_PWR_WARN11 = 0x3C,
	S2MPG12_METER_PWR_HYS1 = 0x55,
	S2MPG12_METER_PWR_HYS2 = 0x56,
	S2MPG12_METER_PWR_HYS3 = 0x57,
	S2MPG12_METER_PWR_HYS4 = 0x58,
	S2MPG12_METER_PWR_HYS5 = 0x59,
	S2MPG12_METER_PWR_HYS6 = 0x5A,
	S2MPG12_METER_ACC_DATA_CH0_1 = 0x63,
	S2MPG12_METER_ACC_DATA_CH0_2 = 0x64,
	S2MPG12_METER_ACC_DATA_CH0_3 = 0x65,
	S2MPG12_METER_ACC_DATA_CH0_4 = 0x66,
	S2MPG12_METER_ACC_DATA_CH0_5 = 0x67,
	S2MPG12_METER_ACC_DATA_CH0_6 = 0x68,
	S2MPG12_METER_ACC_DATA_CH1_1 = 0x69,
	S2MPG12_METER_ACC_DATA_CH1_2 = 0x6A,
	S2MPG12_METER_ACC_DATA_CH1_3 = 0x6B,
	S2MPG12_METER_ACC_DATA_CH1_4 = 0x6C,
	S2MPG12_METER_ACC_DATA_CH1_5 = 0x6D,
	S2MPG12_METER_ACC_DATA_CH1_6 = 0x6E,
	S2MPG12_METER_ACC_DATA_CH2_1 = 0x6F,
	S2MPG12_METER_ACC_DATA_CH2_2 = 0x70,
	S2MPG12_METER_ACC_DATA_CH2_3 = 0x71,
	S2MPG12_METER_ACC_DATA_CH2_4 = 0x72,
	S2MPG12_METER_ACC_DATA_CH2_5 = 0x73,
	S2MPG12_METER_ACC_DATA_CH2_6 = 0x74,
	S2MPG12_METER_ACC_DATA_CH3_1 = 0x75,
	S2MPG12_METER_ACC_DATA_CH3_2 = 0x76,
	S2MPG12_METER_ACC_DATA_CH3_3 = 0x77,
	S2MPG12_METER_ACC_DATA_CH3_4 = 0x78,
	S2MPG12_METER_ACC_DATA_CH3_5 = 0x79,
	S2MPG12_METER_ACC_DATA_CH3_6 = 0x7A,
	S2MPG12_METER_ACC_DATA_CH4_1 = 0x7B,
	S2MPG12_METER_ACC_DATA_CH4_2 = 0x7C,
	S2MPG12_METER_ACC_DATA_CH4_3 = 0x7D,
	S2MPG12_METER_ACC_DATA_CH4_4 = 0x7E,
	S2MPG12_METER_ACC_DATA_CH4_5 = 0x7F,
	S2MPG12_METER_ACC_DATA_CH4_6 = 0x80,
	S2MPG12_METER_ACC_DATA_CH5_1 = 0x81,
	S2MPG12_METER_ACC_DATA_CH5_2 = 0x82,
	S2MPG12_METER_ACC_DATA_CH5_3 = 0x83,
	S2MPG12_METER_ACC_DATA_CH5_4 = 0x84,
	S2MPG12_METER_ACC_DATA_CH5_5 = 0x85,
	S2MPG12_METER_ACC_DATA_CH5_6 = 0x86,
	S2MPG12_METER_ACC_DATA_CH6_1 = 0x87,
	S2MPG12_METER_ACC_DATA_CH6_2 = 0x88,
	S2MPG12_METER_ACC_DATA_CH6_3 = 0x89,
	S2MPG12_METER_ACC_DATA_CH6_4 = 0x8A,
	S2MPG12_METER_ACC_DATA_CH6_5 = 0x8B,
	S2MPG12_METER_ACC_DATA_CH6_6 = 0x8C,
	S2MPG12_METER_ACC_DATA_CH7_1 = 0x8D,
	S2MPG12_METER_ACC_DATA_CH7_2 = 0x8E,
	S2MPG12_METER_ACC_DATA_CH7_3 = 0x8F,
	S2MPG12_METER_ACC_DATA_CH7_4 = 0x90,
	S2MPG12_METER_ACC_DATA_CH7_5 = 0x91,
	S2MPG12_METER_ACC_DATA_CH7_6 = 0x92,
	S2MPG12_METER_ACC_DATA_CH8_1 = 0x93,
	S2MPG12_METER_ACC_DATA_CH8_2 = 0x94,
	S2MPG12_METER_ACC_DATA_CH8_3 = 0x95,
	S2MPG12_METER_ACC_DATA_CH8_4 = 0x96,
	S2MPG12_METER_ACC_DATA_CH8_5 = 0x97,
	S2MPG12_METER_ACC_DATA_CH8_6 = 0x98,
	S2MPG12_METER_ACC_DATA_CH9_1 = 0x99,
	S2MPG12_METER_ACC_DATA_CH9_2 = 0x9A,
	S2MPG12_METER_ACC_DATA_CH9_3 = 0x9B,
	S2MPG12_METER_ACC_DATA_CH9_4 = 0x9C,
	S2MPG12_METER_ACC_DATA_CH9_5 = 0x9D,
	S2MPG12_METER_ACC_DATA_CH9_6 = 0x9E,
	S2MPG12_METER_ACC_DATA_CH10_1 = 0x9F,
	S2MPG12_METER_ACC_DATA_CH10_2 = 0xA0,
	S2MPG12_METER_ACC_DATA_CH10_3 = 0xA1,
	S2MPG12_METER_ACC_DATA_CH10_4 = 0xA2,
	S2MPG12_METER_ACC_DATA_CH10_5 = 0xA3,
	S2MPG12_METER_ACC_DATA_CH10_6 = 0xA4,
	S2MPG12_METER_ACC_DATA_CH11_1 = 0xA5,
	S2MPG12_METER_ACC_DATA_CH11_2 = 0xA6,
	S2MPG12_METER_ACC_DATA_CH11_3 = 0xA7,
	S2MPG12_METER_ACC_DATA_CH11_4 = 0xA8,
	S2MPG12_METER_ACC_DATA_CH11_5 = 0xA9,
	S2MPG12_METER_ACC_DATA_CH11_6 = 0xAA,
	S2MPG12_METER_ACC_COUNT_1 = 0xAB,
	S2MPG12_METER_ACC_COUNT_2 = 0xAC,
	S2MPG12_METER_ACC_COUNT_3 = 0xAD,
	S2MPG12_METER_LPF_DATA_CH0_1 = 0xAE,
	S2MPG12_METER_LPF_DATA_CH0_2 = 0xAF,
	S2MPG12_METER_LPF_DATA_CH0_3 = 0xB0,
	S2MPG12_METER_LPF_DATA_CH1_1 = 0xB1,
	S2MPG12_METER_LPF_DATA_CH1_2 = 0xB2,
	S2MPG12_METER_LPF_DATA_CH1_3 = 0xB3,
	S2MPG12_METER_LPF_DATA_CH2_1 = 0xB4,
	S2MPG12_METER_LPF_DATA_CH2_2 = 0xB5,
	S2MPG12_METER_LPF_DATA_CH2_3 = 0xB6,
	S2MPG12_METER_LPF_DATA_CH3_1 = 0xB7,
	S2MPG12_METER_LPF_DATA_CH3_2 = 0xB8,
	S2MPG12_METER_LPF_DATA_CH3_3 = 0xB9,
	S2MPG12_METER_LPF_DATA_CH4_1 = 0xBA,
	S2MPG12_METER_LPF_DATA_CH4_2 = 0xBB,
	S2MPG12_METER_LPF_DATA_CH4_3 = 0xBC,
	S2MPG12_METER_LPF_DATA_CH5_1 = 0xBD,
	S2MPG12_METER_LPF_DATA_CH5_2 = 0xBE,
	S2MPG12_METER_LPF_DATA_CH5_3 = 0xBF,
	S2MPG12_METER_LPF_DATA_CH6_1 = 0xC0,
	S2MPG12_METER_LPF_DATA_CH6_2 = 0xC1,
	S2MPG12_METER_LPF_DATA_CH6_3 = 0xC2,
	S2MPG12_METER_LPF_DATA_CH7_1 = 0xC3,
	S2MPG12_METER_LPF_DATA_CH7_2 = 0xC4,
	S2MPG12_METER_LPF_DATA_CH7_3 = 0xC5,
	S2MPG12_METER_LPF_DATA_CH8_1 = 0xC6,
	S2MPG12_METER_LPF_DATA_CH8_2 = 0xC7,
	S2MPG12_METER_LPF_DATA_CH8_3 = 0xC8,
	S2MPG12_METER_LPF_DATA_CH9_1 = 0xC9,
	S2MPG12_METER_LPF_DATA_CH9_2 = 0xCA,
	S2MPG12_METER_LPF_DATA_CH9_3 = 0xCB,
	S2MPG12_METER_LPF_DATA_CH10_1 = 0xCC,
	S2MPG12_METER_LPF_DATA_CH10_2 = 0xCD,
	S2MPG12_METER_LPF_DATA_CH10_3 = 0xCE,
	S2MPG12_METER_LPF_DATA_CH11_1 = 0xCF,
	S2MPG12_METER_LPF_DATA_CH11_2 = 0xD0,
	S2MPG12_METER_LPF_DATA_CH11_3 = 0xD1,
	S2MPG12_METER_VBAT_DATA1 = 0xD2,
	S2MPG12_METER_VBAT_DATA2 = 0xD3,
	S2MPG12_METER_EXT_SIGNED_DATA_1 = 0xE4,
	S2MPG12_METER_EXT_SIGNED_DATA_2 = 0xE5,
};

/* gpio(0xC) Registers */
enum S2MPG12_GPIO_REG {
	S2MPG12_GPIO_INT1 = 0x0,
	S2MPG12_GPIO_INT2 = 0x1,
	S2MPG12_GPIO_INT1M = 0x2,
	S2MPG12_GPIO_INT2M = 0x3,
	S2MPG12_GPIO_STATUS = 0x4,
	S2MPG12_GPIO_0_SET = 0x5,
	S2MPG12_GPIO_1_SET = 0x6,
	S2MPG12_GPIO_2_SET = 0x7,
	S2MPG12_GPIO_3_SET = 0x8,
	S2MPG12_GPIO_4_SET = 0x9,
	S2MPG12_GPIO_5_SET = 0xA,
	S2MPG12_GPIO_0_MONSEL = 0xB,
	S2MPG12_GPIO_1_MONSEL = 0xC,
	S2MPG12_GPIO_2_MONSEL = 0xD,
	S2MPG12_GPIO_3_MONSEL = 0xE,
	S2MPG12_GPIO_4_MONSEL = 0xF,
	S2MPG12_GPIO_5_MONSEL = 0x10,
};

/* MT_TRIM(0xE) Registers */
enum S2MPG12_MT_TRIM_REG {
	S2MPG12_MT_TRIM_COMMON = 0x29,
};

/* S2MPG12 regulator ids */
enum S2MPG12_REGULATOR {
	S2MPG12_LDO1,
	S2MPG12_LDO2,
	S2MPG12_LDO3,
	S2MPG12_LDO4,
	S2MPG12_LDO5,
	S2MPG12_LDO6,
	S2MPG12_LDO7,
	S2MPG12_LDO8,
	S2MPG12_LDO9,
	S2MPG12_LDO10,
	S2MPG12_LDO11,
	S2MPG12_LDO12,
	S2MPG12_LDO13,
	S2MPG12_LDO14,
	S2MPG12_LDO15,
	S2MPG12_LDO16,
	S2MPG12_LDO17,
	S2MPG12_LDO18,
	S2MPG12_LDO19,
	S2MPG12_LDO20,
	S2MPG12_LDO21,
	S2MPG12_LDO22,
	S2MPG12_LDO23,
	S2MPG12_LDO24,
	S2MPG12_LDO25,
	S2MPG12_LDO26,
	S2MPG12_LDO27,
	S2MPG12_LDO28,
	S2MPG12_BUCK1,
	S2MPG12_BUCK2,
	S2MPG12_BUCK3,
	S2MPG12_BUCK4,
	S2MPG12_BUCK5,
	S2MPG12_BUCK6,
	S2MPG12_BUCK7,
	S2MPG12_BUCK8,
	S2MPG12_BUCK9,
	S2MPG12_BUCK10,
	S2MPG12_REGULATOR_MAX,
};

enum s2mpg12_irq {
	/* PMIC */
	S2MPG12_IRQ_PWRONF_INT1,
	S2MPG12_IRQ_PWRONR_INT1,
	S2MPG12_IRQ_JIGONBF_INT1,
	S2MPG12_IRQ_JIGONBR_INT1,
	S2MPG12_IRQ_ACOKBF_INT1,
	S2MPG12_IRQ_ACOKBR_INT1,
	S2MPG12_IRQ_PWRON1S_INT1,
	S2MPG12_IRQ_MRB_INT1,

	S2MPG12_IRQ_RTC60S_INT2,
	S2MPG12_IRQ_RTCA1_INT2,
	S2MPG12_IRQ_RTCA0_INT2,
	S2MPG12_IRQ_RTC1S_INT2,
	S2MPG12_IRQ_WTSR_COLDRST_INT2,
	S2MPG12_IRQ_WTSR_INT2,
	S2MPG12_IRQ_WRST_INT2,
	S2MPG12_IRQ_SMPL_INT2,

	S2MPG12_IRQ_120C_INT3,
	S2MPG12_IRQ_140C_INT3,
	S2MPG12_IRQ_TSD_INT3,
	S2MPG12_IRQ_SCL_SOFTRST_INT3,
	S2MPG12_IRQ_WLWP_ACC_INT3,

	S2MPG12_IRQ_OCP_B1M_INT4,
	S2MPG12_IRQ_OCP_B2M_INT4,
	S2MPG12_IRQ_OCP_B3M_INT4,
	S2MPG12_IRQ_OCP_B4M_INT4,
	S2MPG12_IRQ_OCP_B5M_INT4,
	S2MPG12_IRQ_OCP_B6M_INT4,
	S2MPG12_IRQ_OCP_B7M_INT4,
	S2MPG12_IRQ_OCP_B8M_INT4,

	S2MPG12_IRQ_OCP_B9M_INT5,
	S2MPG12_IRQ_OCP_B10M_INT5,
	S2MPG12_IRQ_SMPL_TIMEOUT_INT5,
	S2MPG12_IRQ_WTSR_TIMEOUT_INT5,

	S2MPG12_IRQ_PMETER_OVERF_INT6,
	S2MPG12_IRQ_PWR_WARN_CH0_INT6,
	S2MPG12_IRQ_PWR_WARN_CH1_INT6,
	S2MPG12_IRQ_PWR_WARN_CH2_INT6,
	S2MPG12_IRQ_PWR_WARN_CH3_INT6,
	S2MPG12_IRQ_PWR_WARN_CH4_INT6,
	S2MPG12_IRQ_PWR_WARN_CH5_INT6,

	S2MPG12_IRQ_PWR_WARN_CH6_INT7,
	S2MPG12_IRQ_PWR_WARN_CH7_INT7,
	S2MPG12_IRQ_PWR_WARN_CH8_INT7,
	S2MPG12_IRQ_PWR_WARN_CH9_INT7,
	S2MPG12_IRQ_PWR_WARN_CH10_INT7,
	S2MPG12_IRQ_PWR_WARN_CH11_INT7,

	S2MPG12_IRQ_NR,
};

/* Common(0x0) MASK */
/* S2MPG12_COMMON_IBI0 */
#define S2MPG12_PMIC_M_MASK		BIT(0)
#define S2MPG12_PMIC_S_MASK		BIT(1)

/* S2MPG12_COMMON_IBIM1 */
#define S2MPG12_IRQSRC_MASK		BIT(0)

/* PM(0x1) MASK */
#define S2MPG12_BUCK_MAX		10
#define S2MPG12_LDO_MAX			28
#define S2MPG12_VGPIO_NUM		14
#define S2MPG12_VGPIO_MAX_VAL	(0xFF)

/*
 * _MIN(group) S2MPG12_REG_MIN##group
 * _STEP(group) S2MPG12_REG_STEP##group
 */

/* BUCK 1M~10M ## group: 1 */
#define S2MPG12_REG_MIN1	200000
#define S2MPG12_REG_STEP1	6250
/* LDO 1M,3M,7M,11M~13M,15M,17M,19M,22M ## group: 2 */
#define S2MPG12_REG_MIN2	300000
#define S2MPG12_REG_STEP2	12500
/* LDO 5M,6M,8M,16M,28M ## group: 3 */
#define S2MPG12_REG_MIN3	725000
#define S2MPG12_REG_STEP3	12500
/* LDO 2M,4M,9M,14M,18M,20M,23M,24M,25M ## group: 4 */
#define S2MPG12_REG_MIN4	700000
#define S2MPG12_REG_STEP4	25000
/* LDO 10M,21M,26M,27M ## group: 5 */
#define S2MPG12_REG_MIN5	1800000
#define S2MPG12_REG_STEP5	25000

/* _N_VOLTAGES(num) S2MPG12_REG_N_VOLTAGES_##num */
#define S2MPG12_REG_N_VOLTAGES_64	0x40
#define S2MPG12_REG_N_VOLTAGES_128	0x80
#define S2MPG12_REG_N_VOLTAGES_256	0x100

/* _MASK(num) S2MPG12_REG_ENABLE_MASK##num */
#define S2MPG12_REG_ENABLE_WIDTH		2
#define S2MPG12_REG_ENABLE_MASK_1_0		MASK(S2MPG12_REG_ENABLE_WIDTH, 0)
#define S2MPG12_REG_ENABLE_MASK_3_2		MASK(S2MPG12_REG_ENABLE_WIDTH, 2)
#define S2MPG12_REG_ENABLE_MASK_4_3		MASK(S2MPG12_REG_ENABLE_WIDTH, 3)
#define S2MPG12_REG_ENABLE_MASK_5_4		MASK(S2MPG12_REG_ENABLE_WIDTH, 4)
#define S2MPG12_REG_ENABLE_MASK_7_6		MASK(S2MPG12_REG_ENABLE_WIDTH, 6)
#define S2MPG12_REG_ENABLE_MASK_7		BIT(7)

/* _TIME(macro) S2MPG12_ENABLE_TIME##macro */
#define S2MPG12_ENABLE_TIME_LDO		128
#define S2MPG12_ENABLE_TIME_BUCK	130

/* S2MPG12_PM_DCTRLSEL1 ~ 9 */
#define S2MPG12_DCTRLSEL_VOUT1			0x0
#define S2MPG12_DCTRLSEL_PWREN			0x1
#define S2MPG12_DCTRLSEL_PWREN_TRG		0x2
#define S2MPG12_DCTRLSEL_PWREN_MIF		0x3
#define S2MPG12_DCTRLSEL_PWREN_MIF_TRG		0x4
#define S2MPG12_DCTRLSEL_AP_ACTIVE_N		0x5
#define S2MPG12_DCTRLSEL_AP_ACTIVE_N_TRG	0x6
#define S2MPG12_DCTRLSEL_PWREN_MIF_ACTIVE_N	0x7
#define S2MPG12_DCTRLSEL_AOC_RET		0x8
#define S2MPG12_DCTRLSEL_TPU_EN			0x9

/* VGPIO_RX_MONITOR ADDR. */
#define VGPIO_I3C_BASE			0x18100000
#define VGPIO_MONITOR_ADDR		0x1704

/* VGPIO_PENDING_CLEAR */
#define SYSREG_VGPIO2AP			0x182F0000
#define INTC0_IPEND			0x0290

/* POWER-KEY MASK */
#define S2MPG12_STATUS1_PWRON		BIT(0)
#define S2MPG12_FALLING_EDGE		BIT(1)	/* INT1 reg */
#define S2MPG12_RISING_EDGE		BIT(0)	/* INT1 reg */

/* S2MPG12_PM_SMPL_WARN_CTRL(0x16) */
#define S2MPG12_SMPL_WARN_LBDT_SHIFT	0
#define S2MPG12_SMPL_WARN_HYS_SHIFT		3
#define S2MPG12_SMPL_WARN_LVL_SHIFT		5

/* S2MPG12_PM_OCP_WARN */
#define S2MPG12_OCP_WARN_EN_SHIFT		7
#define S2MPG12_OCP_WARN_CNT_SHIFT		6
#define S2MPG12_OCP_WARN_DVS_MASK_SHIFT	5
#define S2MPG12_OCP_WARN_LVL_SHIFT		0

/* METER(0xA) MASK */
/* S2MPG12_METER_CTRL1 */
#define S2MPG12_METER_EN_MASK		BIT(0)

#endif /* __LINUX_MFD_S2MPG12_REGISTER_H */
