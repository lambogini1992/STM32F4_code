/*
 * boot_proc.h
 *
 *  Created on: Feb 19, 2020
 *      Author: ASUS
 */

#ifndef BOOT_PROC_H_
#define BOOT_PROC_H_

#include "stm32f1xx_hal.h"
#include "flash_handle.h"

#define APPLICATION_ADDRESS_PRO				0x8000000
#define APPLICATION_FLASH_LEN				0x8000

/* address flash	data length		data file			checksum data     end line
 *  4 byte			 1 byte	        256 byte				2 byte         4byte
 *  							(max length data)
 *  This format use *.bin file and this will modify data
 *  Checksum data is value from address flash and data file
 * */

#define DATA_FILE_ADD_POS					0x000
#define DATA_FILE_LEN_POS					0x002
#define DATA_FILE_DATA_POS					0x003
#define DATA_FILE_CHECKSUM_POS				0x102
#define DATA_FILE_RAW_DATA_LEN				0x105
#define DATA_FILE_LEN_BEFORE_DATA_POS		0x003


#define DATA_FILE_FACTOR_CHECKSUM			0xFFFE


#define BOOT_PROCESS_FAIL					0x01
#define BOOT_PROCESS_SUCCESS				0x00

typedef struct _data_file_
{
	uint16_t add_flash;
	uint8_t  data_len;
	uint8_t  *data;
}DATA_FILE;

/*METHOD of BOOTLOADER*/
void BOOT_jump_app(uint32_t add);

uint8_t BOOT_erase(uint32_t add, uint16_t flash_app_len);
uint8_t BOOT_handle_data(uint8_t *raw_data, DATA_FILE *data_prog);
uint8_t BOOT_flash_prog(DATA_FILE data);
uint8_t BOOT_check_data(uint8_t *raw_data);

#endif /* BOOT_PROC_H_ */
