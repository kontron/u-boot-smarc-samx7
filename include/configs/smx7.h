/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2017 Kontron Europe GmbH
 *
 * Configuration settings for the Kontron SMARC SMX7 board.
 */

#ifndef __SMX7_CONFIG_H
#define __SMX7_CONFIG_H

#ifdef CONFIG_SPL
#include "imx7_spl.h"

#ifndef CONFIG_SECURE_BOOT
#define CONFIG_SPL_TARGET		"u-boot-with-spl.imx"
#endif
#endif

#include "mx7_common.h"

#define CONFIG_MXC_UART_BASE            UART6_IPS_BASE_ADDR

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(32 * SZ_1M)

/******************************************************************************
 * Miscellaneous configurable options
 */
#define CONFIG_MISC_INIT_R
#ifdef CONFIG_SPL_BUILD
#undef CONFIG_CMD_KBOARDINFO
#undef CONFIG_KBOARDINFO_MODULE
#undef CONFIG_EMB_EEP_I2C_EEPROM
#undef CONFIG_DM_SPI_FLASH
#undef CONFIG_DM_SPI
#endif

#ifdef CONFIG_CMD_KBOARDINFO
/* #define CONFIG_KBOARDINFO_CARRIER */

#define CONFIG_HAS_ETH0
#define CONFIG_HAS_ETH1

#define D_ETHADDR                       "02:00:00:01:00:44"
#define D_ETH1ADDR                      "02:00:00:01:00:45"
#endif

/******************************************************************************
 * Network
 */
#define CONFIG_FEC_MXC
#define CONFIG_FEC_XCV_TYPE             RGMII
#define CONFIG_ETHPRIME                 "FEC0"
#define CONFIG_FEC_MXC_PHYADDR          0

/* ENET1 */
#define IMX_FEC_BASE			ENET_IPS_BASE_ADDR

/******************************************************************************
 * MMC Config
 */
#undef CONFIG_BOOTM_NETBSD
#undef CONFIG_BOOTM_PLAN9
#undef CONFIG_BOOTM_RTEMS

/******************************************************************************
 * I2C Configs
 */
#define CONFIG_SYS_I2C_MXC
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_SYS_I2C_MXC_I2C1         /* enable I2C bus 1 */
#define CONFIG_SYS_MXC_I2C1_SPEED       100000
#define CONFIG_SYS_I2C_MXC_I2C2         /* enable I2C bus 2 */
#define CONFIG_SYS_MXC_I2C2_SPEED       100000
#define CONFIG_SYS_I2C_MXC_I2C3         /* enable I2C bus 3 */
#define CONFIG_SYS_MXC_I2C3_SPEED       100000
#define CONFIG_SYS_I2C_MXC_I2C4         /* enable I2C bus 4 */
#define CONFIG_SYS_MXC_I2C4_SPEED       100000

#define CONFIG_SUPPORT_EMMC_BOOT	/* eMMC specific */
#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

