/*
 * i2c_dev.c
 *
 *  Created on: Aug 8, 2019
 *      Author: Admin
 */

#include "i2c_dev.h"

void Error_Handler(void);

I2C_HandleTypeDef MX_I2C_Init(void)
{
  I2C_HandleTypeDef hi2c_tmp;

  hi2c_tmp.Instance = I2C1;
  hi2c_tmp.Init.ClockSpeed = 500000;
  hi2c_tmp.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c_tmp.Init.OwnAddress1 = 0;
  hi2c_tmp.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c_tmp.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c_tmp.Init.OwnAddress2 = 0;
  hi2c_tmp.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c_tmp.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c_tmp) != HAL_OK)
  {
	Error_Handler();
  }
  return hi2c_tmp;
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}
