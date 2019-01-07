# SPDX-License-Identifier: GPL-2.0+
#
# Copyright (C) 2007, Guennadi Liakhovetski <lg@denx.de>
# Copyright (C) 2012-2018 Kontron Europe GmbH
#

ifdef IDENT_RELEASE
EXTRA_CFLAGS += -DIDENT_RELEASE=\"$(IDENT_RELEASE)\"
endif


obj-y  := amx6.o
obj-$(CONFIG_SPL_BUILD) += amx6_spl.o
obj-$(CONFIG_VIDEO_IPUV3) += amx6_display.o

obj-$(CONFIG_CMD_IMXOTP) += cmd_imxotp.o imx_otp.o
