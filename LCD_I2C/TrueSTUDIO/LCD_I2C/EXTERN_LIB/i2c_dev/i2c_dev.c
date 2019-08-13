/*
 * i2c_dev.c
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#include "i2c_dev.h"

static I2C_HandleTypeDef hi2c_ctrl;

void I2C_init(void)
{
	hi2c_ctrl.Instance = I2C1;
	hi2c_ctrl.Init.ClockSpeed = 100000;
	hi2c_ctrl.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c_ctrl.Init.OwnAddress1 = 0;
	hi2c_ctrl.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c_ctrl.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c_ctrl.Init.OwnAddress2 = 0;
	hi2c_ctrl.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c_ctrl.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c_ctrl) != HAL_OK)
	{
		Error_Handler();
	}
}

void I2C_send_data(uint8_t add_dev, uint8_t *data_t, uint8_t data_len)
{
	HAL_I2C_Master_Transmit(&hi2c_ctrl, add_dev, data_t, data_len, 100);
}
