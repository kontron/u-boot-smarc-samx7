/*
 * Copyright (C) 2017 Kontron Europe GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/mx7-pins.h>
#include <asm/arch/sys_proto.h>
#include <asm/gpio.h>
#include <asm/imx-common/iomux-v3.h>
#include <asm/io.h>
#include <linux/sizes.h>
#include <common.h>
#include <fsl_esdhc.h>
#include <fdt_support.h>
#include <mmc.h>
#include <miiphy.h>
#include <netdev.h>
#include <power/pmic.h>
#include <power/pfuze3000_pmic.h>
#include <i2c.h>
#include <environment.h>
#include <search.h>
#include <asm/imx-common/mxc_i2c.h>
#include <asm/arch/crm_regs.h>
#include <usb.h>
#include <usb/ehci-ci.h>
#include <dm.h>
#include <dm/platform_data/serial_mxc.h>
#include <version.h>

/* #include "../common/emb_vpd.h" */
#include "../common/emb_eep.h"


extern void BOARD_InitPins(void);
extern void BOARD_FixupPins(void);
extern void hsic_1p2_regulator_out(void);
extern void use_pwm1_out_as_gpio(void);
/* extern void snvs_lpgpr_set(uint32_t); */

extern int EMB_EEP_I2C_EEPROM_BUS_NUM_1;

DECLARE_GLOBAL_DATA_PTR;

#define I2C_PAD_CTRL    (PAD_CTL_DSE_3P3V_32OHM | PAD_CTL_SRE_SLOW | \
	PAD_CTL_HYS | PAD_CTL_PUE | PAD_CTL_PUS_PU100KOHM)


#ifdef CONFIG_SYS_I2C_MXC
/* from ICMC: #define I2C_PAD MUX_PAD_CTRL(0x0001F858) */
#define I2C_PAD MUX_PAD_CTRL(I2C_PAD_CTRL)
/* I2C1 for PMIC */
static struct i2c_pads_info i2c_pad_info1 = {
	.scl = {
		.i2c_mode = MX7D_PAD_UART1_RX_DATA__I2C1_SCL | I2C_PAD,
		.gpio_mode = MX7D_PAD_UART1_RX_DATA__GPIO4_IO0 | I2C_PAD,
		.gp = IMX_GPIO_NR(4, 0),
	},
	.sda = {
		.i2c_mode = MX7D_PAD_UART1_TX_DATA__I2C1_SDA | I2C_PAD,
		.gpio_mode = MX7D_PAD_UART1_TX_DATA__GPIO4_IO1 | I2C_PAD,
		.gp = IMX_GPIO_NR(4, 1),
	},
};

/* I2C2 */
static struct i2c_pads_info i2c_pad_info2 = {
	.scl = {
		.i2c_mode = MX7D_PAD_I2C2_SCL__I2C2_SCL | I2C_PAD,
		.gpio_mode = MX7D_PAD_I2C2_SCL__GPIO4_IO10 | I2C_PAD,
		.gp = IMX_GPIO_NR(4, 10)
	},
	.sda = {
		.i2c_mode = MX7D_PAD_I2C2_SDA__I2C2_SDA | I2C_PAD,
		.gpio_mode = MX7D_PAD_I2C2_SDA__GPIO4_IO11 | I2C_PAD,
		.gp = IMX_GPIO_NR(4, 11)
	}
};

/* I2C3 */
static struct i2c_pads_info i2c_pad_info3 = {
	.scl = {
		.i2c_mode = MX7D_PAD_I2C3_SCL__I2C3_SCL | I2C_PAD,
		.gpio_mode = MX7D_PAD_I2C3_SCL__GPIO4_IO12 | I2C_PAD,
		.gp = IMX_GPIO_NR(4, 12)
	},
	.sda = {
		.i2c_mode = MX7D_PAD_I2C3_SDA__I2C3_SDA | I2C_PAD,
		.gpio_mode = MX7D_PAD_I2C3_SDA__GPIO4_IO13 | I2C_PAD,
		.gp = IMX_GPIO_NR(4, 13)
	}
};

