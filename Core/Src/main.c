/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BMI055.h"
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t uart_buf[256];
int16_t gyro[3];
int16_t accel[3];
float *temp;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
  BMI_acc_int_callback(GPIO_Pin);
}
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

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  if(BMI_init())
  {
    sprintf(&uart_buf, "BMI Error: %d\n", BMI_get_error());
    HAL_UART_Transmit(&huart1, uart_buf, strlen(uart_buf), 100);
    while(1){}
  }

  // set resolution
  BMI_set_acc_range(A_RANGE_2G);
  BMI_set_gyr_range(G_RANGE_125DPS);

  // set filter
  // BMI_set_acc_bw(A_BANDWITH_1000Hz);
  // BMI_set_gyr_bw(G_BANDWIDTH_116Hz);

  // enable int on motion
  BMI_ACC_Interrupt_En acc_int_ens;
  acc_int_ens.slope_en_z = 1;

  A_INT_Latch acc_int_latch = A_INT_LATCH_latched;
  
  BMI_ACC_Interrupt_Map acc_int_map;
  acc_int_map.int1_slope = 1;

  BMI_ACC_Interrupt_Out_Ctrl acc_int_out_ctrl;
  acc_int_out_ctrl.int1_odd = 0; // 0 - push-pull
  acc_int_out_ctrl.int1_lvl = 1; // 1 - active high

  BMI_acc_int_set_out_ctrl(acc_int_out_ctrl);
  BMI_acc_int_set_map(acc_int_map);
  BMI_acc_int_set_latch(acc_int_latch);
  BMI_acc_int_set_en(acc_int_ens);

  BMI_ACC_Int_status acc_int_status = {0};

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if (BMI_acc_int_get_state() == BMI_INT_1) {
      float acc_m[3], gyro_dps[3];
      
      BMI_get_raw_acc(accel);
      BMI_get_raw_gyr(gyro);

      acc_int_status = BMI_acc_int_get_statuses();
  
      BMI_acc_to_metric(accel, acc_m);
      BMI_gyr_to_dps(gyro, gyro_dps);
  
      sprintf(uart_buf, "STATUS: %X ACC: %f %f %f GYRO: %f %f %f\n", 
        (acc_int_status.b_0 << 24) | (acc_int_status.b_1 << 16) | (acc_int_status.b_2 << 8) | (acc_int_status.b_3),
        acc_m[0], acc_m[1], acc_m[2],
        gyro_dps[0], gyro_dps[1], gyro_dps[2]
      );
      
      HAL_UART_Transmit(&huart1, uart_buf, strlen(uart_buf), 100);
  
      BMI_acc_int_latch_clear();
      BMI_acc_int_reset_state();
      HAL_Delay(50);
    }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
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

  /** Initializes the CPU, AHB and APB buses clocks
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
