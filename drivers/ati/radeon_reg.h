/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/ati/radeon_reg.h,v 1.9 2001/05/02 15:06:08 dawes Exp $ */
/*
 * Copyright 2000 ATI Technologies Inc., Markham, Ontario, and
 *                VA Linux Systems Inc., Fremont, California.
 *
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation on the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT.  IN NO EVENT SHALL ATI, VA LINUX SYSTEMS AND/OR
 * THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/*
 * Authors:
 *   Kevin E. Martin <martin@valinux.com>
 *   Rickard E. Faith <faith@valinux.com>
 *   Alan Hourihane <ahourihane@valinux.com>
 *
 * References:
 *
 * !!!! FIXME !!!!
 *   RAGE 128 VR/ RAGE 128 GL Register Reference Manual (Technical
 *   Reference Manual P/N RRG-G04100-C Rev. 0.04), ATI Technologies: April
 *   1999.
 *
 * !!!! FIXME !!!!
 *   RAGE 128 Software Development Manual (Technical Reference Manual P/N
 *   SDK-G04000 Rev. 0.01), ATI Technologies: June 1999.
 *
 */

/* !!!! FIXME !!!!  NOTE: THIS FILE HAS BEEN CONVERTED FROM r128_reg.h
 * AND CONTAINS REGISTERS AND REGISTER DEFINITIONS THAT ARE NOT CORRECT
 * ON THE RADEON.  A FULL AUDIT OF THIS CODE IS NEEDED!  */

#ifndef _RADEON_REG_H_
#define _RADEON_REG_H_




#include "fbdrimain.h"





/* Atomic updates of PLL clock don't seem to always work and stick, thus
 * the bit never resets. Here - we use our own check by reading back the
 * register we've just wrote to make sure it's got the Right! value */
#define RADEON_ATOMIC_UPDATE 0  /* Use PLL Atomic updates (seems broken) */

				/* Memory mapped register access macros */
#define INREG8(addr)        MMIO_IN8(RADEONMMIO, addr)
#define INREG16(addr)       MMIO_IN16(RADEONMMIO, addr)
#define INREG(addr)         MMIO_IN32(RADEONMMIO, addr)
#define OUTREG8(addr, val)  MMIO_OUT8(RADEONMMIO, addr, val)
#define OUTREG16(addr, val) MMIO_OUT16(RADEONMMIO, addr, val)
#define OUTREG(addr, val)   MMIO_OUT32(RADEONMMIO, addr, val)

#define ADDRREG(addr)       ((volatile uint32_t *)(pointer)(RADEONMMIO + (addr)))


#define OUTREGP(addr, val, mask)                                          \
    do {                                                                  \
	uint32_t tmp = INREG(addr);                                         \
	tmp &= (mask);                                                    \
	tmp |= (val);                                                     \
	OUTREG(addr, tmp);                                                \
    } while (0)

#define INPLL(pScrn, addr) RADEONINPLL(pScrn, addr)

#if !RADEON_ATOMIC_UPDATE
#define OUTPLL(addr, val)                                                 \
    do {                                                                  \
	while ( (INREG(RADEON_CLOCK_CNTL_INDEX) & 0x9f) !=                \
					(addr | RADEON_PLL_WR_EN)) {      \
	    OUTREG8(RADEON_CLOCK_CNTL_INDEX, (((addr) & 0x1f) |           \
						RADEON_PLL_WR_EN));       \
	}                                                                 \
	OUTREG(RADEON_CLOCK_CNTL_DATA, val);                              \
    } while (0)
#else
#define OUTPLL(addr, val)                                                 \
    do {                                                                  \
	OUTREG8(RADEON_CLOCK_CNTL_INDEX, (((addr) & 0x1f) |               \
						RADEON_PLL_WR_EN));       \
	OUTREG(RADEON_CLOCK_CNTL_DATA, val);                              \
    } while (0)
#endif

#define OUTPLLP(pScrn, addr, val, mask)                                   \
    do {                                                                  \
	uint32_t tmp = INPLL(pScrn, addr);                                  \
	tmp &= (mask);                                                    \
	tmp |= (val);                                                     \
	OUTPLL(addr, tmp);                                                \
    } while (0)

#define OUTPAL_START(idx)                                                 \
    do {                                                                  \
	OUTREG8(RADEON_PALETTE_INDEX, (idx));                             \
    } while (0)

#define OUTPAL_NEXT(r, g, b)                                              \
    do {                                                                  \
	OUTREG(RADEON_PALETTE_DATA, ((r) << 16) | ((g) << 8) | (b));      \
    } while (0)

#define OUTPAL_NEXT_uint32_t(v)                                             \
    do {                                                                  \
	OUTREG(RADEON_PALETTE_DATA, (v & 0x00ffffff));                    \
    } while (0)

#define OUTPAL(idx, r, g, b)                                              \
    do {                                                                  \
	OUTPAL_START((idx));                                              \
	OUTPAL_NEXT((r), (g), (b));                                       \
    } while (0)

#define INPAL_START(idx)                                                  \
    do {                                                                  \
	OUTREG(RADEON_PALETTE_INDEX, (idx) << 16);                        \
    } while (0)

#define INPAL_NEXT() INREG(RADEON_PALETTE_DATA)

#define PAL_SELECT(idx)                                                   \
    do {                                                                  \
	if (idx) {                                                        \
	    OUTREG(RADEON_DAC_CNTL, INREG(RADEON_DAC_CNTL) |              \
		   RADEON_DAC_PALETTE_ACC_CTL);                           \
	} else {                                                          \
	    OUTREG(RADEON_DAC_CNTL, INREG(RADEON_DAC_CNTL) &              \
		   (uint32_t)~RADEON_DAC_PALETTE_ACC_CTL);                  \
	}                                                                 \
    } while (0)

#define RADEON_ADAPTER_ID                   0x0f2c /* PCI */
#define RADEON_AGP_BASE                     0x0170
#define RADEON_AGP_CNTL                     0x0174
#       define RADEON_AGP_APER_SIZE_256MB   (0x00 << 0)
#       define RADEON_AGP_APER_SIZE_128MB   (0x20 << 0)
#       define RADEON_AGP_APER_SIZE_64MB    (0x30 << 0)
#       define RADEON_AGP_APER_SIZE_32MB    (0x38 << 0)
#       define RADEON_AGP_APER_SIZE_16MB    (0x3c << 0)
#       define RADEON_AGP_APER_SIZE_8MB     (0x3e << 0)
#       define RADEON_AGP_APER_SIZE_4MB     (0x3f << 0)
#       define RADEON_AGP_APER_SIZE_MASK    (0x3f << 0)
#define RADEON_AGP_COMMAND                  0x0f60 /* PCI */
#define RADEON_AGP_PLL_CNTL                 0x000b /* PLL */
#define RADEON_AGP_STATUS                   0x0f5c /* PCI */
#       define RADEON_AGP_1X_MODE           0x01
#       define RADEON_AGP_2X_MODE           0x02
#       define RADEON_AGP_4X_MODE           0x04
#       define RADEON_AGP_MODE_MASK         0x07
#define RADEON_AMCGPIO_A_REG                0x01a0
#define RADEON_AMCGPIO_EN_REG               0x01a8
#define RADEON_AMCGPIO_MASK                 0x0194
#define RADEON_AMCGPIO_Y_REG                0x01a4
#define RADEON_ATTRDR                       0x03c1 /* VGA */
#define RADEON_ATTRDW                       0x03c0 /* VGA */
#define RADEON_ATTRX                        0x03c0 /* VGA */
#define RADEON_AUX_SC_CNTL                  0x1660
#       define RADEON_AUX1_SC_EN            (1 << 0)
#       define RADEON_AUX1_SC_MODE_OR       (0 << 1)
#       define RADEON_AUX1_SC_MODE_NAND     (1 << 1)
#       define RADEON_AUX2_SC_EN            (1 << 2)
#       define RADEON_AUX2_SC_MODE_OR       (0 << 3)
#       define RADEON_AUX2_SC_MODE_NAND     (1 << 3)
#       define RADEON_AUX3_SC_EN            (1 << 4)
#       define RADEON_AUX3_SC_MODE_OR       (0 << 5)
#       define RADEON_AUX3_SC_MODE_NAND     (1 << 5)
#define RADEON_AUX1_SC_BOTTOM               0x1670
#define RADEON_AUX1_SC_LEFT                 0x1664
#define RADEON_AUX1_SC_RIGHT                0x1668
#define RADEON_AUX1_SC_TOP                  0x166c
#define RADEON_AUX2_SC_BOTTOM               0x1680
#define RADEON_AUX2_SC_LEFT                 0x1674
#define RADEON_AUX2_SC_RIGHT                0x1678
#define RADEON_AUX2_SC_TOP                  0x167c
#define RADEON_AUX3_SC_BOTTOM               0x1690
#define RADEON_AUX3_SC_LEFT                 0x1684
#define RADEON_AUX3_SC_RIGHT                0x1688
#define RADEON_AUX3_SC_TOP                  0x168c
#define RADEON_AUX_WINDOW_HORZ_CNTL         0x02d8
#define RADEON_AUX_WINDOW_VERT_CNTL         0x02dc

#define RADEON_BASE_CODE                    0x0f0b
#define RADEON_BIOS_0_SCRATCH               0x0010
#define RADEON_BIOS_1_SCRATCH               0x0014
#define RADEON_BIOS_2_SCRATCH               0x0018
#define RADEON_BIOS_3_SCRATCH               0x001c
#define RADEON_BIOS_ROM                     0x0f30 /* PCI */
#define RADEON_BIST                         0x0f0f /* PCI */
#define RADEON_BRUSH_DATA0                  0x1480
#define RADEON_BRUSH_DATA1                  0x1484
#define RADEON_BRUSH_DATA10                 0x14a8
#define RADEON_BRUSH_DATA11                 0x14ac
#define RADEON_BRUSH_DATA12                 0x14b0
#define RADEON_BRUSH_DATA13                 0x14b4
#define RADEON_BRUSH_DATA14                 0x14b8
#define RADEON_BRUSH_DATA15                 0x14bc
#define RADEON_BRUSH_DATA16                 0x14c0
#define RADEON_BRUSH_DATA17                 0x14c4
#define RADEON_BRUSH_DATA18                 0x14c8
#define RADEON_BRUSH_DATA19                 0x14cc
#define RADEON_BRUSH_DATA2                  0x1488
#define RADEON_BRUSH_DATA20                 0x14d0
#define RADEON_BRUSH_DATA21                 0x14d4
#define RADEON_BRUSH_DATA22                 0x14d8
#define RADEON_BRUSH_DATA23                 0x14dc
#define RADEON_BRUSH_DATA24                 0x14e0
#define RADEON_BRUSH_DATA25                 0x14e4
#define RADEON_BRUSH_DATA26                 0x14e8
#define RADEON_BRUSH_DATA27                 0x14ec
#define RADEON_BRUSH_DATA28                 0x14f0
#define RADEON_BRUSH_DATA29                 0x14f4
#define RADEON_BRUSH_DATA3                  0x148c
#define RADEON_BRUSH_DATA30                 0x14f8
#define RADEON_BRUSH_DATA31                 0x14fc
#define RADEON_BRUSH_DATA32                 0x1500
#define RADEON_BRUSH_DATA33                 0x1504
#define RADEON_BRUSH_DATA34                 0x1508
#define RADEON_BRUSH_DATA35                 0x150c
#define RADEON_BRUSH_DATA36                 0x1510
#define RADEON_BRUSH_DATA37                 0x1514
#define RADEON_BRUSH_DATA38                 0x1518
#define RADEON_BRUSH_DATA39                 0x151c
#define RADEON_BRUSH_DATA4                  0x1490
#define RADEON_BRUSH_DATA40                 0x1520
#define RADEON_BRUSH_DATA41                 0x1524
#define RADEON_BRUSH_DATA42                 0x1528
#define RADEON_BRUSH_DATA43                 0x152c
#define RADEON_BRUSH_DATA44                 0x1530
#define RADEON_BRUSH_DATA45                 0x1534
#define RADEON_BRUSH_DATA46                 0x1538
#define RADEON_BRUSH_DATA47                 0x153c
#define RADEON_BRUSH_DATA48                 0x1540
#define RADEON_BRUSH_DATA49                 0x1544
#define RADEON_BRUSH_DATA5                  0x1494
#define RADEON_BRUSH_DATA50                 0x1548
#define RADEON_BRUSH_DATA51                 0x154c
#define RADEON_BRUSH_DATA52                 0x1550
#define RADEON_BRUSH_DATA53                 0x1554
#define RADEON_BRUSH_DATA54                 0x1558
#define RADEON_BRUSH_DATA55                 0x155c
#define RADEON_BRUSH_DATA56                 0x1560
#define RADEON_BRUSH_DATA57                 0x1564
#define RADEON_BRUSH_DATA58                 0x1568
#define RADEON_BRUSH_DATA59                 0x156c
#define RADEON_BRUSH_DATA6                  0x1498
#define RADEON_BRUSH_DATA60                 0x1570
#define RADEON_BRUSH_DATA61                 0x1574
#define RADEON_BRUSH_DATA62                 0x1578
#define RADEON_BRUSH_DATA63                 0x157c
#define RADEON_BRUSH_DATA7                  0x149c
#define RADEON_BRUSH_DATA8                  0x14a0
#define RADEON_BRUSH_DATA9                  0x14a4
#define RADEON_BRUSH_SCALE                  0x1470
#define RADEON_BRUSH_Y_X                    0x1474
#define RADEON_BUS_CNTL                     0x0030
#       define RADEON_BUS_MASTER_DIS         (1 << 6)
#       define RADEON_BUS_RD_DISCARD_EN      (1 << 24)
#       define RADEON_BUS_RD_ABORT_EN        (1 << 25)
#       define RADEON_BUS_MSTR_DISCONNECT_EN (1 << 28)
#       define RADEON_BUS_WRT_BURST          (1 << 29)
#       define RADEON_BUS_READ_BURST         (1 << 30)
#define RADEON_BUS_CNTL1                    0x0034
#       define RADEON_BUS_WAIT_ON_LOCK_EN    (1 << 4)

