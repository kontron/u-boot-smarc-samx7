/*
 * Copyright 2016 Kontron Europe GmbH
 *
 * SPDX-License-Identifier:      GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <command.h>

#include <asm/arch/imx-regs.h>

/*
 * Kick PLD watchdog
 * Paramters: none
 */
static int kick_it = 1;

#define WDOG_SERVICE1 0x5555
#define WDOG_SERVICE2 0xAAAA

#define WDOG_WCR_WDE  0x0004

#define WDOG_BASE_ADDR WDOG1_BASE_ADDR

static void imx_watchdog_kick(void)
{
	struct wdog_regs *wdog = (struct wdog_regs *)WDOG_BASE_ADDR;

	writew(WDOG_SERVICE1, &wdog->wsr);
	while (readw(&wdog->wsr) != WDOG_SERVICE1)
		;
	writew(WDOG_SERVICE2, &wdog->wsr);
	while (readw(&wdog->wsr) != WDOG_SERVICE2)
		;
}

#if defined(CONFIG_WATCHDOG)
void watchdog_reset(void)
{
	if (kick_it)
		imx_watchdog_kick();
}
#endif

/*
 * Start/restart PLD watchdog timer
 * Parameters:
 * - timeout: watchdog timeout in seconds
 */
static int imx_watchdog_timeout (int timeout)
{
	struct wdog_regs *wdog = (struct wdog_regs *)WDOG_BASE_ADDR;

	timeout = ((timeout << 1) - 1) << 8; /* counter resolution is 0.5 seconds */
	/* set watchdog timeout count */
	writew((readw(&wdog->wcr) & 0xff) | timeout, &wdog->wcr);
	udelay(1000);

	return 0;
}

static void imx_watchdog_enable(void)
{
	struct wdog_regs *wdog = (struct wdog_regs *)WDOG_BASE_ADDR;

	writew(readw(&wdog->wcr) | WDOG_WCR_WDE, &wdog->wcr);
}

#if defined(CONFIG_WATCHDOG_ALLOW_STOP)
static void imx_watchdog_disable(void)
{
	struct wdog_regs *wdog = (struct wdog_regs *)WDOG_BASE_ADDR;

	writew(readw(&wdog->wcr) & ~WDOG_WCR_WDE, &wdog->wcr);
}
#endif

static int do_imx_watchdog (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong timeout = 0;

	if (argc == 2) {
#if defined(CONFIG_WATCHDOG_ALLOW_STOP)
		if (strcmp(argv[1], "stop") == 0) {
			imx_watchdog_disable();
			printf ("watchdog stopped\n");
			return 0;
		}
#endif
		if (strict_strtoul(argv[1], 10, &timeout) < 0)
			return 1;
		if (timeout > 128) {
			printf("timeout %d is not valid, watchdog not kicked!\n", (int)timeout);
			return 1;
		}
		if (timeout == 0) {
			kick_it = 0;
			return 0;
		}
		imx_watchdog_timeout((int)timeout);
		kick_it = 1;
		imx_watchdog_kick();
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
				printf("timeout %d is not valid, watchdog not started!\n", (int)timeout);
				return 1;
			}
			imx_watchdog_timeout((int)timeout);
			imx_watchdog_enable();
			kick_it = 1;            /* enable kicking */
			imx_watchdog_kick();

			return 0;
		} else
			goto usage;
	}

usage:
	printf ("Usage:\n%s\n", cmdtp->usage);
	return 1;
}

/* allow watchdog start from outside this module */
void start_imx_watchdog(int timeout)
{
	imx_watchdog_timeout(timeout);
	imx_watchdog_enable();
	kick_it = 1;
	imx_watchdog_kick();
}


U_BOOT_CMD(
	watchdog,    3,    0,     do_imx_watchdog,
	"start/stop/kick IMX watchdog",
	"<timeout>       - kick watchdog and set timeout (0 = disable kicking)\n"
	"watchdog start <timeout> - start watchdog and set timeout"
#if defined(CONFIG_WATCHDOG_ALLOW_STOP)
	"\nwatchdog stop            - disable watchdog"
#endif
);
