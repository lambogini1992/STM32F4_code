/*
 * spi_driver.c
 *
 *  Created on: Aug 6, 2019
 *      Author: Admin
 */

#include "spi_driver.h"


void MX_GPIO_CSS_Init(void)
{
	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	  /**/
	  LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_4);

	  /**/
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_4;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

SPI_TypeDef *MX_SPI_Init(void)
{
	  LL_SPI_InitTypeDef SPI_InitStruct = {0};

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* Peripheral clock enable */
	  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	  /**SPI1 GPIO Configuration
	  PA5   ------> SPI1_SCK
	  PA6   ------> SPI1_MISO
	  PA7   ------> SPI1_MOSI
	  */
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_5|LL_GPIO_PIN_6|LL_GPIO_PIN_7;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_5;
	  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  /* SPI1 interrupt Init */
	  NVIC_SetPriority(SPI1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	  NVIC_EnableIRQ(SPI1_IRQn);

	  /* USER CODE BEGIN SPI1_Init 1 */

	  /* USER CODE END SPI1_Init 1 */
	  /* SPI1 parameter configuration*/
	  SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	  SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;
	  SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
	  SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
	  SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	  SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
	  SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV2;
	  SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
	  SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
	  SPI_InitStruct.CRCPoly = 10;
	  LL_SPI_Init(SPI1, &SPI_InitStruct);
	  LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);

	  return SPI1;
}

const char *SPI_read(SPI_TypeDef *SPIx, uint8_t add_reg, uint8_t len_data)
{
	char *data;
	uint8_t idx;

	data = malloc(len_data);

	ENA_CSS_PIN;

	LL_SPI_TransmitData8(SPIx, add_reg);

	for(idx = 0; idx < len_data; idx++)
	{
		LL_SPI_TransmitData8(SPIx, DATA_DEFAULT);
		memcpy(data + idx, LL_SPI_ReceiveData8(SPIx), 1);
		while(!LL_SPI_IsActiveFlag_TXE(SPIx));
	}
	DIS_CSS_PIN;

	return (const char *)data;
}

void SPI_write(SPI_TypeDef *SPIx, uint8_t add_reg, const char *data)
{
	uint8_t len_data;
	uint8_t idx;

	len_data = strlen(data);

	ENA_CSS_PIN;

	LL_SPI_TransmitData8(SPIx, add_reg);

	for(idx = 0; idx < len_data; idx++)
	{
		LL_SPI_TransmitData8(SPIx, data + idx);
		while(!LL_SPI_IsActiveFlag_TXE(SPIx));
	}

	DIS_CSS_PIN;
}
