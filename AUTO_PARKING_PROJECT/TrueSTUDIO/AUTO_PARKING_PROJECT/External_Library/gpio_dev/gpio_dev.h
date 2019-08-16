/*
 * gpio_dev.h
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#ifndef _GPIO_DEV_H_
#define _GPIO_DEV_H_

#include "stm32f1xx_hal.h"
#include "main.h"

/*--------Define used GPIO function for pin data*/
#define INFARE_SS_Pin 				GPIO_PIN_0
#define INFARE_SS_GPIO_Port 		GPIOA
#define STEP_DRIVER_PIN_Pin 		GPIO_PIN_1
#define STEP_DRIVER_PIN_GPIO_Port 	GPIOA
#define DIR_DRIVER_PIN_Pin 			GPIO_PIN_2
#define DIR_DRIVER_PIN_GPIO_Port 	GPIOA
#define NSS_PIN_RC522_Pin 			GPIO_PIN_4
#define NSS_PIN_RC522_GPIO_Port 	GPIOA
#define JSW_H1_Pin 					GPIO_PIN_0
#define JSW_H1_GPIO_Port 			GPIOB
#define JSW_L1_Pin 					GPIO_PIN_1
#define JSW_L1_GPIO_Port 			GPIOB
#define JSW_H2_Pin 					GPIO_PIN_10
#define JSW_H2_GPIO_Port 			GPIOB
#define JSW_L2_Pin 					GPIO_PIN_11
#define JSW_L2_GPIO_Port 			GPIOB
#define RELAY_ODOOR_Pin 			GPIO_PIN_12
#define RELAY_ODOOR_GPIO_Port 		GPIOB
#define RELAY_CDOOR_Pin 			GPIO_PIN_13
#define RELAY_CDOOR_GPIO_Port 		GPIOB
#define COLOR_SS_OUT_Pin 			GPIO_PIN_14
#define COLOR_SS_OUT_GPIO_Port 		GPIOB
#define COLOR_SS_S2_Pin 			GPIO_PIN_8
#define COLOR_SS_S2_GPIO_Port 		GPIOA
#define COLOR_SS_S1_Pin 			GPIO_PIN_9
#define COLOR_SS_S1_GPIO_Port 		GPIOA
#define COLOR_SS_S0_Pin 			GPIO_PIN_10
#define COLOR_SS_S0_GPIO_Port 		GPIOA
#define PARKING_BT_Pin 				GPIO_PIN_11
#define PARKING_BT_GPIO_Port 		GPIOA
#define TAKE_BT_Pin 				GPIO_PIN_12
#define TAKE_BT_GPIO_Port 			GPIOA
#define LED_STATUS_Pin 				GPIO_PIN_5
#define LED_STATUS_GPIO_Port 		GPIOB
#define BUZZ_Pin					GPIO_PIN_7
#define BUZZ_GPIO_Port 				GPIOB
/*Function PIN*/
void GPIO_Init(void);

#endif /* EXTERNAL_LIBRARY_GPIO_DEV_GPIO_DEV_H_ */
