/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2012-2018 Kontron Europe GmbH
 *
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/iomux.h>
#include <asm/arch/mx6-pins.h>
#include <asm/mach-imx/iomux-v3.h>
#include <asm/mach-imx/mxc_i2c.h>
#include <asm/gpio.h>
#include <mmc.h>
#include <fsl_esdhc.h>
#include <miiphy.h>
#include <netdev.h>
#include <linux/fb.h>
#include <ipu_pixfmt.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/mxc_hdmi.h>
#include <i2c.h>
#include <environment.h>
#include <search.h>
#include <asm/arch/sys_proto.h>
#include <spi.h>
#include <spi_flash.h>
#include <fdt_support.h>

#include <asm/arch-imx/cpu.h>
#include <asm/mach-imx/sata.h>
#include <version.h>

#include "../common/emb_eep.h"
/* #include "mx6x_pins.h" */

#if defined(CONFIG_BOARD_LATE_INIT)
#include "cesupport.h"
#endif

#define GATE_UNGATE_CLOCKS
#define PATCH_FOR_CLOCKS

#define IDENT_STRING		"Kontron SMARC-sAMX6   Release "

#ifndef IDENT_RELEASE
#define IDENT_RELEASE		"develop"
#endif

const char version_string[] = U_BOOT_VERSION_STRING "\n" IDENT_STRING IDENT_RELEASE;

extern int EMB_EEP_I2C_EEPROM_BUS_NUM_1;

DECLARE_GLOBAL_DATA_PTR;

/* Macros for MUX_PAD_CTRL */
#define UART_PAD_CTRL  (PAD_CTL_PKE | PAD_CTL_PUE |				\
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |			\
		PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#define USDHC_PAD_CTRL (PAD_CTL_PKE | PAD_CTL_PUE |				\
		PAD_CTL_PUS_47K_UP  | PAD_CTL_SPEED_MED |			\
		PAD_CTL_DSE_80ohm   | PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#define ENET_PAD_CTRL  (PAD_CTL_PKE | PAD_CTL_PUE |				\
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED	  |			\
		PAD_CTL_DSE_40ohm   | PAD_CTL_HYS)

#define I2C_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_PUE |				\
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |			\
		PAD_CTL_DSE_40ohm | PAD_CTL_HYS |				\
		PAD_CTL_ODE | PAD_CTL_SRE_FAST)

#define CAN_PAD_CTRL  (PAD_CTL_PKE | PAD_CTL_PUE |            			\
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |               	\
		PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_SLOW  | PAD_CTL_HYS)

#define ECSPI2_PAD_CTRL   (PAD_CTL_PKE | PAD_CTL_PUE |            		\
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |               	\
		PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST  )


#define ECSPI4_PAD_CTRL   (PAD_CTL_PKE | PAD_CTL_PUE |  		\
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |               	\
		PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST | PAD_CTL_HYS )


#define GPIO_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_PUE |            		\
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |       		\
		PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST  )

#define JTAG_GPIO_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_PUE |    		\
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |       		\
		PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST  )

#define I2C_PAD_CTRL	(PAD_CTL_PKE | PAD_CTL_PUE |				\
	PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |				\
	PAD_CTL_DSE_40ohm | PAD_CTL_HYS |					\
	PAD_CTL_ODE | PAD_CTL_SRE_FAST)


#define DDR3_PAD_CTRL  (PAD_CTL_PKE | PAD_CTL_PUE |				\
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |			\
		PAD_CTL_DSE_120ohm   | PAD_CTL_SRE_SLOW  | PAD_CTL_HYS)

static iomux_v3_cfg_t ddr3_pads[] = {
	IOMUX_PADS(PAD_NANDF_CLE__GPIO6_IO07  |  MUX_PAD_CTRL(DDR3_PAD_CTRL)),
	IOMUX_PADS(PAD_NANDF_WP_B__GPIO6_IO09 |  MUX_PAD_CTRL(DDR3_PAD_CTRL)),
};

#define MX6Q	0x63
#define MX6S	0x61

