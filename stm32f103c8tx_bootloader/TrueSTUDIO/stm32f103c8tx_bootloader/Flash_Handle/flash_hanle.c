/*
 * flash_hanle.c
 *
 *  Created on: Feb 18, 2020
 *      Author: Admin
 */

#include "flash_handle.h"

uint8_t FLASH_saving_1byte_data(uint32_t add, uint8_t *data, uint16_t data_len)
{
	uint32_t *data_prog;
	uint16_t data_prog_len;
	uint16_t n_page;
	FLASH_EraseInitTypeDef FErase;
	uint32_t pageError;
	uint16_t idx;
	uint8_t status_prog;
	uint8_t error_prog;


	data_prog_len = data_len/4;
	if((data_len%4) != 0)
	{
		data_prog_len = data_prog_len + 1;
	}

	n_page = (data_len/FLASH_PAGE_SIZE);
	if((data_len % FLASH_PAGE_SIZE) != 0)
	{
		n_page = n_page + 1;
	}

	data_prog = (uint32_t *)malloc(data_prog_len * 4);

	memset(data_prog, 0xFFFFFFFF, data_prog_len);
	strcpy((char *)data_prog, (char *)data);

	while(HAL_OK != HAL_FLASH_Unlock());

	while(HAL_OK != HAL_FLASH_OB_Unlock());

	FErase.TypeErase 	= FLASH_TYPEERASE_PAGES;
	FErase.PageAddress 	= FLASH_ADDRESS_DATA;
	FErase.NbPages		= n_page;

	if(HAL_OK == HAL_FLASHEx_Erase(&FErase, &pageError))
	{
		error_prog = 0;
		idx = 0;
		while(idx < data_prog_len)
		{
			status_prog = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_ADDRESS_DATA + (FLASH_OFFSET_ADD_DATA * idx), data_prog[idx]);
			if(status_prog == HAL_OK)
			{
				idx++;
				error_prog = 0;
			}
			else
			{
				error_prog++;
				if(error_prog == 5)
				{
					while(HAL_OK != HAL_FLASH_OB_Lock());

					while(HAL_OK != HAL_FLASH_Lock());

					return FLASH_WRITE_FAIL;
				}
			}
		}
	}
	else
	{
		while(HAL_OK != HAL_FLASH_OB_Lock());

		while(HAL_OK != HAL_FLASH_Lock());

		return FLASH_ERASE_FAIL;
	}

	while(HAL_OK != HAL_FLASH_OB_Lock());

	while(HAL_OK != HAL_FLASH_Lock());

	free(data_prog);
	return FLASH_WRITE_SUCESS;
}

uint8_t FLASH_saving_2byte_data(uint32_t add, uint16_t *data, uint16_t data_len)
{
	uint16_t *data_prog;
	uint16_t data_prog_len;
	uint8_t n_page;
	FLASH_EraseInitTypeDef FErase;
	uint32_t pageError;
	uint16_t idx;
	uint8_t status_prog;
	uint8_t error_prog;


	data_prog_len = data_len/2;
	if((data_len % 2) != 0)
	{
		data_prog_len = data_prog_len + 1;
	}

	n_page = (uint8_t)(data_len/FLASH_PAGE_SIZE);
	if((data_len % FLASH_PAGE_SIZE) != 0)
	{
		n_page = n_page + 1;
	}

	data_prog = (uint16_t *)malloc(data_prog_len * 2);

	memset(data_prog, 0xFFFFFFFF, data_prog_len);
	strcpy((char *)data_prog, (char *)data);

	while(HAL_OK != HAL_FLASH_Unlock());

	while(HAL_OK != HAL_FLASH_OB_Unlock());

	FErase.TypeErase 	= FLASH_TYPEERASE_PAGES;
	FErase.PageAddress 	= add;
	FErase.NbPages		= n_page;

	if(HAL_OK == HAL_FLASHEx_Erase(&FErase, &pageError))
	{
		error_prog = 0;
		idx = 0;
		while(idx < data_prog_len)
		{
			status_prog = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, add + (FLASH_OFFSET_ADD_DATA * idx), (uint64_t)data_prog[idx]);
			if(status_prog == HAL_OK)
			{
				idx++;
				error_prog = 0;
			}
			else
			{
				error_prog++;
				if(error_prog == 5)
				{
					while(HAL_OK != HAL_FLASH_OB_Lock());

					while(HAL_OK != HAL_FLASH_Lock());
					return FLASH_WRITE_FAIL;
				}
			}
		}
	}
	else
	{
		while(HAL_OK != HAL_FLASH_OB_Lock());

		while(HAL_OK != HAL_FLASH_Lock());
		return FLASH_ERASE_FAIL;
	}

	while(HAL_OK != HAL_FLASH_OB_Lock());

	while(HAL_OK != HAL_FLASH_Lock());

	free(data_prog);
	return FLASH_WRITE_SUCESS;
}

uint8_t FLASH_saving_4byte_data(uint32_t add, uint32_t *data, uint16_t data_len)
{
	uint8_t n_page;
	FLASH_EraseInitTypeDef FErase;
	uint32_t pageError;
	uint16_t idx;
	uint8_t status_prog;
	uint8_t error_prog;

	n_page = (uint8_t)(data_len/FLASH_PAGE_SIZE);
	if((data_len % FLASH_PAGE_SIZE) != 0)
	{
		n_page = n_page + 1;
	}

	while(HAL_OK != HAL_FLASH_Unlock());

	while(HAL_OK != HAL_FLASH_OB_Unlock());

	FErase.TypeErase 	= FLASH_TYPEERASE_PAGES;
	FErase.PageAddress 	= add;
	FErase.NbPages		= n_page;

	if(HAL_OK == HAL_FLASHEx_Erase(&FErase, &pageError))
	{
		error_prog = 0;
		idx = 0;
		while(idx < data_len)
		{
			status_prog = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, add + (FLASH_OFFSET_ADD_DATA * idx), (uint64_t)data[idx]);
			if(status_prog == HAL_OK)
			{
				idx++;
				error_prog = 0;
			}
			else
			{
				error_prog++;
				if(error_prog == 5)
				{
					while(HAL_OK != HAL_FLASH_OB_Lock());

					while(HAL_OK != HAL_FLASH_Lock());
					return FLASH_WRITE_FAIL;
				}
			}
		}
	}
	else
	{
		while(HAL_OK != HAL_FLASH_OB_Lock());

		while(HAL_OK != HAL_FLASH_Lock());
		return FLASH_ERASE_FAIL;
	}

	while(HAL_OK != HAL_FLASH_OB_Lock());

	while(HAL_OK != HAL_FLASH_Lock());

	return FLASH_WRITE_SUCESS;
}


uint32_t FLASH_read_data(uint32_t add)
{
	volatile uint32_t read_data;

	read_data = *(uint32_t *)add;

	return read_data;
}
