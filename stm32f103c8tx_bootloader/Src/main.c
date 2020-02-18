#include <stdbool.h>
#include "main.h"
#include "flash_handle.h"

#define APPLICATION_ADDRESS_PRO				0x8000000

#define DATA_FILE_RECORD_LEN_POS			0x00
#define DATA_FILE_ADD_POS					0x01
#define DATA_FILE_RECODE_TYPE_POS			0x03
#define DATA_FILE_DATA_POS					0x04

#define RECORD_FILE_DATA 					0x00 //data record
#define RECORD_FILE_END_FILE				0x01 //  end-of-file record
#define RECORD_FILE_EXT_SEG_ADD		 		0x02  // extended segment address record
#define RECORD_FILE_EXT_LIN_ADD				0x04  //  extended linear address record
#define RECORD_FILE_START_LINEAR_ADD		0x05  // start linear address record

typedef void (*pFunction)(void);

/*  Data format of Intel Hex for each line
 *  Start code   Byte count   Address   Record type   Data   Checksum
 *    1 byte(:)     1 byte    2 byte      1 byte     depend   1 byte
 *                                                  on value
 *                                                of Byte count
 * */

typedef struct _raw_data_recieve_
{
	char raw_data_str[52]; //raw data in string type
	uint8_t raw_data_hex[25]; //raw data in hex type
	uint8_t len_raw_data;
	uint8_t crc_val;   //checksum of data
}RAW_DATA_RECIEVE;
/*This is struct to saving data after this is handled*/
typedef struct _data_recieve_complete_
{
	uint32_t address_w; 		//address start for programming
	uint32_t address_last_prog; //this will indicate data of
	uint8_t  data_len;  		//length of data will be written
	uint8_t  data[32*1024];      //data will be written
}DATA_RECIEVE_COMPL;

typedef struct _data_prog_flash
{
	uint32_t start_add_prog; // start add program
	uint8_t	 *data_prog; 	 // data program
	uint16_t data_len;		 // length of program's data
}DATA_PROG_FLASH;
/* USER CODE END Includes */
DATA_RECIEVE_COMPL DATA_FLASH;

uint32_t no_page_data; //number of data's pages
/*true: is accept jump to application
 *false: is not accept*/
bool st_boot;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
/* Exported types ------------------------------------------------------------*/
void UART_Trasnmit_Str(char *str);
/* USER CODE BEGIN ET */
bool checksum_data(RAW_DATA_RECIEVE data);
void jump_to_app(uint32_t add_msp_app);
uint8_t handle_raw_data(RAW_DATA_RECIEVE data_raw_rec, DATA_RECIEVE_COMPL *data);
bool convert_str_hex_raw(RAW_DATA_RECIEVE data);
bool write_data_to_flash(DATA_RECIEVE_COMPL *data);
bool check_all_data(DATA_RECIEVE_COMPL *data);
uint8_t merge_compl_data(DATA_PROG_FLASH *data_prog, DATA_RECIEVE_COMPL *data_compl);
/* USER CODE BEGIN PD */

int boot_main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/*This function is handle jump to application process*/
void jump_to_app(uint32_t add_msp_app)
{
	pFunction appEntry;
	uint32_t main_stack;
	/*Disable all IRQs in system*/
	__disable_irq();

	main_stack = (uint32_t) *((__IO uint32_t*)add_msp_app);
	appEntry   = (pFunction) *(__IO uint32_t*) (add_msp_app + 4);

    SCB->VTOR = add_msp_app;

    /* Set the application stack pointer */
    __set_MSP(main_stack);

    appEntry();

}