/******************************************************************************
 * USB Configs
 */
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_MXC_USB_PORTSC           (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS            0
#define CONFIG_USB_MAX_CONTROLLER_COUNT 3
#define CONFIG_MX7_USB_HSIC_PORTSC      (PORT_PTS_HSIC | PORT_PTS_PTW)

#define CONFIG_USBD_HS

/******************************************************************************
 * Environment organization
 */
#define CONFIG_CMDLINE_PS_SUPPORT

#ifdef CONFIG_IMX_BOOTAUX
/* Set to QSPI1 A flash at default */
#define CONFIG_SYS_AUXCORE_BOOTDATA 0x60000000

#define UPDATE_M4_ENV \
        "m4image=m4_qspi.bin\0" \
        "loadm4image=load mmc 0:1 ${loadaddr} ${m4image}\0" \
        "update_m4_from_sd=" \
                "sf probe 0:0 && " \
                "run loadm4image && " \
                "setexpr fw_sz ${filesize} + 0xffff; "  \
                "setexpr fw_sz ${fw_sz} / 0x10000; "    \
                "setexpr fw_sz ${fw_sz} * 0x10000; "    \
                "sf erase 0x0 ${fw_sz} && " \
                "sf write ${loadaddr} 0x0 ${filesize}" "\0" \
        "m4boot=sf probe 0:0; bootaux "__stringify(CONFIG_SYS_AUXCORE_BOOTDATA)"\0"
#else
#define UPDATE_M4_ENV ""
#endif

#if 0
#define CONFIG_EXTRA_ENV_SETTINGS \
        UPDATE_M4_ENV \
        "autoload=no" "\0" \
        "set_fdtfile=setenv fdtfile imx7${core_variant}-samx7-${panel}.dtb;" "\0" \
        "clear_env=sf probe 0 && sf erase " __stringify(CONFIG_ENV_OFFSET) " 10000" "\0" \
        "console=ttymxc0" "\0" \
        "fdt_addr=0x83000000" "\0" \
        "fdt_high=0xffffffff" "\0" \
        "image=zImage" "\0" \
        "initrd_high=0xffffffff" "\0" \
        "panel=ld101" "\0" \
        "pcie_a_prsnt=yes" "\0" \
        "pcie_b_prsnt=yes" "\0" \
        "pcie_c_prsnt=yes" "\0" \
        "pwm_out_disable=yes" "\0" \
        "bootm_boot_mode=sec" "\0" \
        "bootfailed=echo Booting failed from all boot sources && false" "\0" \
        "bootos=run setbootargs && " \
                "run loadimage && " \
                "run loadfdt && " \
                "bootz ${loadaddr} - ${fdt_addr} || false" "\0" \
        "bootsel_boot=echo BOOT_SEL ${boot_sel} selected && run ${boot_sel}_boot" "\0" \
        "module_mmc_boot=run mmcboot" "\0" \
        "module_spi_boot=run mmcboot" "\0" \
        "loadimage=load ${intf} ${bdev}:${bpart} ${loadaddr} /boot/${image}" "\0" \
        "loadfdt=run set_fdtfile && load ${intf} ${bdev}:${bpart} ${fdt_addr} /boot/${fdtfile}" "\0" \
        "setbootargs=setenv bootargs console=${console},${baudrate} root=${rootpath}" "\0" \
        "mmcroot=/dev/mmcblk2p1 rootwait rw" "\0" \
        "mmcboot=echo Booting from mmc ... && " \
                "setenv bdev 1 && setenv bpart 1 && setenv intf mmc && " \
                "mmc dev ${bdev} && setenv rootpath ${mmcroot} && " \
                "run bootos" "\0" \
        "netsetbootargs=bootp && setenv bootargs console=${console},${baudrate} root=/dev/nfs ip=dhcp " \
                "nfsroot=${serverip}:${nfsrootpath},v3,tcp mipi_dsi_samsung.lvds_freq=50" "\0" \
        "nfsrootpath=/srv/export/samx7" "\0" \
        "netboot=echo Booting from net ...; " \
                "run netsetbootargs && " \
                "tftp ${loadaddr} ${image} && " \
                "run set_fdtfile && tftp ${fdt_addr} ${fdtfile} && " \
                "bootz ${loadaddr} - ${fdt_addr} || false" "\0" \
        "sdroot=/dev/mmcblk0p1 rootwait rw" "\0" \
        "sdboot=echo Booting from SD card ... && " \
                "setenv bdev 0 && setenv bpart 1 && setenv intf mmc && " \
                "mmc dev ${bdev} && setenv rootpath ${sdroot} && " \
                "run bootos" "\0" \
        "usbroot=/dev/sda1 rootwait rw" "\0" \
        "usbboot=echo Booting from USB ... && " \
                "setenv bdev 0 && setenv bpart 1 && setenv intf usb && " \
                "usb start && usb dev ${bdev} && setenv rootpath ${usbroot} && " \
                "run bootos" "\0" \
        "qspi_header_file=qspi-header.bin" "\0" \
        "uboot_update_file=u-boot-smx7-spl.imx" "\0" \
        "uboot_install=bootp && tftp 80800000 ${qspi_header_file} && tftp 88000000 ${uboot_update_file} && " \
                "sf probe 0 && sf erase 0 80000 && sf write 80800000 0 200 && sf write 88000000 400 ${filesize}" "\0" \
        "uboot_update=bootp && tftp 88000000 ${uboot_update_file} && " \
                "sf probe 0 && sf read 80800000 0 200 && sf erase 0 80000 && " \
                "sf write 80800000 0 200 && sf write 88000000 400 ${filesize}" "\0"

#define CONFIG_BOOTCOMMAND \
        "run mmcboot || run sdboot || run usbboot || run netboot || run bootfailed"
#else
#define CONFIG_EXTRA_ENV_SETTINGS \
        "autoload=no" "\0" \
        "bootm_boot_mode=sec" "\0" \
        "fdt_high=0xffffffff" "\0" \
        "initrd_high=0xffffffff" "\0" \
        "updfile=update_smx7_spl/update" "\0" \
        "updNet=bootp; if tftp $loadaddr $updfile; then setenv loader tftp; source $loadaddr; else run updFal; fi" "\0" \
        "updUsb=usb start && usb dev 0 && load usb 0:1 $loadaddr $updfile && setenv loader load usb 0:1 && source $loadaddr && true" "\0" \
        "updFal=echo update failed" "\0" \
        "update=run updUsb || run updFal" "\0"

#define CONFIG_BOOTCOMMAND \
	"echo Exit to CLI"
#endif

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

/* Physical Memory Map */
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)


#define CONFIG_SYS_FSL_USDHC_NUM        2

#define CONFIG_IMX_THERMAL

#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_MXS
#define CONFIG_VIDEO_LOGO
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_VIDEO_BMP_LOGO
#endif

#endif	/* __CONFIG_H */
