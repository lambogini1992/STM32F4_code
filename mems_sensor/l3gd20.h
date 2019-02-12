/*
 * l3gd20.h
 *
 *  Created on: Feb 9, 2019
 *      Author: AnhPT26
 */

#ifndef INC_L3GD20_H_
#define INC_L3GD20_H_


/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup STM32F4xx_Libraries
 * @{
 */

/**
 * @defgroup L3GD20
 * @brief    L3GD20 library for STM32F4xx devices - http://stm32f4-discovery.com/2014/08/library-28-l3gd20-3-axis-gyroscope
 * @{
 *
 * L3GD20 3-axis Gyroscope is connected on STM32F429 Discovery board.
 * It works with SPI, has 3 selectable resolutions.
 *
 * \par Default pinout
 *
@verbatim
L3GD20			STM32F4			Description

MOSI			PF9				SPI5 is used by default
MISO			PF8				SPI5 is used by default
SCK				PF7				SPI5 is used by default
CS				PC1				Chip select for SPI
@endverbatim
 *
 * If you want to change SPI, use these two lines below in your defines.h file and edit them:
 *
@verbatim
//Select custom SPI for sensor
#define L3GD20_SPI					SPI5
#define L3GD20_SPI_PINSPACK			SPI_PinsPack_1
@endverbatim
 *
 * If you want to change CS pin, add these lines below in defines.h file and edit them:
 *
@verbatim
//Select CS pin
#define L3GD20_CS_PORT				GPIOC
#define L3GD20_CS_PIN				GPIO_Pin_1
@endverbatim
 *
 * \par Changelog
 *
@verbatim
 Version 1.1
  - March 19, 2015
  - Added support for new GPIO library

 Version 1.0
  - First release
@endverbatim
 *
 * \par Dependencies
 *
@verbatim
 - STM32F4xx
 - STM32F4xx RCC
 - STM32F4xx GPIO
 - defines.h
 - TM SPI
 - TM GPIO
@endverbatim
 */
#include "stm32f4xx_hal.h"

/* Pin macros */
#define L3GD20_ENABLE				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET)
#define L3GD20_DISABLE				HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET)

/* Identification number */
#define L3GD20_WHO_AM_I				0xD4

/* Registers addresses */
#define L3GD20_REG_WHO_AM_I			0x0F
#define L3GD20_REG_CTRL_REG1		0x20
#define L3GD20_REG_CTRL_REG2		0x21
#define L3GD20_REG_CTRL_REG3		0x22
#define L3GD20_REG_CTRL_REG4		0x23
#define L3GD20_REG_CTRL_REG5		0x24
#define L3GD20_REG_REFERENCE		0x25
#define L3GD20_REG_OUT_TEMP			0x26
#define L3GD20_REG_STATUS_REG		0x27
#define L3GD20_REG_OUT_X_L			0x28
#define L3GD20_REG_OUT_X_H			0x29
#define L3GD20_REG_OUT_Y_L			0x2A
#define L3GD20_REG_OUT_Y_H			0x2B
#define L3GD20_REG_OUT_Z_L			0x2C
#define L3GD20_REG_OUT_Z_H			0x2D
#define L3GD20_REG_FIFO_CTRL_REG	0x2E
#define L3GD20_REG_FIFO_SRC_REG		0x2F
#define L3GD20_REG_INT1_CFG			0x30
#define L3GD20_REG_INT1_SRC			0x31
#define L3GD20_REG_INT1_TSH_XH		0x32
#define L3GD20_REG_INT1_TSH_XL		0x33
#define L3GD20_REG_INT1_TSH_YH		0x34
#define L3GD20_REG_INT1_TSH_YL		0x35
#define L3GD20_REG_INT1_TSH_ZH		0x36
#define L3GD20_REG_INT1_TSH_ZL		0x37
#define L3GD20_REG_INT1_DURATION	0x38

/* Sensitivity factors, datasheet pg. 9 */
#define L3GD20_SENSITIVITY_250		8.75	/* 8.75 mdps/digit */
#define L3GD20_SENSITIVITY_500		17.5	/* 17.5 mdps/digit */
#define L3GD20_SENSITIVITY_2000		70		/* 70 mdps/digit */

#define L3GD20_SCALE_250            0x00    /*!< Set full scale to 250 mdps */
#define L3GD20_SCALE_500            0x10    /*!< Set full scale to 500 mdps */
#define L3GD20_SCALE_2000           0x20    /*!< Set full scale to 2000 mdps */
/**
 * @}
 */

/**
 * @defgroup L3GD20_Typedefs
 * @brief    Library Typedefs
 * @{
 */

/**
 * @brief  L3GD20 main working structure
 */
typedef struct {
	int16_t X_data; /*!< X axis rotation */
	int16_t Y_data; /*!< Y axis rotation */
	int16_t Z_data; /*!< Z axis rotation */
} L3GD20_data_out;

/**
 * @brief  L3GD20 Result enumerations
 */
typedef enum {
	L3GD20_Result_Ok,   /*!< Everything OK */
	L3GD20_Result_Error /*!< Error occurred */
} L3GD20_Result_t;



/**
 * @}
 */

/**
 * @defgroup L3GD20_Functions
 * @brief    Library Functions
 * @{
 */

/**
 * @brief  Initializes L3GD20 sensor
 * @param  scale: L3GD20 scale selection. This parameter can be a value of @ref L3GD20_Scale_t enumeration
 * @retval Sensor status:
 *            - L3GD20_Result_Ok: Sensor detected
 *            - L3GD20_Result_Error: Sensor not detected
 */
L3GD20_Result_t L3GD20_Init(SPI_HandleTypeDef *hspi, int8_t scale);

/**
 * @brief  Reads rotation data from sensor
 * @param  *L3DG20_Data: Pointer to working @ef L3GD20_t structure
 * @retval Read status: L3GD20_Result_Ok
 */
L3GD20_Result_t L3GD20_Read(L3GD20_data_out* L3DG20_Data);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/* C++ detection */
#ifdef __cplusplus
}
#endif



#endif /* INC_L3GD20_H_ */
