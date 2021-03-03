/*
 * Copyright (C) 2017 Kontron Europe GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <init.h>
#include <net.h>
#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/mx7-pins.h>
#include <asm/arch-mx7/mx7-ddr.h>
#include <asm/arch/sys_proto.h>
#include <asm/gpio.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/sizes.h>
#include <common.h>
#include <image.h>
#include <fsl_esdhc_imx.h>
#include <mmc.h>
#include <miiphy.h>
#include <fdt_support.h>
#include <netdev.h>
#include <i2c.h>
#include <env.h>
#include <env_internal.h>
#include <search.h>
#include <usb.h>
#include <usb/ehci-ci.h>
#include <dm.h>
#include <dm/platform_data/serial_mxc.h>
#include <version.h>

/* #include "../common/emb_vpd.h" */
#include "../common/emb_eep.h"

#define IDENT_STRING		"Kontron SMX7 SMARC 2.0 Module   Release "

#ifndef IDENT_RELEASE
#define IDENT_RELEASE		"develop"
#endif

const char version_string[] = U_BOOT_VERSION_STRING "\n" IDENT_STRING IDENT_RELEASE;

extern void BOARD_InitPins(void);
extern void BOARD_FixupPins(void);
extern void hsic_1p2_regulator_out(void);
extern void use_pwm1_out_as_gpio(void);
/* extern void snvs_lpgpr_set(uint32_t); */
extern void start_imx_watchdog(int timeout, int kick);

extern int EMB_EEP_I2C_EEPROM_BUS_NUM_1;

DECLARE_GLOBAL_DATA_PTR;

int board_spi_cs_gpio(unsigned bus, unsigned cs)
{
	if ((bus == 2) && (cs == 0))
		return IMX_GPIO_NR(6, 22);

#ifndef CONFIG_KEX_EXTSPI_BOOT
	if ((bus == 2) && (cs == 2))
		return IMX_GPIO_NR(5, 9);
#endif

	return -1;
}

int dram_init(void)
{
	gd->ram_size = imx_ddr_size();

	return 0;
}

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

int board_mmc_init(struct bd_info *bis)
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

#if defined(CONFIG_SPL_MMC_SUPPORT)
#define SRC_GPR10		0x30390098
#define PERSIST_SECONDARY_BOOT	(1<<30)

bool smx7_mmcboot_secondary(void)
{
	return (bool)(readl(SRC_GPR10) & PERSIST_SECONDARY_BOOT);
}

u32 mmc_redundant_boot_block(void)
{
	if (smx7_mmcboot_secondary())
		return 0x800;
	else
		return 0;
}
#endif
#endif /* CONFIG_FSL_ESDHC */

#ifdef CONFIG_FEC_MXC
int board_eth_init(struct bd_info *bis)
{
	int ret;
	struct mxc_ccm_anatop_reg *ccm_anatop
	    = (struct mxc_ccm_anatop_reg *) ANATOP_BASE_ADDR;

	/* enable lvds output buffer for anaclk1, select 0x12 = pll_enet_div40 (25MHz) */
	setbits_le32(&ccm_anatop->clk_misc0, 0x20 | CCM_ANALOG_CLK_MISC0_LVDS1_CLK_SEL(0x12));
	udelay(10);

        gpio_request(IMX_GPIO_NR(3, 21), "fec_reset");
	gpio_direction_output(IMX_GPIO_NR(3, 21), 0);
	udelay(500);
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

	return set_clk_enet(ENET_125MHZ);
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
        struct udevice *dev;
        int ret;
	uint8_t usbattach_cmd[] = {0xaa, 0x55, 0x00};

	/* reset USBHUB */
	gpio_request(IMX_GPIO_NR(1, 0), "usbhub_reset");
	gpio_direction_output(IMX_GPIO_NR(1, 0), 0);
	udelay(1000);
	/* remove USBHUB reset */
	gpio_direction_output(IMX_GPIO_NR(1, 0), 1);
	udelay(250000);

        ret = i2c_get_chip_for_busnum(1, CONFIG_KEX_USBHUB_I2C_ADDR, 1, &dev);
	if (ret) {
		printf("USBHUB not found\n");
		return 0;
	}
        i2c_set_chip_offset_len(dev, 0);
	dm_i2c_write(dev, 0, usbattach_cmd, 3);

	return 0;
}

