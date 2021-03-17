/*
 * Copyright 2013 Kontron Europe GmbH
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <i2c.h>
#include <log.h>
#include <env.h>
#include "emb_eep.h"

#ifdef CONFIG_EMB_EEP_I2C_EEPROM

#ifdef CONFIG_KEX_EEP_BOOTCOUNTER
#define CONFIG_EMB_EEP_WRITE
#endif

int EMB_EEP_I2C_EEPROM_BUS_NUM_1;
int EMB_EEP_I2C_EEPROM_BUS_NUM_2;

static int emb_eep_init (emb_eep_info *vpdi);
static char *emb_eep_find_mac_in_dmi_164 (emb_eep_info *vpdi, int string_num);
static char *emb_eep_find_entry_in_dmi (int eeprom_num, int dmi_num, int entry_num);

static char vpd_header[0x10];
static char vpd_block[CONFIG_EMB_EEP_I2C_EEPROM_SIZE];
static emb_eep_info vpdinfo;

static int i2c_read_emb (emb_eep_info *vpdi, int offset, unsigned char *buffer, int len)
{
#ifdef CONFIG_DM_I2C
        dm_i2c_read(vpdi->i2c_dev, 
                    vpdi->eeprom_offset + offset,
                    (unsigned char *) &buffer[0],
                    len);
#else
        i2c_read (vpdi->eeprom_addr,
                  vpdi->eeprom_offset + offset,
                  vpdi->eeprom_addrlen,
                  (unsigned char *) &buffer[0],
                  len);
#endif

	return 0;
}

#ifdef CONFIG_EMB_EEP_WRITE
static int i2c_write_emb (emb_eep_info *vpdi, int offset, unsigned char *buffer, int len)
{
	int ret = 0;
        do {
                len--;
#ifdef CONFIG_DM_I2C
                dm_i2c_write(vpdi->i2c_dev,
                             vpdi->eeprom_offset + offset + len,
                             buffer+len,
                             1);
#else
                ret |= i2c_write(vpdi->eeprom_addr,
                                 vpdi->eeprom_offset + offset + len,
                                 vpdi->eeprom_addrlen,
                                 buffer+len, 1);
#endif
                udelay(5000);
        } while (len > 0);

	return ret;
}
#endif

static int emb_eep_get_block_size (emb_eep_info *vpdi, int idx)
{
	int block_size;
	uchar buffer[2];

	i2c_read_emb (vpdi, idx+1, (unsigned char *) &buffer[0],2);

	block_size = buffer[0] * 256 + buffer[1];

	block_size *= 2; /* block size in 2 bytes words */

	if (idx + block_size <= vpdi->max_size)
		return block_size;
	else
		return 0;
}

static int emb_eep_find_block(emb_eep_info *vpdi, int idx, int block_id)
{
	int block_size;
	uchar buffer[2];
	int block_len;

	if (idx == 0) {

		/* Calculate offset to first block */
		idx = 2 * (*(vpdi->header + 4));

		memset(buffer, 0, sizeof(buffer));
		i2c_read_emb (vpdi, idx, (unsigned char *) &buffer[0], 1);

		if (buffer[0] == block_id) {
			block_len = emb_eep_get_block_size(vpdi, idx);
			i2c_read_emb (vpdi, idx, (unsigned char *) vpdi->block,
			              block_len);

			return idx;
		}
#if 0
		if (buffer[0] == BLOCK_ID_CRC)
			return -1;
#endif
	}

	do {
		block_size = emb_eep_get_block_size(vpdi, idx);

		if (block_size <= 0)
			return -1;

		idx += block_size;

		i2c_read_emb (vpdi, idx, (unsigned char *) &buffer[0], 1);

		if (buffer[0] == block_id)
			break;
#if 0
		if (buffer[0] == BLOCK_ID_CRC)
			return -1;
#endif
	} while (idx < vpdi->max_size);

	block_size = emb_eep_get_block_size(vpdi, idx);
	if ((idx + block_size) < vpdi->max_size) {
		i2c_read_emb (vpdi, idx, (unsigned char *) vpdi->block,
		              block_size);

		return idx;
	}
	else
		return -1;
}

