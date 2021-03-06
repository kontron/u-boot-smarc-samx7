/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2012-2018 Kontron Europe GmbH
 *
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/mx6-pins.h>
#include <asm/arch/crm_regs.h>
#include <asm/mach-imx/iomux-v3.h>
#include <ipu_pixfmt.h>
#include <asm/gpio.h>
#include <spi.h>
#include <spi_flash.h>
#include <splash.h>
#include <env.h>

#include "amx6_iomux.h"

#define GATE_UNGATE_CLOCKS
#undef PATCH_FOR_CLOCKS

#define PFD_528_CLK			528 			/* [MHz] */
#define PFD_528_CLK_MUL			18
#define PFD_528_CLK_DIV_LOW		12
#define PFD_528_CLK_DIV_HI		35
#define LVDS_CLK_MUL			7

/* calculate PLL2 PFD0_FRAC */
#define PFD_528_DIVIDER(_LVDS_CLK_)								\
	(PFD_528_CLK * PFD_528_CLK_MUL / LVDS_CLK_MUL)/(_LVDS_CLK_)

struct display_info_t {
	int	bus;
	int	addr;
	int	pixfmt;
	int	(*detect)(struct display_info_t const *dev);
	void	(*enable)(struct display_info_t const *dev);
	struct	fb_videomode mode;
	int lvds_clock;
};

static int detect_default(struct display_info_t const *dev)
{
	return 1;
}

iomux_v3_cfg_t backlight_pads[] = {
	IOMUX_PADS(PAD_SD1_CMD__GPIO1_IO18 | MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_SD1_DAT0__GPIO1_IO16 | MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_SD1_DAT1__GPIO1_IO17 | MUX_PAD_CTRL(GPIO_PAD_CTRL)),
};

static void enable_backlight(void)
{
	SETUP_IOMUX_PADS(backlight_pads);

	gpio_request(IMX_GPIO_NR(1, 18), "LCD Backlight PWM");
	gpio_direction_output(IMX_GPIO_NR(1, 18), 1);
	gpio_request(IMX_GPIO_NR(1, 16), "LCD Backlight Enable");
	gpio_direction_output(IMX_GPIO_NR(1, 16), 1);
	gpio_request(IMX_GPIO_NR(1, 17), "LCD VDD Enable");
	gpio_direction_output(IMX_GPIO_NR(1, 17), 1);
}

static void enable_lvds(struct display_info_t const *dev)
{
	u32 reg;
	int pfd_frac_div = PFD_528_CLK_DIV_HI;
	struct iomuxc *iomux = (struct iomuxc *)IOMUXC_BASE_ADDR;
	struct anatop_regs *anatop = (struct anatop_regs *)ANATOP_BASE_ADDR;
	ulong lvds_clk = dev->lvds_clock;

	/* setup_display(dev->lvds_clock); */
	/* Clock value validation */
	if (lvds_clk > 0) {
		pfd_frac_div = PFD_528_DIVIDER(lvds_clk);
		if (pfd_frac_div < PFD_528_CLK_DIV_LOW) {
			pfd_frac_div = PFD_528_CLK_DIV_LOW;
		} else if (pfd_frac_div > PFD_528_CLK_DIV_HI) {
			pfd_frac_div = PFD_528_CLK_DIV_HI;
		}
	} else {
		pfd_frac_div = PFD_528_CLK_DIV_HI;
	}

	/* set PLL2 PFD0_FRAC according to expected LVDS clock value */
	writel(ANATOP_PFD_FRAC_MASK(0), &anatop->pfd_528_clr);
	writel(pfd_frac_div<<ANATOP_PFD_FRAC_SHIFT(0), &anatop->pfd_528_set);


	reg = readl(&iomux->gpr[2]) | IOMUXC_GPR2_DATA_WIDTH_CH0_24BIT;
	writel(reg, &iomux->gpr[2]);

	enable_backlight();
}

static struct splash_location amx6_splash_locations[] = {
	{
		.name = "sf",
		.storage = SPLASH_STORAGE_SF,
		.flags = SPLASH_STORAGE_RAW,
		.offset = 0x100000,
	},
	{
		.name = "mmc",
		.storage = SPLASH_STORAGE_MMC,
		.flags = SPLASH_STORAGE_FS,
		.devpart = "2:1"
	},
	{
		.name = "sd",
		.storage = SPLASH_STORAGE_MMC,
		.flags = SPLASH_STORAGE_FS,
		.devpart = "1:1"
	},
	{
		.name = "sata",
		.storage = SPLASH_STORAGE_SATA,
		.flags = SPLASH_STORAGE_FS,
		.devpart = "0:1"
	},
};

