/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "routines.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef enum {
	INIT,
	IDLE,
	BTN,
	PRINT
} program_mode_t;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
stmdev_ctx_t mag_ctx;
program_mode_t program_mode = INIT;
uint32_t program_mode_time;
uint32_t button_time;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// overwrite _write so that printf sends to SWO
int _write(int file, char* ptr, int len)
{
	for (int i = 0; i < len; i++)
	{
		ITM_SendChar(ptr[i]);
	}
	return len;
}

uint16_t idle_led = LED_ORANGE;
uint16_t btn_led = LED_RED;
uint16_t print_led = LED_BLUE;

int32_t flash_led(void* self)
{
	bad_task_t* bt = (bad_task_t*) self;

//	printf("Flashing LED\n");
	HAL_GPIO_TogglePin(LED_BANK, *( (uint16_t*) (bt->data) ));

	return 0;
}

int32_t print_mag(void* self)
{
	return print_mag_rt(&mag_ctx);
}

int32_t end_print_mag(void* self)
{
	uint32_t cur = SCHED_TIMER_GET(&htim5);
	if (cur - program_mode_time > 20*1000*1000U)
	{
		printf("# END MAG");
		program_mode = IDLE;
		program_mode_time = cur;
	}
	return 0;
}

bad_task_t idle_tasks[] = {
	{.task = flash_led, .data = &idle_led, .timer = &htim5, .period = 250*1000U, .last = 0U}
};

bad_task_t btn_tasks[] = {
	{.task = flash_led, .data = &btn_led, .timer = &htim5, .period = 250*1000U, .last = 0U}
};

bad_task_t print_tasks[] = {
	{.task = flash_led, .data = &print_led, .timer = &htim5, .period = 100000U, .last = 0U},
	{.task = print_mag, .data = NULL, .timer = &htim5, .period = 70000U, .last = 0U},
	{.task = end_print_mag, .data = NULL, .timer = &htim5, .period = 200000U, .last = 0U}
};
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  program_mode = IDLE;
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  MX_TIM5_Init();
  /* USER CODE BEGIN 2 */

  init_mag(&mag_ctx, &hi2c1);
  printf("\nInitalized magnetometer\n");
  HAL_TIM_Base_Start(&htim5);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */
	switch(program_mode)
	{
	  case (INIT):
		program_mode = IDLE;
		break;
	  case (IDLE):
		RUN_TASKS(idle_tasks);
//	    run_tasks(idle_tasks, sizeof(idle_tasks) / sizeof(bad_task_t));
	    break;
	  case (BTN):
	    RUN_TASKS(btn_tasks);
	  	break;
	  case (PRINT):
	    RUN_TASKS(print_tasks);
	    break;
	}
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void handle_button(void)
{
	uint32_t cur = __HAL_TIM_GET_COUNTER(&htim5);
	GPIO_PinState button_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	if (button_state == GPIO_PIN_SET && program_mode == IDLE)
	{
		program_mode = BTN;
		button_time = cur;
		program_mode_time = cur;
	}
	else if (button_state == GPIO_PIN_RESET && program_mode == BTN)
	{
		uint32_t elapsed = cur - button_time;
		uint32_t sec = 1000000;
		if (elapsed > 2 * sec)
		{
			printf("# START MAG\nt,x,y,z\n");

			program_mode = PRINT;
			program_mode_time = cur;
		}
		else
		{
			program_mode = IDLE;
			program_mode_time = cur;
		}
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
//	printf("EXTI %u\n", GPIO_Pin);
	switch(GPIO_Pin)
	{
		case(1):
			handle_button();
			break;
		default:
			printf("# Pin %u ISR not defined\n", GPIO_Pin);
			break;
	}
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
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
