/*
	原版：阎宇威
	修改：贺海育
*/

#include <people.h>

void PEOPLE_PUT(unsigned char *data)
{
	if  (HAL_GPIO_ReadPin(people_GPIO_Port,people_Pin)==1)
		   {
				data[5]=0x01;
		   }
	else
	 	  {
	 		  data[5]=0x00;
	 	  }
}