int splash_screen_prepare(void)
{
	return splash_source_load(amx6_splash_locations,
				  ARRAY_SIZE(amx6_splash_locations));
}

static struct display_info_t displays[] = {{
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_800x480@LVDS",
		.refresh        = 60,
		.xres           = 800,
		.yres           = 480,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 32
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_320x240@LVDS",
		.refresh        = 60,
		.xres           = 320,
		.yres           = 240,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 32
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_480x272@LVDS",
		.refresh        = 60,
		.xres           = 480,
		.yres           = 272,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 32
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_480x320@LVDS",
		.refresh        = 60,
		.xres           = 480,
		.yres           = 320,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 32
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_640x480@LVDS",
		.refresh        = 60,
		.xres           = 640,
		.yres           = 480,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 32
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_800x600@LVDS",
		.refresh        = 60,
		.xres           = 800,
		.yres           = 600,
		.pixclock       = 25000, /* 40.0 MHz */
		.left_margin    = 88,
		.right_margin   = 40,
		.upper_margin   = 23,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 4,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 40
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_960x640@LVDS",
		.refresh        = 60,
		.xres           = 960,
		.yres           = 640,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 32
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1024x576@LVDS",
		.refresh        = 60,
		.xres           = 1024,
		.yres           = 576,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 72
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1024x600@LVDS",
		.refresh        = 60,
		.xres           = 1024,
		.yres           = 600,
		.pixclock       = 19531, /* 51.2 MHz */
		.left_margin    = 160,
		.right_margin   = 24,
		.upper_margin   = 28,
		.lower_margin   = 3,
		.hsync_len      = 136,
		.vsync_len      = 4,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 51
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1024x768@LVDS",
		.refresh        = 60,
		.xres           = 1024,
		.yres           = 768,
		.pixclock       = 15385, /* 64.9 MHz */
		.left_margin    = 160,
		.right_margin   = 24,
		.upper_margin   = 29,
		.lower_margin   = 3,
		.hsync_len      = 136,
		.vsync_len      = 6,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 65
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1152x768@LVDS",
		.refresh        = 60,
		.xres           = 1152,
		.yres           = 768,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 72
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1152x864@LVDS",
		.refresh        = 60,
		.xres           = 1152,
		.yres           = 864,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 72
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1280x720@LVDS",
		.refresh        = 60,
		.xres           = 1280,
		.yres           = 720,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 72
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1280x768@LVDS",
		.refresh        = 60,
		.xres           = 1280,
		.yres           = 768,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 72
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1280x800@LVDS",
		.refresh        = 60,
		.xres           = 1280,
		.yres           = 800,
		.pixclock       = 14085, /* 71.0 MHz */
		.left_margin    = 80,
		.right_margin   = 48,
		.upper_margin   = 14,
		.lower_margin   = 2,
		.hsync_len      = 32,
		.vsync_len      = 6,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 71
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1280x1024@LVDS",
		.refresh        = 50,
		.xres           = 1280,
		.yres           = 1024,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 72
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1360x768@LVDS",
		.refresh        = 50,
		.xres           = 1360,
		.yres           = 768,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 72
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "LCD_1366x768@LVDS",
		.refresh        = 50,
		.xres           = 1366,
		.yres           = 768,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 72
}, {
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds,
	.mode	= {
		.name           = "user",
		.refresh        = 60,
		.xres           = 800,
		.yres           = 480,
		.pixclock       = 15385,
		.left_margin    = 100,
		.right_margin   = 60,
		.upper_margin   = 20,
		.lower_margin   = 3,
		.hsync_len      = 128,
		.vsync_len      = 2,
		.sync           = FB_SYNC_EXT,
		.vmode          = FB_VMODE_NONINTERLACED
	},
	.lvds_clock = 32
} };


