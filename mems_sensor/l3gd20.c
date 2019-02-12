/*
 * l3gd20.c
 *
 *  Created on: Feb 9, 2019
 *      Author: AnhPT26
 */
#include "../Inc/l3gd20.h"


static uint8_t L3GD20_INT_ReadSPI(uint8_t address);
static void L3GD20_INT_WriteSPI(uint8_t address, uint8_t data);
static void sensitivity_data(L3GD20_data_out* L3DG20_Data, float sensity);

static SPI_HandleTypeDef *hspi_l3gd20;
static int8_t scale_init;

L3GD20_Result_t L3GD20_Init(SPI_HandleTypeDef *hspi, int8_t scale)
{
	hspi_l3gd20 = hspi;
	scale_init  = scale;
	/* Check if sensor is L3GD20 */
	if (L3GD20_INT_ReadSPI(L3GD20_REG_WHO_AM_I) != L3GD20_WHO_AM_I) {
		/* Sensor connected is not L3GD20 */
		return L3GD20_Result_Error;
	}

	/* Enable L3GD20 Power bit */
	L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG1, 0xFF);

	/* Set L3GD20 scale */
	L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG4, scale_init);

	/* Set high-pass filter settings */
	L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG2, 0x00);

	/* Everything OK */
	L3GD20_INT_WriteSPI(L3GD20_REG_CTRL_REG5, 0x10);

	return L3GD20_Result_Ok;

}

L3GD20_Result_t L3GD20_Read(L3GD20_data_out* L3DG20_Data)
{
	L3DG20_Data->X_data  = L3GD20_INT_ReadSPI(L3GD20_REG_OUT_X_L);
	L3DG20_Data->X_data |= L3GD20_INT_ReadSPI(L3GD20_REG_OUT_X_H) << 8;

	L3DG20_Data->Y_data  = L3GD20_INT_ReadSPI(L3GD20_REG_OUT_Y_L);
	L3DG20_Data->Y_data |= L3GD20_INT_ReadSPI(L3GD20_REG_OUT_Y_H) << 8;

	L3DG20_Data->Z_data  = L3GD20_INT_ReadSPI(L3GD20_REG_OUT_Z_L);
	L3DG20_Data->Z_data |= L3GD20_INT_ReadSPI(L3GD20_REG_OUT_Z_H) << 8;

	// switch(scale_init)
	// {
	// 	case L3GD20_SCALE_250:
	// 		sensitivity_data(L3DG20_Data, L3GD20_SENSITIVITY_250);
	// 	case L3GD20_SCALE_500:
	// 		sensitivity_data(L3DG20_Data, L3GD20_SENSITIVITY_500);
	// 	case L3GD20_SCALE_2000:
	// 		sensitivity_data(L3DG20_Data, L3GD20_SENSITIVITY_2000);
	// }
	return L3GD20_Result_Ok;
}

static uint8_t L3GD20_INT_ReadSPI(uint8_t address)
{
	uint8_t data_read;
	int i;
	data_read = 0;
	L3GD20_ENABLE;

	HAL_SPI_Transmit_IT(hspi_l3gd20, &address, 1);
	HAL_SPI_TransmitReceive_IT(hspi_l3gd20, (uint8_t *)0xFF, &data_read, 1);
	L3GD20_DISABLE;
	return data_read;
}


static void L3GD20_INT_WriteSPI(uint8_t address, uint8_t data)
{

		L3GD20_ENABLE;

		HAL_SPI_Transmit_IT(hspi_l3gd20, &address, 1);
		HAL_SPI_Transmit_IT(hspi_l3gd20, &data, 1);

		L3GD20_DISABLE;
}


static void sensitivity_data(L3GD20_data_out* L3DG20_Data, float sensity)
{
	float temp, s;

	s = sensity * 0.001;

	temp = (float)L3DG20_Data->X_data * s;
	L3DG20_Data->X_data = (int16_t)temp;

	temp = (float)L3DG20_Data->Y_data * s;
	L3DG20_Data->Y_data = (int16_t)temp;

	temp = (float)L3DG20_Data->Z_data * s;
	L3DG20_Data->Z_data = (int16_t)temp;
}