#define RADEON_CACHE_CNTL                   0x1724
#define RADEON_CACHE_LINE                   0x0f0c /* PCI */
#define RADEON_CAP0_TRIG_CNTL               0x0950 /* ? */
#define RADEON_CAP1_TRIG_CNTL               0x09c0 /* ? */
#define RADEON_CAPABILITIES_ID              0x0f50 /* PCI */
#define RADEON_CAPABILITIES_PTR             0x0f34 /* PCI */
#define RADEON_CLK_PIN_CNTL                 0x0001 /* PLL */
#define RADEON_CLOCK_CNTL_DATA              0x000c
#define RADEON_CLOCK_CNTL_INDEX             0x0008
#       define RADEON_PLL_WR_EN             (1 << 7)
#       define RADEON_PLL_DIV_SEL           (3 << 8)
#define RADEON_CLR_CMP_CLR_3D               0x1a24
#define RADEON_CLR_CMP_CLR_DST              0x15c8
#define RADEON_CLR_CMP_CLR_SRC              0x15c4
#define RADEON_CLR_CMP_CNTL                 0x15c0
#       define RADEON_SRC_CMP_EQ_COLOR      (4 <<  0)
#       define RADEON_SRC_CMP_NEQ_COLOR     (5 <<  0)
#       define RADEON_CLR_CMP_SRC_SOURCE    (1 << 24)
#define RADEON_CLR_CMP_MASK                 0x15cc
#       define RADEON_CLR_CMP_MSK           0xffffffff
#define RADEON_CLR_CMP_MASK_3D              0x1A28
#define RADEON_COMMAND                      0x0f04 /* PCI */
#define RADEON_COMPOSITE_SHADOW_ID          0x1a0c
#define RADEON_CONFIG_APER_0_BASE           0x0100
#define RADEON_CONFIG_APER_1_BASE           0x0104
#define RADEON_CONFIG_APER_SIZE             0x0108
#define RADEON_CONFIG_BONDS                 0x00e8
#define RADEON_CONFIG_CNTL                  0x00e0
#define RADEON_CONFIG_MEMSIZE               0x00f8
#define RADEON_CONFIG_MEMSIZE_EMBEDDED      0x0114
#define RADEON_CONFIG_REG_1_BASE            0x010c
#define RADEON_CONFIG_REG_APER_SIZE         0x0110
#define RADEON_CONFIG_XSTRAP                0x00e4
#define RADEON_CONSTANT_COLOR_C             0x1d34
#       define RADEON_CONSTANT_COLOR_MASK   0x00ffffff
#       define RADEON_CONSTANT_COLOR_ONE    0x00ffffff
#       define RADEON_CONSTANT_COLOR_ZERO   0x00000000
#define RADEON_CRC_CMDFIFO_ADDR             0x0740
#define RADEON_CRC_CMDFIFO_DOUT             0x0744
#define RADEON_CRTC_CRNT_FRAME              0x0214
#define RADEON_CRTC_DEBUG                   0x021c
#define RADEON_CRTC_EXT_CNTL                0x0054
#       define RADEON_CRTC_VGA_XOVERSCAN    (1 <<  0)
#       define RADEON_VGA_ATI_LINEAR        (1 <<  3)
#       define RADEON_XCRT_CNT_EN           (1 <<  6)
#       define RADEON_CRTC_HSYNC_DIS        (1 <<  8)
#       define RADEON_CRTC_VSYNC_DIS        (1 <<  9)
#       define RADEON_CRTC_DISPLAY_DIS      (1 << 10)
#       define RADEON_CRTC_CRT_ON           (1 << 15)
#define RADEON_CRTC_EXT_CNTL_DPMS_BYTE      0x0055
#       define RADEON_CRTC_HSYNC_DIS_BYTE   (1 <<  0)
#       define RADEON_CRTC_VSYNC_DIS_BYTE   (1 <<  1)
#       define RADEON_CRTC_DISPLAY_DIS_BYTE (1 <<  2)
#define RADEON_CRTC_GEN_CNTL                0x0050
#       define RADEON_CRTC_DBL_SCAN_EN      (1 <<  0)
#       define RADEON_CRTC_INTERLACE_EN     (1 <<  1)
#       define RADEON_CRTC_CSYNC_EN         (1 <<  4)
#       define RADEON_CRTC_CUR_EN           (1 << 16)
#       define RADEON_CRTC_CUR_MODE_MASK    (7 << 17)
#       define RADEON_CRTC_ICON_EN          (1 << 20)
#       define RADEON_CRTC_EXT_DISP_EN      (1 << 24)
#       define RADEON_CRTC_EN               (1 << 25)
#       define RADEON_CRTC_DISP_REQ_EN_B    (1 << 26)
#define RADEON_CRTC_GUI_TRIG_VLINE          0x0218
#define RADEON_CRTC_H_SYNC_STRT_WID         0x0204
#       define RADEON_CRTC_H_SYNC_STRT_PIX        (0x07  <<  0)
#       define RADEON_CRTC_H_SYNC_STRT_CHAR       (0x1ff <<  3)
#       define RADEON_CRTC_H_SYNC_STRT_CHAR_SHIFT 3
#       define RADEON_CRTC_H_SYNC_WID             (0x3f  << 16)
#       define RADEON_CRTC_H_SYNC_WID_SHIFT       16
#       define RADEON_CRTC_H_SYNC_POL             (1     << 23)
#define RADEON_CRTC_H_TOTAL_DISP            0x0200
#       define RADEON_CRTC_H_TOTAL          (0x01ff << 0)
#       define RADEON_CRTC_H_TOTAL_SHIFT    0
#       define RADEON_CRTC_H_DISP           (0x00ff << 16)
#       define RADEON_CRTC_H_DISP_SHIFT     16
#define RADEON_CRTC_OFFSET                  0x0224
#define RADEON_CRTC_OFFSET_CNTL             0x0228
#	define RADEON_CRTC_TILE_EN          (1 << 15)
#define RADEON_CRTC_PITCH                   0x022c
#define RADEON_CRTC_STATUS                  0x005c
#       define RADEON_CRTC_VBLANK_SAVE      (1 <<  1)
#define RADEON_CRTC_V_SYNC_STRT_WID         0x020c
#       define RADEON_CRTC_V_SYNC_STRT       (0x7ff <<  0)
#       define RADEON_CRTC_V_SYNC_STRT_SHIFT 0
#       define RADEON_CRTC_V_SYNC_WID        (0x1f  << 16)
#       define RADEON_CRTC_V_SYNC_WID_SHIFT  16
#       define RADEON_CRTC_V_SYNC_POL        (1     << 23)
#define RADEON_CRTC_V_TOTAL_DISP            0x0208
#       define RADEON_CRTC_V_TOTAL          (0x07ff << 0)
#       define RADEON_CRTC_V_TOTAL_SHIFT    0
#       define RADEON_CRTC_V_DISP           (0x07ff << 16)
#       define RADEON_CRTC_V_DISP_SHIFT     16
#define RADEON_CRTC_VLINE_CRNT_VLINE        0x0210
#       define RADEON_CRTC_CRNT_VLINE_MASK  (0x7ff << 16)
#define RADEON_CRTC2_CRNT_FRAME             0x0314
#define RADEON_CRTC2_DEBUG                  0x031c
#define RADEON_CRTC2_GEN_CNTL               0x03f8
#define RADEON_CRTC2_GUI_TRIG_VLINE         0x0318
#define RADEON_CRTC2_H_SYNC_STRT_WID        0x0304
#define RADEON_CRTC2_H_TOTAL_DISP           0x0300
#define RADEON_CRTC2_OFFSET                 0x0324
#define RADEON_CRTC2_OFFSET_CNTL            0x0328
#define RADEON_CRTC2_PITCH                  0x032c
#define RADEON_CRTC2_STATUS                 0x03fc
#define RADEON_CRTC2_V_SYNC_STRT_WID        0x030c
#define RADEON_CRTC2_V_TOTAL_DISP           0x0308
#define RADEON_CRTC2_VLINE_CRNT_VLINE       0x0310
#define RADEON_CRTC8_DATA                   0x03d5 /* VGA, 0x3b5 */
#define RADEON_CRTC8_IDX                    0x03d4 /* VGA, 0x3b4 */
#define RADEON_CUR_CLR0                     0x026c
#define RADEON_CUR_CLR1                     0x0270
#define RADEON_CUR_HORZ_VERT_OFF            0x0268
#define RADEON_CUR_HORZ_VERT_POSN           0x0264
#define RADEON_CUR_OFFSET                   0x0260
#       define RADEON_CUR_LOCK              (1 << 31)

#define RADEON_DAC_CNTL                     0x0058
#       define RADEON_DAC_RANGE_CNTL        (3 <<  0)
#       define RADEON_DAC_BLANKING          (1 <<  2)
#       define RADEON_DAC_CRT_SEL_CRTC2     (1 <<  4)
#       define RADEON_DAC_PALETTE_ACC_CTL   (1 <<  5)
#       define RADEON_DAC_8BIT_EN           (1 <<  8)
#       define RADEON_DAC_VGA_ADR_EN        (1 << 13)
#       define RADEON_DAC_MASK_ALL          (0xff << 24)
#define RADEON_DAC_CRC_SIG                  0x02cc
#define RADEON_DAC_DATA                     0x03c9 /* VGA */
#define RADEON_DAC_MASK                     0x03c6 /* VGA */
#define RADEON_DAC_R_INDEX                  0x03c7 /* VGA */
#define RADEON_DAC_W_INDEX                  0x03c8 /* VGA */
#define RADEON_DDA_CONFIG                   0x02e0
#define RADEON_DDA_ON_OFF                   0x02e4
#define RADEON_DEFAULT_OFFSET               0x16e0
#define RADEON_DEFAULT_PITCH                0x16e4
#define RADEON_DEFAULT_SC_BOTTOM_RIGHT      0x16e8
#       define RADEON_DEFAULT_SC_RIGHT_MAX  (0x1fff <<  0)
#       define RADEON_DEFAULT_SC_BOTTOM_MAX (0x1fff << 16)
#define RADEON_DESTINATION_3D_CLR_CMP_VAL   0x1820
#define RADEON_DESTINATION_3D_CLR_CMP_MSK   0x1824
#define RADEON_DEVICE_ID                    0x0f02 /* PCI */
#define RADEON_DISP_MISC_CNTL               0x0d00
#       define RADEON_SOFT_RESET_GRPH_PP    (1 << 0)
#define RADEON_DP_BRUSH_BKGD_CLR            0x1478
#define RADEON_DP_BRUSH_FRGD_CLR            0x147c
#define RADEON_DP_CNTL                      0x16c0
#       define RADEON_DST_X_LEFT_TO_RIGHT   (1 <<  0)
#       define RADEON_DST_Y_TOP_TO_BOTTOM   (1 <<  1)
#define RADEON_DP_CNTL_XDIR_YDIR_YMAJOR     0x16d0
#       define RADEON_DST_Y_MAJOR             (1 <<  2)
#       define RADEON_DST_Y_DIR_TOP_TO_BOTTOM (1 << 15)
#       define RADEON_DST_X_DIR_LEFT_TO_RIGHT (1 << 31)
#define RADEON_DP_DATATYPE                  0x16c4
#       define RADEON_HOST_BIG_ENDIAN_EN    (1 << 29)
#define RADEON_DP_GUI_MASTER_CNTL           0x146c
#       define RADEON_GMC_SRC_PITCH_OFFSET_CNTL (1    <<  0)
#       define RADEON_GMC_DST_PITCH_OFFSET_CNTL (1    <<  1)
#       define RADEON_GMC_SRC_CLIPPING          (1    <<  2)
#       define RADEON_GMC_DST_CLIPPING          (1    <<  3)
#       define RADEON_GMC_BRUSH_DATATYPE_MASK   (0x0f <<  4)
#       define RADEON_GMC_BRUSH_8X8_MONO_FG_BG  (0    <<  4)
#       define RADEON_GMC_BRUSH_8X8_MONO_FG_LA  (1    <<  4)
#       define RADEON_GMC_BRUSH_1X8_MONO_FG_BG  (4    <<  4)
#       define RADEON_GMC_BRUSH_1X8_MONO_FG_LA  (5    <<  4)
#       define RADEON_GMC_BRUSH_32x1_MONO_FG_BG (6    <<  4)
#       define RADEON_GMC_BRUSH_32x1_MONO_FG_LA (7    <<  4)
#       define RADEON_GMC_BRUSH_32x32_MONO_FG_BG (8    <<  4)
#       define RADEON_GMC_BRUSH_32x32_MONO_FG_LA (9    <<  4)
#       define RADEON_GMC_BRUSH_8x8_COLOR       (10   <<  4)
#       define RADEON_GMC_BRUSH_1X8_COLOR       (12   <<  4)
#       define RADEON_GMC_BRUSH_SOLID_COLOR     (13   <<  4)
#       define RADEON_GMC_BRUSH_NONE            (15   <<  4)
#       define RADEON_GMC_DST_8BPP_CI           (2    <<  8)
#       define RADEON_GMC_DST_15BPP             (3    <<  8)
#       define RADEON_GMC_DST_16BPP             (4    <<  8)
#       define RADEON_GMC_DST_24BPP             (5    <<  8)
#       define RADEON_GMC_DST_32BPP             (6    <<  8)
#       define RADEON_GMC_DST_8BPP_RGB          (7    <<  8)
#       define RADEON_GMC_DST_Y8                (8    <<  8)
#       define RADEON_GMC_DST_RGB8              (9    <<  8)
#       define RADEON_GMC_DST_VYUY              (11   <<  8)
#       define RADEON_GMC_DST_YVYU              (12   <<  8)
#       define RADEON_GMC_DST_AYUV444           (14   <<  8)
#       define RADEON_GMC_DST_ARGB4444          (15   <<  8)
#       define RADEON_GMC_DST_DATATYPE_MASK     (0x0f <<  8)
#       define RADEON_GMC_DST_DATATYPE_SHIFT    8
#       define RADEON_GMC_SRC_DATATYPE_MASK       (3    << 12)
#       define RADEON_GMC_SRC_DATATYPE_MONO_FG_BG (0    << 12)
#       define RADEON_GMC_SRC_DATATYPE_MONO_FG_LA (1    << 12)
#       define RADEON_GMC_SRC_DATATYPE_COLOR      (3    << 12)
#       define RADEON_GMC_BYTE_PIX_ORDER        (1    << 14)
#       define RADEON_GMC_BYTE_MSB_TO_LSB       (0    << 14)
#       define RADEON_GMC_BYTE_LSB_TO_MSB       (1    << 14)
#       define RADEON_GMC_CONVERSION_TEMP       (1    << 15)
#       define RADEON_GMC_CONVERSION_TEMP_6500  (0    << 15)
#       define RADEON_GMC_CONVERSION_TEMP_9300  (1    << 15)
#       define RADEON_GMC_ROP3_MASK             (0xff << 16)
#       define RADEON_DP_SRC_SOURCE_MASK        (7    << 24)
#       define RADEON_DP_SRC_SOURCE_MEMORY      (2    << 24)
#       define RADEON_DP_SRC_SOURCE_HOST_DATA   (3    << 24)
#       define RADEON_GMC_3D_FCN_EN             (1    << 27)
#       define RADEON_GMC_CLR_CMP_CNTL_DIS      (1    << 28)
#       define RADEON_GMC_AUX_CLIP_DIS          (1    << 29)
#       define RADEON_GMC_WR_MSK_DIS            (1    << 30)
#       define RADEON_GMC_LD_BRUSH_Y_X          (1    << 31)
#       define RADEON_ROP3_ZERO             0x00000000
#       define RADEON_ROP3_DSa              0x00880000
#       define RADEON_ROP3_SDna             0x00440000
#       define RADEON_ROP3_S                0x00cc0000
#       define RADEON_ROP3_DSna             0x00220000
#       define RADEON_ROP3_D                0x00aa0000
#       define RADEON_ROP3_DSx              0x00660000
#       define RADEON_ROP3_DSo              0x00ee0000
#       define RADEON_ROP3_DSon             0x00110000
#       define RADEON_ROP3_DSxn             0x00990000
#       define RADEON_ROP3_Dn               0x00550000
#       define RADEON_ROP3_SDno             0x00dd0000
#       define RADEON_ROP3_Sn               0x00330000
#       define RADEON_ROP3_DSno             0x00bb0000
#       define RADEON_ROP3_DSan             0x00770000
#       define RADEON_ROP3_ONE              0x00ff0000
#       define RADEON_ROP3_DPa              0x00a00000
#       define RADEON_ROP3_PDna             0x00500000
#       define RADEON_ROP3_P                0x00f00000
#       define RADEON_ROP3_DPna             0x000a0000
#       define RADEON_ROP3_D                0x00aa0000
#       define RADEON_ROP3_DPx              0x005a0000
#       define RADEON_ROP3_DPo              0x00fa0000
#       define RADEON_ROP3_DPon             0x00050000
#       define RADEON_ROP3_PDxn             0x00a50000
#       define RADEON_ROP3_PDno             0x00f50000
#       define RADEON_ROP3_Pn               0x000f0000
#       define RADEON_ROP3_DPno             0x00af0000
#       define RADEON_ROP3_DPan             0x005f0000


