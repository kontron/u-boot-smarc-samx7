/************************************************************************/
/*
 * Module:	jbistub.c
 *
 * Copyright (C) Altera Corporation 1997-2001
 *
 * Description:	Jam STAPL ByteCode Player main source file
 *
 * Supports Altera ByteBlaster hardware download cable
 * on Windows 95 and Windows NT operating systems.
 * (A device driver is required for Windows NT.)
 *
 * Also supports BitBlaster hardware download cable on
 * Windows 95, Windows NT, and UNIX platforms.
 *
 * Revisions:	1.1 fixed control port initialization for ByteBlaster
 *		2.0 added support for STAPL bytecode format, added code
 *		    to get printer port address from Windows registry
 *		2.1 improved messages, fixed delay-calibration bug in
 *		    16-bit DOS port, added support for "alternative
 *		    cable X", added option to control whether to reset
 *		    the TAP after execution, moved porting macros into
 *		    jbiport.h
 *		2.2 added support for static memory fixed /W4 warnings
 */


#include "jbiport.h"
#include "jbiexprt.h"

#include <common.h>
#include <command.h>
#include <malloc.h>
#include <asm/gpio.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mx6-pins.h>
#include <linux/delay.h>

typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
#define TRUE 1
#define FALSE 0


/************************************************************************
*
*	Global variables
*/

/* file buffer for Jam STAPL ByteCode input file */
unsigned char *file_buffer = NULL;
long file_pointer = 0L;
long file_length = 0L;

/* serial port interface available on all platforms */
BOOL jtag_hardware_initialized = FALSE;
void initialize_jtag_hardware(void);
void close_jtag_hardware(void);

/* function prototypes to allow forward reference */
int getBoardId (void);

#if 0
void amx6_setup_iomux_gpio_jtag(void);
void amx6_clear_iomux_gpio_jtag(void);
int amx6_jbi_jtag_io(int , int , int );
#endif

#define JTAG_GPIO_PAD_CTRL      (PAD_CTL_PKE | PAD_CTL_PUE |			\
				 PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |	\
				 PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST  )

static iomux_v3_cfg_t gpio_jtag_pads[] = {
	/* CPLD_TMS_IMX */
	IOMUX_PADS(PAD_KEY_COL0__GPIO4_IO06 | MUX_PAD_CTRL(JTAG_GPIO_PAD_CTRL)),
	/* CPLD_TDI_IMX */
	IOMUX_PADS(PAD_KEY_ROW0__GPIO4_IO07 | MUX_PAD_CTRL(JTAG_GPIO_PAD_CTRL)),
	/* CPLD_TDO_IMX */
	IOMUX_PADS(PAD_KEY_COL1__GPIO4_IO08 | MUX_PAD_CTRL(JTAG_GPIO_PAD_CTRL)),
	/* CPLD_TCK_IMX */
	IOMUX_PADS(PAD_KEY_ROW1__GPIO4_IO09 | MUX_PAD_CTRL(JTAG_GPIO_PAD_CTRL)),
};

/* Setup bit-banging JTAG interface to on-board CPLD logic */
void amx6_setup_iomux_gpio_jtag(void)
{
	SETUP_IOMUX_PADS(gpio_jtag_pads);

	/* Configure JTAG pins direction */
	gpio_direction_output(IMX_GPIO_NR(4, 6), 0);
	gpio_direction_output(IMX_GPIO_NR(4, 7), 0);
	gpio_direction_input(IMX_GPIO_NR(4, 8));
	gpio_direction_output(IMX_GPIO_NR(4, 9), 0);
}

void amx6_clear_iomux_gpio_jtag(void)
{
	/* clear JTAG pins */
	gpio_direction_input(IMX_GPIO_NR(4, 6));
	gpio_direction_input(IMX_GPIO_NR(4, 7));
	gpio_direction_input(IMX_GPIO_NR(4, 8));
	gpio_direction_input(IMX_GPIO_NR(4, 9));
}

#define GPIO_TO_PORT(n)		((n) / 32)

