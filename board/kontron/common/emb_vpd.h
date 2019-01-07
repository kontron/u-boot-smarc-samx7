/*
 * Copyright (C) 2017 Kontron Europe GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef EMB_EEP_H
#define EMB_EEP_H

typedef struct {
	char * header;
	char * block;
	struct spi_flash *flash;
	unsigned int max_size;
} emb_vpd_info;

#define BLOCK_ID_CRC	(0xF2)
#define BLOCK_ID_SMBIOS	(0xD0)

void emb_vpd_init_r(void);
char *emb_vpd_find_string_in_dmi (int dmi_num, int string_num);

#endif /* EMB_EEP_H */
