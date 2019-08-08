/*
 * i2c_dev.h
 *
 *  Created on: Aug 8, 2019
 *      Author: Admin
 */

#ifndef _I2C_DEV_H_
#define _I2C_DEV_H_

#include "stm32f4xx_hal.h"

I2C_HandleTypeDef hi2c_ctrl;

I2C_HandleTypeDef MX_I2C_Init(void);


#endif /* EXTERNAL_LIB_I2C_DEV_I2C_DEV_H_ */