static struct i2c_pads_info i2c_pad_info4 = {
	.scl = {
		.i2c_mode = MX7D_PAD_LCD_DATA22__I2C4_SCL | I2C_PAD,
		.gpio_mode = MX7D_PAD_LCD_DATA22__GPIO3_IO27 | I2C_PAD,
		.gp = IMX_GPIO_NR(3, 27)
	},
	.sda = {
		.i2c_mode = MX7D_PAD_LCD_DATA23__I2C4_SDA | I2C_PAD,
		.gpio_mode = MX7D_PAD_LCD_DATA23__GPIO3_IO28 | I2C_PAD,
		.gp = IMX_GPIO_NR(3, 28)
	}
};

#endif

int board_spi_cs_gpio(unsigned bus, unsigned cs)
{
	if ((bus == 2) && (cs == 0))
		return IMX_GPIO_NR(6, 22);

	if ((bus == 2) && (cs == 2))
		return IMX_GPIO_NR(5, 9);

	return -1;
}

int dram_init(void)
{
	if (is_cpu_type(MXC_CPU_MX7D))
		gd->ram_size = SZ_2G;
	else if (is_cpu_type(MXC_CPU_MX7S))
		gd->ram_size = SZ_1G;

	return 0;
}

#if 0
static iomux_v3_cfg_t const usb_otg1_pads[] = {
	MX7D_PAD_GPIO1_IO05__USB_OTG1_PWR | MUX_PAD_CTRL(NO_PAD_CTRL),
};

static iomux_v3_cfg_t const usb_otg2_pads[] = {
	MX7D_PAD_UART3_CTS_B__USB_OTG2_PWR | MUX_PAD_CTRL(NO_PAD_CTRL),
};
#endif

#ifdef CONFIG_VIDEO_MXS
static int setup_lcd(void)
{
	/* Reset LCD */
	gpio_direction_output(IMX_GPIO_NR(3, 4) , 0);
	udelay(500);
	gpio_direction_output(IMX_GPIO_NR(3, 4) , 1);

	/* Set Brightness to high */
	gpio_direction_output(IMX_GPIO_NR(1, 1) , 1);

	return 0;
}
#endif

#ifdef CONFIG_FSL_ESDHC

#define USDHC1_CD_GPIO	IMX_GPIO_NR(5, 0)
#define USDHC1_PWR_GPIO	IMX_GPIO_NR(5, 2)
#define USDHC3_PWR_GPIO IMX_GPIO_NR(6, 11)

#define USDHC_PRES_STATE 0x24
#define USDHC_PRES_STATE_CINST_SHIFT 16

struct fsl_esdhc_cfg usdhc_cfg[2] = {
	{USDHC1_BASE_ADDR},
	{USDHC3_BASE_ADDR},
};

int board_mmc_getcd(struct mmc *mmc)
{
	struct fsl_esdhc_cfg *cfg = (struct fsl_esdhc_cfg *)mmc->priv;
	int ret = 0;

	switch (cfg->esdhc_base) {
	case USDHC1_BASE_ADDR:
		ret = esdhc_read32(cfg->esdhc_base+USDHC_PRES_STATE) &
		       (1<<USDHC_PRES_STATE_CINST_SHIFT) ? 1 : 0;
		break;
	case USDHC3_BASE_ADDR:
		ret = 1; /* Assume uSDHC3 emmc is always present */
		break;
	}

	return ret;
}

