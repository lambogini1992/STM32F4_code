/*
 * uart_dev.h
 *
 *  Created on: Aug 6, 2019
 *      Author: ASUS
 */

#ifndef _UART_DEV_H_
#define _UART_DEV_H_

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

USART_TypeDef *UART_ctrl;

USART_TypeDef *MX_USART_UART_Init(void);

const char *UART_read(USART_TypeDef *UARTx, uint8_t len_data);
void UART_write(USART_TypeDef *UARTx, const char *data);

#endif /* UART_DEV_UART_DEV_H_ */