char * emb_eep_find_mac_in_dmi (int eeprom_num, int eth_num)
{
	emb_eep_info *vpdi;

	vpdi = &vpdinfo;
	vpdi->eeprom_num = eeprom_num;
	vpdi->block = &vpd_block[0];
	vpdi->header = &vpd_header[0];

	if (emb_eep_init (vpdi) != 0) {
		return NULL;
	}

	return emb_eep_find_mac_in_dmi_164(vpdi, eth_num);
}

char * emb_eep_find_string_in_dmi (int eeprom_num, int dmi_num, int string_num)
{
	return emb_eep_find_entry_in_dmi(eeprom_num, dmi_num, string_num);
}

static char * emb_eep_find_entry_in_dmi (int eeprom_num, int dmi_num, int entry_num)
{
	emb_eep_info *vpdi;

	int idx = 0, num, tmp_num;
	char *ptr, * block_end;
	int offset_string_index, offset_strings, max_strings;
	int found = 0;

	vpdi = &vpdinfo;
	vpdi->eeprom_num = eeprom_num;
	vpdi->block = &vpd_block[0];
	vpdi->header = &vpd_header[0];

	if (emb_eep_init (vpdi) != 0) {
		return NULL;
	}

	/*
	 * offsets count from SMBIOS dynamic block ID byte (0xd0) address.
	 * as entry_num is starting with 1, actual offset of  1st string
	 * index calculates to (offset-1) in block.
	 */
	switch (dmi_num) {
		case 2:
			offset_string_index = 7-1;
			offset_strings = 18;
			max_strings = 5;
			break;
		case 160:
			offset_string_index = 12-1;
			offset_strings = 16;
			max_strings = 4;
			break;
		case 161:
			offset_string_index = 0;
			if (entry_num == 1)
				offset_strings = BLOCK_161_BOOTCOUNTER;
			if (entry_num == 2)
				offset_strings = BLOCK_161_RUNNINGTIME;
			max_strings = 2;
			break;
			
		default:
			return NULL;
	}

	if ((entry_num < 1) || (entry_num > max_strings))
		return NULL;

	/*
	 * find SMBIOS Block with type dmi_num
	 */
	do {
		idx = emb_eep_find_block (vpdi, idx, BLOCK_ID_SMBIOS);
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
	 * find string index of entry_num
	 */

	if (dmi_num != 161) {
		num = *(vpdi->block + offset_string_index + entry_num);
		if ((num == 0) | (num > max_strings))
			return NULL;
	} else {
		num = 1;
	}

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
	block_end = vpdi->block + emb_eep_get_block_size(vpdi, idx);

	if (ptr < block_end)
		return ptr;
	else
		return NULL;

	return NULL;
}

#ifdef CONFIG_EMB_EEP_WRITE
/*
 * Use ofs parameter to write dedicated elements in a block
 */
static int emb_eep_set_get_dmi_block(int eeprom_num, int dmi_num, char *dmi_block, int ofs, int sz, int rw_flag)
{
	int idx = 0;
	emb_eep_info *vpdi;

	vpdi = &vpdinfo;
	vpdi->eeprom_num = eeprom_num;
	vpdi->block = vpd_block;
	vpdi->header = vpd_header;

	if (emb_eep_init(vpdi) != 0) {
		return -1;
	}

	/*
	 * find SMBIOS Block with type dmi_num
	 */
	do {
		idx = emb_eep_find_block (vpdi, idx, BLOCK_ID_SMBIOS);
		debug("SMBIOS block found with index %d\n", idx);

		if (idx < 0)
			return -1;

		if ((*(vpdi->block + 3)) == dmi_num) {
			if (rw_flag) {
				return (i2c_write_emb (vpdi, idx + ofs,
				            (unsigned char *)(dmi_block + ofs),
				            sz));
			}
			else {
				memcpy(dmi_block, vpdi->block, sz);
				return idx;
			}
		}
	} while (idx < vpdi->max_size);

	return -1;
}
#endif

static char *emb_eep_find_mac_in_dmi_164 (emb_eep_info *vpdi, int eth_num)
{
	int idx = 0, tmp_num, num;
	char *ptr, * block_end;
	int numOfMacs;
	/* find string num */
	if (eth_num < 1)
		return NULL;

	/*
	 * find SMBIOS Block with type 164
	 */
	do {
		idx = emb_eep_find_block (vpdi, idx, BLOCK_ID_SMBIOS);

		if (idx < 0)
			return NULL;

		else if ((*(vpdi->block + 3)) == 164)
			break;

	} while (idx < vpdi->max_size);

	numOfMacs = *(vpdi->block + 12);
	if (eth_num > numOfMacs)
		return NULL;

	/*
	 * get offset to string
	 */
	num = *(vpdi->block + 12 + eth_num);

	ptr = vpdi->block + 12 + eth_num + numOfMacs;
	tmp_num = 1;
	while (tmp_num < num) {
		ptr += strlen (ptr) + 1;
		tmp_num ++;
	}

	/*
	 * check for plausibility
	 */
	block_end = vpdi->block + emb_eep_get_block_size(vpdi, idx);

	if (ptr < block_end)
		return ptr;
	else
		return NULL;

	return ptr;
}


static void emb_eep_default_ethaddr (void)
{
	char *e_ethaddr;

	e_ethaddr = env_get("ethaddr");
	if (e_ethaddr == NULL) {
		printf ("WARNING: ethaddr not found in environment, using default value\n");
		env_set  ("ethaddr", D_ETHADDR);
	}
}

static void emb_eep_import_ethaddr (emb_eep_info *vpdi, const char *eth_x_addr, int num, const char *d_ethaddr)
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
	
	e_ethaddr = env_get((char*)eth_x_addr);

	if (v_ethaddr == NULL) {
		printf ("WARNING: %s not found in embedded EEPROM\n", eth_x_addr);
		return;
	}

	/* Check if ethaddr already exists in Environment */
	if (e_ethaddr) {
		if (!strcmp(d_ethaddr, e_ethaddr)) {
			printf ("Embedded EEPROM: Overwrite default %s to %s\n",
			        eth_x_addr, v_ethaddr);
			env_set((char*)eth_x_addr, v_ethaddr);
			return;
		}
		else {
			if (strcmp (e_ethaddr, v_ethaddr)) {
				printf ("Embedded EEPROM: Not overwriting existing %s\n",
				        eth_x_addr);
			}
			return;
		}
	}

	debug ("Setenv %s\n", eth_x_addr);
	env_set((char*)eth_x_addr, v_ethaddr);
}