int board_mmc_init(bd_t *bis)
{
	int i, ret;
	/*
	 * According to the board_mmc_init() the following map is done:
	 * (U-Boot device node)    (Physical Port)
	 * mmc0                    USDHC1
	 * mmc2                    USDHC3 (eMMC)
	 */
	for (i = 0; i < CONFIG_SYS_FSL_USDHC_NUM; i++) {
		switch (i) {
		case 0:
			gpio_request(USDHC1_CD_GPIO, "usdhc1_cd");
			gpio_direction_input(USDHC1_CD_GPIO);
			gpio_request(USDHC1_PWR_GPIO, "usdhc1_pwr");
			gpio_direction_output(USDHC1_PWR_GPIO, 0);
			udelay(500);
			gpio_direction_output(USDHC1_PWR_GPIO, 1);
			usdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC_CLK);
			break;
		case 1:
			gpio_request(USDHC3_PWR_GPIO, "usdhc3_pwr");
			gpio_direction_output(USDHC3_PWR_GPIO, 0);
			udelay(500);
			gpio_direction_output(USDHC3_PWR_GPIO, 1);
			usdhc_cfg[1].sdhc_clk = mxc_get_clock(MXC_ESDHC3_CLK);
			break;
		default:
			printf("Warning: you configured more USDHC controllers"
				"(%d) than supported by the board\n", i + 1);
			return -EINVAL;
		}

		ret = fsl_esdhc_initialize(bis, &usdhc_cfg[i]);
		if (ret)
			return ret;
	}

	return 0;
}
#endif /* CONFIG_FSL_ESDHC */

#ifdef CONFIG_FEC_MXC
int board_eth_init(bd_t *bis)
{
	int ret;
	struct mxc_ccm_anatop_reg *ccm_anatop
	    = (struct mxc_ccm_anatop_reg *) ANATOP_BASE_ADDR;

	/* enable lvds output buffer for anaclk1, select 0x12 = pll_enet_div40 (25MHz) */
	setbits_le32(&ccm_anatop->clk_misc0, 0x20 | CCM_ANALOG_CLK_MISC0_LVDS1_CLK_SEL(0x12));
	udelay(10);

	/* remove PHY reset */
	gpio_direction_output(IMX_GPIO_NR(3, 21), 1);

	/* FEC0 is connected to PHY#0 */
	ret = fecmxc_initialize_multi(bis, 0, 0, IMX_FEC_BASE);
	if (ret)
		printf("FEC0 MXC: %s:failed\n", __func__);

	if (is_cpu_type(MXC_CPU_MX7D)) {
		/* FEC1 is connected to PHY#1 */
		ret = fecmxc_initialize_multi(bis, 1, 1, IMX_FEC_BASE);
		if (ret)
			printf("FEC1 MXC: %s:failed\n", __func__);
	}

	return ret;
}

static int setup_fec(void)
{
	struct iomuxc_gpr_base_regs *const iomuxc_gpr_regs
		= (struct iomuxc_gpr_base_regs *) IOMUXC_GPR_BASE_ADDR;

	/* Use 125M anatop REF_CLK1 for ENET1 and ENET2, clear gpr1[13], gpr1[17] */
	clrsetbits_le32(&iomuxc_gpr_regs->gpr[1],
		(IOMUXC_GPR_GPR1_GPR_ENET1_TX_CLK_SEL_MASK |
		 IOMUXC_GPR_GPR1_GPR_ENET2_TX_CLK_SEL_MASK |
		 IOMUXC_GPR_GPR1_GPR_ENET1_CLK_DIR_MASK    |
		 IOMUXC_GPR_GPR1_GPR_ENET2_CLK_DIR_MASK), 0);

	return set_clk_enet(ENET_125MHz);
}


int board_phy_config(struct phy_device *phydev)
{
	/*
	 * TBD: check if we can remove this as these registers are
	 *      not used on SMX7 Marvell 88E1510 PHYs.
	 */
	/* enable rgmii rxc skew and phy mode select to RGMII copper */
	phy_write(phydev, MDIO_DEVAD_NONE, 0x1e, 0x21);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x1f, 0x7ea8);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x1e, 0x2f);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x1f, 0x71b7);

	/* adapt LED settings */
	phy_write(phydev, MDIO_DEVAD_NONE, 0x16, 0x03);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x10, 0x157);
	phy_write(phydev, MDIO_DEVAD_NONE, 0x16, 0x00);

	if (phydev->drv->config)
		phydev->drv->config(phydev);
	return 0;
}
#endif

