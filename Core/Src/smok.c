#include <smok.h>

void SMOK_PUT (unsigned char *date)
{
	if  (HAL_GPIO_ReadPin(smok_GPIO_Port,smok_Pin)==0)
		    {
				date[4]=0x01;
		    }
	else
	 	 	 {
				date[4]=0x00;
	 	 	 }
}