static unsigned long gpio_ports[] = {
	[0] = GPIO1_BASE_ADDR,
	[1] = GPIO2_BASE_ADDR,
	[2] = GPIO3_BASE_ADDR,
	[3] = GPIO4_BASE_ADDR,
	[4] = GPIO5_BASE_ADDR,
	[5] = GPIO6_BASE_ADDR,
	[6] = GPIO7_BASE_ADDR,
};

int gpio_set_multivalue(unsigned gpio, int value, int mask)
{
	unsigned int port = GPIO_TO_PORT(gpio);
	struct gpio_regs *regs;
	u32 l;

	if (port >= ARRAY_SIZE(gpio_ports))
		return -1;

	regs = (struct gpio_regs *)gpio_ports[port];

	l = readl(&regs->gpio_dr) & ~mask;
	l |= value & mask;
	writel(l, &regs->gpio_dr);

	return 0;
}

#define AMX6_JTAG_TMS_BIT	(1 << 6)
#define AMX6_JTAG_TDI_BIT	(1 << 7)
#define AMX6_JTAG_TD0_BIT	(1 << 8)
#define AMX6_JTAG_TCK_BIT	(1 << 9)

#define AMX6_JTAG_TMS_GPIO_PIN	IMX_GPIO_NR(4, 6)
#define AMX6_JTAG_TDI_GPIO_PIN	IMX_GPIO_NR(4, 7)
#define AMX6_JTAG_TD0_GPIO_PIN	IMX_GPIO_NR(4, 8)
#define AMX6_JTAG_TCK_GPIO_PIN	IMX_GPIO_NR(4, 9)

#define TMS_SET_BIT(bit)	gpio_set_value(AMX6_JTAG_TMS_GPIO_PIN, bit)
#define TDI_SET_BIT(bit)	gpio_set_value(AMX6_JTAG_TDI_GPIO_PIN, bit)
#define TCK_SET_BIT(bit)	gpio_set_value(AMX6_JTAG_TCK_GPIO_PIN, bit)
#define TDO_GET_BIT()		gpio_get_value(AMX6_JTAG_TD0_GPIO_PIN)

#define JTAG_SET_MASK		(AMX6_JTAG_TMS_BIT | AMX6_JTAG_TDI_BIT | AMX6_JTAG_TCK_BIT)
#define JTAG_SET(val)									\
	{										\
		gpio_set_multivalue(AMX6_JTAG_TMS_GPIO_PIN, val, JTAG_SET_MASK);	\
	}

static int amx6_jbi_jtag_io(int tms, int tdi, int read_tdo)
{
	int tdo = 0;
	int data;

	data = (tdi ? AMX6_JTAG_TDI_BIT : 0) | (tms ? AMX6_JTAG_TMS_BIT : 0);
	JTAG_SET(data);

	if (read_tdo)
		tdo = TDO_GET_BIT();

	JTAG_SET(data | AMX6_JTAG_TCK_BIT);
	JTAG_SET(data);

	return (tdo);
}

/*
*	This structure stores information about each available vector signal
*/
struct VECTOR_LIST_STRUCT
{
	char *signal_name;
	int  hardware_bit;
	int  vector_index;
};

struct VECTOR_LIST_STRUCT vector_list[] =
{
	/* add a record here for each vector signal */
	{ "", 0, -1 }
};

#define VECTOR_SIGNAL_COUNT ((int)(sizeof(vector_list)/sizeof(vector_list[0])))

BOOL verbose = FALSE;

/************************************************************************
*
*	Customized interface functions for Jam STAPL ByteCode Player I/O:
*
*	jbi_jtag_io()
*	jbi_message()
*	jbi_delay()
*/

int jbi_jtag_io(int tms, int tdi, int read_tdo)
{
	if (!jtag_hardware_initialized)
	{
		initialize_jtag_hardware();
		jtag_hardware_initialized = TRUE;
	}

	return amx6_jbi_jtag_io(tms, tdi, read_tdo);
}

void jbi_message(char *message_text)
{
	printf ("%s\n", message_text);
}

void jbi_export_integer(char *key, long value)
{
	if (verbose)
		printf("Export: key = \"%s\", value = %ld\n", key, value);
}

#define HEX_LINE_CHARS 72
#define HEX_LINE_BITS (HEX_LINE_CHARS * 4)