int board_qspi_init(void)
{
	/* Set the clock */
	set_clk_qspi();

	return 0;
}

int board_early_init_f(void)
{
	BOARD_InitPins();
	BOARD_FixupPins();

	setup_i2c(0, CONFIG_SYS_MXC_I2C1_SPEED, 0x7f, &i2c_pad_info1);
	setup_i2c(1, CONFIG_SYS_MXC_I2C2_SPEED, 0x7f, &i2c_pad_info2);
	setup_i2c(2, CONFIG_SYS_MXC_I2C3_SPEED, 0x7f, &i2c_pad_info3);
	setup_i2c(3, CONFIG_SYS_MXC_I2C4_SPEED, 0x7f, &i2c_pad_info4);

#if defined(CONFIG_KEX_ARM_PLL_SPEED) && defined(CONFIG_SPL_BUILD)
	/* increase CPU speed only in SPL and only on dual modules */
	u32 reg, div_sel;
	struct mxc_ccm_anatop_reg *ccm_anatop
	    = (struct mxc_ccm_anatop_reg *) ANATOP_BASE_ADDR;

	if (is_cpu_type(MXC_CPU_MX7D)) {
		/* read ARM PLL control register and mask divider bits */
		reg = readl(&ccm_anatop->pll_arm) & 0xffffff80;
		/* assume 24MHz input osc frequency */
		div_sel = (CONFIG_KEX_ARM_PLL_SPEED*2)/24;
		/* set divider field */
		reg |= div_sel;
		writel(reg, &ccm_anatop->pll_arm);
	}
#endif

#if 0
	imx_iomux_v3_setup_multiple_pads(usb_otg1_pads,
					 ARRAY_SIZE(usb_otg1_pads));
	imx_iomux_v3_setup_multiple_pads(usb_otg2_pads,
					 ARRAY_SIZE(usb_otg2_pads));
#endif

	return 0;
}

int board_init(void)
{
	/* address of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

#ifdef CONFIG_FEC_MXC
	setup_fec();
#endif

#ifdef CONFIG_VIDEO_MXS
	/* setup_lcd(); */
#endif

#ifdef CONFIG_FSL_QSPI
	board_qspi_init();
#endif

#ifdef CONFIG_MXC_SPI
       /* setup_spi(); */
#endif

	return 0;
}

#define GPC_PGC_HSIC            0xd00
#define GPC_PGC_CPU_MAPPING     0xec
#define GPC_PU_PGC_SW_PUP_REQ   0xf8
#define BM_CPU_PGC_SW_PDN_PUP_REQ_USB_HSIC_PHY 0x10
#define USB_HSIC_PHY_A7_DOMAIN  0x40

static int imx_set_usb_hsic_power(void)
{
	u32 reg;
	u32 val;

	writel(1, GPC_IPS_BASE_ADDR + GPC_PGC_HSIC);

	reg = GPC_IPS_BASE_ADDR + GPC_PGC_CPU_MAPPING;
	val = readl(reg);
	val |= USB_HSIC_PHY_A7_DOMAIN;
	writel(val, reg);

	hsic_1p2_regulator_out();

	reg = GPC_IPS_BASE_ADDR + GPC_PU_PGC_SW_PUP_REQ;
	val = readl(reg);
	val |= BM_CPU_PGC_SW_PDN_PUP_REQ_USB_HSIC_PHY;
	writel(val, reg);

	while ((readl(reg) &
		BM_CPU_PGC_SW_PDN_PUP_REQ_USB_HSIC_PHY) != 0)
		;

	writel(0, GPC_IPS_BASE_ADDR + GPC_PGC_HSIC);

	return 0;
}

#define CONFIG_KEX_USBHUB_I2C_ADDR 0x2d