int board_video_init(void)
{
	int i;
	int ret;
	char const *panel = env_get("panel");
	ulong lvds_clk = env_get_ulong("panel_lvds_clk", 10, 0);
	ulong pixclk = env_get_ulong("panel_pixclk", 10, 0);
	ulong x_res = env_get_ulong("panel_x_res", 10, 0);
	ulong y_res = env_get_ulong("panel_y_res", 10, 0);

	if (!panel) {
		for (i = 0; i < ARRAY_SIZE(displays); i++) {
			struct display_info_t const *dev = displays+i;
			if (dev->detect(dev)) {
				panel = dev->mode.name;
				debug("auto-detected panel %s\n", panel);
				break;
			}
		}
		if (!panel) {
			panel = displays[0].mode.name;
			debug("No panel detected: default to %s\n", panel);
		}
	} else {
		for (i = 0; i < ARRAY_SIZE(displays); i++) {
			if (!strcmp(panel, displays[i].mode.name)) {
				/* User defined parameters */
				if (lvds_clk > 0) {
					printf("LVDS clock %ld found in environment, "
					       "overriding panel value %d\n",
					       lvds_clk, displays[i].lvds_clock);
					displays[i].lvds_clock = lvds_clk;
				}
				if (pixclk > 0) {
					printf("Pixelclock %ld found in environment, "
					       "overriding panel value %d\n",
					       pixclk, displays[i].mode.pixclock);
					displays[i].mode.pixclock = pixclk;
				}
				/* Resolution can be adjusted only in "user" mode */
				if (!strcmp(panel, "user")) {
					if (x_res > 0)
						displays[i].mode.xres = x_res;
					if (y_res > 0)
						displays[i].mode.yres = y_res;
				}
				break;
			}
		}
	}
	if (i < ARRAY_SIZE(displays)) {
		ret = ipuv3_fb_init(&displays[i].mode, 0,
				    displays[i].pixfmt);
		if (!ret) {
			displays[i].enable(displays+i);
			printf("Display: %s (Resolution: %ux%u [px], LVDS clk %d [MHz])\n",
				displays[i].mode.name,
				displays[i].mode.xres,
				displays[i].mode.yres,
				displays[i].lvds_clock);
		} else
			printf("Display: %s cannot be configured: %d\n",
				displays[i].mode.name, ret);
	} else {
		if (strcmp(panel, "off")) {
			printf("Display: %s - unsupported panel\n", panel);
			printf("List of supported panels :\n");
			for (i = 0; i < ARRAY_SIZE(displays); i++) {
				printf("\t%s%s", displays[i].mode.name, i == 0 ? " (default)\n" : "\n");
			}
		} else {
			printf("Display: disabled\n");
		}
		return -EINVAL;
	}

	return ret;
}

int board_video_skip(void)
{
	static int init=0, skip;

	if (!init) {
		/* Always load splashimage from SPI Flash to RAM */
		/* env_set_addr("splashimage", (const void*)CONFIG_SPLASH_IMG_ADDR); */
		/* splash_load_from_spi(); */
		skip = board_video_init();
		init = 1;
	}
	return (skip);
}