u32 get_board_rev(void)
{
	u32 cpurev = get_cpu_rev();
	u32 type = ((cpurev >> 12) & 0xff);
	if (type == MXC_CPU_MX6SOLO)
		return MX6S;

	if (type == MXC_CPU_MX6D)
		return MX6Q;

	return type;
}

#define SMX6_OLD_PCB_VERSION	1

u32 get_pcb_version (void)
{
	int PcbVersion;

	gpio_direction_input(IMX_GPIO_NR(2, 2));
	PcbVersion = gpio_get_value(IMX_GPIO_NR(2, 2));

	return (PcbVersion);
}

int dram_init(void)
{
	int id0 = 0,id1 = 0;
	u32 ram_size = 0;

#if 0
	/* get the status of the DDR3_ID-pins to determine the RAM-size */
	gpio_direction_input(IMX_GPIO_NR(6, 7));
	id0 = gpio_get_value(IMX_GPIO_NR(6, 7));

	gpio_direction_input(IMX_GPIO_NR(6, 9));
	id1 = gpio_get_value(IMX_GPIO_NR(6, 9));


	if (get_pcb_version () == SMX6_OLD_PCB_VERSION) {
		if (get_board_rev() == MX6S) {
			debug("Old PCB version: Memory size fix 0x20000000 on Solo CPU\n");
			ram_size = 0x20000000;
		} else {
			debug("Old PCB version: Memory size fix 0x40000000 on Quad CPU\n");
			ram_size = 0x40000000;
		}

	} else {
		/*
		 * On Quad module always 4 memory chips are mounted but on Solo version has only 2
		 * thus DDR3 memory size is on SOLO version two times lower.
		 */
		if(id0 == 0)
		{
			if(id1 == 0) /* 1 GBit densitiy */
			{
				if (get_board_rev() == MX6S) {
					ram_size = 0x10000000;
					debug("\n ids: 0  0 -> 0x10000000 on solo\n");
				} else {
					ram_size = 0x20000000;
					debug("\n ids: 0  0 -> 0x20000000 on quad\n");
				}
			}
			else /* 2 GBit densitiy */
			{
				if (get_board_rev() == MX6S) {
					ram_size = 0x20000000;
					debug("\n ids: 0  1 -> 0x20000000 on solo\n");
				} else {
					ram_size = 0x40000000;
					debug("\n ids: 0  1 -> 0x40000000 on quad\n");
				}
			}
		}
		else
		{
			if(id1 == 0) /* 4 GBit densitiy */
			{
				if (get_board_rev() == MX6S) {
					ram_size = 0x40000000;
					debug("\n ids: 1  0 -> 0x40000000 on solo\n");
				} else {
					ram_size = 0x80000000;
					debug("\n ids: 1  0 -> 0x80000000 on quad\n");
				}
			}
			else /* 8 GBit densitiy */
			{
				if (get_board_rev() == MX6S) {
					ram_size = 0x80000000;
					debug("\n ids: 1  1 -> 0x80000000 on solo\n");
				} else {
					/* 3840 MB = Max value of RAM supported by iMX6 processor */
					ram_size = 0xF0000000;
					debug("\n ids: 1  1 -> 0xf0000000 on quad\n");
				}
			}
		}
	}
#endif
	gd->ram_size = imx_ddr_size();

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
	 *  To read boot select configuration is changed designed for pins purpose
	 *  from PCIe reset (GPIO output) to Boot Select (GPIO input).
	 *
	 */
	SETUP_IOMUX_PADS(boot_sel_pads);

	/* Get the state of the Boot Select pins */
	gpio_direction_input(IMX_GPIO_NR(3, 13));	/* BOOT SEL 0 = PCIE_A_RST_IMX pin */
	gpio_direction_input(IMX_GPIO_NR(3, 14));	/* BOOT SEL 1 = PCIE_B_RST_IMX pin */
	gpio_direction_input(IMX_GPIO_NR(3, 15));	/* BOOT SEL 2 = PCIE_C_RST_IMX pin */
	/*
	 * Enable Boot Select feature :
	 *  1/ When GPB2_GPIO3_1V8 = High or unconnected,
	 *	PCIE_x_RST_IMX_n function will stay unchanged
	 *
	 * 2/ When tied LOW, I_PCIE_x_RST_IMX_n signals will become CPLD outputs asserted as
	 *	I_PCIE_A_RST_IMX_n<=I_BOOT_SEL0_n
	 *	I_PCIE_B_RST_IMX_n<=I_BOOT_SEL1_n
	 *	I_PCIE_C_RST_IMX_n<=I_BOOT_SEL2_n
	 */
	gpio_direction_output(IMX_GPIO_NR(2, 3), 0);	/* Enable Boot select = GPB2_GPIO3_1V8 pin */

	boot_sel = gpio_get_value(IMX_GPIO_NR(3, 13)) & 0x1;
	boot_sel |= (gpio_get_value(IMX_GPIO_NR(3, 14)) & 0x1) << 1;
	boot_sel |= (gpio_get_value(IMX_GPIO_NR(3, 15)) & 0x1) << 2;

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
	printf("Selected Boot source: %s\n", boot_selects[boot_sel]);

	/* Disable Boot Select feature */
	gpio_direction_output(IMX_GPIO_NR(2, 3), 1);
	gpio_direction_output(IMX_GPIO_NR(3, 13), 0); /* Set the PCIE_A_RST_IMX pin to low to possibly workaround a PCIe issue */
	gpio_direction_output(IMX_GPIO_NR(3, 14), 0); /* Set the PCIE_B_RST_IMX pin to low to possibly workaround a PCIe issue */
	gpio_direction_output(IMX_GPIO_NR(3, 15), 0); /* Set the PCIE_C_RST_IMX pin to low to possibly workaround a PCIe issue */

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

	/* Workaround : normally clock for SPI module is enabled by Freescale Bootstrap
	 * but in case of loading U-Boot via e.g. BDI none is eager to do that.
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

#ifdef CONFIG_FSL_ESDHC

struct fsl_esdhc_cfg usdhc_cfg[4] = {
	{USDHC1_BASE_ADDR, 1},
	{USDHC2_BASE_ADDR, 1},
	{USDHC3_BASE_ADDR, 1},
	{USDHC4_BASE_ADDR, 1},
};

int board_mmc_getcd(struct mmc *mmc)
{
	struct fsl_esdhc_cfg *cfg = (struct fsl_esdhc_cfg *)mmc->priv;

	int retval = 0;

	/* only SDIO (USDHC3) has a CardDetect */
	if(cfg->esdhc_base == USDHC3_BASE_ADDR)
	{
		gpio_direction_input(IMX_GPIO_NR(6, 14));

		retval = gpio_get_value(IMX_GPIO_NR(6, 14));
		if(retval == 0)
		{
			gpio_direction_output(IMX_GPIO_NR(1, 29), 0);

			gpio_set_value(IMX_GPIO_NR(1, 29), 1);
		}
	}

	return !retval;
}