static int attach_usb_hub(void)
{
	uint8_t usbattach_cmd[] = {0xaa, 0x55, 0x00};

	/* reset USBHUB */
	gpio_direction_output(IMX_GPIO_NR(1, 0), 0);
	udelay(1000);
	/* remove USBHUB reset */
	gpio_direction_output(IMX_GPIO_NR(1, 0), 1);
	udelay(250000);

	i2c_set_bus_num(1);
	if (i2c_probe(CONFIG_KEX_USBHUB_I2C_ADDR)) {
		printf("USBHUB not found\n");
		return 0;
	}
	i2c_write(CONFIG_KEX_USBHUB_I2C_ADDR, 0, 0, usbattach_cmd, 3);

	return 0;
}

int board_ehci_hcd_init(int port)
{
	debug("%s: port = %d\n", __func__, port);
	if (port == 2) {
		attach_usb_hub();
	}

	return 0;
}

static void set_boot_sel(void)
{
	int boot_sel;

	/* Get the state of the Boot Select pins */
	gpio_direction_input(IMX_GPIO_NR(3, 24));	/* BOOT SEL 0 */
	gpio_direction_input(IMX_GPIO_NR(3, 25));	/* BOOT SEL 1 */
	gpio_direction_input(IMX_GPIO_NR(3, 26));	/* BOOT SEL 2 */

	boot_sel = gpio_get_value(IMX_GPIO_NR(3, 24)) & 0x1;
	boot_sel |= (gpio_get_value(IMX_GPIO_NR(3, 25)) & 0x1) << 1;
	boot_sel |= (gpio_get_value(IMX_GPIO_NR(3, 26)) & 0x1) << 2;

	/*
	 * Jumper settings per SMARC Spec
	 *
	 *   BOOT_SEL2#    BOOT_SEL1#    BOOT_SEL0# Boot Source
	 * 0  	GND           GND           GND        Carrier SATA
	 * 1	GND           GND           Float      Carrier SD Card
	 * 2	GND           Float         GND        Carrier eMMC Flash
	 * 3	GND           Float         Float      Carrier SPI
	 * 4	Float         GND           GND        Module device (NAND, NOR) - vendor specific
	 * 5	Float         GND           Float      Remote boot (GBE, serial) - vendor specific
	 * 6	Float         Float         GND        Module eMMC Flash
	 * 7	Float         Float         Float      Module SPI
	 */

	switch (boot_sel) {
		case 0:
			setenv("boot_sel", "carrier_sata");
			break;
		case 1:
			setenv("boot_sel", "carrier_sd");
			break;
		case 2:
			setenv("boot_sel", "carrier_mmc");
			break;
		case 3:
			setenv("boot_sel", "carrier_spi");
			break;
		case 4:
			setenv("boot_sel", "module_device");
			break;
		case 5:
			setenv("boot_sel", "remote");
			break;
		case 6:
			setenv("boot_sel", "module_mmc");
			break;
		case 7:
			setenv("boot_sel", "module_spi");
			break;
	}
}

