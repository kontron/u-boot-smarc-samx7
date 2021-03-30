/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2012-2018 Kontron Europe GmbH
 *
 */

#include <common.h>
#include <linux/libfdt.h>
#include <spl.h>
#include <log.h>
#include <hang.h>
#include <init.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/mx6-ddr.h>
#include <asm/arch/mx6-pins.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch-imx/cpu.h>
#include <linux/delay.h>

#include "amx6_iomux.h"

static struct mx6_ddr_sysinfo amx6sdl_sysinfo = {
	.ddr_type = DDR_TYPE_DDR3,
	.dsize = 1,		/* size of bus (1=32bit) */
	.cs_density = 32,	/* config for full 4GB range */
	.ncs = 1,
	.cs1_mirror = 0,
	.rtt_nom = 1,		/* RTT_Nom = RZQ/4 */
	.rtt_wr = 2,
	.walat = 0,		/* Write additional latency */
	.ralat = 5,		/* Read additional latency */
	.mif3_mode = 3,		/* Command prediction working mode */
	.bi_on = 1,		/* Bank interleaving enabled */
	.sde_to_rst = 0x10,	/* 14 cycles, 200us (JEDEC default) */
	.rst_to_cke = 0x23,	/* 33 cycles, 500us (JEDEC default) */
	.pd_fast_exit = 0,
	.refsel = 1,		/* Refresh cycles at 32KHz */
	.refr = 3,		/* 4 refresh commands per refresh cycle */
};

static struct mx6_ddr_sysinfo mx6qdl_sysinfo = {
	.ddr_type = DDR_TYPE_DDR3,
	.dsize = 2,		/* size of bus (2=64bit) */
	.cs_density = 32,	/* config for full 4GB range */
	.ncs = 1,
	.cs1_mirror = 0,
	.rtt_nom = 1,		/* RTT_Nom = RZQ/2 */
	.rtt_wr = 2,
	.walat = 0,		/* Write additional latency */
	.ralat = 5,		/* Read additional latency */
	.mif3_mode = 3,		/* Command prediction working mode */
	.bi_on = 1,		/* Bank interleaving enabled */
	.sde_to_rst = 0x10,	/* 14 cycles, 200us (JEDEC default) */
	.rst_to_cke = 0x23,	/* 33 cycles, 500us (JEDEC default) */
	.pd_fast_exit = 0,
	.refsel = 1,		/* Refresh cycles at 64KHz */
	.refr = 3,		/* 4 refresh commands per refresh cycle */
};

static struct mx6_ddr3_cfg mem_ddr = {
	.mem_speed	= 1600,
	.density	= 2,		/* density 2 Gb */
	.width		= 16,
	.banks		= 8,
	.rowaddr	= 14,
	.coladdr	= 10,
	.pagesz		= 2,
	.trcd		= 1375,
	.trcmin		= 4875,
	.trasmin	= 3500,
	.SRT		= 0,
};

static const struct mx6_mmdc_calibration amx6s_calibration = {
	.p0_mpwldectrl0 =  0x001f004d,
	.p0_mpwldectrl1 =  0x001f001f,
	.p0_mpdgctrl0 =    0x020e0208,
	.p0_mpdgctrl1 =    0x01760178,
	.p0_mprddlctl =    0x40444d45,
	.p0_mpwrdlctl =    0x3f3e3f32,
};

static struct mx6_mmdc_calibration mx6dq_calibration = {
	.p0_mpwldectrl0 = 0x000b0017,
	.p0_mpwldectrl1 = 0x001f0010,
	.p1_mpwldectrl0 = 0x000b001c,
	.p1_mpwldectrl1 = 0x00090010,
	.p0_mpdgctrl0 = 0x03090318,
	.p0_mpdgctrl1 = 0x027d027d,
	.p1_mpdgctrl0 = 0x03100313,
	.p1_mpdgctrl1 = 0x02730252,
	.p0_mprddlctl = 0x433b3e41,
	.p1_mprddlctl = 0x423d3a44,
	.p0_mpwrdlctl = 0x44444944,
	.p1_mpwrdlctl = 0x4a414a44,
};

static struct mx6_mmdc_calibration mx6dl_calibration = {
	.p0_mpwldectrl0 = 0x001f0049,
	.p0_mpwldectrl1 = 0x001f001f,
	.p1_mpwldectrl0 = 0x001f002e,
	.p1_mpwldectrl1 = 0x001f001f,
	.p0_mpdgctrl0 = 0x02140211,
	.p0_mpdgctrl1 = 0x017a0201,
	.p1_mpdgctrl0 = 0x0205020d,
	.p1_mpdgctrl1 = 0x0162016f,
	.p0_mprddlctl = 0x3e464844,
	.p1_mprddlctl = 0x46494741,
	.p0_mpwrdlctl = 0x3d3e3a34,
	.p1_mpwrdlctl = 0x3f3a3a3f,
};

static void ccgr_init(void)
{
	struct mxc_ccm_reg *ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;

	writel(0x00c03f3f, &ccm->CCGR0);
	writel(0x0030fc03, &ccm->CCGR1);
	writel(0x0fffc000, &ccm->CCGR2);
	writel(0x3ff00000, &ccm->CCGR3);
	writel(0x00fff300, &ccm->CCGR4);
	writel(0x0f0000c3, &ccm->CCGR5);
	writel(0x000003ff, &ccm->CCGR6);
}

