/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2012-2918 Kontron Europe GmbH
 *
 * Configuration settings for the Kontron sAMX6 board.
 */

#ifndef __AMX6_CONFIG_H
#define __AMX6_CONFIG_H

#ifdef CONFIG_SPL
#include "imx6_spl.h"

#define CONFIG_SYS_SPI_U_BOOT_OFFS	0x11400
#define CONFIG_SPL_TARGET		"u-boot-with-spl.imx"
#endif

#include "mx6_common.h"

#define CONFIG_MACH_TYPE		4329

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(10 * 1024 * 1024)


/******************************************************************************
 * Miscellaneous configurable options
 */
#define CONFIG_MISC_INIT_R

#define CONFIG_CMD_MD5SUM
#define CONFIG_MD5
#define CONFIG_MD5SUM_VERIFY

#ifdef CONFIG_SPL_BUILD
#undef CONFIG_CMD_KBOARDINFO
#undef CONFIG_KBOARDINFO_MODULE
#undef CONFIG_EMB_EEP_I2C_EEPROM
#endif

#define CONFIG_HAS_ETH0

#define D_ETHADDR                       "88:88:88:88:87:88"

#define CONFIG_SAP_NAME			"SK-FIRM-UBOOT-AMX6"
#define CONFIG_SAP_NUM			"1053-6042"

#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "

#undef CONFIG_SYS_CBSIZE
#define CONFIG_SYS_CBSIZE		1024
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_ARP_TIMEOUT		200UL

#define CONFIG_SYS_MEMTEST_START	0x20000000
#define CONFIG_SYS_MEMTEST_END		0x30000000

/* don't use the default CONFIG_LOADADDR */
#undef CONFIG_LOADADDR
#define CONFIG_LOADADDR			0x10800000
#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR

#define CONFIG_PREBOOT


/******************************************************************************
 * UART
 */
#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART1_BASE


/******************************************************************************
 * Network
 */
#define CONFIG_FEC_MXC
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RGMII
#define CONFIG_ETHPRIME			"FEC"
#define CONFIG_FEC_MXC_PHYADDR		1

#define CONFIG_PHY_BROADCOM


/******************************************************************************
 * I2C Configs
 */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_MXC_I2C1_SPEED	100000
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_MXC_I2C2_SPEED	100000
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */
#define CONFIG_SYS_MXC_I2C3_SPEED	100000
#define CONFIG_I2C_MULTI_BUS


/******************************************************************************
 * MMC Configs
 */
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
/* #define CONFIG_SYS_FSL_USDHC_NUM	3 */

#ifdef CONFIG_SPL_BUILD
#undef CONFIG_CMD_MMC_RAW_ECSD
#endif

#undef CONFIG_BOOTM_NETBSD
#undef CONFIG_BOOTM_PLAN9
#undef CONFIG_BOOTM_RTEMS


/******************************************************************************
 * Environment organization
 */
#define CONFIG_ENV_SIZE			(32 * 1024)

#define CONFIG_ENV_OFFSET		(768 * 1024) /* Base ENV : 0xC0000 */
#define CONFIG_ENV_OFFSET_REDUND	(800 * 1024) /* Redundant ENV :0xC8000 */
#define CONFIG_ENV_SIZE_REDUND		(CONFIG_ENV_SIZE)
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT

#if 0
#define CONFIG_ENV_OLD_DETECT
#define CONFIG_ENV_OLD_OFFSET		(768 * 1024) /* Base OLD ENV : 0xC0000 */
#define CONFIG_ENV_OLD_SIZE		(8 * 1024) /* 0x2000 */
#endif

#define CONFIG_ENV_SECT_SIZE		(8 * 1024)

#define CONFIG_ENV_SPI_BUS		CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS		CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED


/******************************************************************************
 * USB Configs
 */
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET


/******************************************************************************
 * Framebuffer and LCD
 */
#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_IPUV3
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_BMP_GZIP
#define CONFIG_SYS_VIDEO_LOGO_MAX_SIZE  (2 << 20)
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO	/* Enable attaching to U-Boot image Kontron Logo */
#endif


#define CONFIG_EXTRA_ENV_SETTINGS \
	"netdev=eth0\0"	\
	"ethprime=FEC\0" \
	"ethact=FEC\0" \
	"machid=10e9\0" \
	"uimage=uImage\0" \
	"console=ttymxc0\0" \
	"mmcdev=1\0" \
	"mmcpart=1\0" \
	"fdt_high=0xffffffff\0" \
	"fdtaddr=11000000\0"	\
	"fdtfile=smx6.dtb\0" \
	"panel=off\0" \
	"mmcroot=/dev/mmcblk1p1 rootwait rw\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"root=${mmcroot}\0" \
	"loaduimage=ext2load mmc ${mmcdev}:${mmcpart} ${loadaddr} ${uimage}\0" \
	"loadfdt=ext2load mmc ${mmcdev}:${mmcpart} ${fdtaddr} ${fdtfile}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"bootm ${loadaddr} - ${fdtaddr}\0" \
	"netargs=setenv bootargs console=${console},${baudrate} " \
		"root=/dev/nfs " \
		"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
	"netboot=echo Booting from net ...; " \
		"tftp ${fdtaddr} ${fdtfile};" \
		"tftp ${loadaddr} ${uimage};" \
		"bootm ${loadaddr} - ${fdtaddr}\0" \


#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev};" \
	"if mmc rescan; then " \
	    "if run loaduimage; then " \
			"if run loadfdt; then " \
	           "run mmcboot; " \
             "else run netboot; " \
		"fi; " \
            "else run netboot; " \
	    "fi; " \
	"else run netboot; " \
	"fi; "


/******************************************************************************
 * Physical Memory Map
 */
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)


/******************************************************************************
 * SATA Configs
 */
#define CONFIG_CMD_SATA

#ifdef CONFIG_CMD_SATA
#define CONFIG_SATA
#define CONFIG_DWC_AHSATA
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_DWC_AHSATA_PORT_ID	0
#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
#define CONFIG_LBA48
#define CONFIG_LIBATA
#endif

#endif                         /* __AMX6_CONFIG_H */