#define RADEON_DP_GUI_MASTER_CNTL_C         0x1c84
#define RADEON_DP_MIX                       0x16c8
#define RADEON_DP_SRC_BKGD_CLR              0x15dc
#define RADEON_DP_SRC_FRGD_CLR              0x15d8
#define RADEON_DP_WRITE_MASK                0x16cc
#define RADEON_DST_BRES_DEC                 0x1630
#define RADEON_DST_BRES_ERR                 0x1628
#define RADEON_DST_BRES_INC                 0x162c
#define RADEON_DST_BRES_LNTH                0x1634
#define RADEON_DST_BRES_LNTH_SUB            0x1638
#define RADEON_DST_HEIGHT                   0x1410
#define RADEON_DST_HEIGHT_WIDTH             0x143c
#define RADEON_DST_HEIGHT_WIDTH_8           0x158c
#define RADEON_DST_HEIGHT_WIDTH_BW          0x15b4
#define RADEON_DST_HEIGHT_Y                 0x15a0
#define RADEON_DST_LINE_START               0x1600
#define RADEON_DST_LINE_END                 0x1604
#define RADEON_DST_OFFSET                   0x1404
#define RADEON_DST_PITCH                    0x1408
#define RADEON_DST_PITCH_OFFSET             0x142c
#define RADEON_DST_PITCH_OFFSET_C           0x1c80
#       define RADEON_PITCH_SHIFT               21
#       define RADEON_DST_TILE_LINEAR       (0 << 30)
#       define RADEON_DST_TILE_MACRO        (1 << 30)
#       define RADEON_DST_TILE_MICRO        (2 << 30)
#       define RADEON_DST_TILE_BOTH         (3 << 30)
#define RADEON_DST_WIDTH                    0x140c
#define RADEON_DST_WIDTH_HEIGHT             0x1598
#define RADEON_DST_WIDTH_X                  0x1588
#define RADEON_DST_WIDTH_X_INCY             0x159c
#define RADEON_DST_X                        0x141c
#define RADEON_DST_X_SUB                    0x15a4
#define RADEON_DST_X_Y                      0x1594
#define RADEON_DST_Y                        0x1420
#define RADEON_DST_Y_SUB                    0x15a8
#define RADEON_DST_Y_X                      0x1438

#define RADEON_FCP_CNTL                     0x0012 /* PLL */
#define RADEON_FLUSH_1                      0x1704
#define RADEON_FLUSH_2                      0x1708
#define RADEON_FLUSH_3                      0x170c
#define RADEON_FLUSH_4                      0x1710
#define RADEON_FLUSH_5                      0x1714
#define RADEON_FLUSH_6                      0x1718
#define RADEON_FLUSH_7                      0x171c
#define RADEON_FOG_3D_TABLE_START           0x1810
#define RADEON_FOG_3D_TABLE_END             0x1814
#define RADEON_FOG_3D_TABLE_DENSITY         0x181c
#define RADEON_FOG_TABLE_INDEX              0x1a14
#define RADEON_FOG_TABLE_DATA               0x1a18
#define RADEON_FP_CRTC_H_TOTAL_DISP         0x0250
#define RADEON_FP_CRTC_V_TOTAL_DISP         0x0254
#define RADEON_FP_GEN_CNTL                  0x0284
#       define RADEON_FP_FPON                  (1 << 0)
#       define RADEON_FP_TDMS_EN               (1 <<  2)
#       define RADEON_FP_DETECT_SENSE          (1 <<  8)
#       define RADEON_FP_SEL_CRTC2             (1 << 13)
#       define RADEON_FP_CRTC_DONT_SHADOW_VPAR (1 << 16)
#       define RADEON_FP_CRTC_USE_SHADOW_VEND  (1 << 18)
#       define RADEON_FP_CRTC_HORZ_DIV2_EN     (1 << 20)
#       define RADEON_FP_CRTC_HOR_CRT_DIV2_DIS (1 << 21)
#       define RADEON_FP_USE_SHADOW_EN         (1 << 24)
#define RADEON_FP_H_SYNC_STRT_WID           0x02c4
#define RADEON_FP_HORZ_STRETCH              0x028c
#       define RADEON_HORZ_STRETCH_RATIO_MASK  0xffff
#       define RADEON_HORZ_STRETCH_RATIO_SHIFT 0
#       define RADEON_HORZ_STRETCH_RATIO_MAX   4096
#       define RADEON_HORZ_PANEL_SIZE          (0xff   << 16)
#       define RADEON_HORZ_PANEL_SHIFT         16
#       define RADEON_HORZ_STRETCH_PIXREP      (0      << 25)
#       define RADEON_HORZ_STRETCH_BLEND       (1      << 25)
#       define RADEON_HORZ_STRETCH_ENABLE      (1      << 26)
#       define RADEON_HORZ_FP_LOOP_STRETCH     (0x7    << 27)
#       define RADEON_HORZ_STRETCH_RESERVED    (1      << 30)
#       define RADEON_HORZ_AUTO_RATIO_FIX_EN   (1      << 31)

#define RADEON_FP_PANEL_CNTL                0x0288
#       define RADEON_FP_DIGON              (1 << 0)
#       define RADEON_FP_BLON               (1 << 1)
#define RADEON_FP_V_SYNC_STRT_WID           0x02c8
#define RADEON_FP_VERT_STRETCH              0x0290
#       define RADEON_VERT_PANEL_SIZE          (0x7ff <<  0)
#       define RADEON_VERT_PANEL_SHIFT         0
#       define RADEON_VERT_STRETCH_RATIO_MASK  0x3ff
#       define RADEON_VERT_STRETCH_RATIO_SHIFT 11
#       define RADEON_VERT_STRETCH_RATIO_MAX   1024
#       define RADEON_VERT_STRETCH_ENABLE      (1     << 24)
#       define RADEON_VERT_STRETCH_LINEREP     (0     << 25)
#       define RADEON_VERT_STRETCH_BLEND       (1     << 25)
#       define RADEON_VERT_AUTO_RATIO_EN       (1     << 26)
#       define RADEON_VERT_STRETCH_RESERVED    0xf8e00000

#define RADEON_GEN_INT_CNTL                 0x0040
#define RADEON_GEN_INT_STATUS               0x0044
#       define RADEON_VSYNC_INT_AK          (1 <<  2)
#       define RADEON_VSYNC_INT             (1 <<  2)
#define RADEON_GENENB                       0x03c3 /* VGA */
#define RADEON_GENFC_RD                     0x03ca /* VGA */
#define RADEON_GENFC_WT                     0x03da /* VGA, 0x03ba */
#define RADEON_GENMO_RD                     0x03cc /* VGA */
#define RADEON_GENMO_WT                     0x03c2 /* VGA */
#define RADEON_GENS0                        0x03c2 /* VGA */
#define RADEON_GENS1                        0x03da /* VGA, 0x03ba */
#define RADEON_GPIO_MONID                   0x0068
#       define RADEON_GPIO_MONID_A_0        (1 <<  0)
#       define RADEON_GPIO_MONID_A_1        (1 <<  1)
#       define RADEON_GPIO_MONID_A_2        (1 <<  2)
#       define RADEON_GPIO_MONID_A_3        (1 <<  3)
#       define RADEON_GPIO_MONID_Y_0        (1 <<  8)
#       define RADEON_GPIO_MONID_Y_1        (1 <<  9)
#       define RADEON_GPIO_MONID_Y_2        (1 << 10)
#       define RADEON_GPIO_MONID_Y_3        (1 << 11)
#       define RADEON_GPIO_MONID_EN_0       (1 << 16)
#       define RADEON_GPIO_MONID_EN_1       (1 << 17)
#       define RADEON_GPIO_MONID_EN_2       (1 << 18)
#       define RADEON_GPIO_MONID_EN_3       (1 << 19)
#       define RADEON_GPIO_MONID_MASK_0     (1 << 24)
#       define RADEON_GPIO_MONID_MASK_1     (1 << 25)
#       define RADEON_GPIO_MONID_MASK_2     (1 << 26)
#       define RADEON_GPIO_MONID_MASK_3     (1 << 27)
#define RADEON_GPIO_MONIDB                  0x006c
#define RADEON_GRPH8_DATA                   0x03cf /* VGA */
#define RADEON_GRPH8_IDX                    0x03ce /* VGA */
#define RADEON_GUI_DEBUG0                   0x16a0
#define RADEON_GUI_DEBUG1                   0x16a4
#define RADEON_GUI_DEBUG2                   0x16a8
#define RADEON_GUI_DEBUG3                   0x16ac
#define RADEON_GUI_DEBUG4                   0x16b0
#define RADEON_GUI_DEBUG5                   0x16b4
#define RADEON_GUI_DEBUG6                   0x16b8
#define RADEON_GUI_SCRATCH_REG0             0x15e0
#define RADEON_GUI_SCRATCH_REG1             0x15e4
#define RADEON_GUI_SCRATCH_REG2             0x15e8
#define RADEON_GUI_SCRATCH_REG3             0x15ec
#define RADEON_GUI_SCRATCH_REG4             0x15f0
#define RADEON_GUI_SCRATCH_REG5             0x15f4
#define RADEON_HEADER                       0x0f0e /* PCI */
#define RADEON_HOST_DATA0                   0x17c0
#define RADEON_HOST_DATA1                   0x17c4
#define RADEON_HOST_DATA2                   0x17c8
#define RADEON_HOST_DATA3                   0x17cc
#define RADEON_HOST_DATA4                   0x17d0
#define RADEON_HOST_DATA5                   0x17d4
#define RADEON_HOST_DATA6                   0x17d8
#define RADEON_HOST_DATA7                   0x17dc
#define RADEON_HOST_DATA_LAST               0x17e0
#define RADEON_HOST_PATH_CNTL               0x0130
#define RADEON_HTOTAL_CNTL                  0x0009 /* PLL */
#define RADEON_HW_DEBUG                     0x0128
#define RADEON_HW_DEBUG2                    0x011c

#define RADEON_I2C_CNTL_1                   0x0094 /* ? */
#define RADEON_INTERRUPT_LINE               0x0f3c /* PCI */
#define RADEON_INTERRUPT_PIN                0x0f3d /* PCI */
#define RADEON_IO_BASE                      0x0f14 /* PCI */

#define RADEON_LATENCY                      0x0f0d /* PCI */
#define RADEON_LEAD_BRES_DEC                0x1608
#define RADEON_LEAD_BRES_LNTH               0x161c
#define RADEON_LEAD_BRES_LNTH_SUB           0x1624
#define RADEON_LVDS_GEN_CNTL                0x02d0
#       define RADEON_LVDS_ON               (1   <<  0)
#       define RADEON_LVDS_BLON             (1   << 19)
#       define RADEON_LVDS_SEL_CRTC2        (1   << 23)
#       define RADEON_HSYNC_DELAY_SHIFT     28
#       define RADEON_HSYNC_DELAY_MASK      (0xf << 28)

