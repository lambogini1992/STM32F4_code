/*
 * flash_handle.h
 *
 *  Created on: Feb 18, 2020
 *      Author: ASUS
 */

#ifndef FLASH_HANDLE_FLASH_HANDLE_H_
#define FLASH_HANDLE_FLASH_HANDLE_H_

#include "stm32f1xx_hal.h"

#define FLASH_OFFSET_ADD_DATA			4

#define FLASH_WRITE_SUCCESS				0
#define FLASH_WRITE_FAIL				1

#define FLASH_READ_FAIL					0xFFFFFFFF

#define FLASH_ERASE_FAIL				1
#define FLASH_ERASE_SUCCESS				0

uint8_t FLASH_erase_page(uint32_t add, uint16_t n_page);
uint8_t FLASH_saving_1byte_data(uint32_t add, uint8_t *data, uint16_t data_len);
uint8_t FLASH_saving_2byte_data(uint32_t add, uint16_t *data, uint16_t data_len);
uint8_t FLASH_saving_4byte_data(uint32_t add, uint32_t *data, uint16_t data_len);
uint32_t FLASH_read_data(uint32_t add);

#endif /* FLASH_HANDLE_FLASH_HANDLE_H_ */
