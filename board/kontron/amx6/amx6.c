/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2012-2018 Kontron Europe GmbH
 *
 */

#include <common.h>
#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/mx6-pins.h>
#include <asm/arch/iomux.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch-imx/cpu.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/mach-imx/mxc_i2c.h>
#include <asm/mach-imx/sata.h>
#include <asm/gpio.h>
#include <fsl_esdhc_imx.h>
#include <mmc.h>
#include <miiphy.h>
#include <netdev.h>
#include <linux/fb.h>
#include <linux/delay.h>
#include <i2c.h>
#include <env.h>
#include <search.h>
#include <spi.h>
#include <spi_flash.h>
#include <fdt_support.h>

#include <version.h>

#include "../common/emb_eep.h"
/* #include "mx6x_pins.h" */

#if defined(CONFIG_BOARD_LATE_INIT)
#include "cesupport.h"
#endif

#include "amx6_iomux.h"

#define IDENT_STRING		"Kontron SMARC-sAMX6   Release "

#ifndef IDENT_RELEASE
#define IDENT_RELEASE		"develop"
#endif

const char version_string[] = U_BOOT_VERSION_STRING "\n" IDENT_STRING IDENT_RELEASE;

extern int EMB_EEP_I2C_EEPROM_BUS_NUM_1;

DECLARE_GLOBAL_DATA_PTR;

static iomux_v3_cfg_t ddr3_pads[] = {
	IOMUX_PADS(PAD_NANDF_CLE__GPIO6_IO07  |  MUX_PAD_CTRL(DDR3_PAD_CTRL)),
	IOMUX_PADS(PAD_NANDF_WP_B__GPIO6_IO09 |  MUX_PAD_CTRL(DDR3_PAD_CTRL)),
};

u32 get_board_rev(void)
{
	u32 cpurev = get_cpu_rev();
	u32 type = ((cpurev >> 12) & 0xff);
	switch (type) {
		case MXC_CPU_MX6SOLO:
		case MXC_CPU_MX6DL:
			return MX6SDL;
			break;
		case MXC_CPU_MX6D:
		case MXC_CPU_MX6Q:
			return MX6DQ;
			break;
		default:
			return 0;
	}
}

u32 get_pcb_version (void)
{
	int PcbVersion;
#if CONFIG_SPL_BUILD
	struct gpio_regs *regs;

	regs = (struct gpio_regs *)GPIO2_BASE_ADDR;
	PcbVersion = spl_read_gpio(regs, 2);
#else
	gpio_direction_input(IMX_GPIO_NR(2, 2));
	PcbVersion = gpio_get_value(IMX_GPIO_NR(2, 2));
#endif

	return (PcbVersion);
}

int get_ddr3_id (void)
{
	int id0, id1;
#if CONFIG_SPL_BUILD
	struct gpio_regs *regs;

	regs = (struct gpio_regs *)GPIO6_BASE_ADDR;
	id1 = spl_read_gpio(regs, 7) << 1;
	id0 = spl_read_gpio(regs, 9);
#else
	/* get the status of the DDR3_ID-pins to determine the RAM-size */
	gpio_direction_input(IMX_GPIO_NR(6, 7));
	id1 = (gpio_get_value(IMX_GPIO_NR(6, 7)) & 1) << 1;

	gpio_direction_input(IMX_GPIO_NR(6, 9));
	id0 = (gpio_get_value(IMX_GPIO_NR(6, 9)) & 1);

#endif

	return (id0 | id1);
}

int dram_init(void)
{
#if defined(CONFIG_SPL)
	gd->ram_size = imx_ddr_size();
#else
	int bits = 27;
	bits += get_ddr3_id() + get_board_rev();
	if (bits == 32)
		gd->ram_size = 0xf0000000;
	else
		gd->ram_size = 1 << bits;
#endif

	return 0;
}

/* I2C ***************************/
/* I2C1 GP */
struct i2c_pads_info i2c_pad_info0 = {
	.scl = {
		.i2c_mode = MX6Q_PAD_CSI0_DAT9__I2C1_SCL | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6Q_PAD_CSI0_DAT9__GPIO5_IO27 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(5, 27)
	},
	.sda = {
		.i2c_mode = MX6Q_PAD_CSI0_DAT8__I2C1_SDA | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6Q_PAD_CSI0_DAT8__GPIO5_IO26 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(5, 26)
	}
};