int board_ehci_hcd_init(int port)
{
	debug("%s: port = %d\n", __func__, port);
	/*
	 * port number will change when read from device tree
	 * note that this depends on device tree and whether
	 * OTG port 1 was detected or not. If not detected,
	 * port number will be 0 again!
	 */
#if CONFIG_IS_ENABLED(DM_USB)
	if (port == 1) {
#else
	if (port == 2) {
#endif
		attach_usb_hub();
	}

	return 0;
}

int board_ehci_hcd_exit(int port)
{
	debug("%s: port = %d\n", __func__, port);
#if CONFIG_IS_ENABLED(DM_USB)
	if (port == 1) {
#else
	if (port == 2) {
#endif
		attach_usb_hub();
	}

	return 0;
}

static void set_boot_sel(void)
{
	int boot_sel;

	/* Get the state of the Boot Select pins */
	gpio_request(IMX_GPIO_NR(3, 24), "bootsel_0");
	gpio_direction_input(IMX_GPIO_NR(3, 24));	/* BOOT SEL 0 */
	gpio_request(IMX_GPIO_NR(3, 25), "bootsel_1");
	gpio_direction_input(IMX_GPIO_NR(3, 25));	/* BOOT SEL 1 */
	gpio_request(IMX_GPIO_NR(3, 26), "bootsel_2");
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
			env_set("boot_sel", "carrier_sata");
			break;
		case 1:
			env_set("boot_sel", "carrier_sd");
			break;
		case 2:
			env_set("boot_sel", "carrier_mmc");
			break;
		case 3:
			env_set("boot_sel", "carrier_spi");
			break;
		case 4:
			env_set("boot_sel", "module_device");
			break;
		case 5:
			env_set("boot_sel", "remote");
			break;
		case 6:
			env_set("boot_sel", "module_mmc");
			break;
		case 7:
			env_set("boot_sel", "module_spi");
			break;
	}
}

#ifndef CONFIG_SPL_BUILD
static void smx7_set_prompt(void)
{
#if defined(CONFIG_SPL_MMC_SUPPORT)
	if (smx7_mmcboot_secondary())
		env_set("PS1", "[eMMC Work] => ");
	else
		env_set("PS1", "[eMMC Recovery] => ");
#endif
#if defined(CONFIG_KEX_EXTSPI_BOOT)
	env_set("PS1", "[ext SPI] => ");
#endif
}
#endif

int misc_init_r(void)
{
	env_set("version", IDENT_STRING IDENT_RELEASE);

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

	gpio_request(IMX_GPIO_NR(3, 16), "pcie_a_prsnt");
	gpio_request(IMX_GPIO_NR(3, 22), "pcie_b_prsnt");
	gpio_request(IMX_GPIO_NR(6, 15), "pcie_c_prsnt");

	/* set PCIE present signal according to environment settings */
	if (is_cpu_type(MXC_CPU_MX7D)) {
		if (env_get_yesno("pcie_a_prsnt"))
			gpio_direction_output(IMX_GPIO_NR(3,16), 0);
		else
			gpio_direction_output(IMX_GPIO_NR(3,16), 1);

		if (env_get_yesno("pcie_b_prsnt"))
			gpio_direction_output(IMX_GPIO_NR(3,22), 0);
		else
			gpio_direction_output(IMX_GPIO_NR(3,22), 1);

		if (env_get_yesno("pcie_c_prsnt"))
			gpio_direction_output(IMX_GPIO_NR(6,15), 0);
		else
			gpio_direction_output(IMX_GPIO_NR(6,15), 1);
	}

	/* fix IOMUX configuration of PWM1_OUT for use as GPIO line if variable set */
	if (env_get_yesno("pwm_out_disable"))
		use_pwm1_out_as_gpio();

	env_set ("core_variant", "unknown");
	if (is_cpu_type(MXC_CPU_MX7D))
		env_set ("core_variant", "d");
	if (is_cpu_type(MXC_CPU_MX7S))
		env_set ("core_variant", "s");

	/* snvs_lpgpr_set(0x12345678); */

	/* init GPIO lines to ground */
	gpio_request(IMX_GPIO_NR(1, 8), "PWM_OUT");
	gpio_direction_output(IMX_GPIO_NR(1,8), 0);	/* GPIO5: PWM_OUT */

	gpio_request(IMX_GPIO_NR(3, 5), "CAM0_PWR");
	gpio_direction_output(IMX_GPIO_NR(3,5), 0);	/* GPIO0: CAM0_PWR */

	gpio_request(IMX_GPIO_NR(3, 6), "CAM1_PWR");
	gpio_direction_output(IMX_GPIO_NR(3,6), 0);	/* GPIO1: CAM1_PWR */

	gpio_request(IMX_GPIO_NR(3, 7), "CAM0_RST");
	gpio_direction_output(IMX_GPIO_NR(3,7), 0);	/* GPIO2: CAM0_RST */

	gpio_request(IMX_GPIO_NR(3, 8), "CAM1_RST");
	gpio_direction_output(IMX_GPIO_NR(3,8), 0);	/* GPIO3: CAM1_RST */

	gpio_request(IMX_GPIO_NR(3, 9), "HDA_RST");
	gpio_direction_output(IMX_GPIO_NR(3,9), 0);	/* GPIO4: HDA_RST */

	gpio_request(IMX_GPIO_NR(3, 10), "TACHIN");
	gpio_direction_output(IMX_GPIO_NR(3,10), 0);	/* GPIO6: TACHIN */

	gpio_request(IMX_GPIO_NR(3, 11), "gpio7");
	gpio_direction_output(IMX_GPIO_NR(3,11), 0);	/* GPIO7 */

	gpio_request(IMX_GPIO_NR(3, 12), "gpio8");
	gpio_direction_output(IMX_GPIO_NR(3,12), 0);	/* GPIO8 */

	gpio_request(IMX_GPIO_NR(4, 4), "gpio9");
	gpio_direction_output(IMX_GPIO_NR(4,4), 0);	/* GPIO9 */

	gpio_request(IMX_GPIO_NR(4, 5), "gpio10");
	gpio_direction_output(IMX_GPIO_NR(4,5), 0);	/* GPIO10 */

	gpio_request(IMX_GPIO_NR(3, 15), "gpio11");
	gpio_direction_output(IMX_GPIO_NR(3,15), 0);	/* GPIO11 */

	return 0;
}

int board_late_init(void)
{
#ifndef CONFIG_SPL_BUILD
	ulong board_rev;

	board_rev = env_get_ulong("board_rev", 10, 1);
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

	smx7_set_prompt();
#endif
	return 0;
}

int checkboard(void)
{
	/* show this information immediatly after U-Boot start message */
	/* printf("Board: " IDENT_STRING IDENT_RELEASE "\n"); */

	return 0;
}

#if defined(CONFIG_OF_BOARD_SETUP)
const char ft_version_string[] = U_BOOT_VERSION_STRING;
int board_fix_fdt(void *blob)
{
        if (is_cpu_type(MXC_CPU_MX7S)) {
                fdt_del_node_and_alias(blob, "usb2");
        }

        return 0;
}

int ft_board_setup(void *blob, struct bd_info *bd)
{
	int err;
	int nodeoffset;
	int create = 1;
	char *name;
	char str_mem_type[] = "memory-type";
	char str_mem_freq[] = "memory-frequency";
	char str_pwm1[] = "/soc/aips-bus@30400000/pwm@30660000";
	char str_ok[] = "okay";

	u64 freq = mxc_get_clock(MXC_DDR_CLK);
	phys_addr_t base = env_get_bootm_low();
	phys_size_t size = env_get_bootm_size();

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

	/*
	 * MXC_DDR_CLK is DFI clock (controller clock),
	 * Data rate is 4 times this value.
	 */
	name = str_mem_freq;
	err = fdt_setprop_u64(blob, nodeoffset, name, (freq << 2));
	if (err < 0)
		goto err;

	printf("bootloader version: %s\n", ft_version_string);
	err = fdt_find_and_setprop(blob, "/chosen", "u-boot,version",
	                     ft_version_string,
	                     sizeof(ft_version_string), create);

	if (err<0)
		goto err;

	/* check pwm_out_disable and enable pwm if needed */
	if (!env_get_yesno("pwm_out_disable")) {
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

#ifdef CONFIG_CMD_KBOARDINFO
/* board infos */

char *getSerNo (void)
{
	struct env_entry e;
	struct env_entry *ep;

	e.key = "serial#";
	e.data = NULL;
	hsearch_r (e, ENV_FIND, &ep, &env_htab, 0);
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
#include <linux/libfdt.h>

#ifndef CONFIG_SPL_MMC_SUPPORT
int spl_start_uboot(void)
{
	return 1;
}
#endif

void board_boot_order(u32 *spl_boot_list)
{
#ifdef CONFIG_SPL_MMC_SUPPORT
	spl_boot_list[0] = BOOT_DEVICE_MMC2;
#else
	spl_boot_list[0] = BOOT_DEVICE_SPI;
#endif
}

static struct ddrc smx7_ddrc_regs = {
	.mstr		= 0x01040001,
	.dfiupd0	= 0x80400003,
	.dfiupd1	= 0x00100020,
	.dfiupd2	= 0x80100004,
	.rfshtmg	= 0x00400046,
	.init0		= 0x00020103,
	.init1		= 0x00690000,
	.init3		= 0x09300004,
	.init4		= 0x04080000,
	.init5		= 0x00100000,
	.rankctl	= 0x0000033f,
	.dramtmg0	= 0x090a080a,
	.dramtmg1	= 0x000d020d,
	.dramtmg2	= 0x04050307,
	.dramtmg3	= 0x00002006,
	.dramtmg4	= 0x04020205,
	.dramtmg5	= 0x03030202,
	.dramtmg8	= 0x00000803,
	.zqctl0		= 0x00800020,
	.zqctl1		= 0x02000100,
	.dfitmg0	= 0x02098204,
	.dfitmg1	= 0x00030303,
	.addrmap0	= 0x0000001f,
	.addrmap1	= 0x00080808,
	.addrmap4	= 0x00000f0f,
	.addrmap5	= 0x07070707,
	.addrmap6	= 0x07070707,
	.odtcfg		= 0x06000604,
	.odtmap		= 0x00000001,
};

static struct ddrc_mp smx7_ddrc_mp_regs = {
	.pctrl_0	= 0x00000001,
};

static struct ddr_phy smx7_ddr_phy_regs = {
	.phy_con0	= 0x17420f40,
	.phy_con1	= 0x10210100,
	.phy_con4	= 0x00060807,
	.mdll_con0	= 0x1010007e,
	.drvds_con0	= 0x00000d6e,
	.offset_rd_con0	= 0x08080808,
	.offset_wr_con0	= 0x08080808,
	.cmd_sdll_con0	= 0x00000010,
	.offset_lp_con0	= 0x0000000f,
};

static struct mx7_calibration smx7_calibration_params = {
	.num_val	= 5,
	.values 	= {
		0x0e407304,
		0x0e447304,
		0x0e447306,
		0x0e447304,
		0x0e407304,
	},
};

static void spl_dram_init(void)
{
	struct iomuxc_gpr_base_regs *const iomuxc_gpr_regs
		= (struct iomuxc_gpr_base_regs *) IOMUXC_GPR_BASE_ADDR;
	struct ddrc *const ddrc_regs = (struct ddrc *)DDRC_IPS_BASE_ADDR;
	struct src *const src_regs = (struct src *)SRC_BASE_ADDR;
	unsigned long ram_size_found;
	int i;

	/* ddr_init(mx7d_dcd_table, ARRAY_SIZE(mx7d_dcd_table)); */
	writel(0x0f400005, &iomuxc_gpr_regs->gpr[1]);

	/*
	 * Make sure that both aresetn/core_ddrc_rstn and preset/PHY reset
	 * bits are set after WDOG reset event. DDRC_PRST can only be
	 * released when DDRC clock inputs are stable for at least 30 cycles.
	 */
	writel(SRC_DDRC_RCR_DDRC_CORE_RST_MASK |
	       SRC_DDRC_RCR_DDRC_PRST_MASK, &src_regs->ddrc_rcr);
	udelay(500);

	for (i=0 ; i<3 ; i++) {
		switch (i) {
		case 1: /* memory size 1GiB */
			smx7_ddrc_regs.addrmap6 = 0x0f070707;
			break;
		case 2: /* memory size 512 MiB */
			smx7_ddrc_regs.addrmap6 = 0x0f0f0707;
			break;
		default:
			break;
		}
		mx7_dram_cfg(&smx7_ddrc_regs,
		             &smx7_ddrc_mp_regs,
		             &smx7_ddr_phy_regs,
		             &smx7_calibration_params);
		ram_size_found = get_ram_size((long *)PHYS_SDRAM, (SZ_2G >> i));
		if (ram_size_found == (SZ_2G >> i))
			break;
	}

	/* wait unitl normal operation mode is indicated in DDRC_STAT */
	do {
		u32 op_mode = readl(&ddrc_regs->stat) & 0x3;
		udelay(10);
		if (op_mode == 0x01)
			break;
	} while (1);
}

#if 0
#define FCR		0x90
#define CR2		0x84
#define UFCR_DCEDTE	0x00000040
#define UFCR_RFDIV2	0x00000200
void board_spl_console_init(void)
{
	u32 fcr;
	u32 base = CONFIG_MXC_UART_BASE;

	gd->baudrate = CONFIG_BAUDRATE;

	serial_init();

	/*
	 * enable DTE mode which is required on SMX7
	 */
	fcr = UFCR_DCEDTE | UFCR_RFDIV2;
	writel(fcr, (base+FCR));

	gd->have_console = 1;

	puts("\nU-Boot " SPL_TPL_NAME " " PLAIN_VERSION " (" U_BOOT_DATE " - "
	      U_BOOT_TIME " " U_BOOT_TZ ")\n");
}
#endif

int reset_out_delay(int delay)
{
	/*
	 * Pull RESET_OUT to low
	 *
	 * This is a workaround to mitigate that signal is pulled high
	 * on the module.
	 */
	gpio_direction_output(IMX_GPIO_NR(2,30), 0);
	/*
	 * Wait 150ms and set RESET_OUT back to high level.
	 * This is to meet requirement that RESET_OUT must go high within
	 * 100 - 500 ms after CARRIER_POWER_ON.
	 */
	udelay(delay*1000);
	gpio_direction_output(IMX_GPIO_NR(2,30), 1);

	return 0;
}

#if defined CONFIG_SPL_MMC_SUPPORT
#define RECOVERY_GPIO IMX_GPIO_NR(3, 13)

void smx7_mmcboot_chk_recovery(void)
{
	bool mmc_force_recovery;

	gpio_request(RECOVERY_GPIO, "MMC_REC");
	gpio_direction_input(RECOVERY_GPIO);
	mmc_force_recovery = !(gpio_get_value(RECOVERY_GPIO) & 0x1);
	if (mmc_force_recovery && smx7_mmcboot_secondary()) {
		/*
		 * jumper is set, so clear the PERSIST_SECONDARY_BOOT
		 * flag and perform reset.
		 */
		writel(0x0, SRC_GPR10);
		do_reset(NULL, 0, 0, NULL);
	}
	if (!mmc_force_recovery && !smx7_mmcboot_secondary()) {
		/* force standard/secondary boot */
		writel(PERSIST_SECONDARY_BOOT, SRC_GPR10);
		do_reset(NULL, 0, 0, NULL);
	}
}
#endif

void board_init_f(ulong dummy)
{
	/* start imx watchdog to cover bootloader runtime */
	/* start_imx_watchdog(15, 1); */

	/* setup AIPS and disable watchdog */
	arch_cpu_init();

	board_qspi_init();

	/* iomux and setup of i2c */
	board_early_init_f();

	/* setup GP timer */
	timer_init();

	/* pull RESET_OUT# high after 150ms delay */
	reset_out_delay(150);

	/* UART clocks enabled and gd valid - init serial console */
	/* preloader_console_init(); * - does not work */
#if 0
	board_spl_console_init(); /* this will show startup messages in SPL */
#endif

#if defined CONFIG_SPL_MMC_SUPPORT
	/*
	 * Check force recovery jumper (LID jumper here).
	 * If unset, set the PERSIST_SECONDARY_BOOT bit and reset the board.
	 * This will force the CPU to boot the redundant bootloader image
	 * (including SPL!) that is stored beginning at block 0x802 (offset
	 * 0x100400) in the eMMC boot partition 1
	 */
        smx7_mmcboot_chk_recovery();
#endif

	/* DDR initialization */
	spl_dram_init();

	/* Clear the BSS. */
	memset(__bss_start, 0, __bss_end - __bss_start);

	/* load/boot image from boot device */
	board_init_r(NULL, 0);
}
#endif /* CONFIG_SPL_BUILD */