#define RADEON_MAX_LATENCY                  0x0f3f /* PCI */
#define RADEON_MC_AGP_LOCATION              0x014c
#define RADEON_MC_FB_LOCATION               0x0148
#define RADEON_MCLK_CNTL                    0x0012 /* PLL */
#       define RADEON_FORCEON_MCLKA         (1 << 16)
#       define RADEON_FORCEON_MCLKB         (1 << 17)
#       define RADEON_FORCEON_YCLKA         (1 << 18)
#       define RADEON_FORCEON_YCLKB         (1 << 19)
#       define RADEON_FORCEON_MC            (1 << 20)
#       define RADEON_FORCEON_AIC           (1 << 21)
#define RADEON_MDGPIO_A_REG                 0x01ac
#define RADEON_MDGPIO_EN_REG                0x01b0
#define RADEON_MDGPIO_MASK                  0x0198
#define RADEON_MDGPIO_Y_REG                 0x01b4
#define RADEON_MEM_ADDR_CONFIG              0x0148
#define RADEON_MEM_BASE                     0x0f10 /* PCI */
#define RADEON_MEM_CNTL                     0x0140
#define RADEON_MEM_INIT_LAT_TIMER           0x0154
#define RADEON_MEM_INTF_CNTL                0x014c
#define RADEON_MEM_SDRAM_MODE_REG           0x0158
#define RADEON_MEM_STR_CNTL                 0x0150
#define RADEON_MEM_VGA_RP_SEL               0x003c
#define RADEON_MEM_VGA_WP_SEL               0x0038
#define RADEON_MIN_GRANT                    0x0f3e /* PCI */
#define RADEON_MM_DATA                      0x0004
#define RADEON_MM_INDEX                     0x0000
#define RADEON_MPLL_CNTL                    0x000e /* PLL */
#define RADEON_MPP_TB_CONFIG                0x01c0 /* ? */
#define RADEON_MPP_GP_CONFIG                0x01c8 /* ? */

#define RADEON_N_VIF_COUNT                  0x0248

#define RADEON_OV0_SCALE_CNTL               0x0420 /* ? */
#define RADEON_OVR_CLR                      0x0230
#define RADEON_OVR_WID_LEFT_RIGHT           0x0234
#define RADEON_OVR_WID_TOP_BOTTOM           0x0238

/* first overlay unit (there is only one) */

#define RADEON_OV0_Y_X_START                0x0400
#define RADEON_OV0_Y_X_END                  0x0404
#define RADEON_OV0_EXCLUSIVE_HORZ           0x0408
#       define  RADEON_EXCL_HORZ_START_MASK        0x000000ff
#       define  RADEON_EXCL_HORZ_END_MASK          0x0000ff00
#       define  RADEON_EXCL_HORZ_BACK_PORCH_MASK   0x00ff0000
#       define  RADEON_EXCL_HORZ_EXCLUSIVE_EN      0x80000000
#define RADEON_OV0_EXCLUSIVE_VERT           0x040C
#       define  RADEON_EXCL_VERT_START_MASK        0x000003ff
#       define  RADEON_EXCL_VERT_END_MASK          0x03ff0000
#define RADEON_OV0_REG_LOAD_CNTL            0x0410
#       define  RADEON_REG_LD_CTL_LOCK                 0x00000001L
#       define  RADEON_REG_LD_CTL_VBLANK_DURING_LOCK   0x00000002L
#       define  RADEON_REG_LD_CTL_STALL_GUI_UNTIL_FLIP 0x00000004L
#       define  RADEON_REG_LD_CTL_LOCK_READBACK        0x00000008L
#define RADEON_OV0_SCALE_CNTL               0x0420
#       define  RADEON_SCALER_PIX_EXPAND           0x00000001L
#       define  RADEON_SCALER_Y2R_TEMP             0x00000002L
#       define  RADEON_SCALER_HORZ_PICK_NEAREST    0x00000003L
#       define  RADEON_SCALER_VERT_PICK_NEAREST    0x00000004L
#       define  RADEON_SCALER_SIGNED_UV            0x00000010L
#       define  RADEON_SCALER_GAMMA_SEL_MASK       0x00000060L
#       define  RADEON_SCALER_GAMMA_SEL_BRIGHT     0x00000000L
#       define  RADEON_SCALER_GAMMA_SEL_G22        0x00000020L
#       define  RADEON_SCALER_GAMMA_SEL_G18        0x00000040L
#       define  RADEON_SCALER_GAMMA_SEL_G14        0x00000060L
#       define  RADEON_SCALER_COMCORE_SHIFT_UP_ONE 0x00000080L
#       define  RADEON_SCALER_SURFAC_FORMAT        0x00000f00L
#       define  RADEON_SCALER_SOURCE_15BPP         0x00000300L
#       define  RADEON_SCALER_SOURCE_16BPP         0x00000400L
#       define  RADEON_SCALER_SOURCE_32BPP         0x00000600L
#       define  RADEON_SCALER_SOURCE_YUV9          0x00000900L
#       define  RADEON_SCALER_SOURCE_YUV12         0x00000A00L
#       define  RADEON_SCALER_SOURCE_VYUY422       0x00000B00L
#       define  RADEON_SCALER_SOURCE_YVYU422       0x00000C00L
#       define  RADEON_SCALER_SMART_SWITCH         0x00008000L
#       define  RADEON_SCALER_BURST_PER_PLANE      0x00ff0000L
#       define  RADEON_SCALER_DOUBLE_BUFFER        0x01000000L
#       define  RADEON_SCALER_DIS_LIMIT            0x08000000L
#       define  RADEON_SCALER_PRG_LOAD_START       0x10000000L
#       define  RADEON_SCALER_INT_EMU              0x20000000L
#       define  RADEON_SCALER_ENABLE               0x40000000L
#       define  RADEON_SCALER_SOFT_RESET           0x80000000L
#define RADEON_OV0_V_INC                    0x0424
#define RADEON_OV0_P1_V_ACCUM_INIT          0x0428
#       define  RADEON_OV0_P1_MAX_LN_IN_PER_LN_OUT 0x00000003L
#       define  RADEON_OV0_P1_V_ACCUM_INIT_MASK    0x01ff8000L
#define RADEON_OV0_P23_V_ACCUM_INIT         0x042C
#define RADEON_OV0_P1_BLANK_LINES_AT_TOP    0x0430
#       define  RADEON_P1_BLNK_LN_AT_TOP_M1_MASK   0x00000fffL
#       define  RADEON_P1_ACTIVE_LINES_M1          0x0fff0000L
#define RADEON_OV0_P23_BLANK_LINES_AT_TOP   0x0434
#       define  RADEON_P23_BLNK_LN_AT_TOP_M1_MASK  0x000007ffL
#       define  RADEON_P23_ACTIVE_LINES_M1         0x07ff0000L
#define RADEON_OV0_VID_BUF0_BASE_ADRS       0x0440
#       define  RADEON_VIF_BUF0_PITCH_SEL          0x00000001L
#       define  RADEON_VIF_BUF0_TILE_ADRS          0x00000002L
#       define  RADEON_VIF_BUF0_BASE_ADRS_MASK     0x03fffff0L
#       define  RADEON_VIF_BUF0_1ST_LINE_LSBS_MASK 0x48000000L
#define RADEON_OV0_VID_BUF1_BASE_ADRS       0x0444
#       define  RADEON_VIF_BUF1_PITCH_SEL          0x00000001L
#       define  RADEON_VIF_BUF1_TILE_ADRS          0x00000002L
#       define  RADEON_VIF_BUF1_BASE_ADRS_MASK     0x03fffff0L
#       define  RADEON_VIF_BUF1_1ST_LINE_LSBS_MASK 0x48000000L
#define RADEON_OV0_VID_BUF2_BASE_ADRS       0x0448
#       define  RADEON_VIF_BUF2_PITCH_SEL          0x00000001L
#       define  RADEON_VIF_BUF2_TILE_ADRS          0x00000002L
#       define  RADEON_VIF_BUF2_BASE_ADRS_MASK     0x03fffff0L
#       define  RADEON_VIF_BUF2_1ST_LINE_LSBS_MASK 0x48000000L
#define RADEON_OV0_VID_BUF3_BASE_ADRS       0x044C
#define RADEON_OV0_VID_BUF4_BASE_ADRS       0x0450
#define RADEON_OV0_VID_BUF5_BASE_ADRS       0x0454
#define RADEON_OV0_VID_BUF_PITCH0_VALUE     0x0460
#define RADEON_OV0_VID_BUF_PITCH1_VALUE     0x0464
#define RADEON_OV0_AUTO_FLIP_CNTL           0x0470
#define RADEON_OV0_DEINTERLACE_PATTERN      0x0474
#define RADEON_OV0_H_INC                    0x0480
#define RADEON_OV0_STEP_BY                  0x0484
#define RADEON_OV0_P1_H_ACCUM_INIT          0x0488
#define RADEON_OV0_P23_H_ACCUM_INIT         0x048C
#define RADEON_OV0_P1_X_START_END           0x0494
#define RADEON_OV0_P2_X_START_END           0x0498
#define RADEON_OV0_P3_X_START_END           0x049C
#define RADEON_OV0_FILTER_CNTL              0x04A0
#define RADEON_OV0_FOUR_TAP_COEF_0          0x04B0
#define RADEON_OV0_FOUR_TAP_COEF_1          0x04B4
#define RADEON_OV0_FOUR_TAP_COEF_2          0x04B8
#define RADEON_OV0_FOUR_TAP_COEF_3          0x04BC
#define RADEON_OV0_FOUR_TAP_COEF_4          0x04C0
#define RADEON_OV0_COLOUR_CNTL              0x04E0
#define RADEON_OV0_VIDEO_KEY_CLR            0x04E4
#define RADEON_OV0_VIDEO_KEY_MSK            0x04E8
#define RADEON_OV0_GRAPHICS_KEY_CLR         0x04EC
#define RADEON_OV0_GRAPHICS_KEY_MSK         0x04F0
#define RADEON_OV0_KEY_CNTL                 0x04F4
#       define  RADEON_VIDEO_KEY_FN_MASK           0x00000007L
#       define  RADEON_VIDEO_KEY_FN_FALSE          0x00000000L
#       define  RADEON_VIDEO_KEY_FN_TRUE           0x00000001L
#       define  RADEON_VIDEO_KEY_FN_EQ             0x00000004L
#       define  RADEON_VIDEO_KEY_FN_NE             0x00000005L
#       define  RADEON_GRAPHIC_KEY_FN_MASK         0x00000070L
#       define  RADEON_GRAPHIC_KEY_FN_FALSE        0x00000000L
#       define  RADEON_GRAPHIC_KEY_FN_TRUE         0x00000010L
#       define  RADEON_GRAPHIC_KEY_FN_EQ           0x00000040L
#       define  RADEON_GRAPHIC_KEY_FN_NE           0x00000050L
#       define  RADEON_CMP_MIX_MASK                0x00000100L
#       define  RADEON_CMP_MIX_OR                  0x00000000L
#       define  RADEON_CMP_MIX_AND                 0x00000100L
#define RADEON_OV0_TEST                     0x04F8

#define RADEON_PALETTE_DATA                 0x00b4
#define RADEON_PALETTE_30_DATA              0x00b8
#define RADEON_PALETTE_INDEX                0x00b0
#define RADEON_PCI_GART_PAGE                0x017c
#define RADEON_PLANE_3D_MASK_C              0x1d44
#define RADEON_PLL_TEST_CNTL                0x0013 /* PLL */
#define RADEON_PMI_CAP_ID                   0x0f5c /* PCI */
#define RADEON_PMI_DATA                     0x0f63 /* PCI */
#define RADEON_PMI_NXT_CAP_PTR              0x0f5d /* PCI */
#define RADEON_PMI_PMC_REG                  0x0f5e /* PCI */
#define RADEON_PMI_PMCSR_REG                0x0f60 /* PCI */
#define RADEON_PMI_REGISTER                 0x0f5c /* PCI */
#define RADEON_PPLL_CNTL                    0x0002 /* PLL */
#       define RADEON_PPLL_RESET                (1 <<  0)
#       define RADEON_PPLL_SLEEP                (1 <<  1)
#       define RADEON_PPLL_ATOMIC_UPDATE_EN     (1 << 16)
#       define RADEON_PPLL_VGA_ATOMIC_UPDATE_EN (1 << 17)
#       define RADEON_PPLL_ATOMIC_UPDATE_VSYNC  (1 << 18)
#define RADEON_PPLL_DIV_0                   0x0004 /* PLL */
#define RADEON_PPLL_DIV_1                   0x0005 /* PLL */
#define RADEON_PPLL_DIV_2                   0x0006 /* PLL */
#define RADEON_PPLL_DIV_3                   0x0007 /* PLL */
#       define RADEON_PPLL_FB3_DIV_MASK     0x07ff
#       define RADEON_PPLL_POST3_DIV_MASK   0x00070000
#define RADEON_PPLL_REF_DIV                 0x0003 /* PLL */
#       define RADEON_PPLL_REF_DIV_MASK     0x03ff
#       define RADEON_PPLL_ATOMIC_UPDATE_R  (1 << 15) /* same as _W */
#       define RADEON_PPLL_ATOMIC_UPDATE_W  (1 << 15) /* same as _R */
#define RADEON_PWR_MNGMT_CNTL_STATUS        0x0f60 /* PCI */
#define RADEON_RBBM_SOFT_RESET              0x00f0
#       define RADEON_SOFT_RESET_CP           (1 <<  0)
#       define RADEON_SOFT_RESET_HI           (1 <<  1)
#       define RADEON_SOFT_RESET_SE           (1 <<  2)
#       define RADEON_SOFT_RESET_RE           (1 <<  3)
#       define RADEON_SOFT_RESET_PP           (1 <<  4)
#       define RADEON_SOFT_RESET_E2           (1 <<  5)
#       define RADEON_SOFT_RESET_RB           (1 <<  6)
#       define RADEON_SOFT_RESET_HDP          (1 <<  7)
#define RADEON_RBBM_STATUS                  0x0e40
#       define RADEON_RBBM_FIFOCNT_MASK     0x007f
#       define RADEON_RBBM_ACTIVE           (1 << 31)
#define RADEON_RB2D_DSTCACHE_CTLSTAT        0x342c
#       define RADEON_RB2D_DC_FLUSH         (3 << 0)
#       define RADEON_RB2D_DC_FREE          (3 << 2)
#       define RADEON_RB2D_DC_FLUSH_ALL     0xf
#       define RADEON_RB2D_DC_BUSY          (1 << 31)
#define RADEON_RB2D_DSTCACHE_MODE           0x3428
#define RADEON_REG_BASE                     0x0f18 /* PCI */
#define RADEON_REGPROG_INF                  0x0f09 /* PCI */
#define RADEON_REVISION_ID                  0x0f08 /* PCI */