char conv_to_hex(unsigned long value)
{
	char c;

	if (value > 9)
	{
		c = (char) (value + ('A' - 10));
	}
	else
	{
		c = (char) (value + '0');
	}

	return (c);
}

void jbi_export_boolean_array(char *key, unsigned char *data, long count)
{
	char string[HEX_LINE_CHARS + 1];
	long i, offset;
	unsigned long size, line, lines, linebits, value, j, k;

	if (verbose)
	{
		if (count > HEX_LINE_BITS)
		{
			printf("Export: key = \"%s\", %ld bits, value = HEX\n", key, count);
			lines = (count + (HEX_LINE_BITS - 1)) / HEX_LINE_BITS;

			for (line = 0; line < lines; ++line)
			{
				if (line < (lines - 1))
				{
					linebits = HEX_LINE_BITS;
					size = HEX_LINE_CHARS;
					offset = count - ((line + 1) * HEX_LINE_BITS);
				}
				else
				{
					linebits = count - ((lines - 1) * HEX_LINE_BITS);
					size = (linebits + 3) / 4;
					offset = 0L;
				}

				string[size] = '\0';
				j = size - 1;
				value = 0;

				for (k = 0; k < linebits; ++k)
				{
					i = k + offset;
					if (data[i >> 3] & (1 << (i & 7))) value |= (1 << (i & 3));
					if ((i & 3) == 3)
					{
						string[j] = conv_to_hex(value);
						value = 0;
						--j;
					}
				}
				if ((k & 3) > 0) string[j] = conv_to_hex(value);

				printf("%s\n", string);
			}

/*			fflush(stdout);*/
		}
		else
		{
			size = (count + 3) / 4;
			string[size] = '\0';
			j = size - 1;
			value = 0;

			for (i = 0; i < count; ++i)
			{
				if (data[i >> 3] & (1 << (i & 7))) value |= (1 << (i & 3));
				if ((i & 3) == 3)
				{
					string[j] = conv_to_hex(value);
					value = 0;
					--j;
				}
			}
			if ((i & 3) > 0) string[j] = conv_to_hex(value);

			printf("Export: key = \"%s\", %ld bits, value = HEX %s\n",
				key, count, string);
/*			fflush(stdout);*/
		}
	}
}

void jbi_delay(long microseconds)
{
	udelay (microseconds);
}

int jbi_vector_map
(
	int signal_count,
	char **signals
)
{
	int signal, vector, ch_index, diff;
	int matched_count = 0;
	char l, r;

	for (vector = 0; (vector < VECTOR_SIGNAL_COUNT); ++vector)
	{
		vector_list[vector].vector_index = -1;
	}

	for (signal = 0; signal < signal_count; ++signal)
	{
		diff = 1;
		for (vector = 0; (diff != 0) && (vector < VECTOR_SIGNAL_COUNT);
			++vector)
		{
			if (vector_list[vector].vector_index == -1)
			{
				ch_index = 0;
				do
				{
					l = signals[signal][ch_index];
					r = vector_list[vector].signal_name[ch_index];
					diff = (((l >= 'a') && (l <= 'z')) ? (l - ('a' - 'A')) : l)
						- (((r >= 'a') && (r <= 'z')) ? (r - ('a' - 'A')) : r);
					++ch_index;
				}
				while ((diff == 0) && (l != '\0') && (r != '\0'));

				if (diff == 0)
				{
					vector_list[vector].vector_index = signal;
					++matched_count;
				}
			}
		}
	}

	return (matched_count);
}

