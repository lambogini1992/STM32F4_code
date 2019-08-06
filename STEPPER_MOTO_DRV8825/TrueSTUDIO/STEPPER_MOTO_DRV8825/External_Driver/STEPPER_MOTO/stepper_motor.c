/*
 * stepper_motor.c
 *
 *  Created on: Aug 6, 2019
 *      Author: ASUS
 */

#include "stepper_motor.h"

void STEPPER_INIT(void)
{
	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOH);
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);

	  /**/
	  LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_14|LL_GPIO_PIN_15);

	  /**/
	  GPIO_InitStruct.Pin = DIR_PIN|STEP_PIN;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void STEPPER_rotate_step_clockwise(uint8_t deg)
{
	uint8_t idx;
	LL_GPIO_SetOutputPin(GPIOD, DIR_PIN);
	for(idx = 0; idx < deg; idx++)
	{
		LL_GPIO_SetOutputPin(GPIOD, STEP_PIN);
		LL_mDelay(100);
		LL_GPIO_ResetOutputPin(GPIOD, STEP_PIN);
	}
}

void STEPPER_rotate_step_anti_clockwise(uint8_t deg)
{
	uint8_t idx;
	LL_GPIO_ResetOutputPin(GPIOD, DIR_PIN);
	for(idx = 0; idx < deg; idx++)
	{
		LL_GPIO_SetOutputPin(GPIOD, STEP_PIN);
		LL_mDelay(100);
		LL_GPIO_ResetOutputPin(GPIOD, STEP_PIN);
	}
}