static int emb_eep_check_header (emb_eep_info *vpdi)
{
	if (*(vpdi->header + 1) != '3'){
		printf ("emb_eep_check_header: 0x%x instead of 3\n",
		        *(vpdi->header + 1));
		return 0;
	}
	if (*(vpdi->header + 2) != 'P'){
		printf ("emb_eep_check_header: 0x%x instead of P\n",
		        *(vpdi->header + 2));
		return 0;
	}
#if 0	
	if (*(vpdi->header + 3) != 0x10)
		return 0;
#endif

	return 1;
}

static int emb_eep_init (emb_eep_info *vpdi)
{
        debug ("Initialize vpd_init, vpdi = 0x%x\n", (int)vpdi);

        switch (vpdi->eeprom_num) {
#ifdef CONFIG_EMB_EEP_I2C_EEPROM_ADDR_1
        case 1:
                vpdi->eeprom_busnum = EMB_EEP_I2C_EEPROM_BUS_NUM_1;
                vpdi->eeprom_addr = CONFIG_EMB_EEP_I2C_EEPROM_ADDR_1;
                vpdi->eeprom_addrlen = CONFIG_EMB_EEP_I2C_EEPROM_ADDR_LEN_1;
                vpdi->eeprom_offset = CONFIG_EMB_EEP_I2C_EEPROM_OFFSET_1;
                break;
#endif
#ifdef CONFIG_EMB_EEP_I2C_EEPROM_ADDR_2
        case 2:
                vpdi->eeprom_busnum = EMB_EEP_I2C_EEPROM_BUS_NUM_2;
                vpdi->eeprom_addr = CONFIG_EMB_EEP_I2C_EEPROM_ADDR_2;
                vpdi->eeprom_addrlen = CONFIG_EMB_EEP_I2C_EEPROM_ADDR_LEN_2;
                vpdi->eeprom_offset = CONFIG_EMB_EEP_I2C_EEPROM_OFFSET_2;
                break;

#endif
        default:
                printf ("Warning: EEPROM number %d not supported\n",
                        vpdi->eeprom_num);
                return -1;
        }

	/* read 6 bytes first */
#ifdef CONFIG_DM_I2C
        int ret;
        ret = i2c_get_chip_for_busnum(vpdi->eeprom_busnum, 
                                      vpdi->eeprom_addr,
                                      vpdi->eeprom_addrlen,
                                      &(vpdi->i2c_dev));
	if (ret) {
		printf("EEPROM 0x%02x not foundon bus %d\n",
                        vpdi->eeprom_addr, vpdi->eeprom_busnum);
		return -1;
	}
#else
	i2c_set_bus_num(vpdi->eeprom_busnum);
#endif

	i2c_read_emb(vpdi, 0, (unsigned char *)&vpdi->header[0], 6);

	if (!emb_eep_check_header(vpdi)) {
		printf ("WARNING: Embedded EEPROM header not valid, abort\n");
		return -1;
	}

	vpdi->max_size = 256 << (vpdi->header[5] & 0x7);
	if ( vpdi->max_size > CONFIG_EMB_EEP_I2C_EEPROM_SIZE) {
		printf ("Embedded EEPROM contents too large\n");
		return -1;
	}
		
	return 0;
}