#define RADEON_SC_BOTTOM                    0x164c
#define RADEON_SC_BOTTOM_RIGHT              0x16f0
#define RADEON_SC_BOTTOM_RIGHT_C            0x1c8c
#define RADEON_SC_LEFT                      0x1640
#define RADEON_SC_RIGHT                     0x1644
#define RADEON_SC_TOP                       0x1648
#define RADEON_SC_TOP_LEFT                  0x16ec
#define RADEON_SC_TOP_LEFT_C                0x1c88
#define RADEON_SDRAM_MODE_REG               0x0158
#define RADEON_SEQ8_DATA                    0x03c5 /* VGA */
#define RADEON_SEQ8_IDX                     0x03c4 /* VGA */
#define RADEON_SNAPSHOT_F_COUNT             0x0244
#define RADEON_SNAPSHOT_VH_COUNTS           0x0240
#define RADEON_SNAPSHOT_VIF_COUNT           0x024c
#define RADEON_SRC_OFFSET                   0x15ac
#define RADEON_SRC_PITCH                    0x15b0
#define RADEON_SRC_PITCH_OFFSET             0x1428
#define RADEON_SRC_SC_BOTTOM                0x165c
#define RADEON_SRC_SC_BOTTOM_RIGHT          0x16f4
#define RADEON_SRC_SC_RIGHT                 0x1654
#define RADEON_SRC_X                        0x1414
#define RADEON_SRC_X_Y                      0x1590
#define RADEON_SRC_Y                        0x1418
#define RADEON_SRC_Y_X                      0x1434
#define RADEON_STATUS                       0x0f06 /* PCI */
#define RADEON_SUBPIC_CNTL                  0x0540 /* ? */
#define RADEON_SUB_CLASS                    0x0f0a /* PCI */
#define RADEON_SURFACE_CNTL                 0x0b00
#define RADEON_SURFACE0_INFO                0x0b0c
#define RADEON_SURFACE0_LOWER_BOUND         0x0b04
#define RADEON_SURFACE0_UPPER_BOUND         0x0b08
#define RADEON_SURFACE1_INFO                0x0b1c
#define RADEON_SURFACE1_LOWER_BOUND         0x0b14
#define RADEON_SURFACE1_UPPER_BOUND         0x0b18
#define RADEON_SURFACE2_INFO                0x0b2c
#define RADEON_SURFACE2_LOWER_BOUND         0x0b24
#define RADEON_SURFACE2_UPPER_BOUND         0x0b28
#define RADEON_SURFACE3_INFO                0x0b3c
#define RADEON_SURFACE3_LOWER_BOUND         0x0b34
#define RADEON_SURFACE3_UPPER_BOUND         0x0b38
#define RADEON_SURFACE4_INFO                0x0b4c
#define RADEON_SURFACE4_LOWER_BOUND         0x0b44
#define RADEON_SURFACE4_UPPER_BOUND         0x0b48
#define RADEON_SURFACE5_INFO                0x0b5c
#define RADEON_SURFACE5_LOWER_BOUND         0x0b54
#define RADEON_SURFACE5_UPPER_BOUND         0x0b58
#define RADEON_SURFACE6_INFO                0x0b6c
#define RADEON_SURFACE6_LOWER_BOUND         0x0b64
#define RADEON_SURFACE6_UPPER_BOUND         0x0b68
#define RADEON_SURFACE7_INFO                0x0b7c
#define RADEON_SURFACE7_LOWER_BOUND         0x0b74
#define RADEON_SURFACE7_UPPER_BOUND         0x0b78
#define RADEON_SW_SEMAPHORE                 0x013c

#define RADEON_TEST_DEBUG_CNTL              0x0120
#define RADEON_TEST_DEBUG_MUX               0x0124
#define RADEON_TEST_DEBUG_OUT               0x012c
#define RADEON_TMDS_CRC                     0x02a0
#define RADEON_TRAIL_BRES_DEC               0x1614
#define RADEON_TRAIL_BRES_ERR               0x160c
#define RADEON_TRAIL_BRES_INC               0x1610
#define RADEON_TRAIL_X                      0x1618
#define RADEON_TRAIL_X_SUB                  0x1620

#define RADEON_VCLK_ECP_CNTL                0x0008 /* PLL */
#define RADEON_VENDOR_ID                    0x0f00 /* PCI */
#define RADEON_VGA_DDA_CONFIG               0x02e8
#define RADEON_VGA_DDA_ON_OFF               0x02ec
#define RADEON_VID_BUFFER_CONTROL           0x0900
#define RADEON_VIDEOMUX_CNTL                0x0190
#define RADEON_VIPH_CONTROL                 0x0c40 /* ? */

#define RADEON_WAIT_UNTIL                   0x1720
#	define RADEON_WAIT_CRTC_PFLIP       (1 << 0)
#	define RADEON_WAIT_2D_IDLECLEAN     (1 << 16)
#	define RADEON_WAIT_3D_IDLECLEAN     (1 << 17)
#	define RADEON_WAIT_HOST_IDLECLEAN   (1 << 18)

#define RADEON_X_MPLL_REF_FB_DIV            0x000a /* PLL */
#define RADEON_XCLK_CNTL                    0x000d /* PLL */
#define RADEON_XDLL_CNTL                    0x000c /* PLL */
#define RADEON_XPLL_CNTL                    0x000b /* PLL */

				/* Registers for 3D/TCL */
