/*
 * stepper_ctrl.c
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#include "stepper_ctrl.h"


void check_count_step(GPIO_PinState dir)
{
	HAL_GPIO_WritePin(DIR_DRIVER_PIN_GPIO_Port, DIR_DRIVER_PIN_Pin, dir);
	HAL_GPIO_WritePin(STEP_DRIVER_PIN_GPIO_Port, STEP_DRIVER_PIN_Pin, GPIO_PIN_SET);
    HAL_Delay(10);
	HAL_GPIO_WritePin(STEP_DRIVER_PIN_GPIO_Port, STEP_DRIVER_PIN_Pin, GPIO_PIN_RESET);
    HAL_Delay(10);
}

void rotate_motor(GPIO_PinState dir, uint64_t step)
{
	uint32_t count;
	HAL_GPIO_WritePin(DIR_DRIVER_PIN_GPIO_Port, DIR_DRIVER_PIN_Pin, dir);
	for (count = 0; count < step; ++count)
	{
		HAL_GPIO_WritePin(STEP_DRIVER_PIN_GPIO_Port, STEP_DRIVER_PIN_Pin, GPIO_PIN_SET);
	    HAL_Delay(26);
		HAL_GPIO_WritePin(STEP_DRIVER_PIN_GPIO_Port, STEP_DRIVER_PIN_Pin, GPIO_PIN_RESET);
	    HAL_Delay(26);
	}

}
