/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2012-2018 Kontron Europe GmbH
 */
#ifndef _AMX6_IOMUX_H_
#define _AMX6_IOMUX_H_

u32 get_pcb_version (void);
int get_ddr3_id (void);
u32 get_board_rev (void);
u32 spl_read_gpio (struct gpio_regs *, int);

#define MX6SDL	1
#define MX6DQ	2
#define SMX6_OLD_PCB_VERSION	1

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


#endif  /* _AMX6_IOMUX_H_ */

