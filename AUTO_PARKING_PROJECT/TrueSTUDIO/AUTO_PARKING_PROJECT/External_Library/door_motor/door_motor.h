/*
 * door_motor.h
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#ifndef _DOOR_MOTOR_H_
#define _DOOR_MOTOR_H_

#include "stm32f1xx_hal.h"
#include "../gpio_dev/gpio_dev.h"

#define ACTION_OPEN_DOOR		0
#define ACTION_CLOSE_DOOR		1

#define SW_IS_ATTACK			GPIO_PIN_SET
#define SW_IS_RELEASE			GPIO_PIN_RESET

bool check_jsw_button(uint8_t action);

void action_motor(uint8_t action);

#endif /* EXTERNAL_LIBRARY_DOOR_MOTOR_DOOR_MOTOR_H_ */
