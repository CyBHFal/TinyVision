/*
 * Copyright (C) 2016 Allwinnertech
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Adjustable factor-based clock implementation
 */

#ifndef __MACH_SUNXI_CLK_SUN8IW16_H
#define __MACH_SUNXI_CLK_SUN8IW16_H

#include <linux/clk-provider.h>
#include <linux/clkdev.h>
#include <linux/io.h>

#include "clk-factors.h"
#include "clk-sdm.h"

/* CCMU Register List */
#define PLL_CPU             0x0000
#define PLL_DDR0            0x0010
/*#define PLL_DDR1            0x0018 */
#define PLL_PERIPH0         0x0020
#define PLL_UNI             0x0028
#define PLL_VIDEO0          0x0040
/*
#define PLL_VE              0x0058
#define PLL_DE              0x0060
#define PLL_ISP             0x0068
*/
#define PLL_AUDIO           0x0078
/*
#define PLL_EVE             0x00C0
#define PLL_CVE             0x00C8
#define PLL_ISE             0x00D0
*/
#define PLL_CSI             0x00E0

#define PLL_DDR0PAT         0x0110
#define PLL_DDR1PAT         0x0118
#define PLL_PERI0PAT0       0x0120
#define PLL_PERI0PAT1       0x0124
#define PLL_UNIPAT0         0x0128
#define PLL_UNIPAT1         0x012C
#define PLL_VIDEO0PAT0      0x0140
#define PLL_VIDEO0PAT1      0x0144
/*
#define PLL_VEPAT0          0x0158
#define PLL_VEPAT1          0x015C
#define PLL_DEPAT0          0x0160
#define PLL_DEPAT1          0x0164
#define PLL_ISPPAT0         0x0168
#define PLL_ISPPAT1         0x016C
*/
#define PLL_AUDIOPAT0       0x0178
#define PLL_AUDIOPAT1       0x017C
/*
#define PLL_EVEPAT0         0x01C0
#define PLL_EVEPAT1         0x01C4
#define PLL_CVEPAT0         0x01C8
#define PLL_CVEPAT1         0x01CC
*/
#define PLL_CSIPAT0         0x01E0
#define PLL_CSIPAT1         0x01E4
/*
#define PLL_ISEPAT0         0x01D0
#define PLL_ISEPAT1         0x01D4
*/

#define CPU_CFG             0x0500
#define PSI_CFG             0x0510
#define AHB3_CFG            0x051C
#define APB1_CFG            0x0520
#define APB2_CFG            0x0524
#define MBUS_CFG            0x0540

/* Accelerator */
#define DE_CFG              0x0600
#define DE_GATE             0x060C
/*
#define DI_CFG              0x0620
#define DI_GATE             0x062C
*/
#define G2D_CFG             0x0630
#define G2D_GATE            0x063C
/*
#define EVE_CFG             0x0650
#define EVE_GATE            0x065C
#define CVE_CFG             0x0660
#define CVE_GATE            0x066C
*/
#define CE_CFG              0x0680
#define CE_GATE             0x068C
#define VE_CFG              0x0690
#define VE_GATE             0x069C
/*
#define ISE_CFG             0x06A0
#define ISE_GATE            0x06AC
*/
#define EISE_CFG			0x06D0
#define EISE_GATE			0x06DC
#define NNA_CFG             0x06E0
#define NNA_GATE            0x06EC

/* SYS Resource */
#define DMA_GATE            0x070C
/*
#define MSGBOX_GATE         0x071C
#define SPINLOCK_GATE       0x072C
*/
#define HSTIMER_GATE        0x073C
#define AVS_CFG             0x0740
#define DBGSYS_GATE         0x078C
#define PSI_GATE            0x079C
#define PWM_GATE            0x07AC
#define IOMMU_GATE          0x07BC

/* Storage Medium */
#define DRAM_CFG            0x0800
#define MBUS_GATE           0x0804
#define DRAM_GATE           0x080C
/*
#define NAND0_CFG           0x0810
#define NAND1_CFG           0x0814
#define NAND_GATE           0x082C
*/
#define SMHC0_CFG           0x0830
#define SMHC1_CFG           0x0834
#define SMHC2_CFG           0x0838
#define SMHC_GATE           0x084C

/* Common Interface */
#define UART_GATE           0x090C
#define TWI_GATE            0x091C
#define SPI0_CFG            0x0940
#define SPI1_CFG            0x0944
#define SPI2_CFG            0x0948
#define SPI3_CFG            0x094C
#define SPI_GATE            0x096C
#define EPHY_25M_CFG        0x0970
#define GMAC_GATE           0x097C
#define GPADC_GATE          0x09EC
#define THS_GATE            0x09FC
#define I2S0_CFG            0x0A10
#define I2S1_CFG            0x0A14
/*
#define I2S2_CFG            0x0A18
*/
#define I2S_GATE            0x0A1C
/*
#define DMIC_CFG            0x0A40
#define DMIC_GATE           0x0A4C
*/
#define CODEC_1X_CFG        0x0A50
#define CODEC_4X_CFG        0x0A54
#define CODEC_GATE          0x0A5C
#define USB0_CFG            0x0A70
/*#define USB1_CFG            0x0A74 */
#define USB_GATE            0x0A8C

