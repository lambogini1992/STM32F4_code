/*
 * i2c_dev.h
 *
 *  Created on: Aug 12, 2019
 *      Author: Admin
 */

#ifndef _I2C_DEV_H_
#define _I2C_DEV_H_

#include "stm32f1xx_hal.h"
#include "../gpio_dev/gpio_dev.h"
#include "main.h"

void I2C_init(void);

void I2C_send_data(uint8_t add_dev, uint8_t *data, uint8_t data_len);

#endif /* EXTERNAL_LIBRARY_I2C_DEV_I2C_DEV_H_ */
