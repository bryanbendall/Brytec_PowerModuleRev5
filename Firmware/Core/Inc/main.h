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
#include "stm32g4xx_hal.h"

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
#define CanSilent_Pin GPIO_PIN_13
#define CanSilent_GPIO_Port GPIOC
#define NRST_Pin GPIO_PIN_10
#define NRST_GPIO_Port GPIOG
#define Is9_10_Pin GPIO_PIN_0
#define Is9_10_GPIO_Port GPIOA
#define Is4_Pin GPIO_PIN_1
#define Is4_GPIO_Port GPIOA
#define Is3_Pin GPIO_PIN_2
#define Is3_GPIO_Port GPIOA
#define Is6_Pin GPIO_PIN_3
#define Is6_GPIO_Port GPIOA
#define Memory_Hold_Pin GPIO_PIN_4
#define Memory_Hold_GPIO_Port GPIOA
#define Memory_SS_Pin GPIO_PIN_4
#define Memory_SS_GPIO_Port GPIOC
#define Memory_Wp_Pin GPIO_PIN_0
#define Memory_Wp_GPIO_Port GPIOB
#define Is7_8_Pin GPIO_PIN_1
#define Is7_8_GPIO_Port GPIOB
#define PowerSwitchStatus_Pin GPIO_PIN_2
#define PowerSwitchStatus_GPIO_Port GPIOB
#define User_Led_Pin GPIO_PIN_10
#define User_Led_GPIO_Port GPIOB
#define Is2_Pin GPIO_PIN_11
#define Is2_GPIO_Port GPIOB
#define Is5_Pin GPIO_PIN_12
#define Is5_GPIO_Port GPIOB
#define Is1_Pin GPIO_PIN_14
#define Is1_GPIO_Port GPIOB
#define Den2_Pin GPIO_PIN_15
#define Den2_GPIO_Port GPIOB
#define Dsel7_8_Pin GPIO_PIN_6
#define Dsel7_8_GPIO_Port GPIOC
#define Den7_8_Pin GPIO_PIN_10
#define Den7_8_GPIO_Port GPIOA
#define Den5_Pin GPIO_PIN_15
#define Den5_GPIO_Port GPIOA
#define SPI_SS_L9966_Pin GPIO_PIN_10
#define SPI_SS_L9966_GPIO_Port GPIOC
#define L9966_Rst_Pin GPIO_PIN_11
#define L9966_Rst_GPIO_Port GPIOC
#define L9966_Int_Pin GPIO_PIN_4
#define L9966_Int_GPIO_Port GPIOB
#define L9966_Sync_Pin GPIO_PIN_7
#define L9966_Sync_GPIO_Port GPIOB
#define BOOT_0_Pin GPIO_PIN_8
#define BOOT_0_GPIO_Port GPIOB
#define Pwm_Ctr_Enable_Pin GPIO_PIN_9
#define Pwm_Ctr_Enable_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
