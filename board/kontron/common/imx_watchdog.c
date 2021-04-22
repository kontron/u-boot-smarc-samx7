/*
 * Copyright 2016 Kontron Europe GmbH
 *
 * SPDX-License-Identifier:      GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/global_data.h>
#include <command.h>
#include <watchdog.h>
#include <wdt.h>

#include <asm/arch/imx-regs.h>

DECLARE_GLOBAL_DATA_PTR;


/* allow watchdog start from outside this module */
void start_imx_watchdog(int timeout)
{
	if (timeout == 0) {
		gd->flags &= ~GD_FLG_WDT_READY;
		return;
	} else
		gd->flags |= GD_FLG_WDT_READY;

	wdt_start(gd->watchdog_dev, timeout * 1000, 0);
	watchdog_reset();
}

static int do_imx_watchdog (struct cmd_tbl *cmdtp, int flag, int argc,
			    char * const argv[])
{
	ulong timeout = 0;

	if (!gd->watchdog_dev) {
		printf("No valid watchdog device found in DTB\n");
		return 1;
	}

	if (argc == 2) {
		if (strict_strtoul(argv[1], 10, &timeout) < 0)
			return 1;
		if (timeout > 128) {
			printf("timeout %d is not valid, watchdog not kicked!\n",
			       (int)timeout);
			return 1;
		}
		start_imx_watchdog(timeout);

		return 0;
	}

	if (argc == 3) {
		if (strcmp(argv[1], "start") == 0) {
			if (strict_strtoul(argv[2], 10, &timeout) < 0)
				return 1;
			if (timeout == 0) {
				printf("timeout is 0, watchdog not started\n");
				return 1;
			}
			if (timeout > 128) {
				printf("timeout %d is not valid, watchdog "
				       "not started!\n", (int)timeout);
				return 1;
			}
			start_imx_watchdog(timeout);

			return 0;
		} else
			goto usage;
	}

usage:
	printf ("Usage:\n%s\n", cmdtp->usage);
	return 1;
}


U_BOOT_CMD(
	watchdog,    3,    0,     do_imx_watchdog,
	"start/kick IMX watchdog",
	"<timeout>       - kick watchdog and set timeout (0 = disable kicking)\n"
	"watchdog start <timeout> - start watchdog and set timeout\n"
	"NOTE: This command is deprecated and is kept only for backward"
	" compatibility\n"
	"      Preferably use 'wdt' command instead"
);
