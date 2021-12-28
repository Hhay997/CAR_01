/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "delay.h"
#include "start.h"
#include "math.h"
#include "motor_l1.h"
#include "motor_l2.h"
#include "motor_r1.h"
#include "motor_r2.h"
#include "communication.h"
#include "ultrasonic.h"
#include "people.h"
#include "flame.h"
#include "smok.h"
#include "buzzer.h"
#include "mbotLinuxUsart.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

float leftvollinearvelocity_pre=0;
float rightvollinearvelocity_pre=0;
int leftvollinearvelocity_set=0;
int rightvollinearvelocity_set=0;
unsigned char p_crtlFlag=0;

float setpoint[4]={0};
unsigned char date[30];
int motor=0;
int ultrasonic=0;
int sensor=0;
int send=0;
int receive=0;
int spi=0;
unsigned char date_t[8]={0x56,0xaa,0,0,0,0,0,0};

//测试发�?�变�????????????
short testSend1   =5000;
short testSend2   =2000;
short testSend3   =1000;
unsigned char testSend4 = 0x05;

//测试接收变量
int testRece1     =0;
int testRece2     =0;
unsigned char testRece3 = 0x00;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_TIM9_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_TIM6_Init();
  MX_SPI1_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM1_Init();
  MX_TIM7_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */

  /*
  //====================================串口中断服务程序=================================================
  void HAL_UART_RxCpltCallback()
  {
  	if(HAL_UART_GetState(&huart2) == HAL_UART_STATE_BUSY_RX)
   	 {
  		// USART_ClearITPendingBit(USART1,USART_IT_RXNE);//首先清除中断标志�????????????
  		 //从ROS接收到的数据，存放到下面三个变量�????????????
  		 usartReceiveOneData(&testRece1,&testRece2,&testRece3);
  	 }
  }
  __HAL_UART_ENABLE_IT(&huart2, UART_IT_ERR);

*/
//int rx_buffer[]={0};
//HAL_UART_Receive_DMA(&huart2,rx_buffer,11);
 //  电机控制程序
 //PWM，编码器，芯片使�????????????????????????????????????????????
  motor_start();

   //读取给定速度并转�????????????????????????????????????????????
  //readsetpoint(0.1,0,setpoint);
   __HAL_SPI_ENABLE(&hspi1);
	HAL_GPIO_WritePin(SPI1_CE_GPIO_Port,SPI1_CE_Pin,1);
