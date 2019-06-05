#
# (C) Copyright 2017
# Thomas Schaefer, Kontron Europe GmbH, thomas.schaefer@kontron.com
#
# SPDX-License-Identifier:	GPL-2.0+
#

obj-$(CONFIG_KEX_IMX_WATCHDOG) += imx_watchdog.o

ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_CMD_MMC_RAW_ECSD) += cmd_mmc_raw_ecsd.o
obj-$(CONFIG_CMD_KBOARDINFO) += cmd_kboardinfo.o
obj-$(CONFIG_EMB_EEP_SPI) += emb_spi.o
obj-$(CONFIG_EMB_EEP_I2C_EEPROM) += emb_eep.o

# if kjtag support is required, include jamStapl
obj-$(CONFIG_JAM_STAPL) += jamStapl/
endif
