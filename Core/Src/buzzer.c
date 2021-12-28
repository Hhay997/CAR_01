#include "buzzer.h"
#include "main.h"
#include "delay.h"

void BUZZER(unsigned char  *data)
{

	for(int i=1;i<5;i++)
	{

		if(data[i]==1)
		{
			HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, 1);
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 1);

		}
		else if(HAL_GPIO_ReadPin(buzzer_GPIO_Port, buzzer_Pin)==1)
			{
			delay_ms(500);
			HAL_GPIO_WritePin(buzzer_GPIO_Port, buzzer_Pin, 0);
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, 0);
			}
	}

}
