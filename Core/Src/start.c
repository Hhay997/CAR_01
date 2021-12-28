#include <start.h>
#include "tim.h"

void motor_start(void)
{
	//tt6612芯片使能
	 HAL_GPIO_WritePin(STBY1_GPIO_Port,  STBY1_Pin, 1);
	 HAL_GPIO_WritePin(STBY2_GPIO_Port,  STBY2_Pin, 1);

	 //PWM通道使能
	 HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
	 HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
	 HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
	 HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);

	 //编码器使能
	 HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	 HAL_TIM_Encoder_Start(&htim4,TIM_CHANNEL_ALL);
	 HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	 HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_ALL);

	 //定时器先清零
	 __HAL_TIM_SET_COUNTER(&htim2,0);
	 __HAL_TIM_SET_COUNTER(&htim3,0);
	 __HAL_TIM_SET_COUNTER(&htim4,0);
	 __HAL_TIM_SET_COUNTER(&htim8,0);
}
