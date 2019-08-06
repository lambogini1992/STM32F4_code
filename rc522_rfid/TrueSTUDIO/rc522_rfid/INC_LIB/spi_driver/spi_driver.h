/*
 * spi_driver.h
 *
 *  Created on: Aug 6, 2019
 *      Author: Admin
 */

#ifndef _SPI_DRIVER_H_
#define _SPI_DRIVER_H_

#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"


#define ENA_CSS_PIN		LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4)
#define DIS_CSS_PIN		LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_4)

#define DATA_DEFAULT	0x00

SPI_TypeDef *SPI_ctrl;

void MX_GPIO_CSS_Init(void);
SPI_TypeDef *MX_SPI_Init(void);

const char *SPI_read(SPI_TypeDef *SPIx, uint8_t add_reg, uint8_t len_data);
void SPI_write(SPI_TypeDef *SPIx, uint8_t add_reg, const char *data);

#endif /* INC_LIB_SPI_DRIVER_SPI_DRIVER_H_ */
