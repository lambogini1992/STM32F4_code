/*
 * boot_proc.c
 *
 *  Created on: Feb 19, 2020
 *      Author: ASUS
 */

#include "boot_proc.h"

typedef void (*pFunction)(void);

void BOOT_jump_app(uint32_t add)
{
	pFunction appEntry;
	uint32_t main_stack;
	/*Disable all IRQs in system*/
	__disable_irq();

	main_stack = (uint32_t) *((__IO uint32_t*)add);
	appEntry   = (pFunction) *(__IO uint32_t*)(add + 4);

    SCB->VTOR = main_stack;

    /* Set the application stack pointer */
    __set_MSP(main_stack);

    appEntry();
}

uint8_t BOOT_erase(uint32_t add, uint16_t flash_app_len)
{
	uint8_t ret_val;

	ret_val = FLASH_erase_page(add, flash_app_len);

	return ret_val;
}

uint8_t BOOT_handle_data(uint8_t *raw_data, DATA_FILE *data_prog)
{
	uint8_t idx;

	data_prog->add_flash = (((uint32_t)raw_data[DATA_FILE_ADD_POS] << 24) & 0xFF000000) | (((uint32_t)raw_data[DATA_FILE_ADD_POS + 1] << 16) & 0x00FF0000) |\
			 (((uint32_t)raw_data[DATA_FILE_ADD_POS + 2] << 8) & 0x0000FF00) | ((uint32_t)raw_data[DATA_FILE_ADD_POS + 3] & 0x000000FF);

	data_prog->data_len = raw_data[DATA_FILE_LEN_POS];

	for(idx = 0; idx < data_prog->data_len; idx++)
	{
		data_prog->data[idx] = raw_data[DATA_FILE_DATA_POS + idx];
	}

	return BOOT_PROCESS_SUCCESS;
}

uint8_t BOOT_flash_prog(DATA_FILE data)
{
	uint8_t ret_val;

	ret_val = FLASH_saving_1byte_data(data.add_flash, data.data, data.data_len);

	return ret_val;
}

uint8_t BOOT_check_data(uint8_t *raw_data)
{
	uint16_t cc_value_user;
	uint16_t cc_value_raw;
	uint8_t data_lenght;
	uint16_t sum;
	uint16_t idx;

	data_lenght = raw_data[DATA_FILE_LEN_POS];

	cc_value_user = (((uint16_t)raw_data[data_lenght + DATA_FILE_DATA_POS] << 8) & 0xFF00) | ((uint16_t)raw_data[data_lenght + DATA_FILE_DATA_POS] & 0x00FF);

	sum = 0;
	for(idx = 0; idx < (data_lenght + DATA_FILE_LEN_BEFORE_DATA_POS); idx++)
	{
		sum = (uint16_t)(sum + raw_data[idx]);
	}

	cc_value_raw = (uint16_t)(DATA_FILE_FACTOR_CHECKSUM + sum);
	cc_value_raw = ~cc_value_raw;

	if(cc_value_raw == cc_value_user)
	{
		return BOOT_PROCESS_SUCCESS;
	}
	return BOOT_PROCESS_FAIL;
}