/*
 * initialize environment from embedded EEPROM
 */
void emb_eep_init_r(int eeprom_num_serial, int eeprom_num_eth, int num_of_macs)
{
	char *val;
	emb_eep_info *vpdi;

	vpdi = &vpdinfo;
	vpdi->block = &vpd_block[0];
	vpdi->header = &vpd_header[0];
	vpdi->eeprom_num = eeprom_num_serial;

	if (emb_eep_init (vpdi) == 0) {
		/*
		* Import serial number to environment
		* Block SMBIOS, type 2, string number 4
		*/
		val = emb_eep_find_string_in_dmi (eeprom_num_serial, 2, 4);
		if (val != NULL)
			env_set("serial#", val);
	}

	vpdi->eeprom_num = eeprom_num_eth;

	if (emb_eep_init (vpdi) != 0) {
		emb_eep_default_ethaddr ();
		return;
	}

	/*
	 * Import eth addresses to environment
	 */
	emb_eep_import_ethaddr (vpdi, "ethaddr", 1, D_ETHADDR);

#if defined(CONFIG_HAS_ETH1)
	if (num_of_macs >= 2)
		emb_eep_import_ethaddr (vpdi, "eth1addr", 2, D_ETH1ADDR);
#endif

#if defined(CONFIG_HAS_ETH2)
	if (num_of_macs >= 3)
		emb_eep_import_ethaddr (vpdi, "eth2addr", 3, D_ETH1ADDR);
#endif

#if defined(CONFIG_HAS_ETH3)
	if (num_of_macs >= 4)
		emb_eep_import_ethaddr (vpdi, "eth3addr", 4, D_ETH1ADDR);
#endif

#if defined(CONFIG_HAS_ETH4)
	if (num_of_macs >= 5)
		emb_eep_import_ethaddr (vpdi, "eth4addr", 5, D_ETH1ADDR);
#endif

	return;
}

#if defined(CONFIG_EMB_EEP_WRITE)
int emb_eep_update_bootcounter(int eeprom_num)
{
	int ret;
	uint64_t bc;
	emb_running_time_block_t emb_rt_block;

	ret = emb_eep_set_get_dmi_block(eeprom_num, 161,
	                                (char *)(&emb_rt_block),
					0,
	                                sizeof(emb_rt_block), 0);
	if (ret < 0) {
		printf("Could not read SMBIOS block 161\n");
		return ret;
	}

	memcpy(&bc, emb_rt_block.boot_counter, sizeof(uint64_t));
	bc = be64_to_cpu(bc);
	if ((bc & SIGN_64BIT) && (bc ^ -1ULL)) {
		printf("WARNING: Invalid boot counter\n");
		return 0;
	}

	bc = cpu_to_be64(bc + 1);
	memcpy(emb_rt_block.boot_counter, &bc, sizeof(uint64_t));

	/* write back only boot_counter bytes! */
	ret = emb_eep_set_get_dmi_block(eeprom_num, 161,
	                                (char *)(&emb_rt_block),
					BLOCK_161_BOOTCOUNTER,
	                                sizeof(uint64_t), 1);
	if (ret < 0) {
		printf("WARNING: Could not update boot counter\n");
		return ret;
	}

	return ret;
}
#endif

#endif /* CONFIG_EMB_EEP_I2C_EEPROM */