int jbi_vector_io
(
	int signal_count,
	long *dir_vect,
	long *data_vect,
	long *capture_vect
)
{
	int signal, vector, bit;
	int matched_count = 0;
	int data = 0;
	int mask = 0;
	int dir = 0;

	if (!jtag_hardware_initialized)
	{
		initialize_jtag_hardware();
		jtag_hardware_initialized = TRUE;
	}

	/*
	*	Collect information about output signals
	*/
	for (vector = 0; vector < VECTOR_SIGNAL_COUNT; ++vector)
	{
		signal = vector_list[vector].vector_index;

		if ((signal >= 0) && (signal < signal_count))
		{
			bit = (1 << vector_list[vector].hardware_bit);

			mask |= bit;
			if (data_vect[signal >> 5] & (1L << (signal & 0x1f))) data |= bit;
			if (dir_vect[signal >> 5] & (1L << (signal & 0x1f))) dir |= bit;

			++matched_count;
		}
	}

#if 0
	/*
	*	Write outputs to hardware interface, if any
	*/
	if (dir != 0)
	{
		if (specified_com_port)
		{
			ch_data = (char) (((data >> 6) & 0x01) | (data & 0x02) |
					  ((data << 2) & 0x04) | ((data << 3) & 0x08) | 0x60);
			write(com_port, &ch_data, 1);
		}
		else
		{
#if PORT == WINDOWS || PORT == DOS

			write_byteblaster(0, data);

#endif
		}
	}

	/*
	* Read the input signals and save information in capture_vect[]
	*/
	if ((dir != mask) && (capture_vect != NULL))
	{
		if (specified_com_port)
		{
			ch_data = 0x7e;
			write(com_port, &ch_data, 1);
			for (i = 0; (i < 100) && (result != 1); ++i)
			{
				result = read(com_port, &ch_data, 1);
			}
			if (result == 1)
			{
				data = ((ch_data << 7) & 0x80) | ((ch_data << 3) & 0x10);
			}
			else
			{
				fprintf(stderr, "Error:  BitBlaster not responding\n");
			}
		}
		else
		{
#if PORT == WINDOWS || PORT == DOS

			data = read_byteblaster(1) ^ 0x80; /* parallel port inverts bit 7 */

#endif
		}

		for (vector = 0; vector < VECTOR_SIGNAL_COUNT; ++vector)
		{
			signal = vector_list[vector].vector_index;

			if ((signal >= 0) && (signal < signal_count))
			{
				bit = (1 << vector_list[vector].hardware_bit);

				if ((dir & bit) == 0)	/* if it is an input signal... */
				{
					if (data & bit)
					{
						capture_vect[signal >> 5] |= (1L << (signal & 0x1f));
					}
					else
					{
						capture_vect[signal >> 5] &= ~(unsigned long)
							(1L << (signal & 0x1f));
					}
				}
			}
		}
	}
#endif

	return (matched_count);
}


void *jbi_malloc(unsigned int size)
{
	return malloc (size);
}

void jbi_free(void *ptr)
{
	free (ptr);
}

char *error_text[] =
{
/* JBIC_SUCCESS            0 */ "success",
/* JBIC_OUT_OF_MEMORY      1 */ "out of memory",
/* JBIC_IO_ERROR           2 */ "file access error",
/* JAMC_SYNTAX_ERROR       3 */ "syntax error",
/* JBIC_UNEXPECTED_END     4 */ "unexpected end of file",
/* JBIC_UNDEFINED_SYMBOL   5 */ "undefined symbol",
/* JAMC_REDEFINED_SYMBOL   6 */ "redefined symbol",
/* JBIC_INTEGER_OVERFLOW   7 */ "integer overflow",
/* JBIC_DIVIDE_BY_ZERO     8 */ "divide by zero",
/* JBIC_CRC_ERROR          9 */ "CRC mismatch",
/* JBIC_INTERNAL_ERROR    10 */ "internal error",
/* JBIC_BOUNDS_ERROR      11 */ "bounds error",
/* JAMC_TYPE_MISMATCH     12 */ "type mismatch",
/* JAMC_ASSIGN_TO_CONST   13 */ "assignment to constant",
/* JAMC_NEXT_UNEXPECTED   14 */ "NEXT unexpected",
/* JAMC_POP_UNEXPECTED    15 */ "POP unexpected",
/* JAMC_RETURN_UNEXPECTED 16 */ "RETURN unexpected",
/* JAMC_ILLEGAL_SYMBOL    17 */ "illegal symbol name",
/* JBIC_VECTOR_MAP_FAILED 18 */ "vector signal name not found",
/* JBIC_USER_ABORT        19 */ "execution cancelled",
/* JBIC_STACK_OVERFLOW    20 */ "stack overflow",
/* JBIC_ILLEGAL_OPCODE    21 */ "illegal instruction code",
/* JAMC_PHASE_ERROR       22 */ "phase error",
/* JAMC_SCOPE_ERROR       23 */ "scope error",
/* JBIC_ACTION_NOT_FOUND  24 */ "action not found",
};