void setup_display(void)
{
	struct mxc_ccm_reg *mxc_ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;
	struct anatop_regs *anatop = (struct anatop_regs *)ANATOP_BASE_ADDR;
	struct iomuxc *iomux = (struct iomuxc *)IOMUXC_BASE_ADDR;

	int reg;

	enable_ipu_clock();

	/* Turn on LDB0, LDB1, IPU,IPU DI0 clocks */
	reg = readl(&mxc_ccm->CCGR3);
	reg |= MXC_CCM_CCGR3_IPU1_IPU_MASK | MXC_CCM_CCGR3_LDB_DI0_MASK;
	writel(reg, &mxc_ccm->CCGR3);

	/* set LDB0, LDB1 clk derive from PLL2 PFD0 clock wich value is 271,5 MHz */

#ifdef GATE_UNGATE_CLOCKS
	/*
	 * gate/ungate the source clocks before changing the output clock of the mux
	 * necessary according to CPU manual
	 */
	debug ("gate/ungate active\n");

	writel(0x80, &anatop->pfd_528_clr);
	writel(0x80, &anatop->pfd_528_set);
#endif

	select_ldb_di_clock_source(MXC_PLL2_PFD0_CLK);

#ifdef PATCH_FOR_CLOCKS
	/*
	 * In some situations the display clock did not start up correctly
	 * Imported the following patch from Linux:
	 * http://git.freescale.com/git/cgit.cgi/imx/linux-2.6-
	 * imx.git/commit/?h=imx_3.10.17_1.0.0_ga&id=eecbe9a52587cf9eec30132fb9b8a6761f3a1e6d
	 */
	debug ("WA1 active\n");

	/* Set MMDC_CH1 mask bit */
	reg = readl(&mxc_ccm->ccdr); /* ccm_base + 0x4 */
	reg |= (1 << 16);
	writel(reg, &mxc_ccm->ccdr);

	/*
	 * Set the periph2_clk_sel to the top mux so that
	 * mmdc_ch1 is from pll3_sw_clk.
	 */
	reg = readl(&mxc_ccm->cbcdr); /* ccm_base + 0x14 */
	reg |= (1 << 26);
	writel(reg, &mxc_ccm->cbcdr);

	/* wait for the clock switch */
	while (readl(&mxc_ccm->cdhipr)); /* ccm_base + 0x48 */

	/* Disable pll3_sw_clk by selection the bypass clock source */
	reg = readl(&mxc_ccm->ccsr); /* ccm_base + 0xC */
	reg |= 1 << 0;
	writel(reg, &mxc_ccm->ccsr);
#endif

	/* set LDB0, LDB1 clk select to 011/011 */
	reg = readl(&mxc_ccm->cs2cdr);
	reg &= ~(MXC_CCM_CS2CDR_LDB_DI0_CLK_SEL_MASK
		 | MXC_CCM_CS2CDR_LDB_DI1_CLK_SEL_MASK);
	reg |= (1 << MXC_CCM_CS2CDR_LDB_DI0_CLK_SEL_OFFSET)
	      | (1 << MXC_CCM_CS2CDR_LDB_DI1_CLK_SEL_OFFSET);
	writel(reg, &mxc_ccm->cs2cdr);

	reg = readl(&mxc_ccm->cscmr2);
	reg |= MXC_CCM_CSCMR2_LDB_DI0_IPU_DIV;
	writel(reg, &mxc_ccm->cscmr2);

	reg = readl(&mxc_ccm->chsccdr);
	reg &= ~(MXC_CCM_CHSCCDR_IPU1_DI0_PRE_CLK_SEL_MASK
		| MXC_CCM_CHSCCDR_IPU1_DI0_PODF_MASK
		| MXC_CCM_CHSCCDR_IPU1_DI0_CLK_SEL_MASK);
	reg |= (CHSCCDR_CLK_SEL_LDB_DI0
		<< MXC_CCM_CHSCCDR_IPU1_DI0_CLK_SEL_OFFSET)
	       | (CHSCCDR_PODF_DIVIDE_BY_3
		  << MXC_CCM_CHSCCDR_IPU1_DI0_PODF_OFFSET)
	       | (CHSCCDR_IPU_PRE_CLK_540M_PFD
		  << MXC_CCM_CHSCCDR_IPU1_DI0_PRE_CLK_SEL_OFFSET);
	writel(reg, &mxc_ccm->chsccdr);

#ifdef PATCH_FOR_CLOCKS
	debug ("WA1 active\n");
	/* Unbypass pll3_sw_clk */
	reg = readl(&mxc_ccm->ccsr);  /* ccm_base + 0xC */
	reg &= ~(1 << 0);
	writel(reg, &mxc_ccm->ccsr);

	/*
	 * Set the periph2_clk_sel back to the bootom mux so that
	 * mmdc_ch1 is from its original parent.
	 */
	reg = readl(&mxc_ccm->cbcdr); /* ccm_base + 0x14 */
	reg &= ~(1 << 26);
	writel(reg, &mxc_ccm->cbcdr);

	/* wait for the clock switch */
	while (readl(&mxc_ccm->cdhipr)); /* ccm_base + 0x48 */

	/* Clear MMDC_CH1 mask bit */
	reg = readl(&mxc_ccm->ccdr); /* ccm_base + 0x4 */
	reg &= ~(1 << 16);
	writel(reg, &mxc_ccm->ccdr);
#endif

#ifdef GATE_UNGATE_CLOCKS
	/*
	 * gate/ungate the source clocks before changing the output clock of the mux
	 * necessary according to CPU manual
	 */
	debug ("WA2 active\n");

	/* set PFD0_CLKGATE to 0 to ungate PFD0 */
	writel(0x80,&anatop->pfd_528_clr);
	writel(0, &anatop->pfd_528_set);
#endif

	reg = IOMUXC_GPR2_BGREF_RRMODE_EXTERNAL_RES
	     |IOMUXC_GPR2_DI1_VS_POLARITY_ACTIVE_HIGH
	     |IOMUXC_GPR2_DI0_VS_POLARITY_ACTIVE_LOW
	     |IOMUXC_GPR2_BIT_MAPPING_CH1_SPWG
	     |IOMUXC_GPR2_DATA_WIDTH_CH1_18BIT
	     |IOMUXC_GPR2_BIT_MAPPING_CH0_SPWG
	     |IOMUXC_GPR2_DATA_WIDTH_CH0_18BIT
	     |IOMUXC_GPR2_LVDS_CH1_MODE_DISABLED
	     |IOMUXC_GPR2_LVDS_CH0_MODE_ENABLED_DI0;
	writel(reg, &iomux->gpr[2]);

	reg = readl(&iomux->gpr[3]);
	reg = (reg & ~(IOMUXC_GPR3_LVDS0_MUX_CTL_MASK
		      | IOMUXC_GPR3_HDMI_MUX_CTL_MASK))
	    | (IOMUXC_GPR3_MUX_SRC_IPU1_DI0
	       << IOMUXC_GPR3_LVDS0_MUX_CTL_OFFSET);
	writel(reg, &iomux->gpr[3]);
}
