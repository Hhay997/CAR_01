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

#define 	__RF24L01_TX_TEST__							//**@@ 如果测试发�?�功能则�?要定义该宏，如果测试接收则需要屏蔽该�? **@@//
//#define 	__USE_SOFT_SPI_INTERFACE__					//**@@ 如果使用软件SPI则需要定义该宏，反之如果使用硬件SPI则需要屏蔽该�? **@@//


/** 发�?�模式定�? */
enum
{
	TX_MODE_1 = 0,		//发�?�模�?1，发送固定的字符�?
	TX_MODE_2			//发�?�模�?2，发送串口接收到的数�?
};

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
#define SPI2_SCK_Pin GPIO_PIN_3
#define SPI2_SCK_GPIO_Port GPIOE
#define SPI2_NSS_Pin GPIO_PIN_4
#define SPI2_NSS_GPIO_Port GPIOE
#define Echo3_Pin GPIO_PIN_6
#define Echo3_GPIO_Port GPIOF
#define SPI1_CE_Pin GPIO_PIN_7
#define SPI1_CE_GPIO_Port GPIOF
#define SPI1_IRQ_Pin GPIO_PIN_8
#define SPI1_IRQ_GPIO_Port GPIOF
#define I2C3_SDA_Pin GPIO_PIN_9
#define I2C3_SDA_GPIO_Port GPIOF
#define I2C3_SCL_Pin GPIO_PIN_10
#define I2C3_SCL_GPIO_Port GPIOF
#define SPI2_MISO_Pin GPIO_PIN_2
#define SPI2_MISO_GPIO_Port GPIOC
#define SPI1_NSS_Pin GPIO_PIN_4
#define SPI1_NSS_GPIO_Port GPIOA
#define Echo1_Pin GPIO_PIN_4
#define Echo1_GPIO_Port GPIOC
#define Tring1_Pin GPIO_PIN_5
#define Tring1_GPIO_Port GPIOC
#define Echo2_Pin GPIO_PIN_0
#define Echo2_GPIO_Port GPIOB
#define Tring2_Pin GPIO_PIN_1
#define Tring2_GPIO_Port GPIOB
#define Tring3_Pin GPIO_PIN_11
#define Tring3_GPIO_Port GPIOF
#define flame12_Pin GPIO_PIN_7
#define flame12_GPIO_Port GPIOE
#define flame13_Pin GPIO_PIN_8
#define flame13_GPIO_Port GPIOE
#define I2C1_SDA_Pin GPIO_PIN_9
#define I2C1_SDA_GPIO_Port GPIOE
#define flame14_Pin GPIO_PIN_10
#define flame14_GPIO_Port GPIOE
#define flame15_Pin GPIO_PIN_11
#define flame15_GPIO_Port GPIOE
#define Echo4_Pin GPIO_PIN_12
#define Echo4_GPIO_Port GPIOE
#define Tring4_Pin GPIO_PIN_13
#define Tring4_GPIO_Port GPIOE
#define people_Pin GPIO_PIN_14
#define people_GPIO_Port GPIOE
#define buzzer_Pin GPIO_PIN_15
#define buzzer_GPIO_Port GPIOE
#define SPI2_MOSI_Pin GPIO_PIN_10
#define SPI2_MOSI_GPIO_Port GPIOB
#define smok_Pin GPIO_PIN_12
#define smok_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_13
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C2_SCL_Pin GPIO_PIN_14
#define I2C2_SCL_GPIO_Port GPIOB
#define I2C2_SDA_Pin GPIO_PIN_15
#define I2C2_SDA_GPIO_Port GPIOB
#define motor1_Pin GPIO_PIN_14
#define motor1_GPIO_Port GPIOD
#define motor2_Pin GPIO_PIN_15
#define motor2_GPIO_Port GPIOD
#define motor3_Pin GPIO_PIN_7
#define motor3_GPIO_Port GPIOG
#define motor4_Pin GPIO_PIN_8
#define motor4_GPIO_Port GPIOG
#define motor5_Pin GPIO_PIN_8
#define motor5_GPIO_Port GPIOC
#define motor6_Pin GPIO_PIN_9
#define motor6_GPIO_Port GPIOC
#define motor7_Pin GPIO_PIN_8
#define motor7_GPIO_Port GPIOA
#define motor8_Pin GPIO_PIN_9
#define motor8_GPIO_Port GPIOA
#define STBY1_Pin GPIO_PIN_11
#define STBY1_GPIO_Port GPIOA
#define STBY2_Pin GPIO_PIN_12
#define STBY2_GPIO_Port GPIOA
#define flame1_Pin GPIO_PIN_0
#define flame1_GPIO_Port GPIOD
#define flame2_Pin GPIO_PIN_1
#define flame2_GPIO_Port GPIOD
#define flame3_Pin GPIO_PIN_3
#define flame3_GPIO_Port GPIOD
#define flame4_Pin GPIO_PIN_4
#define flame4_GPIO_Port GPIOD
#define flame5_Pin GPIO_PIN_7
#define flame5_GPIO_Port GPIOD
#define LED_Pin GPIO_PIN_10
#define LED_GPIO_Port GPIOG
#define flame8_Pin GPIO_PIN_11
#define flame8_GPIO_Port GPIOG
#define flame9_Pin GPIO_PIN_13
#define flame9_GPIO_Port GPIOG
#define flame11_Pin GPIO_PIN_15
#define flame11_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
