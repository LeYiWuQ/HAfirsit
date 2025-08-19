/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define DHT11_Pin GPIO_PIN_0
#define DHT11_GPIO_Port GPIOA
#define MQ2_Pin GPIO_PIN_1
#define MQ2_GPIO_Port GPIOA
#define RC522_RESET_Pin GPIO_PIN_0
#define RC522_RESET_GPIO_Port GPIOB
#define Temp_Pin GPIO_PIN_1
#define Temp_GPIO_Port GPIOB
#define STR2_Pin GPIO_PIN_11
#define STR2_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_12
#define KEY1_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_13
#define KEY2_GPIO_Port GPIOB
#define KEY3_Pin GPIO_PIN_14
#define KEY3_GPIO_Port GPIOB
#define KEY4_Pin GPIO_PIN_15
#define KEY4_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_8
#define LED_GPIO_Port GPIOA
#define Fire_Pin GPIO_PIN_15
#define Fire_GPIO_Port GPIOA
#define STR1_Pin GPIO_PIN_4
#define STR1_GPIO_Port GPIOB
#define BEEP_Pin GPIO_PIN_5
#define BEEP_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define beep_on()  HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
#define beep_off() HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
#define Fire_get() HAL_GPIO_ReadPin(Fire_GPIO_Port,Fire_Pin)		//
#define LED_on()   HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
#define LED_off()   HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
