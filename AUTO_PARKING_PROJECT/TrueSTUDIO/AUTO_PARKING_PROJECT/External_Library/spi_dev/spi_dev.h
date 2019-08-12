/*
 * spi_dev.h
 *
 *  Created on: Aug 11, 2019
 *      Author: ASUS
 */

#ifndef _SPI_DEV_H_
#define _SPI_DEV_H_

#include "stm32f1xx_hal.h"
#include "../gpio_dev/gpio_dev.h"
#include "main.h"

/*define Enable and Disable for SPI NSS control*/
#define ENA_SPI_COM_CTRL			HAL_GPIO_WritePin(NSS_PIN_RC522_GPIO_Port, NSS_PIN_RC522_Pin, GPIO_PIN_RESET);
#define DIS_SPI_COM_CTRL			HAL_GPIO_WritePin(NSS_PIN_RC522_GPIO_Port, NSS_PIN_RC522_Pin, GPIO_PIN_SET);




void SPI_INIT_project(void);

void SPI_write_reg(uint8_t add_reg, uint8_t data);
uint8_t SPI_read_reg(uint8_t add_reg);

#endif /* EXTERNAL_LIBRARY_SPI_DEV_SPI_DEV_H_ */