//打开定时器中
  HAL_TIM_Base_Start_IT(&htim1);


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
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim==&htim1)//判断是否威定时器7中断
	{
		motor++;
		ultrasonic++;
		sensor++;
		send++;
		receive++;
	if(motor==200)
		{
	//	leftvollinearvelocity_set=200;
		//rightvollinearvelocity_set=200;
		float v[4]={0};//小车实际线�?�度清零
		float angular[4]={0};//计算小车转动角度清零
		//控制小车前进或后�???????????????????????????????????????????
		// readsetpoint(leftvollinearvelocity_,rightvollinearvelocity_set,setpoint);
	    go_or_back_L_1((float)leftvollinearvelocity_set);
		go_or_back_L_2((float)leftvollinearvelocity_set);
		go_or_back_R_1((float)rightvollinearvelocity_set);
		go_or_back_R_2((float)rightvollinearvelocity_set);
		//测出小车行驶速度
		v[0]= contol_L_1((float)leftvollinearvelocity_set,(float)rightvollinearvelocity_set,angular);
		v[1]= contol_L_2((float)leftvollinearvelocity_set,(float)rightvollinearvelocity_set,angular);
		v[2]= contol_R_1((float)rightvollinearvelocity_set,(float)leftvollinearvelocity_set,angular);
		v[3]= contol_R_2((float)rightvollinearvelocity_set,(float)leftvollinearvelocity_set,angular);
		date[12]=(v[0]+v[1]+v[2]+v[3])/4*1000;//计算小车4个轮子平均�?�度
		date[13]=(angular[0]+angular[1]+angular[2]+angular[3])/4*1000;//计算小车4个轮子平均转角度
		leftvollinearvelocity_pre=(v[1]+v[1])/2*1000;
		rightvollinearvelocity_pre=(v[2]+v[3])/2*1000;
		motor=0;
		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,20);//通过pwm控制电机速度
		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,20);//通过pwm控制电机速度
		__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,20);//通过pwm控制电机速度
		__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_2,20);//通过pwm控制电机速度
		date_t[7]=(leftvollinearvelocity_pre+rightvollinearvelocity_pre)/2;

		}
		/*if(ultrasonic==300)
			{
			float t1,t2,t3,t4=0;
			HAL_TIM_Encoder_Stop(&htim3,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Stop(&htim4,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Stop(&htim2,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Stop(&htim8,TIM_CHANNEL_ALL);
			HAL_TIM_Base_Start(&htim7);//启动定时�????????????????????7
			htim7.Instance->CNT = 0;//定时�????????????????????6计数器清0
			Ultrasonic1(date);
			 t1=htim7.Instance->CNT;
			//Ultrasonic2(date);
			 t2=htim7.Instance->CNT;
			Ultrasonic3(date);
			 t3=htim7.Instance->CNT;
			Ultrasonic4(date);
			ultrasonic=0;
			 t4=htim7.Instance->CNT;
			 date[7]=date[7]-(t4-t1)*0.0001*date[12];
			 date[8]=date[8]-(t4-t2)*0.0001*date[12];
			 date[9]=date[9]-(t4-t3)*0.0001*date[12];
			 HAL_TIM_Base_Stop(&htim7);//启动定时�????????????????????7
			 if(date[7]<20||date[8]<20||date[9]<20||date[10]<20)
			{
				HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, 1);
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
			}
			else
			{
				HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, 0);
				HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
			}
			HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
			 HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_ALL);
			}*/
		if (sensor==1000)
		{
			HAL_TIM_Encoder_Stop(&htim3,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Stop(&htim4,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Stop(&htim2,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Stop(&htim8,TIM_CHANNEL_ALL);
			SMOK_PUT(date);
			FLAME_A_PUT(date);
			FLAME_B_PUT(date);
			FLAME_C_PUT(date);
			PEOPLE_PUT(date);
			date_t[2]=date[1];
			date_t[3]=date[2];
			date_t[4]=date[3];
			date_t[5]=date[4];
			 if(date[1]||date[2]||date[3]||date[4]==1)
				{
					HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, 1);
					HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);
				}
			else
				{
					HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, 0);
					HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
				}
			sensor=0;
		HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
		HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
		HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
		HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_ALL);
	}
		if (send==100)
	{
			HAL_TIM_Encoder_Stop(&htim3,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Stop(&htim4,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Stop(&htim2,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Stop(&htim8,TIM_CHANNEL_ALL);
			usartSendData(leftvollinearvelocity_pre,rightvollinearvelocity_pre,0,0);
			USART_Send_String(date_t,8);
			HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
			HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_ALL);
			send=0;
	}

	if (receive==50)
			{
					HAL_TIM_Encoder_Stop(&htim3,TIM_CHANNEL_ALL);
					HAL_TIM_Encoder_Stop(&htim4,TIM_CHANNEL_ALL);
					HAL_TIM_Encoder_Stop(&htim2,TIM_CHANNEL_ALL);
					HAL_TIM_Encoder_Stop(&htim8,TIM_CHANNEL_ALL);
					//HAL_UART_DMAResume(&huart2);
					usartReceiveOneData(&leftvollinearvelocity_set,&rightvollinearvelocity_set,&p_crtlFlag);
					//HAL_UART_DMAPause(&huart2);
					HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
					HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
					HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
					HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_ALL);
					receive=0;
			}
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
