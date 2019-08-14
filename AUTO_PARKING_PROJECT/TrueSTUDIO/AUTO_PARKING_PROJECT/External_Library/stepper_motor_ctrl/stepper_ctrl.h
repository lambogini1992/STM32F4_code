/*
 * stepper_ctrl.h
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#ifndef _STEPPER_CTRL_H_
#define _STEPPER_CTRL_H_

#include "stm32f1xx_hal.h"
#include "../gpio_dev/gpio_dev.h"


#define ROTATE_CLOCKWISE			   	GPIO_PIN_SET
#define ROTATE_ANTI_CLOCKWISE			GPIO_PIN_RESET

void check_count_step(GPIO_PinState dir);
void rotate_motor(GPIO_PinState dir, uint64_t step);


#endif /* EXTERNAL_LIBRARY_STEPPER_MOTOR_CTRL_STEPPER_CTRL_H_ */
