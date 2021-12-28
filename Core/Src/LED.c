#include "LED.h"
#include "main.h"
#include "tim.h"
#include "delay.h"
#include "buzzer.h"

int k=0;


void PWM_LED(void)

{
	 __HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,1000);
	/*if(HAL_GPIO_ReadPin(LED_GPIO_Port, LED_Pin)==0)
	//{
	k=600;
		while(k<1000)
		{
			//delay_ms(10);
			k++;
			__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,k);


		}
		k=300;
		/*while(k>0)
		{
			//delay_ms(10);
			__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_2,k);
			k--;


		}
	//}*/
}





