/*
 * Copyright (C) 2017 Kontron Europe GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <spi_flash.h>
#include <spi.h>
#include "emb_vpd.h"
#include "crc.h"


int EMB_EEP_I2C_EEPROM_BUS_NUM_1;
int EMB_EEP_I2C_EEPROM_BUS_NUM_2;

static emb_vpd_info emb_spi;

static uchar emb_buf[CONFIG_EMB_EEP_SPI_SIZE];

static int spi_read_emb (emb_vpd_info *vpdi, int offset, unsigned char *buffer, int len)
{
	int ret = 0;

	if (vpdi->flash) {
		ret = spi_flash_read(vpdi->flash, CONFIG_EMB_EEP_SPI_OFFSET,
		                     CONFIG_EMB_EEP_SPI_SIZE, buffer);
	}

	if (ret) {
		printf("VPD: spi_read_emb() failed\n");
		ret = 1;
	}

#if 0
	spi_flash_free(vpdi->flash);
	vpdi->flash = NULL;
#endif

	return ret;
}

static int emb_vpd_get_block_size (emb_vpd_info *vpdi, int idx)
{
	int block_size;

	block_size = emb_buf[idx+1] * 16 + emb_buf[idx+2];
	block_size *= 2; /* block size in 2 bytes words */

	if (idx + block_size <= vpdi->max_size)
		return block_size;
	else
		return 0;
}

/*
 * We only search blocks before the CRC block.
 */
static int emb_vpd_find_block(emb_vpd_info *vpdi, int idx, int block_id)
{
	int block_size;
	int block_len;

	debug("emb_vpd_find_block: idx=%d, block_id=%d: START\n", idx, block_id);
	if (idx == 0) {

		/* Calculate offset to first block */
		idx = 2 * (*(vpdi->header + 4));
		debug("emb_vpd_find_block: offset to first block is %d\n", idx);

		debug("emb_vpd_find_block: emb_buf[0] = %d\n", emb_buf[idx]);
		if (emb_buf[idx] == block_id) {
			block_len = emb_vpd_get_block_size(vpdi, idx);
			debug("emb_vpd_find_block: block_len is %d\n", block_len);
			vpdi->block = (char *)(emb_buf + idx);

			return idx;
		}

		if (emb_buf[idx] == BLOCK_ID_CRC)
			return -1;
	}

	do {
		block_size = emb_vpd_get_block_size(vpdi, idx);
		debug("emb_vpd_find_block: block_size is %d\n", block_size);

		if (block_size <= 0)
			return -1;

		idx += block_size;

		if (emb_buf[idx] == block_id)
			break;

		if (emb_buf[idx] == BLOCK_ID_CRC)
			return -1;

	} while (idx < vpdi->max_size);

	block_size = emb_vpd_get_block_size(vpdi, idx);
	if ((idx + block_size) < vpdi->max_size) {
		vpdi->block = (char *)(emb_buf+idx);

		return idx;
	}
	else
		return -1;
}

static char *emb_eep_find_mac_in_dmi_164 (emb_vpd_info *vpdi, int string_num)
{
	int idx = 0, tmp_num, num;
	char *ptr, * block_end;
	int numOfMacs;
	/* find string num */
	if (string_num < 1)
		return NULL;

	/*
	 * find SMBIOS Block with type 164
	 */
	do {
		idx = emb_vpd_find_block (vpdi, idx, BLOCK_ID_SMBIOS);

		if (idx < 0)
			return NULL;

		else if ((*(vpdi->block + 3)) == 164)
			break;

	} while (idx < vpdi->max_size);

	numOfMacs = *(vpdi->block + 12);
	if (string_num > numOfMacs)
		return NULL;

	/*
	 * get offset to string
	 */
	num = *(vpdi->block + 12 + string_num);

	ptr = vpdi->block + 12 + string_num + 1;
	tmp_num = 1;
	while (tmp_num < num) {
		ptr += strlen (ptr) + 1;
		tmp_num ++;
	}

	/*
	 * check for plausibility
	 */
	block_end = vpdi->block + emb_vpd_get_block_size(vpdi, idx);

	if (ptr < block_end)
		return ptr;
	else
		return NULL;

	return ptr;
}


#if defined(D_ETHADDR)
static void emb_spi_default_ethaddr (void)
{
	char *e_ethaddr;

	e_ethaddr = getenv("ethaddr");
	if (e_ethaddr == NULL) {
		printf ("WARNING: ethaddr not found in environment, using default value\n");
		setenv  ("ethaddr", D_ETHADDR);
	}
}
#endif

