/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define I2S_LRCLK_Pin       GPIO_PIN_12
#define I2S_LRCLK_GPIO_Port GPIOB
#define I2S_SCK_Pin         GPIO_PIN_13
#define I2S_SCK_GPIO_Port   GPIOB
#define I2S_SDIN_Pin        GPIO_PIN_14
#define I2S_SDIN_GPIO_Port  GPIOB
#define I2S_SDOUT_Pin       GPIO_PIN_15
#define I2S_SDOUT_GPIO_Port GPIOB
#define I2S_MCK_Pin         GPIO_PIN_6
#define I2S_MCK_GPIO_Port   GPIOC
#define I2S_EN_Pin          GPIO_PIN_2
#define I2S_EN_GPIO_Port    GPIOD
#define SPI_SCK_Pin         GPIO_PIN_10
#define SPI_SCK_GPIO_Port   GPIOC
#define SPI_MISO_Pin        GPIO_PIN_11
#define SPI_MISO_GPIO_Port  GPIOC
#define SPI_MOSI_Pin        GPIO_PIN_12
#define SPI_MOSI_GPIO_Port  GPIOC
#define SPI_CS_Pin          GPIO_PIN_12
#define SPI_CS_GPIO_Port    GPIOG
#define FIR_LOAD_Pin        GPIO_PIN_4
#define FIR_LOAD_GPIO_Port  GPIOA
#define FIR_SCK_Pin         GPIO_PIN_5
#define FIR_SCK_GPIO_Port   GPIOA
#define FIR_DO_Pin          GPIO_PIN_7
#define FIR_DO_GPIO_Port    GPIOA
#define ENC_INT_Pin         GPIO_PIN_0
#define ENC_INT_GPIO_Port   GPIOA
#define ENC_INT_EXTI_IRQn   EXTI0_IRQn
#define ENC_SENSE_Pin       GPIO_PIN_1
#define ENC_SENSE_GPIO_Port GPIOA
#define ENC_BTN_Pin         GPIO_PIN_2
#define ENC_BTN_GPIO_Port   GPIOA
#define FPGA_READY_Pin      GPIO_PIN_6
#define FPGA_READY_GPIO_Port GPIOA
#define STATE_LED_Pin       GPIO_PIN_6
#define STATE_LED_GPIO_Port GPIOF
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