#undef JAM_STAPL_PLATFORM_CHECK
#undef JAM_STAPL_SUPPORT_NATIVE_CMD

#define MAX_ERROR_CODE (int)((sizeof(error_text)/sizeof(error_text[0]))+1)

/************************************************************************/

int do_jbi (struct cmd_tbl *cmdtp, int flag, int argc, char * const argv [])
{
	JBI_RETURN_TYPE exec_result = JBIC_SUCCESS;
	JBI_RETURN_TYPE crc_result = JBIC_SUCCESS;
	unsigned short expected_crc = 0;
	unsigned short actual_crc = 0;
	char *action = NULL;
	char *workspace = NULL;
	long workspace_size = 0;
	int execute_program = 1;
	int format_version = 0;
	int action_count = 0;
	int procedure_count = 0;
	long offset = 0L;
	int index = 0;
	char *action_name = NULL;
	char *description = NULL;
	JBI_PROCINFO *procedure_list = NULL;
	JBI_PROCINFO *procptr = NULL;
	int reset_jtag = 1;
	long error_address = 0L;
	int arg;
	int exit_code = 0;
	char *exit_string = NULL;
	char *init_list[10];
	int init_count = 0;
	char key[33] = {0};
	char value[257] = {0};
#ifdef JAM_STAPL_PLATFORM_CHECK
	int fileId, maskId;
#endif

	init_list[0] = NULL;

	/* pick a default */
	workspace_size = 64 * 1024;

	if (argc < 3)
	{
		cmd_usage (cmdtp);
		return 0;
	}


	/* print out the version string and copyright message */
	fprintf(stderr, "Jam STAPL ByteCode Player Version 2.2\n"
	                "Copyright (C) 1998-2001 Altera Corporation\n\n");

	/* args parsing */
	for (arg = 1; arg < argc; arg++)
	{
		if (argv [arg][0] == '-')
		{
			switch (argv [arg][1])
			{
				case 'a':
					action = &argv [arg][2];
					break;

				case 'd':
					init_list [init_count] = &argv [arg][2];
					init_list [++init_count] = NULL;
					break;

				case 'm':
					workspace_size = simple_strtoul (&argv [arg][2], NULL, 16);
					break;

				case 'v':
					verbose = TRUE;
					break;

				case 'i':
					verbose = TRUE;
					execute_program = 0;
					break;

				default:
				{
					cmd_usage (cmdtp);
					return 0;
				}
			}
		}
	}

	file_buffer = (unsigned char *)simple_strtoul (argv [argc - 2], NULL, 16);
	file_length = simple_strtoul (argv [argc - 1], NULL, 16);

#ifdef JAM_STAPL_PLATFORM_CHECK
	/* check buffer */
	if (file_buffer [0] != 'K' || file_buffer [1] != 'L')
	{
		printf ("Program file magic does not match - abort\n");
		return 0;
	}

	if (file_buffer [2] != '0' || file_buffer [3] != '1')
	{
		printf ("Program header version not supported - abort\n");
		return 0;
	}

	fileId = (file_buffer [4] << 8) | file_buffer [5];
	maskId = (file_buffer [6] << 8) | file_buffer [7];

	if ((getBoardId () & maskId) != (fileId & maskId))
	{
		printf ("Program file does not match board - abort\n");
		return 0;
	}

	file_buffer += 16;
	file_length -= 16;
#endif
	if ((workspace_size > 0) &&
		((workspace = (char *) jbi_malloc((size_t) workspace_size)) == NULL))
	{
		printf ("Error: can't allocate memory (%d Kbytes)\n",
			(int) (workspace_size / 1024L));
		/*exit_status = 1;*/
		return 0;
	}

	/*
	*	Check CRC
	*/
	crc_result = jbi_check_crc(file_buffer, file_length,
		&expected_crc, &actual_crc);

	if (verbose || (crc_result == JBIC_CRC_ERROR))
	{
		switch (crc_result)
		{
		case JBIC_SUCCESS:
			printf("CRC matched: CRC value = %04X\n", actual_crc);
			break;

		case JBIC_CRC_ERROR:
			printf("CRC mismatch: expected %04X, actual %04X\n",
				expected_crc, actual_crc);
			break;

		case JBIC_UNEXPECTED_END:
			printf("Expected CRC not found, actual CRC value = %04X\n",
				actual_crc);
			break;

		case JBIC_IO_ERROR:
			printf("Error: File format is not recognized.\n");
			return 0;
			break;

		default:
			printf("CRC function returned error code %d\n", crc_result);
			break;
		}
	}

	if (verbose)
	{
		/*
		*	Display file format version
		*/
		jbi_get_file_info(file_buffer, file_length,
			&format_version, &action_count, &procedure_count);

		printf("File format is %s ByteCode format\n",
			(format_version == 2) ? "Jam STAPL" : "pre-standardized Jam 1.1");

		/*
		*	Dump out NOTE fields
		*/
		while (jbi_get_note(file_buffer, file_length,
			&offset, key, value, 256) == 0)
		{
			printf("NOTE \"%s\" = \"%s\"\n", key, value);
		}

		/*
		*	Dump the action table
		*/
		if ((format_version == 2) && (action_count > 0))
		{
			printf("\nActions available in this file:\n");

			for (index = 0; index < action_count; ++index)
			{
				jbi_get_action_info(file_buffer, file_length,
					index, &action_name, &description, &procedure_list);

				if (description == NULL)
				{
					printf("%s\n", action_name);
				}
				else
				{
					printf("%s \"%s\"\n", action_name, description);
				}

				procptr = procedure_list;
				while (procptr != NULL)
				{
					if (procptr->attributes != 0)
					{
						printf("    %s (%s)\n", procptr->name,
							(procptr->attributes == 1) ?
							"optional" : "recommended");
					}

					procedure_list = procptr->next;
					jbi_free(procptr);
					procptr = procedure_list;
				}
			}

			/* add a blank line before execution messages */
			if (execute_program) printf("\n");
		}
	}


	if (execute_program)
	{
		/*
		*	Execute the Jam STAPL ByteCode program
		*/
		exec_result = jbi_execute(file_buffer, file_length, workspace,
			workspace_size, action, init_list, reset_jtag,
			&error_address, &exit_code, &format_version);

		if (exec_result == JBIC_SUCCESS)
		{
			if (format_version == 2)
			{
				switch (exit_code)
				{
				case  0: exit_string = "Success"; break;
				case  1: exit_string = "Checking chain failure"; break;
				case  2: exit_string = "Reading IDCODE failure"; break;
				case  3: exit_string = "Reading USERCODE failure"; break;
				case  4: exit_string = "Reading UESCODE failure"; break;
				case  5: exit_string = "Entering ISP failure"; break;
				case  6: exit_string = "Unrecognized device"; break;
				case  7: exit_string = "Device revision is not supported"; break;
				case  8: exit_string = "Erase failure"; break;
				case  9: exit_string = "Device is not blank"; break;
				case 10: exit_string = "Device programming failure"; break;
				case 11: exit_string = "Device verify failure"; break;
				case 12: exit_string = "Read failure"; break;
				case 13: exit_string = "Calculating checksum failure"; break;
				case 14: exit_string = "Setting security bit failure"; break;
				case 15: exit_string = "Querying security bit failure"; break;
				case 16: exit_string = "Exiting ISP failure"; break;
				case 17: exit_string = "Performing system test failure"; break;
				default: exit_string = "Unknown exit code"; break;
				}
			}
			else
			{
				switch (exit_code)
				{
				case 0: exit_string = "Success"; break;
				case 1: exit_string = "Illegal initialization values"; break;
				case 2: exit_string = "Unrecognized device"; break;
				case 3: exit_string = "Device revision is not supported"; break;
				case 4: exit_string = "Device programming failure"; break;
				case 5: exit_string = "Device is not blank"; break;
				case 6: exit_string = "Device verify failure"; break;
				case 7: exit_string = "SRAM configuration failure"; break;
				default: exit_string = "Unknown exit code"; break;
				}
			}

			printf("Exit code = %d... %s\n", exit_code, exit_string);
		}
		else if ((format_version == 2) &&
			(exec_result == JBIC_ACTION_NOT_FOUND))
		{
			if ((action == NULL) || (*action == '\0'))
			{
				printf("Error: no action specified for Jam STAPL file.\nProgram terminated.\n");
			}
			else
			{
				printf("Error: action \"%s\" is not supported for this Jam STAPL file.\nProgram terminated.\n", action);
			}
		}
		else if (exec_result < MAX_ERROR_CODE)
		{
			printf("Error at address %ld: %s.\nProgram terminated.\n",
				error_address, error_text[exec_result]);
		}
		else
		{
			printf("Unknown error code %d\n", exec_result);
		}
	}

	if (jtag_hardware_initialized) {
		close_jtag_hardware();
		jtag_hardware_initialized = FALSE;
	}

	if (workspace != NULL)
		jbi_free(workspace);

	return 0;
}

