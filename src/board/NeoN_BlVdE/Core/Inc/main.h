/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

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
#define LSM_CS_Pin GPIO_PIN_13
#define LSM_CS_GPIO_Port GPIOC
#define MOTOR_Pin GPIO_PIN_14
#define MOTOR_GPIO_Port GPIOC
#define STATE_Pin GPIO_PIN_15
#define STATE_GPIO_Port GPIOC
#define TDC_INT_Pin GPIO_PIN_0
#define TDC_INT_GPIO_Port GPIOH
#define TDC_SHIM_Pin GPIO_PIN_2
#define TDC_SHIM_GPIO_Port GPIOA
#define DPA_TDC_Pin GPIO_PIN_3
#define DPA_TDC_GPIO_Port GPIOA
#define LIS_CS_Pin GPIO_PIN_4
#define LIS_CS_GPIO_Port GPIOA
#define NRF_CE_Pin GPIO_PIN_1
#define NRF_CE_GPIO_Port GPIOB
#define NRF_CS_Pin GPIO_PIN_2
#define NRF_CS_GPIO_Port GPIOB
#define CS_TDC_Pin GPIO_PIN_10
#define CS_TDC_GPIO_Port GPIOB
#define PEREGIGATEL_Pin GPIO_PIN_12
#define PEREGIGATEL_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_14
#define LED_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_8
#define BUZZER_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
