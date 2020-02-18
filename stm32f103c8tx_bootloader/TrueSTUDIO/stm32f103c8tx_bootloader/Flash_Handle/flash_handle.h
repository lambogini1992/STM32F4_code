/*
 * flash_handle.h
 *
 *  Created on: Feb 18, 2020
 *      Author: Admin
 */

#ifndef FLASH_HANDLE_FLASH_HANDLE_H_
#define FLASH_HANDLE_FLASH_HANDLE_H_
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "stm32f1xx_hal.h"


#define FLASH_ADDRESS_DATA 				0x8009000
#define FLASH_OFFSET_ADD_DATA			4
#define FLASH_WRITE_SUCESS				0
#define FLASH_ERASE_FAIL				1
#define FLASH_WRITE_FAIL				2

uint8_t FLASH_saving_1byte_data(uint32_t add, uint8_t *data, uint16_t data_len);
uint8_t FLASH_saving_2byte_data(uint32_t add, uint16_t *data, uint16_t data_len);
uint8_t FLASH_saving_4byte_data(uint32_t add, uint32_t *data, uint16_t data_len);
uint32_t FLASH_read_data(uint32_t add);


#endif /* FLASH_HANDLE_FLASH_HANDLE_H_ */