/* Display Interface */
/*
#define HDMI_CFG            0x0B00
#define HDMI_SLOW_CFG       0x0B04
#define HDMI_CEC_CFG        0x0B10
#define HDMI_GATE           0x0B1C
*/
#define MIPI_DPHY0_CFG      0x0B20
#define MIPI_HOST0_CFG      0x0B24
#define MIPI_GATE           0x0B4C
#define DISPLAY_TOP_GATE    0x0B5C
#define TCON_LCD_CFG        0x0B60
#define TCON_LCD_GATE       0x0B7C
/*
#define TCON_TV_CFG         0x0B80
#define TCON_TV_GATE        0x0B9C
#define LVDS_GATE           0x0BAC
#define TVE_CFG             0x0BB0
#define TVE_GATE            0x0BBC
#define CSI_MISC_CFG        0x0C00
*/
#define CSI_TOP_CFG         0x0C04
#define CSI_MASTER0_CFG     0x0C08
#define CSI_MASTER1_CFG     0x0C0C
#define CSI_MASTER2_CFG     0x0C10
#define CSI_MASTER3_CFG     0x0C14
#define ISP_CFG				0x0C20
#define CSI_GATE            0x0C2C
/*
#define VDPO_CFG            0x0C50
#define VDPO_GATE           0x0C5C
*/
#define DSPO_CFG            0x0C60
#define DSPO_GATE           0x0C6C
#define SUNXI_CLK_MAX_REG   0x0C6C

/* PRCM Register List */
#define CPUS_CFG            0x0000
#define CPUS_APBS1_CFG      0x000C
#define CPUS_APBS2_CFG      0x0010
#define CPUS_TIMER_GATE     0x011C
#define CPUS_PWM_GATE       0x013C
#define CPUS_UART_GATE      0x018C
#define CPUS_TWI_GATE       0x019C
#define CPUS_RSB_GATE       0x01BC
#define CPUS_CIR_CFG        0x01C0
#define CPUS_CIR_GATE       0x01CC
#define CPUS_OWC_CFG        0x01E0
#define CPUS_OWC_GATE       0x01EC
#define CPUS_RTC_GATE       0x020C
#define CPUS_CLK_MAX_REG    0x020C

/* RTC Register List */
#define LOSC_OUT_GATE       0x0060
#define DCXO_OUT_CFG        0x0160

#define F_N8X8_M0X2_P16x2(nv, mv, pv)      (FACTOR_ALL(nv, 8, 8, 0, 0, 0, mv, 0, 2, pv, 16, 2, 0, 0, 0, 0, 0, 0))
#define F_N8X8_D1V1X1_D2V0X1(nv, d1v, d2v) (FACTOR_ALL(nv, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, d1v, 1, 1, d2v, 0, 1))
#define F_N8X8_D1V1X1(nv, d1v)             (FACTOR_ALL(nv, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, d1v, 1, 1, 0, 0, 0))
#define F_N8X8_D1V4X2_D2V0X2(nv, d1v, d2v) (FACTOR_ALL(nv, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, d1v, 4, 2, d2v, 0, 2))
#define F_N8X8_P16X6_D1V1X1_D2V0X1(nv, pv, d1v, d2v) (FACTOR_ALL(nv, 8, 8, 0, 0, 0, 0, 0, 0, pv, 16, 6, d1v, 1, 1, d2v, 0, 1))

#define PLLCPU(n, m, p, freq)        {F_N8X8_M0X2_P16x2(n,  m, p), freq}
#define PLLDDR0(n, d1, d2, freq)     {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLDDR1(n, d1, d2, freq)     {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLPERIPH0(n, d1, d2, freq)  {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLPERIPH1(n, d1, d2, freq)  {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLVIDEO0(n, d1, freq)       {F_N8X8_D1V1X1(n, d1), freq}
#define PLLVE(n, d1, d2, freq)       {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLDE(n, d1, d2, freq)       {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLISP(n, d1, d2, freq)      {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLAUDIO(n, p, d1, d2, freq) {F_N8X8_P16X6_D1V1X1_D2V0X1(n, p, d1, d2), freq}
#define PLLEVE(n, d1, d2, freq)      {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLCVE(n, d1, d2, freq)      {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLISE(n, d1, d2, freq)      {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#define PLLCSI(n, d1, d2, freq)      {F_N8X8_D1V1X1_D2V0X1(n, d1, d2), freq}
#endif