const struct mx6sdl_iomux_ddr_regs amx6sdl_ddr_ioregs = {
	.dram_dqm0 = 0x00000030,
	.dram_dqm1 = 0x00000030,
	.dram_dqm2 = 0x00000030,
	.dram_dqm3 = 0x00000030,
	.dram_dqm4 = 0x00000030,
	.dram_dqm5 = 0x00000030,
	.dram_dqm6 = 0x00000030,
	.dram_dqm7 = 0x000c0030,
	.dram_ras = 0x00000030,
	.dram_cas = 0x00000030,
	.dram_sdodt0 = 0x00003030,
	.dram_sdodt1 = 0x00003030,
	.dram_sdba2 = 0x00000000,
	.dram_sdcke0 = 0x00003000,
	.dram_sdcke1 = 0x00003000,
	.dram_sdclk_0 = 0x00000030,
	.dram_sdclk_1 = 0x00000030,
	.dram_sdqs0 = 0x00000038,
	.dram_sdqs1 = 0x00000038,
	.dram_sdqs2 = 0x00000038,
	.dram_sdqs3 = 0x00000038,
	.dram_sdqs4 = 0x00000038,
	.dram_sdqs5 = 0x00000038,
	.dram_sdqs6 = 0x00000038,
	.dram_sdqs7 = 0x00000038,
	.dram_reset = 0x000c0030,
};

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

const struct mx6sdl_iomux_grp_regs amx6sdl_grp_ioregs = {
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

u32 spl_read_gpio (struct gpio_regs *regs, int pins)
{
	return ((readl(&regs->gpio_psr) >> pins) & 0x01);
}
static void spl_dram_init(void)
{
	int ddr3_id;

	if (get_pcb_version () == SMX6_OLD_PCB_VERSION) {
		if (get_board_rev() == MX6SDL) {
			/* use initial settings for memory configuration structs */
			debug("Old PCB version: Memory size fix 0x20000000 on Solo CPU\n");
			mx6sdl_dram_iocfg(64, &amx6sdl_ddr_ioregs,
			                  &amx6sdl_grp_ioregs);
			mx6_dram_cfg(&amx6sdl_sysinfo, &amx6s_calibration,
			              &mem_ddr);
		}
		if (get_board_rev() == MX6DQ) {
			/* use initial settings for memory configuration structs */
			debug("Old PCB version: Memory size fix 0x40000000 on Quad CPU\n");
			mx6dq_dram_iocfg(64, &amx6dq_ddr_ioregs,
			                  &amx6dq_grp_ioregs);
			mx6_dram_cfg(&mx6qdl_sysinfo, &mx6dq_calibration,
			              &mem_ddr);
		}
		return;
	}

	ddr3_id = get_ddr3_id();
	debug("%s: ddr3_id=%d\n", __func__, ddr3_id);

	switch (ddr3_id) {
		case 0:	/* 1 Gb density */
			mem_ddr.density = 1;
			mem_ddr.rowaddr = 13;
			break;
		case 1:	/* 2 Gb density */
			mem_ddr.density = 2;
			mem_ddr.rowaddr = 14;
			break;
		case 2:	/* 4 Gb density */
			mem_ddr.density = 4;
			mem_ddr.rowaddr = 15;
			break;
		case 3:	/* 8 Gb density */
			mem_ddr.density = 8;
			mem_ddr.rowaddr = 16;
			break;
		default:
			puts("Error: Bad DDR3 ID pinconfig\n");
			hang();
			break;
	}
	debug("               density=%d\n", mem_ddr.density);
	debug("               rowaddr=%d\n", mem_ddr.rowaddr);

	switch (get_cpu_type()) {
		case MXC_CPU_MX6Q:
		case MXC_CPU_MX6D:
			mx6qdl_sysinfo.dsize = 2;
			mx6dq_dram_iocfg(64, &amx6dq_ddr_ioregs,
			                 &amx6dq_grp_ioregs);
			mx6_dram_cfg(&mx6qdl_sysinfo, &mx6dq_calibration,
			              &mem_ddr);
			break;
		case MXC_CPU_MX6SOLO:
			amx6sdl_sysinfo.dsize = 1;
			mx6sdl_dram_iocfg(32, &amx6sdl_ddr_ioregs,
			                 &amx6sdl_grp_ioregs);
			mx6_dram_cfg(&amx6sdl_sysinfo, &amx6s_calibration,
			              &mem_ddr);
			break;
		case MXC_CPU_MX6DL:
			mx6qdl_sysinfo.dsize = 2;
			mem_ddr.mem_speed = 800;
			mx6sdl_dram_iocfg(64, &amx6sdl_ddr_ioregs,
			                 &amx6sdl_grp_ioregs);
			mx6_dram_cfg(&mx6qdl_sysinfo, &mx6dl_calibration,
			              &mem_ddr);
			break;
		default:
			puts("Error: CPU type not supported\n");
			hang();
			break;
	}

	udelay(100);
}

void board_init_f(ulong dummy)
{
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

	/* UART clocks enabled - init serial console */
	preloader_console_init();

	/* DDR initialization */
	spl_dram_init();

	/* Clear the BSS. */
	memset(__bss_start, 0, __bss_end - __bss_start);

	/* load/boot image from boot device */
	board_init_r(NULL, 0);
}