#define SYSCTL_OFS		0x2c
#define SYSCTL_IPP_RST_N	0x00800000

int board_mmc_init(bd_t *bis)
{
	int ret = 0;

	/* Reset eMMC device first */
	uint *usdhc4_sysctl = (uint *)(USDHC4_BASE_ADDR + SYSCTL_OFS);
	clrbits_le32(usdhc4_sysctl, SYSCTL_IPP_RST_N);
	udelay(1000);
	setbits_le32(usdhc4_sysctl, SYSCTL_IPP_RST_N);

	SETUP_IOMUX_PADS(usdhc2_pads);
	SETUP_IOMUX_PADS(usdhc3_pads);
	SETUP_IOMUX_PADS(usdhc4_pads);

	usdhc_cfg[1].sdhc_clk = mxc_get_clock(MXC_ESDHC2_CLK);
	usdhc_cfg[2].sdhc_clk = mxc_get_clock(MXC_ESDHC3_CLK);
	usdhc_cfg[3].sdhc_clk = mxc_get_clock(MXC_ESDHC4_CLK);

	ret |= fsl_esdhc_initialize(bis, &usdhc_cfg[1]);
	ret |= fsl_esdhc_initialize(bis, &usdhc_cfg[2]);
	ret |= fsl_esdhc_initialize(bis, &usdhc_cfg[3]);

	return ret;
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

int board_eth_init(bd_t *bis)
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
	gpio_direction_output(IMX_GPIO_NR(7, 12), 0);
	mdelay(2);
	gpio_set_value(IMX_GPIO_NR(7, 12), 1);

	return 0;
}
#endif