struct i2c_pads_info mx6dl_i2c_pad_info0 = {
	.scl = {
		.i2c_mode = MX6DL_PAD_CSI0_DAT9__I2C1_SCL | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6DL_PAD_CSI0_DAT9__GPIO5_IO27 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(5, 27)
	},
	.sda = {
		.i2c_mode = MX6DL_PAD_CSI0_DAT8__I2C1_SDA | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6DL_PAD_CSI0_DAT8__GPIO5_IO26 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(5, 26)
	}
};

/* I2C2  PM */
struct i2c_pads_info i2c_pad_info1 = {
	.scl = {
		.i2c_mode = MX6Q_PAD_KEY_COL3__I2C2_SCL   | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6Q_PAD_KEY_COL3__GPIO4_IO12 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(4, 12)
	},
	.sda = {
		.i2c_mode = MX6Q_PAD_KEY_ROW3__I2C2_SDA | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6Q_PAD_KEY_ROW3__GPIO4_IO13 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(4, 13)
	}
};

struct i2c_pads_info mx6dl_i2c_pad_info1 = {
	.scl = {
		.i2c_mode = MX6DL_PAD_KEY_COL3__I2C2_SCL   | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6DL_PAD_KEY_COL3__GPIO4_IO12 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(4, 12)
	},
	.sda = {
		.i2c_mode = MX6DL_PAD_KEY_ROW3__I2C2_SDA | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6DL_PAD_KEY_ROW3__GPIO4_IO13 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(4, 13)
	}
};

/* I2C3 CAM */
struct i2c_pads_info i2c_pad_info2 = {
	.scl = {
		.i2c_mode = MX6Q_PAD_GPIO_5__I2C3_SCL | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6Q_PAD_GPIO_5__GPIO1_IO05 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(1, 5)
	},
	.sda = {
		.i2c_mode = MX6Q_PAD_GPIO_16__I2C3_SDA | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6Q_PAD_GPIO_16__GPIO7_IO11 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(7, 11)
	}
};

struct i2c_pads_info mx6dl_i2c_pad_info2 = {
	.scl = {
		.i2c_mode = MX6DL_PAD_GPIO_5__I2C3_SCL | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6DL_PAD_GPIO_5__GPIO1_IO05 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(1, 5)
	},
	.sda = {
		.i2c_mode = MX6DL_PAD_GPIO_16__I2C3_SDA | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gpio_mode = MX6DL_PAD_GPIO_16__GPIO7_IO11 | MUX_PAD_CTRL(I2C_PAD_CTRL),
		.gp = IMX_GPIO_NR(7, 11)
	}
};


