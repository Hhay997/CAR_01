#include "main.h"
#include "flame.h"

void FLAME_A_PUT (unsigned char *date)
{
	int i[5]={0};
 if  (HAL_GPIO_ReadPin(flame1_GPIO_Port,flame1_Pin )==1)
	   {
	 	 	 i[0]=0x01;
	   }
 	 else
 	 	 {
 		 	 i[0]=0x00;
 	 	 }
 if  (HAL_GPIO_ReadPin(flame2_GPIO_Port,flame2_Pin)==1)
	    {
	 	 	 i[1]=0x01;
	    }
 	 else
  	 	 {
 		 	 i[1]=0x00;
  	 	 }
if  (HAL_GPIO_ReadPin(flame3_GPIO_Port,flame3_Pin)==1)
	    {
			 i[2]=0x01;
	    }
else
 	 	 {
			i[2]=0x00;
 	 	 }
if  (HAL_GPIO_ReadPin(flame4_GPIO_Port,flame4_Pin)==1)
	    {
			 i[3]=0x01;

	    }
else
 	 	 {
			i[3]=0x00;
 	 	 }
if  (HAL_GPIO_ReadPin(flame5_GPIO_Port,flame5_Pin)==1)
	    {
	 	 	 i[4]=0x01;

	    }
else
 	 	 {
			i[4]=0x00;
 	 	 }
for(int j=0;j<5;j++)
{
	if (i[j]==1)
		{
			date[1]=1;
			break;
		}
		else if (i[j]==0)
		{
			date[1]=0;
		}
}
}


void FLAME_B_PUT (unsigned char *date)
{
	int i[5]={0};
 /*if  (HAL_GPIO_ReadPin(flame6_GPIO_Port,flame6_Pin )==1)
	   {
	 	  i[0]=0x01;
	   }
 	 else
 	 	 {
 		i[0]=0x00;
 	 	 }
 if  (HAL_GPIO_ReadPin(flame7_GPIO_Port,flame7_Pin)==1)
	    {
	 i[1]=0x01;
	    }
 	 else
  	 	 {
 		i[1]=0x00;
  	 	 }*/
if  (HAL_GPIO_ReadPin(flame8_GPIO_Port,flame8_Pin)==1)
	    {
	 i[2]=0x01;
	    }
else
 	 	 {
	i[2]=0x00;
 	 	 }
if  (HAL_GPIO_ReadPin(flame9_GPIO_Port,flame9_Pin)==1)
	    {
	 i[3]=0x01;
	    }
else
 	 	 {
	i[3]=0x00;
 	 	 }
/*if  (HAL_GPIO_ReadPin(flame10_GPIO_Port,flame10_Pin)==1)
	    {
	 i[4]=0x01;
	    }
else
 	 	 {
	i[4]=0x00;
 	 	 }*/
for(int j=0;j<5;j++)
{
	if (i[j]==1)
	{
		date[2]=1;
		break;
	}
	else if (i[j]==0)
	{
		date[2]=0;

	}
}
}

void FLAME_C_PUT (unsigned char *date)
{
	int i[5]={0};
 if  (HAL_GPIO_ReadPin(flame11_GPIO_Port,flame11_Pin )==1)
	   {
	 	  i[0]=0x01;
	   }
 	 else
 	 	 {
 		i[0]=0x00;
 	 	 }
 if  (HAL_GPIO_ReadPin(flame12_GPIO_Port,flame12_Pin)==1)
	    {
	 i[1]=0x01;
	    }
 	 else
  	 	 {
 		i[1]=0x00;
  	 	 }
if  (HAL_GPIO_ReadPin(flame13_GPIO_Port,flame13_Pin)==1)
	    {
	 i[2]=0x01;
	    }
else
 	 	 {
	i[2]=0x00;
 	 	 }
if  (HAL_GPIO_ReadPin(flame14_GPIO_Port,flame14_Pin)==1)
	    {
	 i[3]=0x01;
	    }
else
 	 	 {
	i[3]=0x00;
 	 	 }
if  (HAL_GPIO_ReadPin(flame15_GPIO_Port,flame15_Pin)==1)
	    {
	 i[4]=0x01;
	    }
else
 	 	 {
	i[4]=0x00;
 	 	 }
for(int j=0;j<5;j++)
{
	if (i[j]==1)
		{
			date[3]=1;
			break;
		}
		else if (i[j]==0)
		{
			date[3]=0;
		}
}
}