#ifdef JAM_STAPL_SUPPORT_NATIVE_CMD
U_BOOT_CMD (
	jbi, 20, 0, do_jbi,
	"jam Stapl byte-code Player for programming onboard logic",
	"[options] <address> <size>\n"
	"  options are:\n"
	"    -v          : show verbose messages\n"
	"    -i          : show file info only - does not execute any action\n"
	"    -a<action>  : specify an action name (Jam STAPL)\n"
	"    -d<var=val> : initialize variable to specified value (Jam 1.1)\n"
	"    -d<proc=1>  : enable optional procedure (Jam STAPL)\n"
	"    -d<proc=0>  : disable recommended procedure (Jam STAPL)\n"
);
#endif

/* kjtag - Kontron wrapper for programming logic with using Jam STAPL ByteCode Player */
int do_kjtag (struct cmd_tbl *cmdtp, int flag, int argc, char * const argv [])
{
	int program = 0;
	int raw_image = 0; /* FIXME: for future use */
	int arg, jbi_argc;
	char *jbi_argv[CONFIG_SYS_MAXARGS + 1];

	/* FIXME: now do_kjtag supports only programming of raw image
	 *	thus options "-p -r" are mandatory.
	 */
	if (argc < 5)
	{
		cmd_usage (cmdtp);
		return 0;
	}

	/* args parsing */
	for (arg = 1; arg < argc; arg++)
	{
		if (argv [arg][0] == '-')
		{
			switch (argv [arg][1])
			{
				case 'p':
					program = TRUE;
					break;

				case 'r':
					raw_image = TRUE;
					break;

				default:
				{
					cmd_usage (cmdtp);
					return 0;
				}
			}
		}
	}

	if (!raw_image) {
		printf("Only programming of raw image supported for now, set '-r' option!\n");
		cmd_usage(cmdtp);
		return 0;
	}

	/* Clear argv pointers tabel */
	jbi_argc = 0;
	while(jbi_argc <= CONFIG_SYS_MAXARGS)
	{
		jbi_argv[jbi_argc++] = NULL;
	}

	/* Prepare arguments for do_jbi command*/
	jbi_argc = 0;
	jbi_argv[jbi_argc++] = "jbi";
	jbi_argv[jbi_argc++] = "-dDO_REAL_TIME_ISP=1";
	if (program) {
		jbi_argv[jbi_argc++] = "-aPROGRAM";
	}
	/* copy arguments : file address buffer and file length */
	jbi_argv[jbi_argc++] = argv [argc - 2];
	jbi_argv[jbi_argc++] = argv [argc - 1];

	return do_jbi(cmdtp, flag, jbi_argc, jbi_argv);
}

U_BOOT_CMD (
	kjtag, 20, 0, do_kjtag,
	"Kontron's command to programe onboard logic with using Jam STAPL ByteCode Player",
	"[options] <address> <size>\n"
	"  options are:\n"
	"    -p  : program logic\n"
	"    -r  : raw image withouth any container\n"
);

void initialize_jtag_hardware()
{
	amx6_setup_iomux_gpio_jtag();
}

void close_jtag_hardware()
{
	amx6_clear_iomux_gpio_jtag();
}


/*- eof -*/
