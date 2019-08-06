/*
 * uart_dev.c
 *
 *  Created on: Aug 6, 2019
 *      Author: ASUS
 */

#include "uart_dev.h"

USART_TypeDef *MX_USART_UART_Init(void)
{

	  /* USER CODE BEGIN USART1_Init 0 */

	  /* USER CODE END USART1_Init 0 */

	  LL_USART_InitTypeDef USART_InitStruct = {0};

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* Peripheral clock enable */
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	  /**USART1 GPIO Configuration
	  PA9   ------> USART1_TX
	  PA10   ------> USART1_RX
	  */
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_9|LL_GPIO_PIN_10;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /* USART1 interrupt Init */
	  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	  NVIC_EnableIRQ(USART1_IRQn);

	  /* USER CODE BEGIN USART1_Init 1 */

	  /* USER CODE END USART1_Init 1 */
	  USART_InitStruct.BaudRate = 9600;
	  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	  LL_USART_Init(USART1, &USART_InitStruct);
	  LL_USART_ConfigAsyncMode(USART1);
	  LL_USART_Enable(USART1);
	  /* USER CODE BEGIN USART1_Init 2 */
	  return USART1;
}

const char *UART_read(USART_TypeDef *UARTx, uint8_t len_data)
{
	char *data;
	uint8_t idx;

	data = malloc(len_data);

	for(idx = 0; idx < len_data; idx++)
	{
		data[idx] = (char)LL_USART_ReceiveData8(UARTx);
	}

	return (const char *)data;
}


void UART_write(USART_TypeDef *UARTx, const char *data)
{
	uint8_t data_len;
	uint8_t idx;

	data_len = strlen(data);

	for(idx = 0; idx < data_len; idx++)
	{
		LL_USART_TransmitData8(UARTx, (uint8_t)data[idx]);

	}
}