int misc_init_r(void)
{
	attach_usb_hub();
	imx_set_usb_hsic_power();
	set_boot_sel();

#ifdef CONFIG_EMB_EEP_SPI
	emb_vpd_init_r();
#endif

#ifdef CONFIG_EMB_EEP_I2C_EEPROM
	EMB_EEP_I2C_EEPROM_BUS_NUM_1 = CONFIG_EMB_EEP_I2C_EEPROM_BUS_NUM_EE1;
	if (is_cpu_type(MXC_CPU_MX7D))
		emb_eep_init_r (1, 1, 2); /* import 2 MAC addresses */
	if (is_cpu_type(MXC_CPU_MX7S))
		emb_eep_init_r (1, 1, 1); /* import 1 MAC address */
#endif

	/* set PCIE present signal according to environment settings */
	if (is_cpu_type(MXC_CPU_MX7D)) {
		if (getenv_yesno("pcie_a_prsnt"))
			gpio_direction_output(IMX_GPIO_NR(3,16), 0);
		else
			gpio_direction_output(IMX_GPIO_NR(3,16), 1);

		if (getenv_yesno("pcie_b_prsnt"))
			gpio_direction_output(IMX_GPIO_NR(3,22), 0);
		else
			gpio_direction_output(IMX_GPIO_NR(3,22), 1);

		if (getenv_yesno("pcie_c_prsnt"))
			gpio_direction_output(IMX_GPIO_NR(6,15), 0);
		else
			gpio_direction_output(IMX_GPIO_NR(6,15), 1);
	}

	/* fix IOMUX configuration of PWM1_OUT for use as GPIO line if variable set */
	if (getenv_yesno("pwm_out_disable"))
		use_pwm1_out_as_gpio();

	setenv ("core_variant", "unknown");
	if (is_cpu_type(MXC_CPU_MX7D))
		setenv ("core_variant", "d");
	if (is_cpu_type(MXC_CPU_MX7S))
		setenv ("core_variant", "s");

	/* snvs_lpgpr_set(0x12345678); */

	/* init GPIO lines to ground */
	gpio_direction_output(IMX_GPIO_NR(1,8), 0);	/* GPIO5: PWM_OUT */
	gpio_direction_output(IMX_GPIO_NR(3,5), 0);	/* GPIO0: CAM0_PWR */
	gpio_direction_output(IMX_GPIO_NR(3,6), 0);	/* GPIO1: CAM1_PWR */
	gpio_direction_output(IMX_GPIO_NR(3,7), 0);	/* GPIO2: CAM0_RST */
	gpio_direction_output(IMX_GPIO_NR(3,8), 0);	/* GPIO3: CAM1_RST */
	gpio_direction_output(IMX_GPIO_NR(3,9), 0);	/* GPIO4: HDA_RST */
	gpio_direction_output(IMX_GPIO_NR(3,10), 0);	/* GPIO6: TACHIN */
	gpio_direction_output(IMX_GPIO_NR(3,11), 0);	/* GPIO7 */
	gpio_direction_output(IMX_GPIO_NR(3,12), 0);	/* GPIO8 */
	gpio_direction_output(IMX_GPIO_NR(4,4), 0);	/* GPIO9 */
	gpio_direction_output(IMX_GPIO_NR(4,5), 0);	/* GPIO10 */
	gpio_direction_output(IMX_GPIO_NR(3,15), 0);	/* GPIO11 */

	return 0;
}

int board_late_init(void)
{
#ifndef CONFIG_SPL_BUILD
	ulong board_rev;

	board_rev = getenv_ulong("board_rev", 10, 1);
	if (board_rev == 0) {
		u32 reg;
		struct mxc_ccm_anatop_reg *ccm_anatop
		    = (struct mxc_ccm_anatop_reg *) ANATOP_BASE_ADDR;

		if (is_cpu_type(MXC_CPU_MX7D)) {
			/* read ARM PLL control register and mask divider bits */
			reg = readl(&ccm_anatop->pll_arm) & 0xffffff80;
			/* set default divider field for 792 MHz */
			reg |= 66;
			writel(reg, &ccm_anatop->pll_arm);
			printf("\n!!! Board revision 0 detected, setting CPU speed to 792 MHz !!!\n\n");
		}

	}
#if defined(CONFIG_KEX_EEP_BOOTCOUNTER)
	emb_eep_update_bootcounter(1);
#endif
#endif
	return 0;
}

int checkboard(void)
{
	printf("Board: Kontron SMX7 SMARC 2.0 Module\n");

	return 0;
}

#if defined(CONFIG_OF_BOARD_SETUP)
const char ft_version_string[] = U_BOOT_VERSION_STRING;

