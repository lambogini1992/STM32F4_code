#include <stdint.h>
#include <string.h>
#include "main.h"

#define FLASH_ADDRESS_DATA 				0x8009000
#define FLASH_OFFSET_ADD_DATA			4

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t FLASH_saving_1byte_data(uint32_t add, uint8_t *data, uint16_t data_len)
{
	uint32_t *data_prog;
	uint16_t data_prog_len;
	uint16_t n_page;
	FLASH_EraseInitTypeDef FErase;
	uint32_t pageError;
	uint16_t idx;
	uint8_t status_prog;
	uint8_t error_prog;


	data_prog_len = data_len/4;
	if((data_len%4) != 0)
	{
		data_prog_len = data_prog_len + 1;
	}

	n_page = (data_len/FLASH_PAGE_SIZE);
	if((data_len % FLASH_PAGE_SIZE) != 0)
	{
		n_page = n_page + 1;
	}

	data_prog = (uint32_t *)malloc(data_prog_len * 4);

	memset(data_prog, 0xFFFFFFFF, data_prog_len);
	strcpy((char *)data_prog, (char *)data);

	while(HAL_OK != HAL_FLASH_Unlock());

	while(HAL_OK != HAL_FLASH_OB_Unlock());

	FErase.TypeErase 	= FLASH_TYPEERASE_PAGES;
	FErase.PageAddress 	= FLASH_ADDRESS_DATA;
	FErase.NbPages		= n_page;

	if(HAL_OK == HAL_FLASHEx_Erase(&FErase, &pageError))
	{
		error_prog = 0;
		idx = 0;
		while(idx < data_prog_len)
		{
			status_prog = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, FLASH_ADDRESS_DATA + (FLASH_OFFSET_ADD_DATA * idx), data_prog[idx]);
			if(status_prog == HAL_OK)
			{
				idx++;
				error_prog = 0;
			}
			else
			{
				error_prog++;
				if(error_prog == 5)
				{
					return 2;
				}
			}
		}
	}
	else
	{
		return 0;
	}

	while(HAL_OK != HAL_FLASH_OB_Lock());

	while(HAL_OK != HAL_FLASH_Lock());

	free(data_prog);
	return 1;
}

uint8_t FLASH_saving_2byte_data(uint32_t add, uint16_t *data, uint16_t data_len)
{
	uint16_t *data_prog;
	uint16_t data_prog_len;
	uint8_t n_page;
	FLASH_EraseInitTypeDef FErase;
	uint32_t pageError;
	uint16_t idx;
	uint8_t status_prog;
	uint8_t error_prog;


	data_prog_len = data_len/2;
	if((data_len % 2) != 0)
	{
		data_prog_len = data_prog_len + 1;
	}

	n_page = (uint8_t)(data_len/FLASH_PAGE_SIZE);
	if((data_len % FLASH_PAGE_SIZE) != 0)
	{
		n_page = n_page + 1;
	}

	data_prog = (uint16_t *)malloc(data_prog_len * 2);

	memset(data_prog, 0xFFFFFFFF, data_prog_len);
	strcpy((char *)data_prog, (char *)data);

	while(HAL_OK != HAL_FLASH_Unlock());

	while(HAL_OK != HAL_FLASH_OB_Unlock());

	FErase.TypeErase 	= FLASH_TYPEERASE_PAGES;
	FErase.PageAddress 	= add;
	FErase.NbPages		= n_page;

	if(HAL_OK == HAL_FLASHEx_Erase(&FErase, &pageError))
	{
		error_prog = 0;
		idx = 0;
		while(idx < data_prog_len)
		{
			status_prog = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, add + (FLASH_OFFSET_ADD_DATA * idx), (uint64_t)data_prog[idx]);
			if(status_prog == HAL_OK)
			{
				idx++;
				error_prog = 0;
			}
			else
			{
				error_prog++;
				if(error_prog == 5)
				{
					return 2;
				}
			}
		}
	}
	else
	{
		return 0;
	}

	while(HAL_OK != HAL_FLASH_OB_Lock());

	while(HAL_OK != HAL_FLASH_Lock());

	free(data_prog);
	return 1;
}

uint8_t FLASH_saving_4byte_data(uint32_t add, uint32_t *data, uint16_t data_len)
{
	uint8_t n_page;
	FLASH_EraseInitTypeDef FErase;
	uint32_t pageError;
	uint16_t idx;
	uint8_t status_prog;
	uint8_t error_prog;

	n_page = (uint8_t)(data_len/FLASH_PAGE_SIZE);
	if((data_len % FLASH_PAGE_SIZE) != 0)
	{
		n_page = n_page + 1;
	}

	while(HAL_OK != HAL_FLASH_Unlock());

	while(HAL_OK != HAL_FLASH_OB_Unlock());

	FErase.TypeErase 	= FLASH_TYPEERASE_PAGES;
	FErase.PageAddress 	= add;
	FErase.NbPages		= n_page;

	if(HAL_OK == HAL_FLASHEx_Erase(&FErase, &pageError))
	{
		error_prog = 0;
		idx = 0;
		while(idx < data_len)
		{
			status_prog = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, add + (FLASH_OFFSET_ADD_DATA * idx), (uint64_t)data[idx]);
			if(status_prog == HAL_OK)
			{
				idx++;
				error_prog = 0;
			}
			else
			{
				error_prog++;
				if(error_prog == 5)
				{
					return 2;
				}
			}
		}
	}
	else
	{
		return 0;
	}

	while(HAL_OK != HAL_FLASH_OB_Lock());

	while(HAL_OK != HAL_FLASH_Lock());

	return 1;
}


uint32_t FLASH_read_data(uint32_t add)
{
	volatile uint32_t read_data;

	read_data = *(uint32_t *)add;

	return read_data;
}
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/
  uint8_t write_data = 0;
  uint32_t read_data = 0;
  uint8_t write_status;
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();



  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE BEGIN Init */
//  read_data = FLASH_read_data(FLASH_ADDRESS_DATA);
  read_data = FLASH_read_data(FLASH_ADDRESS_DATA);
  if(read_data == 0xFFFFFFFF)
  {
	  read_data = 0;
  }
  write_data = read_data + 1;

  write_status = FLASH_saving_1byte_data(FLASH_ADDRESS_DATA, &write_data, 1);
  if(write_status == 0)
  {
  	write_data = 7;
  }


  /* USER CODE END Init */
  /* USER CODE END 2 */
  if(write_status == 2)
  {
  	write_data = 10;
	while(write_data != 0)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(100);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(100);
		write_data--;
	}
	return 0;	
  }
  while(write_data != 0)
  {
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  HAL_Delay(1000);
	  HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
	  HAL_Delay(1000);
	  write_data--;
  }

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  return 0;
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
