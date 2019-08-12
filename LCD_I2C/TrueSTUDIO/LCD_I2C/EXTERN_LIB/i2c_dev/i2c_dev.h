/*
 * i2c_dev.h
 *
 *  Created on: Aug 7, 2019
 *      Author: Admin
 */

#ifndef _I2C_DEV_H_
#define _I2C_DEV_H_

#include "stm32f4xx.h"
#include "stm32f4xx_ll_i2c.h"
#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_exti.h"
#include "stm32f4xx_ll_cortex.h"
#include "stm32f4xx_ll_utils.h"
#include "stm32f4xx_ll_pwr.h"
#include "stm32f4xx_ll_dma.h"
#include "stm32f4xx_ll_gpio.h"

I2C_TypeDef *I2C_ctrl;

I2C_TypeDef *I2C_init(void);
uint8_t I2C_read(I2C_TypeDef *I2Cx, uint8_t add);
void I2C_write(I2C_TypeDef *I2Cx, uint8_t add, uint8_t data);

#endif /* EXTERN_LIB_I2C_DEV_I2C_DEV_H_ */