int ft_board_setup(void *blob, bd_t *bd)
{
	int err;
	int nodeoffset;
	int create = 1;
	char *name;
	char str_mem_type[] = "memory-type";
	char str_mem_freq[] = "memory-frequency";
	char str_pwm1[] = "/soc/aips-bus@30400000/pwm@30660000";
	char str_ok[] = "okay";

	u64 freq = mxc_get_clock(MXC_ARM_CLK);
	phys_addr_t base = getenv_bootm_low();
	phys_size_t size = getenv_bootm_size();

	debug("/memory device tree settings: base=0x%08x, size=0x%08x\n",
	      (u32)base, (u32)size);
	fdt_fixup_memory(blob, (u64)base, (u64)size);
	nodeoffset = fdt_find_or_add_subnode(blob, 0, "memory");
	if (nodeoffset < 0)
		return 1;

	/*
	 * increase DT size to add sufficient space for additional properties
	 */
	fdt_increase_size(blob, 0x100);
	name = str_mem_type;
	err = fdt_find_and_setprop(blob, "/memory", name, "DDR3",
	                           sizeof("DDR3"), 1);
	if (err < 0)
		goto err;

	name = str_mem_freq;
	err = fdt_setprop_u64(blob, nodeoffset, name, freq);
	if (err < 0)
		goto err;

	printf("bootloader version: %s\n", ft_version_string);
	err = fdt_find_and_setprop(blob, "/chosen", "u-boot,version",
	                     ft_version_string,
	                     sizeof(ft_version_string), create);

	if (err<0)
		goto err;

	/* check pwm_out_disable and enable pwm if needed */
	if (!getenv_yesno("pwm_out_disable")) {
		fdt_find_and_setprop(blob, "/pwm-fan", "status",
		                     str_ok, sizeof(str_ok), 0);
		fdt_find_and_setprop(blob, str_pwm1, "status",
		                     str_ok, sizeof(str_ok), 0);
	}

	return 0;

err:
	printf("Could not set %s property to memory node: %s\n",
	       name, fdt_strerror(err));

	return 1;
}
#endif /* CONFIG_OF_BOARD_SETUP */

static struct mxc_serial_platdata mxc_serial_plat = {
	.reg = (struct mxc_uart *)CONFIG_MXC_UART_BASE,
	.use_dte = true,
	.use_rtscts = true,
};

U_BOOT_DEVICE(mxc_serial) = {
	.name = "serial_mxc",
	.platdata = &mxc_serial_plat,
};

#ifdef CONFIG_CMD_KBOARDINFO
/* board infos */

char *getSerNo (void)
{
	ENTRY e;
	static ENTRY *ep;

	e.key = "serial#";
	e.data = NULL;
	hsearch_r (e, FIND, &ep, &env_htab, 0);
	if (ep == NULL)
		return "na";
	else
		return ep->data;
}

/* try to fetch identnumber */
char *getSapId (int eeprom_num)
{
	return (emb_eep_find_string_in_dmi(eeprom_num, 2, 5));
}

char *getManufacturer (int eeprom_num)
{
	return (emb_eep_find_string_in_dmi(eeprom_num, 2, 1));
}

char *getProductName (int eeprom_num)
{
	return (emb_eep_find_string_in_dmi(eeprom_num, 2, 2));
}

char *getManufacturerDate (int eeprom_num)
{
	return (emb_eep_find_string_in_dmi(eeprom_num, 160, 2));
}

char *getRevision (int eeprom_num)
{
	return (emb_eep_find_string_in_dmi(eeprom_num, 2, 3));
}

char *getMacAddress (int eeprom_num, int eth_num)
{
	char *macaddress;

	macaddress = emb_eep_find_mac_in_dmi(eeprom_num, eth_num);
	if (macaddress != NULL)
		return (macaddress);
	else
		return "na";
}

uint64_t getBootCounter (int eeprom_num)
{
	uint64_t bc;
	char *tmp;

	tmp = emb_eep_find_string_in_dmi(eeprom_num, 161, 1);
	if (tmp != NULL) {
		memcpy(&bc, tmp, sizeof(uint64_t));
		return (be64_to_cpu(bc));
	} else
		return (-1ULL);
}

#endif

#ifdef CONFIG_SPL_BUILD
#include <spl.h>
#include <libfdt.h>

