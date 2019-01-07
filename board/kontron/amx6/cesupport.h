/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2012-2018 Kontron Europe GmbH
 */
#ifndef _CESUPPORT_H_
#define _CESUPPORT_H_


#ifdef __cplusplus
extern "C" {
#endif

/*
 * Defines
 */

#define WEC7_ARGS_START 0x10001000

typedef struct KTT20_WArgs {
	u8 magic[8];
	u32 length;
	u32 debugPort;
	u32 debugBaud;
	u32 kitlMode;
} BootArgs;

/*
 * Global variables.
 */
extern BootArgs*   g_pBootArgs;


#ifdef __cplusplus
}
#endif

#endif  /* _BSP_ARGS_H_ */