#define RADEON_PP_BORDER_COLOR_0            0x1d40
#define RADEON_PP_BORDER_COLOR_1            0x1d44
#define RADEON_PP_BORDER_COLOR_2            0x1d48
#define RADEON_PP_CNTL                      0x1c38
#       define RADEON_STIPPLE_ENABLE        (1 <<  0)
#       define RADEON_SCISSOR_ENABLE        (1 <<  1)
#       define RADEON_PATTERN_ENABLE        (1 <<  2)
#       define RADEON_SHADOW_ENABLE         (1 <<  3)
#       define RADEON_TEX_ENABLE_MASK       (0xf << 4)
#       define RADEON_TEX_0_ENABLE          (1 <<  4)
#       define RADEON_TEX_1_ENABLE          (1 <<  5)
#       define RADEON_TEX_2_ENABLE          (1 <<  6)
#       define RADEON_TEX_3_ENABLE          (1 <<  7)
#       define RADEON_TEX_BLEND_ENABLE_MASK (0xf << 12)
#       define RADEON_TEX_BLEND_0_ENABLE    (1 << 12)
#       define RADEON_TEX_BLEND_1_ENABLE    (1 << 13)
#       define RADEON_TEX_BLEND_2_ENABLE    (1 << 14)
#       define RADEON_TEX_BLEND_3_ENABLE    (1 << 15)
#       define RADEON_PLANAR_YUV_ENABLE     (1 << 20)
#       define RADEON_SPECULAR_ENABLE       (1 << 21)
#       define RADEON_FOG_ENABLE            (1 << 22)
#       define RADEON_ALPHA_TEST_ENABLE     (1 << 23)
#       define RADEON_ANTI_ALIAS_NONE       (0 << 24)
#       define RADEON_ANTI_ALIAS_LINE       (1 << 24)
#       define RADEON_ANTI_ALIAS_POLY       (2 << 24)
#       define RADEON_ANTI_ALIAS_LINE_POLY  (3 << 24)
#       define RADEON_BUMP_MAP_ENABLE       (1 << 26)
#       define RADEON_BUMPED_MAP_T0         (0 << 27)
#       define RADEON_BUMPED_MAP_T1         (1 << 27)
#       define RADEON_BUMPED_MAP_T2         (2 << 27)
#       define RADEON_TEX_3D_ENABLE_0       (1 << 29)
#       define RADEON_TEX_3D_ENABLE_1       (1 << 30)
#       define RADEON_MC_ENABLE             (1 << 31)
#define RADEON_PP_FOG_COLOR                 0x1c18
#       define RADEON_FOG_COLOR_MASK        0x00ffffff
#       define RADEON_FOG_VERTEX            (0 << 24)
#       define RADEON_FOG_TABLE             (1 << 24)
#       define RADEON_FOG_USE_DEPTH         (0 << 25)
#       define RADEON_FOG_USE_DIFFUSE_ALPHA (2 << 25)
#       define RADEON_FOG_USE_SPEC_ALPHA    (3 << 25)
#define RADEON_PP_LUM_MATRIX                0x1d00
#define RADEON_PP_MISC                      0x1c14
#       define RADEON_REF_ALPHA_MASK        0x000000ff
#       define RADEON_ALPHA_TEST_FAIL       (0 << 8)
#       define RADEON_ALPHA_TEST_LESS       (1 << 8)
#       define RADEON_ALPHA_TEST_LEQUAL     (2 << 8)
#       define RADEON_ALPHA_TEST_EQUAL      (3 << 8)
#       define RADEON_ALPHA_TEST_GEQUAL     (4 << 8)
#       define RADEON_ALPHA_TEST_GREATER    (5 << 8)
#       define RADEON_ALPHA_TEST_NEQUAL     (6 << 8)
#       define RADEON_ALPHA_TEST_PASS       (7 << 8)
#       define RADEON_ALPHA_TEST_OP_MASK    (7 << 8)
#       define RADEON_CHROMA_FUNC_FAIL      (0 << 16)
#       define RADEON_CHROMA_FUNC_PASS      (1 << 16)
#       define RADEON_CHROMA_FUNC_NEQUAL    (2 << 16)
#       define RADEON_CHROMA_FUNC_EQUAL     (3 << 16)
#       define RADEON_CHROMA_KEY_NEAREST    (0 << 18)
#       define RADEON_CHROMA_KEY_ZERO       (1 << 18)
#       define RADEON_SHADOW_ID_AUTO_INC    (1 << 20)
#       define RADEON_SHADOW_FUNC_EQUAL     (0 << 21)
#       define RADEON_SHADOW_FUNC_NEQUAL    (1 << 21)
#       define RADEON_SHADOW_PASS_1         (0 << 22)
#       define RADEON_SHADOW_PASS_2         (1 << 22)
#       define RADEON_RIGHT_HAND_CUBE_D3D   (0 << 24)
#       define RADEON_RIGHT_HAND_CUBE_OGL   (1 << 24)
#define RADEON_PP_ROT_MATRIX_0              0x1d58
#define RADEON_PP_ROT_MATRIX_1              0x1d5c
#define RADEON_PP_TXFILTER_0                0x1c54
#define RADEON_PP_TXFILTER_1                0x1c6c
#define RADEON_PP_TXFILTER_2                0x1c84
#       define RADEON_MAG_FILTER_NEAREST                   (0  <<  0)
#       define RADEON_MAG_FILTER_LINEAR                    (1  <<  0)
#       define RADEON_MAG_FILTER_MASK                      (1  <<  0)
#       define RADEON_MIN_FILTER_NEAREST                   (0  <<  1)
#       define RADEON_MIN_FILTER_LINEAR                    (1  <<  1)
#       define RADEON_MIN_FILTER_NEAREST_MIP_NEAREST       (2  <<  1)
#       define RADEON_MIN_FILTER_NEAREST_MIP_LINEAR        (3  <<  1)
#       define RADEON_MIN_FILTER_LINEAR_MIP_NEAREST        (6  <<  1)
#       define RADEON_MIN_FILTER_LINEAR_MIP_LINEAR         (7  <<  1)
#       define RADEON_MIN_FILTER_ANISO_NEAREST             (8  <<  1)
#       define RADEON_MIN_FILTER_ANISO_LINEAR              (9  <<  1)
#       define RADEON_MIN_FILTER_ANISO_NEAREST_MIP_NEAREST (10 <<  1)
#       define RADEON_MIN_FILTER_ANISO_NEAREST_MIP_LINEAR  (11 <<  1)
#       define RADEON_MIN_FILTER_MASK                      (15 <<  1)
#       define RADEON_LOD_BIAS_MASK                        (0xffff <<  8)
#       define RADEON_LOD_BIAS_SHIFT                       8
#       define RADEON_MAX_MIP_LEVEL_MASK                   (0x0f << 16)
#       define RADEON_MAX_MIP_LEVEL_SHIFT                  16
#       define RADEON_WRAPEN_S                             (1  << 22)
#       define RADEON_CLAMP_S_WRAP                         (0  << 23)
#       define RADEON_CLAMP_S_MIRROR                       (1  << 23)
#       define RADEON_CLAMP_S_CLAMP_LAST                   (2  << 23)
#       define RADEON_CLAMP_S_MIRROR_CLAMP_LAST            (3  << 23)
#       define RADEON_CLAMP_S_CLAMP_BORDER                 (4  << 23)
#       define RADEON_CLAMP_S_MIRROR_CLAMP_BORDER          (5  << 23)
#       define RADEON_CLAMP_S_MASK                         (7  << 23)
#       define RADEON_WRAPEN_T                             (1  << 26)
#       define RADEON_CLAMP_T_WRAP                         (0  << 27)
#       define RADEON_CLAMP_T_MIRROR                       (1  << 27)
#       define RADEON_CLAMP_T_CLAMP_LAST                   (2  << 27)
#       define RADEON_CLAMP_T_MIRROR_CLAMP_LAST            (3  << 27)
#       define RADEON_CLAMP_T_CLAMP_BORDER                 (4  << 27)
#       define RADEON_CLAMP_T_MIRROR_CLAMP_BORDER          (5  << 27)
#       define RADEON_CLAMP_T_MASK                         (7  << 27)
#       define RADEON_BORDER_MODE_OGL                      (0  << 31)
#       define RADEON_BORDER_MODE_D3D                      (1  << 31)
#		define RADEON_PP_TXFORMAT_0 			   0x1c58
#		define RADEON_PP_TXFORMAT_1 			   0x1c70
#		define RADEON_PP_TXFORMAT_2 			   0x1c88
#       define RADEON_TXFORMAT_I8                 (0  <<  0)
#       define RADEON_TXFORMAT_AI88               (1  <<  0)
#       define RADEON_TXFORMAT_RGB332             (2  <<  0)
#       define RADEON_TXFORMAT_ARGB1555           (3  <<  0)
#       define RADEON_TXFORMAT_RGB565             (4  <<  0)
#       define RADEON_TXFORMAT_ARGB4444           (5  <<  0)
#       define RADEON_TXFORMAT_ARGB8888           (6  <<  0)
#       define RADEON_TXFORMAT_RGBA8888           (7  <<  0)
#       define RADEON_TXFORMAT_Y8                 (8  <<  0)
#       define RADEON_TXFORMAT_YUV12              (10 <<  0)
#       define RADEON_TXFORMAT_FORMAT_MASK        (31 <<  0)
#       define RADEON_TXFORMAT_FORMAT_SHIFT       0
#       define RADEON_TXFORMAT_APPLE_YUV_MODE     (1  <<  5)
#       define RADEON_TXFORMAT_ALPHA_IN_MAP       (1  <<  6)
#       define RADEON_TXFORMAT_NON_POWER2         (1  <<  7)
#       define RADEON_TXFORMAT_WIDTH_MASK         (15 <<  8)
#       define RADEON_TXFORMAT_WIDTH_SHIFT        8
#       define RADEON_TXFORMAT_HEIGHT_MASK        (15 << 12)
#       define RADEON_TXFORMAT_HEIGHT_SHIFT       12
#       define RADEON_TXFORMAT_ST_ROUTE_STQ0      (0  << 24)
#       define RADEON_TXFORMAT_ST_ROUTE_MASK      (3  << 24)
#       define RADEON_TXFORMAT_ST_ROUTE_STQ1      (1  << 24)
#       define RADEON_TXFORMAT_ST_ROUTE_STQ2      (2  << 24)
#       define RADEON_TXFORMAT_ENDIAN_NO_SWAP     (0  << 26)
#       define RADEON_TXFORMAT_ENDIAN_16BPP_SWAP  (1  << 26)
#       define RADEON_TXFORMAT_ENDIAN_32BPP_SWAP  (2  << 26)
#       define RADEON_TXFORMAT_ENDIAN_HALFDW_SWAP (3  << 26)
#       define RADEON_TXFORMAT_ALPHA_MASK_ENABLE  (1  << 28)
#       define RADEON_TXFORMAT_CHROMA_KEY_ENABLE  (1  << 29)
#       define RADEON_TXFORMAT_CUBIC_MAP_ENABLE   (1  << 30)
#       define RADEON_TXFORMAT_PERSPECTIVE_ENABLE (1  << 31)
#define RADEON_PP_TXOFFSET_0                0x1c5c
#define RADEON_PP_TXOFFSET_1                0x1c74
#define RADEON_PP_TXOFFSET_2                0x1c8c
#       define RADEON_TXO_ENDIAN_NO_SWAP     (0 << 0)
#       define RADEON_TXO_ENDIAN_BYTE_SWAP   (1 << 0)
#       define RADEON_TXO_ENDIAN_WORD_SWAP   (2 << 0)
#       define RADEON_TXO_ENDIAN_HALFDW_SWAP (3 << 0)
#       define RADEON_TXO_MACRO_LINEAR       (0 << 2)
#       define RADEON_TXO_MACRO_TILE         (1 << 2)
#       define RADEON_TXO_MICRO_LINEAR       (0 << 3)
#       define RADEON_TXO_MICRO_TILE_X2      (1 << 3)
#       define RADEON_TXO_MICRO_TILE_OPT     (2 << 3)
#       define RADEON_TXO_OFFSET_MASK        0xffffffe0
#       define RADEON_TXO_OFFSET_SHIFT       5
#define RADEON_PP_TXCBLEND_0                0x1c60
#define RADEON_PP_TXCBLEND_1                0x1c78
#define RADEON_PP_TXCBLEND_2                0x1c90
#	define RADEON_COLOR_ARG_A_SHIFT			0
#	define RADEON_COLOR_ARG_A_MASK			(0x1f << 0)
#	define RADEON_COLOR_ARG_A_ZERO			(0 << 0)
#	define RADEON_COLOR_ARG_A_CURRENT_COLOR		(2 << 0)
#	define RADEON_COLOR_ARG_A_CURRENT_ALPHA		(3 << 0)
#	define RADEON_COLOR_ARG_A_DIFFUSE_COLOR		(4 << 0)
#	define RADEON_COLOR_ARG_A_DIFFUSE_ALPHA		(5 << 0)
#	define RADEON_COLOR_ARG_A_SPECULAR_COLOR	(6 << 0)
#	define RADEON_COLOR_ARG_A_SPECULAR_ALPHA	(7 << 0)
#	define RADEON_COLOR_ARG_A_TFACTOR_COLOR		(8 << 0)
#	define RADEON_COLOR_ARG_A_TFACTOR_ALPHA		(9 << 0)
#	define RADEON_COLOR_ARG_A_T0_COLOR		(10 << 0)
#	define RADEON_COLOR_ARG_A_T0_ALPHA		(11 << 0)
#	define RADEON_COLOR_ARG_A_T1_COLOR		(12 << 0)
#	define RADEON_COLOR_ARG_A_T1_ALPHA		(13 << 0)
#	define RADEON_COLOR_ARG_A_T2_COLOR		(14 << 0)
#	define RADEON_COLOR_ARG_A_T2_ALPHA		(15 << 0)
#	define RADEON_COLOR_ARG_A_T3_COLOR		(16 << 0)
#	define RADEON_COLOR_ARG_A_T3_ALPHA		(17 << 0)
#	define RADEON_COLOR_ARG_B_SHIFT			5
#	define RADEON_COLOR_ARG_B_MASK			(0x1f << 5)
#	define RADEON_COLOR_ARG_B_ZERO			(0 << 5)
#	define RADEON_COLOR_ARG_B_CURRENT_COLOR		(2 << 5)
#	define RADEON_COLOR_ARG_B_CURRENT_ALPHA		(3 << 5)
#	define RADEON_COLOR_ARG_B_DIFFUSE_COLOR		(4 << 5)
#	define RADEON_COLOR_ARG_B_DIFFUSE_ALPHA		(5 << 5)
#	define RADEON_COLOR_ARG_B_SPECULAR_COLOR	(6 << 5)
#	define RADEON_COLOR_ARG_B_SPECULAR_ALPHA	(7 << 5)
#	define RADEON_COLOR_ARG_B_TFACTOR_COLOR		(8 << 5)
#	define RADEON_COLOR_ARG_B_TFACTOR_ALPHA		(9 << 5)
#	define RADEON_COLOR_ARG_B_T0_COLOR		(10 << 5)
#	define RADEON_COLOR_ARG_B_T0_ALPHA		(11 << 5)
#	define RADEON_COLOR_ARG_B_T1_COLOR		(12 << 5)
#	define RADEON_COLOR_ARG_B_T1_ALPHA		(13 << 5)
#	define RADEON_COLOR_ARG_B_T2_COLOR		(14 << 5)
#	define RADEON_COLOR_ARG_B_T2_ALPHA		(15 << 5)
#	define RADEON_COLOR_ARG_B_T3_COLOR		(16 << 5)
#	define RADEON_COLOR_ARG_B_T3_ALPHA		(17 << 5)
#	define RADEON_COLOR_ARG_C_SHIFT			10
#	define RADEON_COLOR_ARG_C_MASK			(0x1f << 10)
#	define RADEON_COLOR_ARG_C_ZERO			(0 << 10)
#	define RADEON_COLOR_ARG_C_CURRENT_COLOR		(2 << 10)
#	define RADEON_COLOR_ARG_C_CURRENT_ALPHA		(3 << 10)
#	define RADEON_COLOR_ARG_C_DIFFUSE_COLOR		(4 << 10)
#	define RADEON_COLOR_ARG_C_DIFFUSE_ALPHA		(5 << 10)
#	define RADEON_COLOR_ARG_C_SPECULAR_COLOR	(6 << 10)
#	define RADEON_COLOR_ARG_C_SPECULAR_ALPHA	(7 << 10)
#	define RADEON_COLOR_ARG_C_TFACTOR_COLOR		(8 << 10)
#	define RADEON_COLOR_ARG_C_TFACTOR_ALPHA		(9 << 10)
#	define RADEON_COLOR_ARG_C_T0_COLOR		(10 << 10)
#	define RADEON_COLOR_ARG_C_T0_ALPHA		(11 << 10)
#	define RADEON_COLOR_ARG_C_T1_COLOR		(12 << 10)
#	define RADEON_COLOR_ARG_C_T1_ALPHA		(13 << 10)
#	define RADEON_COLOR_ARG_C_T2_COLOR		(14 << 10)
#	define RADEON_COLOR_ARG_C_T2_ALPHA		(15 << 10)
#	define RADEON_COLOR_ARG_C_T3_COLOR		(16 << 10)
#	define RADEON_COLOR_ARG_C_T3_ALPHA		(17 << 10)
#	define RADEON_COMP_ARG_A			(1 << 15)
#	define RADEON_COMP_ARG_A_SHIFT			15
#	define RADEON_COMP_ARG_B			(1 << 16)
#	define RADEON_COMP_ARG_B_SHIFT			16
#	define RADEON_COMP_ARG_C			(1 << 17)
#	define RADEON_COMP_ARG_C_SHIFT			17
#	define RADEON_BLEND_CTL_MASK			(7 << 18)
#	define RADEON_BLEND_CTL_ADD			(0 << 18)
#	define RADEON_BLEND_CTL_SUBTRACT		(1 << 18)
#	define RADEON_BLEND_CTL_ADDSIGNED		(2 << 18)
#	define RADEON_BLEND_CTL_BLEND			(3 << 18)
#	define RADEON_BLEND_CTL_DOT3			(4 << 18)
#	define RADEON_SCALE_SHIFT			21
#	define RADEON_SCALE_MASK			(3 << 21)
#	define RADEON_SCALE_1X				(0 << 21)
#	define RADEON_SCALE_2X				(1 << 21)
#	define RADEON_SCALE_4X				(2 << 21)
#	define RADEON_CLAMP_TX				(1 << 23)
#	define RADEON_T0_EQ_TCUR			(1 << 24)
#	define RADEON_T1_EQ_TCUR			(1 << 25)
#	define RADEON_T2_EQ_TCUR			(1 << 26)
#	define RADEON_T3_EQ_TCUR			(1 << 27)
#	define RADEON_COLOR_ARG_MASK			0x1f
#	define RADEON_COMP_ARG_SHIFT			15
#define RADEON_PP_TXABLEND_0                0x1c64
#define RADEON_PP_TXABLEND_1                0x1c7c
#define RADEON_PP_TXABLEND_2                0x1c94
#	define RADEON_ALPHA_ARG_A_SHIFT			0
#	define RADEON_ALPHA_ARG_A_MASK			(0xf << 0)
#	define RADEON_ALPHA_ARG_A_ZERO			(0 << 0)
#	define RADEON_ALPHA_ARG_A_CURRENT_ALPHA		(1 << 0)
#	define RADEON_ALPHA_ARG_A_DIFFUSE_ALPHA		(2 << 0)
#	define RADEON_ALPHA_ARG_A_SPECULAR_ALPHA	(3 << 0)
#	define RADEON_ALPHA_ARG_A_TFACTOR_ALPHA		(4 << 0)
#	define RADEON_ALPHA_ARG_A_T0_ALPHA		(5 << 0)
#	define RADEON_ALPHA_ARG_A_T1_ALPHA		(6 << 0)
#	define RADEON_ALPHA_ARG_A_T2_ALPHA		(7 << 0)
#	define RADEON_ALPHA_ARG_A_T3_ALPHA		(8 << 0)
#	define RADEON_ALPHA_ARG_B_SHIFT			4
#	define RADEON_ALPHA_ARG_B_MASK			(0xf << 4)
#	define RADEON_ALPHA_ARG_B_ZERO			(0 << 4)
#	define RADEON_ALPHA_ARG_B_CURRENT_ALPHA		(1 << 4)
#	define RADEON_ALPHA_ARG_B_DIFFUSE_ALPHA		(2 << 4)
#	define RADEON_ALPHA_ARG_B_SPECULAR_ALPHA	(3 << 4)
#	define RADEON_ALPHA_ARG_B_TFACTOR_ALPHA		(4 << 4)
#	define RADEON_ALPHA_ARG_B_T0_ALPHA		(5 << 4)
#	define RADEON_ALPHA_ARG_B_T1_ALPHA		(6 << 4)
#	define RADEON_ALPHA_ARG_B_T2_ALPHA		(7 << 4)
#	define RADEON_ALPHA_ARG_B_T3_ALPHA		(8 << 4)
#	define RADEON_ALPHA_ARG_C_SHIFT			8
#	define RADEON_ALPHA_ARG_C_MASK			(0xf << 8)
#	define RADEON_ALPHA_ARG_C_ZERO			(0 << 8)
#	define RADEON_ALPHA_ARG_C_CURRENT_ALPHA		(1 << 8)
#	define RADEON_ALPHA_ARG_C_DIFFUSE_ALPHA		(2 << 8)
#	define RADEON_ALPHA_ARG_C_SPECULAR_ALPHA	(3 << 8)
#	define RADEON_ALPHA_ARG_C_TFACTOR_ALPHA		(4 << 8)
#	define RADEON_ALPHA_ARG_C_T0_ALPHA		(5 << 8)
#	define RADEON_ALPHA_ARG_C_T1_ALPHA		(6 << 8)
#	define RADEON_ALPHA_ARG_C_T2_ALPHA		(7 << 8)
#	define RADEON_ALPHA_ARG_C_T3_ALPHA		(8 << 8)
#	define RADEON_DOT_ALPHA_DONT_REPLICATE		(1 << 9)
#	define RADEON_ALPHA_ARG_MASK			0xf

#define RADEON_PP_TFACTOR_0                 0x1c68
#define RADEON_PP_TFACTOR_1                 0x1c80
#define RADEON_PP_TFACTOR_2                 0x1c98