#if defined(CONFIG_VIDEO_IPUV3)

struct display_info_t {
	int	bus;
	int	addr;
	int	pixfmt;
	int	(*detect)(struct display_info_t const *dev);
	void	(*enable)(struct display_info_t const *dev);
	struct	fb_videomode mode;
	int lvds_clock;
};

void setup_display(ulong );

static int detect_default(struct display_info_t const *dev)
{
	return 1;
}

iomux_v3_cfg_t backlight_pads[] = {
	IOMUX_PADS(PAD_SD1_CMD__GPIO1_IO18 | MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_SD1_DAT0__GPIO1_IO16 | MUX_PAD_CTRL(GPIO_PAD_CTRL)),
	IOMUX_PADS(PAD_SD1_DAT1__GPIO1_IO17 | MUX_PAD_CTRL(GPIO_PAD_CTRL)),
};

void enable_lvds(void)
{
	struct iomuxc *iomux = (struct iomuxc *)
				IOMUXC_BASE_ADDR;
	u32 reg = readl(&iomux->gpr[2]);
	reg |= IOMUXC_GPR2_DATA_WIDTH_CH0_24BIT;
	writel(reg, &iomux->gpr[2]);
	SETUP_IOMUX_PADS(backlight_pads);

	/* Enable back light for LVDS */
	gpio_direction_output(IMX_GPIO_NR(1, 18), 1);
	gpio_direction_output(IMX_GPIO_NR(1, 16), 1);
	gpio_direction_output(IMX_GPIO_NR(1, 17), 1);
}

static void enable_lvds_and_display(struct display_info_t const *dev)
{
	setup_display(dev->lvds_clock);
	enable_lvds ();
}

