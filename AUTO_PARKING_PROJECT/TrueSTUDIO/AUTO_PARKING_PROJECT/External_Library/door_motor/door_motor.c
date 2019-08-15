/*
 * door_motor.c
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#include "door_motor.h"

bool check_jsw_button(uint8_t action)
{
	if(ACTION_OPEN_DOOR == action)
	{
		if(SW_IS_ATTACK ==  HAL_GPIO_ReadPin(JSW_H1_GPIO_Port, JSW_H1_Pin))
		{
			HAL_Delay(500);
			if(SW_IS_ATTACK ==  HAL_GPIO_ReadPin(JSW_H1_GPIO_Port, JSW_H1_Pin))
			{
				return true;
			}
		}
	}
	else if(ACTION_CLOSE_DOOR == action)
	{
		if(SW_IS_ATTACK ==  HAL_GPIO_ReadPin(JSW_H2_GPIO_Port, JSW_H2_Pin))
		{
			HAL_Delay(500);
			if(SW_IS_ATTACK ==  HAL_GPIO_ReadPin(JSW_H2_GPIO_Port, JSW_H2_Pin))
			{
				return true;
			}
		}
	}
	return false;
}


void action_motor(uint8_t action)
{
	HAL_GPIO_WritePin(RELAY_ODOOR_GPIO_Port, RELAY_ODOOR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RELAY_CDOOR_GPIO_Port, RELAY_CDOOR_Pin, GPIO_PIN_RESET);
	if(ACTION_OPEN_DOOR == action)
	{
		HAL_GPIO_WritePin(RELAY_CDOOR_GPIO_Port, RELAY_CDOOR_Pin, GPIO_PIN_SET);
		HAL_Delay(2500);
	}
	else if(ACTION_CLOSE_DOOR == action)
	{
		HAL_GPIO_WritePin(RELAY_ODOOR_GPIO_Port, RELAY_ODOOR_Pin, GPIO_PIN_SET);
		HAL_Delay(2500);
	}
	HAL_GPIO_WritePin(RELAY_ODOOR_GPIO_Port, RELAY_ODOOR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RELAY_CDOOR_GPIO_Port, RELAY_CDOOR_Pin, GPIO_PIN_RESET);
	HAL_Delay(1000);
}