#define RADEON_RB3D_BLENDCNTL               0x1c20
#       define RADEON_COMB_FCN_ADD_CLAMP               (0  << 12)
#       define RADEON_COMB_FCN_ADD_NOCLAMP             (1  << 12)
#       define RADEON_COMB_FCN_SUB_CLAMP               (2  << 12)
#       define RADEON_COMB_FCN_SUB_NOCLAMP             (3  << 12)
#       define RADEON_SRC_BLEND_GL_ZERO                (32 << 16)
#       define RADEON_SRC_BLEND_GL_ONE                 (33 << 16)
#       define RADEON_SRC_BLEND_GL_SRC_COLOR           (34 << 16)
#       define RADEON_SRC_BLEND_GL_ONE_MINUS_SRC_COLOR (35 << 16)
#       define RADEON_SRC_BLEND_GL_DST_COLOR           (36 << 16)
#       define RADEON_SRC_BLEND_GL_ONE_MINUS_DST_COLOR (37 << 16)
#       define RADEON_SRC_BLEND_GL_SRC_ALPHA           (38 << 16)
#       define RADEON_SRC_BLEND_GL_ONE_MINUS_SRC_ALPHA (39 << 16)
#       define RADEON_SRC_BLEND_GL_DST_ALPHA           (40 << 16)
#       define RADEON_SRC_BLEND_GL_ONE_MINUS_DST_ALPHA (41 << 16)
#       define RADEON_SRC_BLEND_GL_SRC_ALPHA_SATURATE  (42 << 16)
#       define RADEON_SRC_BLEND_MASK                   (63 << 16)
#       define RADEON_DST_BLEND_GL_ZERO                (32 << 24)
#       define RADEON_DST_BLEND_GL_ONE                 (33 << 24)
#       define RADEON_DST_BLEND_GL_SRC_COLOR           (34 << 24)
#       define RADEON_DST_BLEND_GL_ONE_MINUS_SRC_COLOR (35 << 24)
#       define RADEON_DST_BLEND_GL_DST_COLOR           (36 << 24)
#       define RADEON_DST_BLEND_GL_ONE_MINUS_DST_COLOR (37 << 24)
#       define RADEON_DST_BLEND_GL_SRC_ALPHA           (38 << 24)
#       define RADEON_DST_BLEND_GL_ONE_MINUS_SRC_ALPHA (39 << 24)
#       define RADEON_DST_BLEND_GL_DST_ALPHA           (40 << 24)
#       define RADEON_DST_BLEND_GL_ONE_MINUS_DST_ALPHA (41 << 24)
#       define RADEON_DST_BLEND_MASK                   (63 << 24)
#define RADEON_RB3D_CNTL                    0x1c3c
#       define RADEON_ALPHA_BLEND_ENABLE       (1  <<  0)
#       define RADEON_PLANE_MASK_ENABLE        (1  <<  1)
#       define RADEON_DITHER_ENABLE            (1  <<  2)
#       define RADEON_ROUND_ENABLE             (1  <<  3)
#       define RADEON_SCALE_DITHER_ENABLE      (1  <<  4)
#       define RADEON_DITHER_INIT              (1  <<  5)
#       define RADEON_ROP_ENABLE               (1  <<  6)
#       define RADEON_STENCIL_ENABLE           (1  <<  7)
#       define RADEON_Z_ENABLE                 (1  <<  8)
#       define RADEON_DEPTH_XZ_OFFEST_ENABLE   (1  <<  9)
#       define RADEON_COLOR_FORMAT_ARGB1555    (3  << 10)
#       define RADEON_COLOR_FORMAT_RGB565      (4  << 10)
#       define RADEON_COLOR_FORMAT_ARGB8888    (6  << 10)
#       define RADEON_COLOR_FORMAT_RGB332      (7  << 10)
#       define RADEON_COLOR_FORMAT_Y8          (8  << 10)
#       define RADEON_COLOR_FORMAT_RGB8        (9  << 10)
#       define RADEON_COLOR_FORMAT_YUV12       (10 << 10)
#       define RADEON_COLOR_FORMAT_aYUV444     (14 << 10)
#       define RADEON_COLOR_FORMAT_ARGB4444    (15 << 10)
#       define RADEON_CLRCMP_FLIP_ENABLE       (1  << 14)
#       define RADEON_ZBLOCK8                  (0  << 15)
#       define RADEON_ZBLOCK16                 (1  << 15)
#define RADEON_RB3D_COLOROFFSET             0x1c40
#       define RADEON_COLOROFFSET_MASK      0xfffffff0
#define RADEON_RB3D_COLORPITCH              0x1c48
#       define RADEON_COLORPITCH_MASK         0x000001ff8
#       define RADEON_COLOR_TILE_ENABLE       (1 << 16)
#       define RADEON_COLOR_MICROTILE_ENABLE  (1 << 17)
#       define RADEON_COLOR_ENDIAN_NO_SWAP    (0 << 18)
#       define RADEON_COLOR_ENDIAN_WORD_SWAP  (1 << 18)
#       define RADEON_COLOR_ENDIAN_DWORD_SWAP (2 << 18)
#define RADEON_RB3D_DEPTHOFFSET             0x1c24
#define RADEON_RB3D_DEPTHPITCH              0x1c28
#       define RADEON_DEPTHPITCH_MASK         0x00001ff8
#       define RADEON_DEPTH_ENDIAN_NO_SWAP    (0 << 18)
#       define RADEON_DEPTH_ENDIAN_WORD_SWAP  (1 << 18)
#       define RADEON_DEPTH_ENDIAN_DWORD_SWAP (2 << 18)
#define RADEON_RB3D_PLANEMASK               0x1d84
#define RADEON_RB3D_ROPCNTL                 0x1d80
#define RADEON_RB3D_STENCILREFMASK          0x1d7c
#       define RADEON_STENCIL_REF_SHIFT       0
#       define RADEON_STENCIL_MASK_SHIFT      16
#       define RADEON_STENCIL_WRITEMASK_SHIFT 24
#define RADEON_RB3D_ZSTENCILCNTL            0x1c2c
#       define RADEON_DEPTH_FORMAT_MASK          (0xf << 0)
#       define RADEON_DEPTH_FORMAT_16BIT_INT_Z   (0  <<  0)
#       define RADEON_DEPTH_FORMAT_24BIT_INT_Z   (2  <<  0)
#       define RADEON_DEPTH_FORMAT_24BIT_FLOAT_Z (3  <<  0)
#       define RADEON_DEPTH_FORMAT_32BIT_INT_Z   (4  <<  0)
#       define RADEON_DEPTH_FORMAT_32BIT_FLOAT_Z (5  <<  0)
#       define RADEON_DEPTH_FORMAT_16BIT_FLOAT_W (7  <<  0)
#       define RADEON_DEPTH_FORMAT_24BIT_FLOAT_W (9  <<  0)
#       define RADEON_DEPTH_FORMAT_32BIT_FLOAT_W (11 <<  0)
#       define RADEON_Z_TEST_NEVER               (0  <<  4)
#       define RADEON_Z_TEST_LESS                (1  <<  4)
#       define RADEON_Z_TEST_LEQUAL              (2  <<  4)
#       define RADEON_Z_TEST_EQUAL               (3  <<  4)
#       define RADEON_Z_TEST_GEQUAL              (4  <<  4)
#       define RADEON_Z_TEST_GREATER             (5  <<  4)
#       define RADEON_Z_TEST_NEQUAL              (6  <<  4)
#       define RADEON_Z_TEST_ALWAYS              (7  <<  4)
#       define RADEON_Z_TEST_MASK                (7  <<  4)
#       define RADEON_HIERARCHICAL_Z_ENABLE      (1  <<  8)
#       define RADEON_STENCIL_TEST_NEVER         (0  << 12)
#       define RADEON_STENCIL_TEST_LESS          (1  << 12)
#       define RADEON_STENCIL_TEST_LEQUAL        (2  << 12)
#       define RADEON_STENCIL_TEST_EQUAL         (3  << 12)
#       define RADEON_STENCIL_TEST_GEQUAL        (4  << 12)
#       define RADEON_STENCIL_TEST_GREATER       (5  << 12)
#       define RADEON_STENCIL_TEST_NEQUAL        (6  << 12)
#       define RADEON_STENCIL_TEST_ALWAYS        (7  << 12)
#       define RADEON_STENCIL_S_FAIL_KEEP        (0  << 16)
#       define RADEON_STENCIL_S_FAIL_ZERO        (1  << 16)
#       define RADEON_STENCIL_S_FAIL_REPLACE     (2  << 16)
#       define RADEON_STENCIL_S_FAIL_INC         (3  << 16)
#       define RADEON_STENCIL_S_FAIL_DEC         (4  << 16)
#       define RADEON_STENCIL_S_FAIL_INVERT      (5  << 16)
#       define RADEON_STENCIL_ZPASS_KEEP         (0  << 20)
#       define RADEON_STENCIL_ZPASS_ZERO         (1  << 20)
#       define RADEON_STENCIL_ZPASS_REPLACE      (2  << 20)
#       define RADEON_STENCIL_ZPASS_INC          (3  << 20)
#       define RADEON_STENCIL_ZPASS_DEC          (4  << 20)
#       define RADEON_STENCIL_ZPASS_INVERT       (5  << 20)
#       define RADEON_STENCIL_ZFAIL_KEEP         (0  << 20)
#       define RADEON_STENCIL_ZFAIL_ZERO         (1  << 20)
#       define RADEON_STENCIL_ZFAIL_REPLACE      (2  << 20)
#       define RADEON_STENCIL_ZFAIL_INC          (3  << 20)
#       define RADEON_STENCIL_ZFAIL_DEC          (4  << 20)
#       define RADEON_STENCIL_ZFAIL_INVERT       (5  << 20)
#       define RADEON_Z_COMPRESSION_ENABLE       (1  << 28)
#       define RADEON_FORCE_Z_DIRTY              (1  << 29)
#       define RADEON_Z_WRITE_ENABLE             (1  << 30)
#       define RADEON_Z_DECOMPRESSION_ENABLE     (1  << 31)
#define RADEON_RE_LINE_PATTERN              0x1cd0
#       define RADEON_LINE_PATTERN_MASK             0x0000ffff
#       define RADEON_LINE_REPEAT_COUNT_SHIFT       16
#       define RADEON_LINE_PATTERN_START_SHIFT      24
#       define RADEON_LINE_PATTERN_LITTLE_BIT_ORDER (0 << 28)
#       define RADEON_LINE_PATTERN_BIG_BIT_ORDER    (1 << 28)
#       define RADEON_LINE_PATTERN_AUTO_RESET       (1 << 29)
#define RADEON_RE_LINE_STATE                0x1cd4
#       define RADEON_LINE_CURRENT_PTR_SHIFT   0
#       define RADEON_LINE_CURRENT_COUNT_SHIFT 8
#define RADEON_RE_MISC                      0x26c4
#       define RADEON_STIPPLE_COORD_MASK       0x1f
#       define RADEON_STIPPLE_X_OFFSET_SHIFT   0
#       define RADEON_STIPPLE_X_OFFSET_MASK    (0x1f << 0)
#       define RADEON_STIPPLE_Y_OFFSET_SHIFT   8
#       define RADEON_STIPPLE_Y_OFFSET_MASK    (0x1f << 8)
#       define RADEON_STIPPLE_LITTLE_BIT_ORDER (0 << 16)
#       define RADEON_STIPPLE_BIG_BIT_ORDER    (1 << 16)
#define RADEON_RE_SOLID_COLOR               0x1c1c
#define RADEON_RE_TOP_LEFT                  0x26c0
#       define RADEON_RE_LEFT_SHIFT         0
#       define RADEON_RE_TOP_SHIFT          16
#define RADEON_RE_WIDTH_HEIGHT              0x1c44
#       define RADEON_RE_WIDTH_SHIFT        0
#       define RADEON_RE_HEIGHT_SHIFT       16

