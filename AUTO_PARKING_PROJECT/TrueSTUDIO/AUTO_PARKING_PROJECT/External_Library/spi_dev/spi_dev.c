/*
 * spi_dev.c
 *
 *  Created on: Aug 11, 2019
 *      Author: ASUS
 */

#include "spi_dev/spi_dev.h"

/*SPI control peripheral hardware*/
static SPI_HandleTypeDef hspi_ctrl;

uint8_t SPI_send_byte(uint8_t data);

void SPI_INIT_project(void)
{
	hspi_ctrl.Instance = SPI1;
	hspi_ctrl.Init.Mode = SPI_MODE_MASTER;
	hspi_ctrl.Init.Direction = SPI_DIRECTION_2LINES;
	hspi_ctrl.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi_ctrl.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi_ctrl.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi_ctrl.Init.NSS = SPI_NSS_SOFT;
	hspi_ctrl.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hspi_ctrl.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi_ctrl.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi_ctrl.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi_ctrl.Init.CRCPolynomial = 10;
	if (HAL_SPI_Init(&hspi_ctrl) != HAL_OK)
	{
		Error_Handler();
	}
}


uint8_t SPI_send_byte(uint8_t data)
{
	unsigned char writeCommand[1];
	unsigned char readValue[1];

	writeCommand[0] = data;
	HAL_SPI_TransmitReceive(&hspi_ctrl, (uint8_t*)&writeCommand, (uint8_t*)&readValue, 1, 100);
	return readValue[0];
}

void SPI_write_reg(uint8_t add_reg, uint8_t data)
{
	ENA_SPI_COM_CTRL;
	(void)SPI_send_byte(add_reg);
	(void)SPI_send_byte(data);
	DIS_SPI_COM_CTRL;
}

uint8_t SPI_read_reg(uint8_t add_reg)
{
	uint8_t ret_val;
	ENA_SPI_COM_CTRL;
	(void)SPI_send_byte(add_reg);
	ret_val = SPI_send_byte(0x00);
	DIS_SPI_COM_CTRL;
	return ret_val;
}