int spl_start_uboot(void)
{
	return 1;
}

void board_boot_order(u32 *spl_boot_list)
{
	spl_boot_list[0] = BOOT_DEVICE_SPI;
}

static int mx7d_dcd_table[] = {
0x30340004, 0x0F400005,
0x30391000, 0x00000003,
0x30391000, 0x00000002,
0x307a0000, 0x01040001,
0x307a01a0, 0x80400003,
0x307a01a4, 0x00100020,
0x307a01a8, 0x80100004,
0x307a0064, 0x00400046,
0x307a0490, 0x00000001,
0x307a00d0, 0x00020103,
0x307a00d4, 0x00690000,
0x307a00dc, 0x09300004,
0x307a00e0, 0x04080000,
0x307a00e4, 0x00100000,
0x307a00f4, 0x0000033f,
0x307a0100, 0x09080809,
0x307a0104, 0x000d020d,
0x307a0108, 0x04050307,
0x307a010c, 0x00002006,
0x307a0110, 0x04020205,
0x307a0114, 0x03030202,
0x307a0120, 0x00000803,
0x307a0180, 0x00800020,
0x307a0184, 0x02000100,
0x307a0190, 0x02098204,
0x307a0194, 0x00030303,
0x307a0200, 0x0000001f,
0x307a0204, 0x00080808,
0x307a0214, 0x07070707,
0x307a0218, 0x07070707,
0x307a0240, 0x06000604,
0x307a0244, 0x00000001,
0x30391000, 0x00000000,
0x30790000, 0x17420f40,
0x30790004, 0x10210100,
0x30790010, 0x00060807,
0x307900b0, 0x1010007e,
0x3079009c, 0x00000d6e,
0x30790020, 0x08080808,
0x30790030, 0x08080808,
0x30790050, 0x01000010,
0x30790050, 0x00000010,
0x307900c0, 0x0e407304,
0x307900c0, 0x0e447304,
0x307900c0, 0x0e447306,
0x307900c4, 0x1,
0x307900c0, 0x0e447304,
0x307900c0, 0x0e407304,
0x30384130, 0x00000000,
0x30340020, 0x00000178,
0x30384130, 0x00000002,
0x30790018, 0x0000000f,
/* CHECK_BITS_SET 4 0x307a0004 0x1 */
};

static void ddr_init(int *table, int size)
{
	int i;

	for (i = 0; i < size / 2 ; i++) {
		if (table[2*i] == 0x30391000) {
			/* wait some time when DDRC is in reset */
			udelay(200);
		}
		if (table[2*i] == 0x307900c4) {
			/* wait until ZQ calibration is finished */
			do {
				unsigned int ddr_phy_zq_con1 = readl(table[2*i]) & 0x1;
				udelay(10);
				if (ddr_phy_zq_con1)
					break;
			} while (1);
		} else
			writel(table[2 * i + 1], table[2 * i]);
	}
	/* wait unitl normal operation mode is indicated in DDRC_STAT */
	do {
		unsigned int ddrc_stat = readl(0x307a0004) & 0x3;
		udelay(10);
		if (ddrc_stat == 0x01)
			break;
	} while (1);
}

static void spl_dram_init(void)
{
	/* there is no difference for dual- and solo modules */
	ddr_init(mx7d_dcd_table, ARRAY_SIZE(mx7d_dcd_table));
}

void board_init_f(ulong dummy)
{
	/* setup AIPS and disable watchdog */
	arch_cpu_init();

	board_qspi_init();

	/* iomux and setup of i2c */
	board_early_init_f();

	/* setup GP timer */
	timer_init();

	/* UART clocks enabled and gd valid - init serial console */
	/* preloader_console_init(); - does not work so far... */

	/* DDR initialization */
	spl_dram_init();

	/* Clear the BSS. */
	memset(__bss_start, 0, __bss_end - __bss_start);

	/* load/boot image from boot device */
	board_init_r(NULL, 0);
}
#endif /* CONFIG_SPL_BUILD */