#define RADEON_SE_CNTL                      0x1c4c
#       define RADEON_FFACE_CULL_CW          (0 <<  0)
#       define RADEON_FFACE_CULL_CCW         (1 <<  0)
#       define RADEON_FFACE_CULL_DIR_MASK    (1 <<  0)
#       define RADEON_BFACE_CULL             (0 <<  1)
#       define RADEON_BFACE_SOLID            (3 <<  1)
#       define RADEON_FFACE_CULL             (0 <<  3)
#       define RADEON_FFACE_SOLID            (3 <<  3)
#       define RADEON_FFACE_CULL_MASK        (3 <<  3)
#       define RADEON_BADVTX_CULL_DISABLE    (1 <<  5)
#       define RADEON_FLAT_SHADE_VTX_0       (0 <<  6)
#       define RADEON_FLAT_SHADE_VTX_1       (1 <<  6)
#       define RADEON_FLAT_SHADE_VTX_2       (2 <<  6)
#       define RADEON_FLAT_SHADE_VTX_LAST    (3 <<  6)
#       define RADEON_DIFFUSE_SHADE_SOLID    (0 <<  8)
#       define RADEON_DIFFUSE_SHADE_FLAT     (1 <<  8)
#       define RADEON_DIFFUSE_SHADE_GOURAUD  (2 <<  8)
#       define RADEON_DIFFUSE_SHADE_MASK     (3 <<  8)
#       define RADEON_ALPHA_SHADE_SOLID      (0 << 10)
#       define RADEON_ALPHA_SHADE_FLAT       (1 << 10)
#       define RADEON_ALPHA_SHADE_GOURAUD    (2 << 10)
#       define RADEON_ALPHA_SHADE_MASK       (3 << 10)
#       define RADEON_SPECULAR_SHADE_SOLID   (0 << 12)
#       define RADEON_SPECULAR_SHADE_FLAT    (1 << 12)
#       define RADEON_SPECULAR_SHADE_GOURAUD (2 << 12)
#       define RADEON_SPECULAR_SHADE_MASK    (3 << 12)
#       define RADEON_FOG_SHADE_SOLID        (0 << 14)
#       define RADEON_FOG_SHADE_FLAT         (1 << 14)
#       define RADEON_FOG_SHADE_GOURAUD      (2 << 14)
#       define RADEON_FOG_SHADE_MASK         (3 << 14)
#       define RADEON_ZBIAS_ENABLE_POINT     (1 << 16)
#       define RADEON_ZBIAS_ENABLE_LINE      (1 << 17)
#       define RADEON_ZBIAS_ENABLE_TRI       (1 << 18)
#       define RADEON_WIDELINE_ENABLE        (1 << 20)
#       define RADEON_VPORT_XY_XFORM_ENABLE  (1 << 24)
#       define RADEON_VPORT_Z_XFORM_ENABLE   (1 << 25)
#       define RADEON_VTX_PIX_CENTER_D3D     (0 << 27)
#       define RADEON_VTX_PIX_CENTER_OGL     (1 << 27)
#       define RADEON_ROUND_MODE_TRUNC       (0 << 28)
#       define RADEON_ROUND_MODE_ROUND       (1 << 28)
#       define RADEON_ROUND_MODE_ROUND_EVEN  (2 << 28)
#       define RADEON_ROUND_MODE_ROUND_ODD   (3 << 28)
#       define RADEON_ROUND_PREC_16TH_PIX    (0 << 30)
#       define RADEON_ROUND_PREC_8TH_PIX     (1 << 30)
#       define RADEON_ROUND_PREC_4TH_PIX     (2 << 30)
#       define RADEON_ROUND_PREC_HALF_PIX    (3 << 30)
#define RADEON_SE_CNTL_STATUS               0x2140
#       define RADEON_VC_NO_SWAP            (0 << 0)
#       define RADEON_VC_16BIT_SWAP         (1 << 0)
#       define RADEON_VC_32BIT_SWAP         (2 << 0)
#       define RADEON_VC_HALF_DWORD_SWAP    (3 << 0)
#       define RADEON_TCL_BYPASS            (1 << 8)
#define RADEON_SE_COORD_FMT                 0x15c0
#       define RADEON_VTX_XY_PRE_MULT_1_OVER_W0  (1 <<  0)
#       define RADEON_VTX_Z_PRE_MULT_1_OVER_W0   (1 <<  1)
#       define RADEON_VTX_ST0_NONPARAMETRIC      (1 <<  8)
#       define RADEON_VTX_ST1_NONPARAMETRIC      (1 <<  9)
#       define RADEON_VTX_ST2_NONPARAMETRIC      (1 << 10)
#       define RADEON_VTX_ST3_NONPARAMETRIC      (1 << 11)
#       define RADEON_VTX_W0_NORMALIZE           (1 << 12)
#       define RADEON_VTX_W0_IS_NOT_1_OVER_W0    (1 << 16)
#       define RADEON_VTX_ST0_PRE_MULT_1_OVER_W0 (1 << 17)
#       define RADEON_VTX_ST1_PRE_MULT_1_OVER_W0 (1 << 19)
#       define RADEON_VTX_ST2_PRE_MULT_1_OVER_W0 (1 << 21)
#       define RADEON_VTX_ST3_PRE_MULT_1_OVER_W0 (1 << 23)
#       define RADEON_TEX1_W_ROUTING_USE_W0      (0 << 26)
#       define RADEON_TEX1_W_ROUTING_USE_Q1      (1 << 26)
#define RADEON_SE_LINE_WIDTH                0x1db8
#define RADEON_SE_TCL_LIGHT_MODEL_CTL       0x226c
#define RADEON_SE_TCL_MATERIAL_AMBIENT_RED     0x2220
#define RADEON_SE_TCL_MATERIAL_AMBIENT_GREEN   0x2224
#define RADEON_SE_TCL_MATERIAL_AMBIENT_BLUE    0x2228
#define RADEON_SE_TCL_MATERIAL_AMBIENT_ALPHA   0x222c
#define RADEON_SE_TCL_MATERIAL_DIFFUSE_RED     0x2230
#define RADEON_SE_TCL_MATERIAL_DIFFUSE_GREEN   0x2234
#define RADEON_SE_TCL_MATERIAL_DIFFUSE_BLUE    0x2238
#define RADEON_SE_TCL_MATERIAL_DIFFUSE_ALPHA   0x223c
#define RADEON_SE_TCL_MATERIAL_EMMISSIVE_RED   0x2210
#define RADEON_SE_TCL_MATERIAL_EMMISSIVE_GREEN 0x2214
#define RADEON_SE_TCL_MATERIAL_EMMISSIVE_BLUE  0x2218
#define RADEON_SE_TCL_MATERIAL_EMMISSIVE_ALPHA 0x221c
#define RADEON_SE_TCL_MATERIAL_SPECULAR_RED    0x2240
#define RADEON_SE_TCL_MATERIAL_SPECULAR_GREEN  0x2244
#define RADEON_SE_TCL_MATERIAL_SPECULAR_BLUE   0x2248
#define RADEON_SE_TCL_MATERIAL_SPECULAR_ALPHA  0x224c
#define RADEON_SE_TCL_MATRIX_SELECT_0       0x225c
#define RADEON_SE_TCL_MATRIX_SELECT_1       0x2260
#define RADEON_SE_TCL_OUTPUT_VTX_FMT        0x2254
#define RADEON_SE_TCL_OUTPUT_VTX_SEL        0x2258
#define RADEON_SE_TCL_PER_LIGHT_CTL_0       0x2270
#define RADEON_SE_TCL_PER_LIGHT_CTL_1       0x2274
#define RADEON_SE_TCL_PER_LIGHT_CTL_2       0x2278
#define RADEON_SE_TCL_PER_LIGHT_CTL_3       0x227c
#define RADEON_SE_TCL_SHININESS             0x2250
#define RADEON_SE_TCL_TEXTURE_PROC_CTL      0x2268
#define RADEON_SE_TCL_UCP_VERT_BLEND_CTL    0x2264
#define RADEON_SE_VPORT_XSCALE              0x1d98
#define RADEON_SE_VPORT_XOFFSET             0x1d9c
#define RADEON_SE_VPORT_YSCALE              0x1da0
#define RADEON_SE_VPORT_YOFFSET             0x1da4
#define RADEON_SE_VPORT_ZSCALE              0x1da8
#define RADEON_SE_VPORT_ZOFFSET             0x1dac

				/* Registers for CP and Microcode Engine */
#define RADEON_CP_ME_RAM_ADDR               0x07d4
#define RADEON_CP_ME_RAM_RADDR              0x07d8
#define RADEON_CP_ME_RAM_DATAH              0x07dc
#define RADEON_CP_ME_RAM_DATAL              0x07e0

#define RADEON_CP_RB_BASE                   0x0700
#define RADEON_CP_RB_CNTL                   0x0704
#define RADEON_CP_RB_RPTR_ADDR              0x070c
#define RADEON_CP_RB_RPTR                   0x0710
#define RADEON_CP_RB_WPTR                   0x0714

#define RADEON_CP_IB_BASE                   0x0738
#define RADEON_CP_IB_BUFSZ                  0x073c

#define RADEON_CP_CSQ_CNTL                  0x0740
#       define RADEON_CSQ_CNT_PRIMARY_MASK  (0xff << 0)
#       define RADEON_CSQ_PRIDIS_INDDIS     (0    << 28)
#       define RADEON_CSQ_PRIPIO_INDDIS     (1    << 28)
#       define RADEON_CSQ_PRIBM_INDDIS      (2    << 28)
#       define RADEON_CSQ_PRIPIO_INDBM      (3    << 28)
#       define RADEON_CSQ_PRIBM_INDBM       (4    << 28)
#       define RADEON_CSQ_PRIPIO_INDPIO     (15   << 28)
#define RADEON_CP_CSQ_STAT                  0x07f8
#       define RADEON_CSQ_RPTR_PRIMARY_MASK  (0xff <<  0)
#       define RADEON_CSQ_WPTR_PRIMARY_MASK  (0xff <<  8)
#       define RADEON_CSQ_RPTR_INDIRECT_MASK (0xff << 16)
#       define RADEON_CSQ_WPTR_INDIRECT_MASK (0xff << 24)
#define RADEON_CP_CSQ_ADDR                  0x07f0
#define RADEON_CP_CSQ_DATA                  0x07f4
#define RADEON_CP_CSQ_APER_PRIMARY          0x1000
#define RADEON_CP_CSQ_APER_INDIRECT         0x1300

#define RADEON_CP_RB_WPTR_DELAY             0x0718
#       define RADEON_PRE_WRITE_TIMER_SHIFT      0
#       define RADEON_PRE_WRITE_LIMIT_SHIFT     23

#define RADEON_AIC_CNTL                     0x01d0
#       define RADEON_PCIGART_TRANSLATE_EN  (1 << 0)

				/* Constants */
#define RADEON_AGP_TEX_OFFSET               0x02000000

#define RADEON_LAST_FRAME_REG               RADEON_GUI_SCRATCH_REG0
#define RADEON_LAST_CLEAR_REG               RADEON_GUI_SCRATCH_REG2

				/* CP packet types */
#define RADEON_CP_PACKET0                           0x00000000
#define RADEON_CP_PACKET1                           0x40000000
#define RADEON_CP_PACKET2                           0x80000000
#define RADEON_CP_PACKET3                           0xC0000000
#       define RADEON_CP_PACKET_MASK                0xC0000000
#       define RADEON_CP_PACKET_COUNT_MASK          0x3fff0000
#       define RADEON_CP_PACKET_MAX_DWORDS          (1 << 12)
#       define RADEON_CP_PACKET0_REG_MASK           0x000007ff
#       define RADEON_CP_PACKET1_REG0_MASK          0x000007ff
#       define RADEON_CP_PACKET1_REG1_MASK          0x003ff800

#define RADEON_CP_PACKET0_ONE_REG_WR                0x00008000

#define RADEON_CP_PACKET3_NOP                       0xC0001000
#define RADEON_CP_PACKET3_NEXT_CHAR                 0xC0001900
#define RADEON_CP_PACKET3_PLY_NEXTSCAN              0xC0001D00
#define RADEON_CP_PACKET3_SET_SCISSORS              0xC0001E00
#define RADEON_CP_PACKET3_3D_RNDR_GEN_INDX_PRIM     0xC0002300
#define RADEON_CP_PACKET3_LOAD_MICROCODE            0xC0002400
#define RADEON_CP_PACKET3_3D_RNDR_GEN_PRIM          0xC0002500
#define RADEON_CP_PACKET3_WAIT_FOR_IDLE             0xC0002600
#define RADEON_CP_PACKET3_3D_DRAW_VBUF              0xC0002800
#define RADEON_CP_PACKET3_3D_DRAW_IMMD              0xC0002900
#define RADEON_CP_PACKET3_3D_DRAW_INDX              0xC0002A00
#define RADEON_CP_PACKET3_LOAD_PALETTE              0xC0002C00
#define RADEON_CP_PACKET3_3D_LOAD_VBPNTR            0xC0002F00
#define RADEON_CP_PACKET3_3D_CLEAR_ZMASK            0xC0003200
#define RADEON_CP_PACKET3_CNTL_PAINT                0xC0009100
#define RADEON_CP_PACKET3_CNTL_BITBLT               0xC0009200
#define RADEON_CP_PACKET3_CNTL_SMALLTEXT            0xC0009300
#define RADEON_CP_PACKET3_CNTL_HOSTDATA_BLT         0xC0009400
#define RADEON_CP_PACKET3_CNTL_POLYLINE             0xC0009500
#define RADEON_CP_PACKET3_CNTL_POLYSCANLINES        0xC0009800
#define RADEON_CP_PACKET3_CNTL_PAINT_MULTI          0xC0009A00
#define RADEON_CP_PACKET3_CNTL_BITBLT_MULTI         0xC0009B00
#define RADEON_CP_PACKET3_CNTL_TRANS_BITBLT         0xC0009C00


#define RADEON_CP_VC_FRMT_XY                        0x00000000
#define RADEON_CP_VC_FRMT_W0                        0x00000001
#define RADEON_CP_VC_FRMT_FPCOLOR                   0x00000002
#define RADEON_CP_VC_FRMT_FPALPHA                   0x00000004
#define RADEON_CP_VC_FRMT_PKCOLOR                   0x00000008
#define RADEON_CP_VC_FRMT_FPSPEC                    0x00000010
#define RADEON_CP_VC_FRMT_FPFOG                     0x00000020
#define RADEON_CP_VC_FRMT_PKSPEC                    0x00000040
#define RADEON_CP_VC_FRMT_ST0                       0x00000080
#define RADEON_CP_VC_FRMT_ST1                       0x00000100
#define RADEON_CP_VC_FRMT_Q1                        0x00000200
#define RADEON_CP_VC_FRMT_ST2                       0x00000400
#define RADEON_CP_VC_FRMT_Q2                        0x00000800
#define RADEON_CP_VC_FRMT_ST3                       0x00001000
#define RADEON_CP_VC_FRMT_Q3                        0x00002000
#define RADEON_CP_VC_FRMT_Q0                        0x00004000
#define RADEON_CP_VC_FRMT_BLND_WEIGHT_CNT_MASK      0x00038000
#define RADEON_CP_VC_FRMT_N0                        0x00040000
#define RADEON_CP_VC_FRMT_XY1                       0x08000000
#define RADEON_CP_VC_FRMT_Z1                        0x10000000
#define RADEON_CP_VC_FRMT_W1                        0x20000000
#define RADEON_CP_VC_FRMT_N1                        0x40000000
#define RADEON_CP_VC_FRMT_Z                         0x80000000

#define RADEON_CP_VC_CNTL_PRIM_TYPE_NONE            0x00000000
#define RADEON_CP_VC_CNTL_PRIM_TYPE_POINT           0x00000001
#define RADEON_CP_VC_CNTL_PRIM_TYPE_LINE            0x00000002
#define RADEON_CP_VC_CNTL_PRIM_TYPE_LINE_STRIP      0x00000003
#define RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_LIST        0x00000004
#define RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_FAN         0x00000005
#define RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_STRIP       0x00000006
#define RADEON_CP_VC_CNTL_PRIM_TYPE_TRI_TYPE2       0x00000007
#define RADEON_CP_VC_CNTL_PRIM_TYPE_RECT_LIST       0x00000008
#define RADEON_CP_VC_CNTL_PRIM_TYPE_3VRT_POINT_LIST 0x00000009
#define RADEON_CP_VC_CNTL_PRIM_TYPE_3VRT_LINE_LIST  0x0000000a
#define RADEON_CP_VC_CNTL_PRIM_WALK_IND             0x00000010
#define RADEON_CP_VC_CNTL_PRIM_WALK_LIST            0x00000020
#define RADEON_CP_VC_CNTL_PRIM_WALK_RING            0x00000030
#define RADEON_CP_VC_CNTL_COLOR_ORDER_BGRA          0x00000000
#define RADEON_CP_VC_CNTL_COLOR_ORDER_RGBA          0x00000040
#define RADEON_CP_VC_CNTL_MAOS_ENABLE               0x00000080
#define RADEON_CP_VC_CNTL_VTX_FMT_NON_RADEON_MODE   0x00000000
#define RADEON_CP_VC_CNTL_VTX_FMT_RADEON_MODE       0x00000100
#define RADEON_CP_VC_CNTL_NUM_SHIFT                 16

#endif
