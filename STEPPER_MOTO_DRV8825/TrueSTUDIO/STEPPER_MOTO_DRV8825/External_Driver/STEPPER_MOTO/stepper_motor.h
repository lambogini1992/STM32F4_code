/*
 * stepper_motor.h
 *
 *  Created on: Aug 6, 2019
 *      Author: ASUS
 */

#ifndef _STEPPER_MOTOR_H_
#define _STEPPER_MOTOR_H_

#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_usart.h"
#include "stm32f4xx.h"
#include "stm32f4xx_ll_gpio.h"

#define DIR_PIN			LL_GPIO_PIN_15
#define STEP_PIN		LL_GPIO_PIN_14

void STEPPER_INIT(void);
void STEPPER_rotate_step_clockwise(uint8_t deg);//degree of moto is be multiple 1.8*deg
void STEPPER_rotate_step_anti_clockwise(uint8_t deg);//degree of moto is be multiple 1.8*deg
#endif /* EXTERNAL_DRIVER_STEPPER_MOTO_STEPPER_MOTOR_H_ */
