/*
 * i2c_dev.c
 *
 *  Created on: Aug 7, 2019
 *      Author: Admin
 */


#include "i2c_dev.h"

I2C_TypeDef *I2C_init(void)
{
	  /* USER CODE BEGIN I2C1_Init 0 */

	  /* USER CODE END I2C1_Init 0 */

	  LL_I2C_InitTypeDef I2C_InitStruct = {0};

	  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
	  /**I2C1 GPIO Configuration
	  PB6   ------> I2C1_SCL
	  PB7   ------> I2C1_SDA
	  */
	  GPIO_InitStruct.Pin = LL_GPIO_PIN_6|LL_GPIO_PIN_7;
	  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	  GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	  GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
	  LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /* Peripheral clock enable */
	  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

	  /* USER CODE BEGIN I2C1_Init 1 */

	  /* USER CODE END I2C1_Init 1 */
	  /** I2C Initialization
	  */
	  LL_I2C_DisableOwnAddress2(I2C1);
	  LL_I2C_DisableGeneralCall(I2C1);
	  LL_I2C_EnableClockStretching(I2C1);
	  I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
	  I2C_InitStruct.ClockSpeed = 100000;
	  I2C_InitStruct.DutyCycle = LL_I2C_DUTYCYCLE_2;
	  I2C_InitStruct.OwnAddress1 = 0;
	  I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
	  I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;
	  LL_I2C_Init(I2C1, &I2C_InitStruct);
	  LL_I2C_SetOwnAddress2(I2C1, 0);

	  return I2C1;
}


uint8_t I2C_read(I2C_TypeDef *I2Cx, uint8_t add)
{

}


void I2C_write(I2C_TypeDef *I2Cx, uint8_t add, const char *data)
{
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx));


}