static struct display_info_t displays[] = {{
	.bus	= -1,
	.addr	= 0,
	.pixfmt	= IPU_PIX_FMT_LVDS666,
	.detect	= detect_default,
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
	.mode	= {
		.name           = "LCD_800x600@LVDS",
		.refresh        = 60,
		.xres           = 800,
		.yres           = 600,
		.pixclock       = 25000, /* 40.0 MHz */
		.left_margin    = 88,
		.right_margin   = 40,
		.upper_margin   = 23,
		.lower_margin   = 1,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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
	.enable	= enable_lvds_and_display,
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


void splash_load_from_spi(void)
{
	int ret;
	unsigned char *tmp_splash = (unsigned char *)CONFIG_SPLASH_IMG_ADDR;
	struct spi_flash *splash_flash;

	splash_flash = spi_flash_probe(CONFIG_SF_DEFAULT_BUS, CONFIG_SF_DEFAULT_CS,
			CONFIG_SF_DEFAULT_SPEED, CONFIG_SF_DEFAULT_MODE);

	if (!splash_flash) {
		printf ("Loading bootlogo from SPI Flash failed in flash_probe\n");
		return;
	}

	ret = spi_flash_read(splash_flash, CONFIG_SPLASH_OFFSET,
					CONFIG_SPLASH_SIZE, tmp_splash);

	if (ret) {
		printf ("Loading bootlogo from SPI Flash failed in flash_read\n");
		return;
	}
}

int board_video_init(void)
{
	int i;
	int ret;
	char const *panel = env_get("panel");
	ulong lvds_clk = env_get_ulong("panel_lvds_clk", 10, 0);
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
				if (lvds_clk > 0)
					displays[i].lvds_clock = lvds_clk;
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
		ret = -EINVAL;
	}
	return (0 != ret);
}

int board_video_skip(void)
{
	static int init=0, skip;

	if (!init) {
		/* Always load splashimage from SPI Flash to RAM */
		env_set_addr("splashimage", (const void*)CONFIG_SPLASH_IMG_ADDR);
		splash_load_from_spi();
		skip = board_video_init();
		init = 1;
	}
	return (skip);
}

#define PFD_528_CLK				528 			/* [MHz] */
#define PFD_528_CLK_MUL			18
#define PFD_528_CLK_DIV_LOW		12
#define PFD_528_CLK_DIV_HI		35
#define LVDS_CLK_MUL			7

/* calculate PLL2 PFD0_FRAC */
#define PFD_528_DIVIDER(_LVDS_CLK_)								\
	(PFD_528_CLK * PFD_528_CLK_MUL / LVDS_CLK_MUL)/(_LVDS_CLK_)

void setup_display(ulong lvds_clk)
{
	struct mxc_ccm_reg *mxc_ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;
	struct anatop_regs *anatop = (struct anatop_regs *)ANATOP_BASE_ADDR;
	struct iomuxc *iomux = (struct iomuxc *)IOMUXC_BASE_ADDR;

	int reg, pfd_frac_div = PFD_528_CLK_DIV_HI;

	/* Turn on LDB0,IPU,IPU DI0 clocks */
	reg = __raw_readl(&mxc_ccm->CCGR3);
	reg |=   MXC_CCM_CCGR3_IPU1_IPU_MASK
		|MXC_CCM_CCGR3_LDB_DI0_MASK;
	writel(reg, &mxc_ccm->CCGR3);

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

	reg = readl(&mxc_ccm->cs2cdr);
	reg &= ~(MXC_CCM_CS2CDR_LDB_DI0_CLK_SEL_MASK
		 |MXC_CCM_CS2CDR_LDB_DI1_CLK_SEL_MASK);
	reg |= (1<<MXC_CCM_CS2CDR_LDB_DI0_CLK_SEL_OFFSET)
	      |(1<<MXC_CCM_CS2CDR_LDB_DI1_CLK_SEL_OFFSET);
	writel(reg, &mxc_ccm->cs2cdr);

	reg = readl(&mxc_ccm->cscmr2);
	reg |= MXC_CCM_CSCMR2_LDB_DI0_IPU_DIV;
	writel(reg, &mxc_ccm->cscmr2);

	reg = readl(&mxc_ccm->chsccdr);
	reg &= ~(MXC_CCM_CHSCCDR_IPU1_DI0_PRE_CLK_SEL_MASK
		|MXC_CCM_CHSCCDR_IPU1_DI0_PODF_MASK
		|MXC_CCM_CHSCCDR_IPU1_DI0_CLK_SEL_MASK);
	reg |= (CHSCCDR_CLK_SEL_LDB_DI0
		<<MXC_CCM_CHSCCDR_IPU1_DI0_CLK_SEL_OFFSET)
	      |(CHSCCDR_PODF_DIVIDE_BY_3
		<<MXC_CCM_CHSCCDR_IPU1_DI0_PODF_OFFSET)
	      |(CHSCCDR_IPU_PRE_CLK_540M_PFD
		<<MXC_CCM_CHSCCDR_IPU1_DI0_PRE_CLK_SEL_OFFSET);
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
	reg = (reg & ~IOMUXC_GPR3_LVDS0_MUX_CTL_MASK)
	    | (IOMUXC_GPR3_MUX_SRC_IPU1_DI0
	       <<IOMUXC_GPR3_LVDS0_MUX_CTL_OFFSET);
	writel(reg, &iomux->gpr[3]);
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

	if(get_board_rev() == MX6Q) {
		setup_i2c(0, CONFIG_SYS_MXC_I2C1_SPEED, 0x7f, &i2c_pad_info0);
		setup_i2c(1, CONFIG_SYS_MXC_I2C2_SPEED, 0x7f, &i2c_pad_info1);
		setup_i2c(2, CONFIG_SYS_MXC_I2C3_SPEED, 0x7f, &i2c_pad_info2);
	} else if (get_board_rev() == MX6S) {
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

#ifdef CONFIG_MXC_SPI
int board_spi_cs_gpio(unsigned bus, unsigned cs)
{
	return (bus == CONFIG_SF_DEFAULT_BUS && cs == CONFIG_SF_DEFAULT_CS) ? (IMX_GPIO_NR(3, 24)) : -1;
}
#endif

int checkboard(void)
{
	puts("Board: " IDENT_STRING IDENT_RELEASE "\n");

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

extern char *print_if_avail (char *);

int ft_board_setup(void *blob, bd_t *bd) {
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
	if(get_board_rev() == MX6S)
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

#ifdef CONFIG_SPL_BUILD
#include <linux/libfdt.h>
#include <spl.h>
#include <asm/arch/mx6-ddr.h>
/* configure different ddr_sysinfo for mx6q! */
static struct mx6_ddr_sysinfo mx6q_sysinfo = {
	.ddr_type = DDR_TYPE_DDR3,
	.dsize = 2,		/* size of bus (2=64bit) */
	.cs_density = 18,	/* config for full 4GB range */
	.ncs = 1,
	.cs1_mirror = 0,
	.rtt_nom = 2,		/* RTT_Nom = RZQ/2 */
	.rtt_wr = 2,
	.walat = 0,		/* Write additional latency */
	.ralat = 5,		/* Read additional latency */
	.mif3_mode = 3,		/* Command prediction working mode */
	.bi_on = 1,		/* Bank interleaving enabled */
	.sde_to_rst = 0x10,	/* 14 cycles, 200us (JEDEC default) */
	.rst_to_cke = 0x23,	/* 33 cycles, 500us (JEDEC default) */
	.refsel = 1,		/* Refresh cycles at 32KHz */
	.refr = 7,		/* 8 refresh commands per refresh cycle */
};

static const struct mx6_ddr3_cfg mem_ddr_2g = {
	.mem_speed	= 1600,
	.density	= 2,	/* density 2Gb */
	.width		= 16,	/* width of DRAM device */
	.banks		= 8,
	.rowaddr	= 14,
	.coladdr	= 10,
	.pagesz		= 2,
	.trcd		= 1375,
	.trcmin		= 4875,
	.trasmin	= 3500,
	.SRT		= 0,
};

static const struct mx6_ddr3_cfg mem_ddr_4g = {
	.mem_speed	= 1600,
	.density	= 4,		/* density 4Gb */
	.width		= 16,
	.banks		= 8,
	.rowaddr	= 15,
	.coladdr	= 10,
	.pagesz		= 2,
	.trcd		= 1375,
	.trcmin		= 4875,
	.trasmin	= 3500,
	.SRT		= 0,
};

static const struct mx6_mmdc_calibration mx6s_calibration = {
	.p0_mpwldectrl0 =  0x0040003c,
	.p0_mpwldectrl1 =  0x0032003e,
	.p0_mpdgctrl0 =    0x42350231,
	.p0_mpdgctrl1 =    0x021a0218,
	.p0_mprddlctl =    0x4b4b4e49,
	.p0_mpwrdlctl =    0x3f3f3035,
};

static struct mx6_mmdc_calibration mx6dq_calib = {
	.p0_mpwldectrl0 = 0x0025001f,
	.p0_mpwldectrl1 = 0x00290027,
	.p1_mpwldectrl0 = 0x001f002b,
	.p1_mpwldectrl1 = 0x000f0029,
	.p0_mpdgctrl0 = 0x42740304,
	.p0_mpdgctrl1 = 0x026e0265,
	.p1_mpdgctrl0 = 0x02750306,
	.p1_mpdgctrl1 = 0x02720244,
	.p0_mprddlctl = 0x463d4041,
	.p1_mprddlctl = 0x42413c47,
	.p0_mpwrdlctl = 0x37414441,
	.p1_mpwrdlctl = 0x4633473b,
};

static void ccgr_init(void)
{
	struct mxc_ccm_reg *ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;

	writel(0x00C03F3F, &ccm->CCGR0);
	writel(0x0030FC03, &ccm->CCGR1);
	writel(0x0FFFC000, &ccm->CCGR2);
	writel(0x3FF00000, &ccm->CCGR3);
	writel(0x00FFF300, &ccm->CCGR4);
	writel(0x0F0000C3, &ccm->CCGR5);
	writel(0x000003FF, &ccm->CCGR6);
}

const struct mx6dq_iomux_ddr_regs amx6dq_ddr_ioregs = {
	.dram_dqm0 = 0x00020030,
	.dram_dqm1 = 0x00020030,
	.dram_dqm2 = 0x00020030,
	.dram_dqm3 = 0x00020030,
	.dram_dqm4 = 0x00020030,
	.dram_dqm5 = 0x00020030,
	.dram_dqm6 = 0x00020030,
	.dram_dqm7 = 0x00020030,
	.dram_ras = 0x00020030,
	.dram_cas = 0x00020030,
	.dram_sdodt0 = 0x00003030,
	.dram_sdodt1 = 0x00003030,
	.dram_sdba2 = 0x00000000,
	.dram_sdcke0 = 0x00003000,
	.dram_sdcke1 = 0x00003000,
	.dram_sdclk_0 = 0x00020030,
	.dram_sdclk_1 = 0x00020030,
	.dram_sdqs0 = 0x00000030,
	.dram_sdqs1 = 0x00000030,
	.dram_sdqs2 = 0x00000030,
	.dram_sdqs3 = 0x00000030,
	.dram_sdqs4 = 0x00000030,
	.dram_sdqs5 = 0x00000030,
	.dram_sdqs6 = 0x00000030,
	.dram_sdqs7 = 0x00000030,
	.dram_reset = 0x00020030,
};

const struct mx6dq_iomux_grp_regs amx6dq_grp_ioregs = {
	.grp_addds = 0x00000030,
	.grp_ddrmode_ctl = 0x00020000,
	.grp_ddrpke = 0x00000000,
	.grp_ddrmode = 0x00020000,
	.grp_b0ds = 0x00000030,
	.grp_b1ds = 0x00000030,
	.grp_ctlds = 0x00000030,
	.grp_ddr_type = 0x000c0000,
	.grp_b2ds = 0x00000030,
	.grp_b3ds = 0x00000030,
	.grp_b4ds = 0x00000030,
	.grp_b5ds = 0x00000030,
	.grp_b6ds = 0x00000030,
	.grp_b7ds = 0x00000030,
};

static void spl_dram_init(void)
{
	switch (get_cpu_type()) {
		case MXC_CPU_MX6Q:
		case MXC_CPU_MX6D:
			mx6dq_dram_iocfg(64, &amx6dq_ddr_ioregs,
			                 &amx6dq_grp_ioregs);
			mx6_dram_cfg(&mx6q_sysinfo, &mx6dq_calib, &mem_ddr_4g);
			break;
		case MXC_CPU_MX6SOLO:
		#if 0
			mx6sdl_dram_iocfg(32, &mx6_ddr_ioregs,
			                 &mx6_grp_ioregs);
			mx6_dram_cfg(&sysinfo, &mx6_calibration, &mem_ddr_2g);
		#endif
			break;
		case MXC_CPU_MX6DL:
		#if 0
			mx6sdl_dram_iocfg(64, &mx6_ddr_ioregs,
			                 &mx6_grp_ioregs);
			mx6_dram_cfg(&sysinfo, &mx6_mmcd_calib, &mem_ddr);
		#endif
			break;
		default:
			puts("Error: CPU type not supported\n");
			break;
	}

	udelay(100);
}

void board_init_f(ulong dummy)
{
	memset((void *)gd, 0, sizeof(struct global_data));

	/* setup AIPS and disable watchdog */
	arch_cpu_init();

	ccgr_init();
	/*
	 * enable AXI cache for VDOA/VPU/IPU and
	 * set IPU AXI-id0 Qos=0xf(bypass) AXI-id1 Qos=0x7
	 */
	gpr_init();

	/* iomux uart and spi setup */
	board_early_init_f();

	/* setup GP timer */
	timer_init();

	/* UART clocks enabled and gd valid - init serial console */
	preloader_console_init();

	/* DDR initialization */
	spl_dram_init();

	/* Clear the BSS. */
	memset(__bss_start, 0, __bss_end - __bss_start);

	/* load/boot image from boot device */
	board_init_r(NULL, 0);
}
#endif