/*This function is used to convert data from string to hex file*/
bool convert_str_hex_raw(RAW_DATA_RECIEVE data)
{
	char buff[200];
	uint8_t i;
	i = 0;
	while(data.raw_data_str[i] != 0)
	{
		switch(data.raw_data_str[i])
		{
			case '0':
				buff[i] = 0x00;
				break;
			case '1':
				buff[i] = 0x01;
				break;
			case '2':
				buff[i] = 0x02;
				break;
			case '3':
				buff[i] = 0x03;
				break;
			case '4':
				buff[i] = 0x04;
				break;
			case '5':
				buff[i] = 0x05;
				break;
			case '6':
				buff[i] = 0x06;
				break;
			case '7':
				buff[i] = 0x07;
				break;
			case '8':
				buff[i] = 0x08;
				break;
			case '9':
				buff[i] = 0x09;
				break;
			case 'a':
				buff[i] = 0x0A;
				break;
			case 'A':
				buff[i] = 0x0A;
				break;
			case 'b':
				buff[i] = 0x0B;
				break;
			case 'B':
				buff[i] = 0x0B;
				break;
			case 'c':
				buff[i] = 0x0C;
				break;
			case 'C':
				buff[i] = 0x0C;
				break;
			case 'd':
				buff[i] = 0x0D;
				break;
			case 'D':
				buff[i] = 0x0D;
				break;
			case 'e':
				buff[i] = 0x0E;
				break;
			case 'E':
				buff[i] = 0x0E;
				break;
			case 'f':
				buff[i] = 0x0F;
				break;
			case 'F':
				buff[i] = 0x0F;
				break;
			default:
				return false;
		}
		i++;
	}
	memset(data.raw_data_hex, 0, 25);
	/*check length data is odd or even*/
	if((i % 2) != 0)
	{
		return false;
	}

	i = (i - 1)/2;
	/* Because last data is value of crc and we have another variable for saving this data
	 * So we can remove this data late after handle*/
	data.len_raw_data = i;
	while(i >= 0)
	{
		data.raw_data_hex[i] = ((uint8_t)(buff[i*2] << 4) & 0xF0) | ((uint8_t)(buff[i*2  + 1] << 4) & 0x0F);
		i--;
	}

	data.crc_val = data.raw_data_hex[data.len_raw_data];
	data.raw_data_hex[data.len_raw_data] = 0x00;

	return true;
}

/* This function is used to check crc of data is valid or not
 * Return value:
 *      		- false: the received data is invalid
 *      		- true : the received data is valid
 **/
bool checksum_data(RAW_DATA_RECIEVE data)
{
	uint32_t sum_data;/*Summary of all data in *.hex file except crc value and start code*/
	uint8_t crc;      /*this is crc value, we get from check real data*/
	uint8_t idx;

	sum_data = 0;

	for(idx = 0; idx < data.len_raw_data; idx++)
	{
		sum_data = sum_data + data.raw_data_hex[idx];
	}

	sum_data = ~sum_data;

	crc = ((uint8_t)sum_data) + 0x01;

	if(crc == data.crc_val)
	{
		return true;
	}
	return false;
}

/* This function is used to hanlde raw data to prepare data
* Return value:
*      		- 0 : the received data is invalid
*      		- 1 : the received data is valid
*      		- 2 : the received data is not handled
**/
uint8_t handle_raw_data(RAW_DATA_RECIEVE data_raw_rec, DATA_RECIEVE_COMPL *data)
{
	uint8_t idx;
	data->data_len  = data->data_len + data_raw_rec.raw_data_hex[DATA_FILE_RECORD_LEN_POS];

	data->address_w = ((((uint16_t)data_raw_rec.raw_data_hex[DATA_FILE_ADD_POS]) << 8) & 0xFF00) | \
			(((uint16_t)data_raw_rec.raw_data_hex[DATA_FILE_ADD_POS + 1]) & 0x00FF);

	switch(data_raw_rec.raw_data_hex[DATA_FILE_RECODE_TYPE_POS])
	{
		case RECORD_FILE_DATA:
			for(idx = 0; idx < data->data_len; idx++)
			{
				data->data[idx] = data_raw_rec.raw_data_hex[DATA_FILE_DATA_POS + idx];
			}
			break;

		case RECORD_FILE_END_FILE:
			return 2;
			break;

		case RECORD_FILE_EXT_LIN_ADD:
			return 2;
			break;

		case RECORD_FILE_EXT_SEG_ADD:
			return 2;
			break;

		case RECORD_FILE_START_LINEAR_ADD:
			return 2;
			break;

		default:
			return 0;
			break;
	}
	return 1;
}

bool write_data_to_flash(DATA_RECIEVE_COMPL *data)
{
//	uint8_t i;
//	FLASH_PageErase(data->address_w);
//	HAL_FLASHEx_Erase()

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