static void emb_spi_import_ethaddr (emb_vpd_info *vpdi, const char *eth_x_addr, int num, const char *d_ethaddr)
{
	char *e_ethaddr;
	char *v_ethaddr;

	v_ethaddr = emb_eep_find_mac_in_dmi_164(vpdi, num);

	if ((v_ethaddr[2] != ':') || (v_ethaddr[5] != ':') ||
		(v_ethaddr[8] != ':') || (v_ethaddr[11] != ':')  ||
		(v_ethaddr[14] != ':') ) {
		printf ("Error in MAC Address, no import possible\n");
		return;
	}
	
	e_ethaddr = getenv((char*)eth_x_addr);

	if (v_ethaddr == NULL) {
		printf ("WARNING: %s not found in embedded EEPROM\n", eth_x_addr);
		return;
	}

	/* Check if ethaddr already exists in Environment */
	if (e_ethaddr && (d_ethaddr != NULL)) {
		if (!strcmp(d_ethaddr, e_ethaddr)) {
			printf ("Embedded EEPROM: Overwrite default %s to %s\n", eth_x_addr, v_ethaddr);
			setenv((char*)eth_x_addr, v_ethaddr);
			return;
		}
		else {
			if (strcmp (e_ethaddr, v_ethaddr)) {
				printf ("Embedded EEPROM: Not overwriting existing %s\n", eth_x_addr);
			}
			return;
		}
	}

	debug ("Setenv %s\n", eth_x_addr);
	setenv((char*)eth_x_addr, v_ethaddr);
}


static int emb_spi_check_header (emb_vpd_info *vpdi)
{
	if (*(vpdi->header + 1) != '3'){
		printf ("emb_spi_check_header: 0x%x instead of 3\n",*(vpdi->header + 1));
		return 0;
	}
	if (*(vpdi->header + 2) != 'P'){
		printf ("emb_spi_check_header: 0x%x instead of P\n",*(vpdi->header + 2));
		return 0;
	}
#if 0	
	if (*(vpdi->header + 3) != 0x10)
		return 0;
#endif

	return 1;
}

static int emb_spi_init (emb_vpd_info *vpdi)
{
	debug ("Initialize vpd_init, vpdi = 0x%x\n", (int)vpdi);

	vpdi->flash = spi_flash_probe(CONFIG_EMB_EEP_SPI_BUS, CONFIG_EMB_EEP_SPI_CS,
	                              CONFIG_EMB_EEP_SPI_SPEED, CONFIG_EMB_EEP_SPI_MODE);
	if (!vpdi->flash) {
		printf("VPD: Probing embedded SPI flash failed\n");
		return 1;
	}

	/* read embedded VPD data from SPI */
	spi_read_emb (vpdi, 0, emb_buf, 0);

	/* set header pointer */
	vpdi->header = (char *)emb_buf;

	if (!emb_spi_check_header (vpdi)) {
		printf ("WARNING: Embedded EEPROM header not valid, abort\n");
		return -1;
	}

	vpdi->max_size = 256 << (vpdi->header[5] & 0x7);
	if ( vpdi->max_size > CONFIG_EMB_EEP_SPI_SIZE) {
		printf ("Embedded EEPROM contents too large\n");
		return -1;
	}

	return 0;
}

/*
 * find embedded string in VPD
 */
char * emb_vpd_find_string_in_dmi (int dmi_num, int string_num)
{
	int idx = 0, num, tmp_num;
	char *ptr, * block_end;
	int offset_nums, offset_strings, max_strings;
	emb_vpd_info *vpdi = &emb_spi;
	int found = 0;

	switch (dmi_num) {
		case 2:
			offset_nums = 6;
			offset_strings = 18;
			max_strings = 5;
			break;
		case 160:
			offset_nums = 11;
			offset_strings = 15;
			max_strings = 5;
			break;
		default:
			return NULL;
	}

	if ((string_num < 1) || (string_num > max_strings))
		return NULL;

	/*
	 * find SMBIOS Block with type dmi_num
	 */
	do {
		idx = emb_vpd_find_block (vpdi, idx, BLOCK_ID_SMBIOS);
		debug("SMBIOS block found with index %d\n", idx);

		if (idx < 0)
			return NULL;

		if ((*(vpdi->block + 3)) == dmi_num) {
			found = 1;
			break;
		}

	} while (idx < vpdi->max_size);

	if (found == 0)
		return NULL;
	/*
	 * find string index of string_num
	 */

	num = *(vpdi->block + offset_nums + string_num);
	if ((num == 0) | (num > max_strings))
		return NULL;

	/*
	 * get offset to string
	 */
	ptr = vpdi->block + offset_strings;
	tmp_num = 1;
	while (tmp_num < num) {
		ptr += strlen (ptr) + 1;
		tmp_num ++;
	}

	/*
	 * check for plausibility
	 */
	block_end = emb_spi.block + emb_vpd_get_block_size(&emb_spi, idx);

	if (ptr < block_end)
		return ptr;
	else
		return NULL;

	return NULL;
}

/*
 * initialize environment from embedded EEPROM
 */
void emb_vpd_init_r(void)
{
	char *val;

	if (emb_spi_init (&emb_spi) == 0) {
		/*
		* Import serial number to environment
		* Block SMBIOS, type 2, string number 4
		*/
		val = emb_vpd_find_string_in_dmi (2, 4);
		if (val != NULL)
			setenv("serial#", val);
	} else {
#if defined(D_ETHADDR)
		emb_spi_default_ethaddr ();
#endif
		return;
	}

	/*
	 * Import eth addresses to environment
	 */
#if defined(D_ETHADDR)
	emb_spi_import_ethaddr (&emb_spi, "ethaddr", 1, D_ETHADDR);
#else
	emb_spi_import_ethaddr (&emb_spi, "ethaddr", 1, NULL);
#endif

	return;
}