/* GPIO ***************************/
static iomux_v3_cfg_t const gpio_pads[] = {
	IOMUX_PADS(PAD_EIM_DA0__GPIO3_IO00	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA1__GPIO3_IO01	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA2__GPIO3_IO02	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA3__GPIO3_IO03	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA4__GPIO3_IO04	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA5__GPIO3_IO05	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA6__GPIO3_IO06	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA7__GPIO3_IO07	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA8__GPIO3_IO08	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA9__GPIO3_IO09	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA10__GPIO3_IO10	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA11__GPIO3_IO11	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
};

/* Boot select configuration ********************/
static iomux_v3_cfg_t boot_sel_pads[] = {
	IOMUX_PADS(PAD_EIM_DA13__GPIO3_IO13	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA14__GPIO3_IO14	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_DA15__GPIO3_IO15	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_NANDF_D3__GPIO2_IO03	|  MUX_PAD_CTRL(GPIO_PAD_CTRL)),
};

char boot_selects[][32] = {
	"Carrier SATA",
	"Carrier SD Card",
	"Carrier eMMC Flash",
	"Carrier SPI",
	"Not supported", /* Module device (NAND, NOR) */
	"Remote boot (GBE)",
	"Module eMMC Flash",
	"Module SPI"
};

static void setup_boot_sel(void)
{
	int boot_sel;

	/*
	 * Caution :
	 * To read boot select configuration is changed designed for pins
	 * purpose from PCIe reset (GPIO output) to Boot Select (GPIO input).
	 *
	 */
	SETUP_IOMUX_PADS(boot_sel_pads);

	/* Get the state of the Boot Select pins */
	gpio_request(IMX_GPIO_NR(3, 13), "bootsel_0");
	gpio_direction_input(IMX_GPIO_NR(3, 13));	/* BOOT SEL 0 */
	gpio_request(IMX_GPIO_NR(3, 14), "bootsel_1");
	gpio_direction_input(IMX_GPIO_NR(3, 14));	/* BOOT SEL 1 */
	gpio_request(IMX_GPIO_NR(3, 15), "bootsel_2");
	gpio_direction_input(IMX_GPIO_NR(3, 15));	/* BOOT SEL 2 */
	/*
	 * Enable Boot Select feature :
	 * 1/ When GPB2_GPIO3_1V8 = High or unconnected,
	 *    PCIE_x_RST_IMX_n function will stay unchanged
	 *
	 * 2/ When tied LOW, I_PCIE_x_RST_IMX_n signals will become CPLD
	 *    outputs asserted as
	 *    I_PCIE_A_RST_IMX_n<=I_BOOT_SEL0_n
	 *    I_PCIE_B_RST_IMX_n<=I_BOOT_SEL1_n
	 *    I_PCIE_C_RST_IMX_n<=I_BOOT_SEL2_n
	 */

	/* Enable Boot select = GPB2_GPIO3_1V8 pin */
	gpio_request(IMX_GPIO_NR(2, 3), "bootsel_en");
	gpio_direction_output(IMX_GPIO_NR(2, 3), 0);

	boot_sel = gpio_get_value(IMX_GPIO_NR(3, 13)) & 0x1;
	boot_sel |= (gpio_get_value(IMX_GPIO_NR(3, 14)) & 0x1) << 1;
	boot_sel |= (gpio_get_value(IMX_GPIO_NR(3, 15)) & 0x1) << 2;

	/*
	 * Jumper settings per SMARC Spec
	 *
	 *    BOOT_SEL2#  BOOT_SEL1#  BOOT_SEL0# Boot Source
	 * 0  GND         GND         GND        Carrier SATA
	 * 1  GND         GND         Float      Carrier SD Card
	 * 2  GND         Float       GND        Carrier eMMC Flash
	 * 3  GND         Float       Float      Carrier SPI
	 * 4  Float       GND         GND        Module device (NAND, NOR)
	 * 5  Float       GND         Float      Remote boot (GBE, serial)
	 * 6  Float       Float       GND        Module eMMC Flash
	 * 7  Float       Float       Float      Module SPI
	 */
	printf("Selected Boot source: %s\n", boot_selects[boot_sel]);

	/* Disable Boot Select feature */
	gpio_direction_output(IMX_GPIO_NR(2, 3), 1);

	/*
	 * Set the PCIE_A/B/C_RST_IMX pin to low to possibly workaround a
	 * PCIe issue.
	 */
	gpio_direction_output(IMX_GPIO_NR(3, 13), 0); /* PCIE_A_RST_IMX */
	gpio_direction_output(IMX_GPIO_NR(3, 14), 0); /* PCIE_B_RST_IMX */
	gpio_direction_output(IMX_GPIO_NR(3, 15), 0); /* PCIE_C_RST_IMX */

	switch (boot_sel) {
		case 0:
			env_set("bootsel_script", "sataboot");
			break;
		case 1:
			env_set("bootsel_script", "sdboot");
			break;
		case 2:
			env_set("bootsel_script", "mmcboot_carrier");
			break;
		case 3:
			env_set("bootsel_script", "spiboot_carrier");
			break;
		case 5:
			env_set("bootsel_script", "netboot");
			break;
		case 6:
			env_set("bootsel_script", "mmcboot");
			break;
		case 7:
			env_set("bootsel_script", "spiboot");
			break;
		default:
			debug("Not supported Boot mode\n");
	}
}

#ifdef CONFIG_JAM_STAPL
/* JTAG interface to program on-board CPLD ***************************/
/* GPIO - Used as bit-banging JTAG interface to program CPLD on-board logic */
static iomux_v3_cfg_t gpio_jtag_pads[] = {
		/*  */
	IOMUX_PADS(PAD_KEY_COL0__GPIO4_IO06 | MUX_PAD_CTRL(JTAG_GPIO_PAD_CTRL)),	// CPLD_TMS_IMX
	IOMUX_PADS(PAD_KEY_ROW0__GPIO4_IO07 | MUX_PAD_CTRL(JTAG_GPIO_PAD_CTRL)),	// CPLD_TDI_IMX
	IOMUX_PADS(PAD_KEY_COL1__GPIO4_IO08 | MUX_PAD_CTRL(JTAG_GPIO_PAD_CTRL)),	// CPLD_TDO_IMX
	IOMUX_PADS(PAD_KEY_ROW1__GPIO4_IO09 | MUX_PAD_CTRL(JTAG_GPIO_PAD_CTRL)),	// CPLD_TCK_IMX
};

/* Setup bit-banging JTAG interface to on-board CPLD logic */
void amx6_setup_iomux_gpio_jtag(void)
{
	SETUP_IOMUX_PADS(gpio_jtag_pads);

	/* Configure JTAG pins direction */
	gpio_direction_output(IMX_GPIO_NR(4, 6), 0);
	gpio_direction_output(IMX_GPIO_NR(4, 7), 0);
	gpio_direction_input(IMX_GPIO_NR(4, 8));
	gpio_direction_output(IMX_GPIO_NR(4, 9), 0);
}

void amx6_clear_iomux_gpio_jtag(void)
{
	/* Clear JTAG pins */
	gpio_direction_input(IMX_GPIO_NR(4, 6));
	gpio_direction_input(IMX_GPIO_NR(4, 7));
	gpio_direction_input(IMX_GPIO_NR(4, 8));
	gpio_direction_input(IMX_GPIO_NR(4, 9));
}

int gpio_set_multivalue(unsigned gpio, int value, int mask);

#define AMX6_JTAG_TMS_BIT 	(1 << 6)
#define AMX6_JTAG_TDI_BIT 	(1 << 7)
#define AMX6_JTAG_TD0_BIT 	(1 << 8)
#define AMX6_JTAG_TCK_BIT 	(1 << 9)

#define AMX6_JTAG_TMS_GPIO_PIN 	IMX_GPIO_NR(4, 6)
#define AMX6_JTAG_TDI_GPIO_PIN 	IMX_GPIO_NR(4, 7)
#define AMX6_JTAG_TD0_GPIO_PIN 	IMX_GPIO_NR(4, 8)
#define AMX6_JTAG_TCK_GPIO_PIN 	IMX_GPIO_NR(4, 9)

#define TMS_SET_BIT(bit)	gpio_set_value(AMX6_JTAG_TMS_GPIO_PIN, bit)
#define TDI_SET_BIT(bit)	gpio_set_value(AMX6_JTAG_TDI_GPIO_PIN, bit)
#define TCK_SET_BIT(bit)	gpio_set_value(AMX6_JTAG_TCK_GPIO_PIN, bit)
#define TDO_GET_BIT()		gpio_get_value(AMX6_JTAG_TD0_GPIO_PIN)

#define JTAG_SET_MASK		(AMX6_JTAG_TMS_BIT | AMX6_JTAG_TDI_BIT | AMX6_JTAG_TCK_BIT)
#define JTAG_SET(val)									\
	{										\
		gpio_set_multivalue(AMX6_JTAG_TMS_GPIO_PIN, val, JTAG_SET_MASK);	\
	}

int amx6_jbi_jtag_io(int tms, int tdi, int read_tdo)
{
	int tdo = 0;
	int data;

	data = (tdi ? AMX6_JTAG_TDI_BIT : 0) | (tms ? AMX6_JTAG_TMS_BIT : 0);
	JTAG_SET(data);

	if (read_tdo)
		tdo = TDO_GET_BIT();

	JTAG_SET(data | AMX6_JTAG_TCK_BIT);
	JTAG_SET(data);

	return (tdo);
}

#endif // CONFIG_JAM_STAPL

/* SPI ***************************/

static iomux_v3_cfg_t ecspi2_pads[] = {
	IOMUX_PADS(PAD_EIM_OE__ECSPI2_MISO  |  MUX_PAD_CTRL(ECSPI2_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_CS1__ECSPI2_MOSI |  MUX_PAD_CTRL(ECSPI2_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_CS0__ECSPI2_SCLK |  MUX_PAD_CTRL(ECSPI2_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_RW__ECSPI2_SS0   |  MUX_PAD_CTRL(ECSPI2_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_LBA__ECSPI2_SS1  |  MUX_PAD_CTRL(ECSPI2_PAD_CTRL)),
};

static iomux_v3_cfg_t ecspi4_pads[] = {
	IOMUX_PADS(PAD_EIM_D22__ECSPI4_MISO |  MUX_PAD_CTRL(ECSPI4_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D28__ECSPI4_MOSI |  MUX_PAD_CTRL(ECSPI4_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D21__ECSPI4_SCLK |  MUX_PAD_CTRL(ECSPI4_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D29__ECSPI4_SS0  |  MUX_PAD_CTRL(ECSPI4_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D24__GPIO3_IO24  |  MUX_PAD_CTRL(NO_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D25__ECSPI4_SS3  |  MUX_PAD_CTRL(ECSPI4_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_EB2__GPIO2_IO30  |  MUX_PAD_CTRL(NO_PAD_CTRL)),
};

void board_spi_init(void)
{
	u32 reg = 0;

	/* Enable SPI-clocks for bus 2 and 4*/
	reg = readl(0x020C406C);
	reg |= 0xCC;
	writel(reg,0x020C406C );
}

static void setup_iomux_spi(void)
{
	SETUP_IOMUX_PADS(ecspi2_pads);
	SETUP_IOMUX_PADS(ecspi4_pads);

	/* Workaround : normally clock for SPI module is enabled by
	 * Freescale Bootstrap but in case of loading U-Boot via e.g.
	 * BDI none is eager to do that.
	 */
	board_spi_init();
}

/* UART ***************************/

/* UART1 U-Boot console, rest of UART's doesn't used */

static iomux_v3_cfg_t uart1_pads[] = {
	IOMUX_PADS(PAD_CSI0_DAT10__UART1_TX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL)),
	IOMUX_PADS(PAD_CSI0_DAT11__UART1_RX_DATA | MUX_PAD_CTRL(UART_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D19__UART1_CTS_B | MUX_PAD_CTRL(UART_PAD_CTRL)),
	IOMUX_PADS(PAD_EIM_D20__UART1_RTS_B | MUX_PAD_CTRL(UART_PAD_CTRL)),
};

#if defined(CONFIG_FSL_ESDHC_IMX) && defined(CONFIG_SPL_BUILD)

#define USDHC3_CD_GPIO	IMX_GPIO_NR(6, 14)
#define USDHC3_PWR_GPIO	IMX_GPIO_NR(1, 29)
#define USDHC4_RST_GPIO	IMX_GPIO_NR(6, 8)

/* SD / MMC  ***************************/
/* SD2 : SDMMC , 8-bit */
static iomux_v3_cfg_t const usdhc2_pads[] = {
	IOMUX_PADS(PAD_SD2_CLK__SD2_CLK       | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD2_CMD__SD2_CMD       | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD2_DAT0__SD2_DATA0    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD2_DAT1__SD2_DATA1    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD2_DAT2__SD2_DATA2    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD2_DAT3__SD2_DATA3    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_NANDF_D4__SD2_DATA4    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_NANDF_D5__SD2_DATA5    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_NANDF_D6__SD2_DATA6    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_NANDF_D7__SD2_DATA7    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_GPIO_4__SD2_CD_B       | MUX_PAD_CTRL(NO_PAD_CTRL)),
};

static iomux_v3_cfg_t const usdhc3_pads[] = {
	IOMUX_PADS(PAD_SD3_CLK__SD3_CLK       | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_CMD__SD3_CMD       | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_DAT0__SD3_DATA0    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_DAT1__SD3_DATA1    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_DAT2__SD3_DATA2    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_SD3_DAT3__SD3_DATA3    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
	IOMUX_PADS(PAD_ENET_RXD1__GPIO1_IO26  | MUX_PAD_CTRL(NO_PAD_CTRL)), /* WP */
	IOMUX_PADS(PAD_ENET_TXD1__GPIO1_IO29  | MUX_PAD_CTRL(NO_PAD_CTRL)), /* POWER ENABLE*/
	IOMUX_PADS(PAD_NANDF_CS1__GPIO6_IO14  | MUX_PAD_CTRL(NO_PAD_CTRL)), /* CD# */
	IOMUX_PADS(PAD_NANDF_CS2__CCM_CLKO2   | MUX_PAD_CTRL(NO_PAD_CTRL)),
};

static iomux_v3_cfg_t const usdhc4_pads[] = {
       IOMUX_PADS(PAD_SD4_CLK__SD4_CLK        | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_SD4_CMD__SD4_CMD        | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_SD4_DAT0__SD4_DATA0     | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_SD4_DAT1__SD4_DATA1     | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_SD4_DAT2__SD4_DATA2     | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_SD4_DAT3__SD4_DATA3     | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_SD4_DAT4__SD4_DATA4     | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_SD4_DAT5__SD4_DATA5     | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_SD4_DAT6__SD4_DATA6     | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_SD4_DAT7__SD4_DATA7     | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
       IOMUX_PADS(PAD_NANDF_ALE__SD4_RESET    | MUX_PAD_CTRL(USDHC_PAD_CTRL)),
};

struct fsl_esdhc_cfg usdhc_cfg[3] = {
	{USDHC2_BASE_ADDR},
	{USDHC3_BASE_ADDR},
	{USDHC4_BASE_ADDR},
};

int board_mmc_getcd(struct mmc *mmc)
{
	struct fsl_esdhc_cfg *cfg = (struct fsl_esdhc_cfg *)mmc->priv;
	int ret = 0;

	switch (cfg->esdhc_base) {
	case USDHC2_BASE_ADDR: /* carrier eMMC */
		break;
	case USDHC3_BASE_ADDR: /* carrier SD */
		gpio_direction_input(USDHC3_CD_GPIO);
		ret = !gpio_get_value(USDHC3_CD_GPIO);
		if (!ret) {
			gpio_direction_output(USDHC3_PWR_GPIO, 0);
			gpio_set_value(USDHC3_PWR_GPIO, 1);
		}
		break;
	case USDHC4_BASE_ADDR: /* onboard eMMC */
		ret = 1; /* onboard eMMC is always present */
		break;
	}

	return ret;
}

#define SYSCTL_OFS		0x2c
#define SYSCTL_IPP_RST_N	0x00800000

int board_mmc_init(struct bd_info *bis)
{
	int i;
	int ret = 0;

	for (i=0 ; i<CONFIG_SYS_FSL_USDHC_NUM ; i++) {
		uint *sysctl;
		switch(i) {
		case 0:
			SETUP_IOMUX_PADS(usdhc2_pads);
			usdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC2_CLK);
			break;
		case 1:
			SETUP_IOMUX_PADS(usdhc3_pads);
			usdhc_cfg[1].sdhc_clk = mxc_get_clock(MXC_ESDHC3_CLK);
			break;
		case 2:
			/* Reset eMMC device first */
			sysctl = (uint *)(USDHC4_BASE_ADDR + SYSCTL_OFS);
			clrbits_le32(sysctl, SYSCTL_IPP_RST_N);
			udelay(1000);
			setbits_le32(sysctl, SYSCTL_IPP_RST_N);

			SETUP_IOMUX_PADS(usdhc4_pads);
			usdhc_cfg[2].sdhc_clk = mxc_get_clock(MXC_ESDHC4_CLK);
			break;
		default:
			printf("Warning: you configured more USDHC "
			       "controllers (%d) than supported by the "
			       "board\n", i+1);
			return -EINVAL;
		}

		ret = fsl_esdhc_initialize(bis, &usdhc_cfg[i]);
		if (ret)
			return ret;
	}

	return 0;
}
#endif

/* Ethernet ***************************/
static iomux_v3_cfg_t const enet_pads[] = {
	IOMUX_PADS(PAD_ENET_MDIO__ENET_MDIO		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_ENET_MDC__ENET_MDC		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TXC__RGMII_TXC		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TD0__RGMII_TD0		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TD1__RGMII_TD1		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TD2__RGMII_TD2		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TD3__RGMII_TD3		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_TX_CTL__RGMII_TX_CTL	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_ENET_REF_CLK__ENET_TX_CLK	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RXC__RGMII_RXC		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RD0__RGMII_RD0		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RD1__RGMII_RD1		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RD2__RGMII_RD2		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RD3__RGMII_RD3		| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_RGMII_RX_CTL__RGMII_RX_CTL	| MUX_PAD_CTRL(ENET_PAD_CTRL)),
	IOMUX_PADS(PAD_GPIO_0__CCM_CLKO1		| MUX_PAD_CTRL(NO_PAD_CTRL)),
	IOMUX_PADS(PAD_GPIO_3__CCM_CLKO2		| MUX_PAD_CTRL(NO_PAD_CTRL)),
};

int board_phy_config(struct phy_device *phydev)
{
	if (phydev->drv->config)
		phydev->drv->config(phydev);

	return 0;
}

int board_eth_init(struct bd_info *bis)
{
	int ret;

	SETUP_IOMUX_PADS(enet_pads);

	ret = cpu_eth_init(bis);
	if (ret)
		printf("FEC MXC: %s:failed\n", __func__);

	return 0;
}

/* USB ***************************/

iomux_v3_cfg_t usb_pads[] = {
	IOMUX_PADS(PAD_GPIO_17__GPIO7_IO12 | MUX_PAD_CTRL(NO_PAD_CTRL)),
};

#ifdef CONFIG_USB_EHCI_MX6
int board_ehci_hcd_init(int port)
{
	SETUP_IOMUX_PADS(usb_pads);

	/* Reset USB hub */
	gpio_request(IMX_GPIO_NR(7, 12), "usbhub_rst");
	gpio_direction_output(IMX_GPIO_NR(7, 12), 0);
	mdelay(2);
	gpio_set_value(IMX_GPIO_NR(7, 12), 1);

	return 0;
}
#endif

int board_early_init_f(void)
{
	SETUP_IOMUX_PADS(uart1_pads);
	SETUP_IOMUX_PADS(ddr3_pads);
	setup_iomux_spi();

	return 0;
}

/*
 * Do not overwrite the console
 * Use always serial for U-Boot console
 */
int overwrite_console(void)
{
	return 1;
}

int board_init(void)
{
	/* address of boot parameters */
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;

#ifdef CONFIG_CMD_SF
	setup_iomux_spi();
#endif

	if(get_board_rev() == MX6DQ) {
		setup_i2c(0, CONFIG_SYS_MXC_I2C1_SPEED, 0x7f, &i2c_pad_info0);
		setup_i2c(1, CONFIG_SYS_MXC_I2C2_SPEED, 0x7f, &i2c_pad_info1);
		setup_i2c(2, CONFIG_SYS_MXC_I2C3_SPEED, 0x7f, &i2c_pad_info2);
	} else if (get_board_rev() == MX6SDL) {
		setup_i2c(0, CONFIG_SYS_MXC_I2C1_SPEED, 0x7f, &mx6dl_i2c_pad_info0);
		setup_i2c(1, CONFIG_SYS_MXC_I2C2_SPEED, 0x7f, &mx6dl_i2c_pad_info1);
		setup_i2c(2, CONFIG_SYS_MXC_I2C3_SPEED, 0x7f, &mx6dl_i2c_pad_info2);
	}

#ifdef CONFIG_CMD_SATA
	setup_sata();
#endif

#ifdef CONFIG_CMD_GPIO
	SETUP_IOMUX_PADS(gpio_pads);
#endif

	return 0;
}

int checkboard(void)
{
	return 0;
}

#ifdef CONFIG_MISC_INIT_R
int misc_init_r (void)
{
	env_set("version", IDENT_STRING IDENT_RELEASE);

	/* Bus number of Embedded EEPROM depends on PCB version */

#ifdef CONFIG_EMB_EEP_I2C_EEPROM
	if (get_pcb_version() == SMX6_OLD_PCB_VERSION)
		EMB_EEP_I2C_EEPROM_BUS_NUM_1 = 1;
	else
		EMB_EEP_I2C_EEPROM_BUS_NUM_1 = \
		    CONFIG_EMB_EEP_I2C_EEPROM_BUS_NUM_EE1;

	debug("misc_init_r: PcbVersion = %d, BUS_NUM = %d\n",
	       get_pcb_version(), EMB_EEP_I2C_EEPROM_BUS_NUM_1);

	emb_eep_init_r (1, 1, 1); /* import 1 MAC address */
#endif

	setup_boot_sel ();

	return 0;
}
#endif

#if defined(CONFIG_OF_BOARD_FIXUP)
const char ft_version_string[] = U_BOOT_VERSION_STRING;

int board_fix_fdt(void *blob)
{
	return 0;
}
#endif

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
#endif

#if defined(CONFIG_CMD_KBOARDINFO)
static int fdt_setup_info_string(void *blob, char *name, char *value)
{
	int err, nodeoffset;

	err = fdt_check_header(blob);
	if (err < 0) {
		printf("%s: %s\n", __FUNCTION__, fdt_strerror(err));
		return err;
	}

	/* update, or add and update /uboot-version node */
	nodeoffset = fdt_path_offset(blob, "/");
	if (nodeoffset < 0) {
		printf("WARNING: there is no / on FDT\n");
		return nodeoffset;
	}
	if (value == 0)
		err = fdt_setprop_string(blob, nodeoffset, name, "na");
	else
		err = fdt_setprop_string(blob, nodeoffset, name, value);

	if (err < 0) {
		printf("WARNING: could not set %s %s.\n", name,
			fdt_strerror(err));
		return err;
	}
	return 0;
}
#endif

extern char *print_if_avail (char *);

#if defined(CONFIG_OF_BOARD_SETUP)
int ft_board_setup(void *blob, struct bd_info *bd) {
#if defined(CONFIG_CMD_KBOARDINFO)
	/* set up in FDT u-boot version information */
	fdt_setup_info_string(blob, "O000060,uboot_version", (char *)version_string);
	fdt_setup_info_string(blob, "O000060,serial_number", getSerNo ());
	fdt_setup_info_string(blob, "O000060,material_number", print_if_avail (getSapId(1)));
	fdt_setup_info_string(blob, "O000060,product_name", print_if_avail (getProductName(1)));
	fdt_setup_info_string(blob, "O000060,manufact_date", print_if_avail (getManufacturerDate(1)));
	fdt_setup_info_string(blob, "O000060,revision", print_if_avail (getRevision(1)));
	fdt_setup_info_string(blob, "O000060,manufacturer", print_if_avail (getManufacturer(1)));
#endif

	fdt_fixup_memory(blob, (u64) CONFIG_SYS_SDRAM_BASE, (u64) gd->ram_size);
	fdt_fixup_ethernet(blob);

	return 0;
}
#endif

#ifdef CONFIG_BOARD_LATE_INIT

BootArgs*   g_pBootArgs;

int board_late_init (void)
{
	char const *kitlMode = env_get("wince_kitl");

	g_pBootArgs = (BootArgs*)WEC7_ARGS_START;

	memset (g_pBootArgs, 0x00, sizeof(g_pBootArgs[0]));
	strcpy((char*)g_pBootArgs->magic, "SMX6");
	g_pBootArgs->length    = sizeof(g_pBootArgs[0]);
	g_pBootArgs->debugPort = 3;          /* UARTC */
	g_pBootArgs->debugBaud = 115200;
	g_pBootArgs->kitlMode  = 0;

	if (kitlMode != NULL) {
		if (!strncmp(kitlMode, "enabled", 6))
			g_pBootArgs->kitlMode  = 1;
	}

	return 0;
}
#endif

int board_sata_enable(void)
{
	if(get_board_rev() == MX6SDL)
		return 0;
	else
		return 1;
}

/* board infos */
int getBoardId (void)
{
	/*
	 * FIXME : implement method of obtaining ID
	 * and verifiy it againt this which is coded
	 * in jbc file ( program for on-board logic )
	*/

	return 0;
}

#if defined(CONFIG_SYS_DRAM_TEST)
int testdram (void)
{
	uint *pstart = (uint *) CONFIG_SYS_MEMTEST_START;
	uint *pend = (uint *) CONFIG_SYS_MEMTEST_END;
	uint *p;

	printf ("SDRAM test phase 1:\n");
	for (p = pstart; p < pend; p++)
		*p = 0xaaaaaaaa;

	for (p = pstart; p < pend; p++) {
		if (*p != 0xaaaaaaaa) {
			printf ("SDRAM test fails at: %08x\n", (uint) p);
			return 1;
		}
	}

	printf ("SDRAM test phase 2:\n");
	for (p = pstart; p < pend; p++)
		*p = 0x55555555;

	for (p = pstart; p < pend; p++) {
		if (*p != 0x55555555) {
			printf ("SDRAM test fails at: %08x\n", (uint) p);
			return 1;
		}
	}

	printf ("SDRAM test passed.\n");
	return 0;
}
#endif
