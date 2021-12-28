#include <ultrasonic.h>
#include  "tim.h"
#include  "delay.h"
#include "mc_math.h"

//共同体转换数据类型
/*union sendData
{
	short d;
	unsigned char data[2];
}CJ1_FtC,CJ2_FtC,CJ3_FtC,CJ4_FtC;*/

void Ultrasonic1(unsigned char *data)
{
	int i=0;
    float data_1[10]={0};
    float distance_1=0;
	while(i<10)
	{
         HAL_TIM_Base_Start(&htim6);//启动定时器6
	     float t11,t12=0; //定义单精度浮点数t1,t2,distance
	     HAL_GPIO_WritePin(Tring1_GPIO_Port,Tring1_Pin,GPIO_PIN_RESET);//设置引脚Tring1为低电平
	     HAL_GPIO_WritePin(Tring1_GPIO_Port,Tring1_Pin,GPIO_PIN_SET);//设置引脚Tring1为高电平
	     delay_us(50);//延时1ms
	     HAL_GPIO_WritePin(Tring1_GPIO_Port,Tring1_Pin,GPIO_PIN_RESET);//设置引脚Tring1为低电平
	     htim6.Instance->CNT = 0;//定时器6计数器清0
	     while(HAL_GPIO_ReadPin(Echo1_GPIO_Port,Echo1_Pin) == GPIO_PIN_RESET)//判断引脚Echo1是否为低电平
	    {
	    	t11=htim6.Instance->CNT;
	    }
	    while(HAL_GPIO_ReadPin(Echo1_GPIO_Port,Echo1_Pin) == GPIO_PIN_SET)//判断引脚Echo1是否为高电平
	    {
	    	t12=htim6.Instance->CNT;
	    }
	    htim6.Instance->CNT = 0;//定时器2计数器清0
	    data_1[i]=(t12-t11)*34/(float)2000;//赋值 distance
	    HAL_GPIO_WritePin(Tring1_GPIO_Port,Tring1_Pin,GPIO_PIN_RESET);//设置引脚Tring1为低电平
	    HAL_TIM_Base_Stop(&htim6);//关闭定时器
	    delay_us(50);//延时50ms
	    i++;
	}

	 array( data_1,10);//冒泡排序
	 distance_1=sum (data_1,10)/8;//去最值后求均值
	 //排除20cm之外的数据
	 if(	distance_1>20)
	 	    {
	 	    	data[7]=0xff;
	 	    }
	 	    else
	 	    {
	 	  	 data[7]=(unsigned char)distance_1;
	 	    }
}

void Ultrasonic2(unsigned char *data)
{
	int i=0;
	float data_2[10]={0};
	float distance_2=0;
	while(i<10)
	{
         HAL_TIM_Base_Start(&htim6);//启动定时器6中断
	     float t21,t22=0;//定义单精度浮点数t1,t2,distance
	     HAL_GPIO_WritePin(Tring2_GPIO_Port,Tring2_Pin,GPIO_PIN_RESET);//设置引脚Tring2为低电平
	     HAL_GPIO_WritePin(Tring2_GPIO_Port,Tring2_Pin,GPIO_PIN_SET);//设置引脚Tring2为高电平
	     delay_us(20);//延时1ms
	     HAL_GPIO_WritePin(Tring2_GPIO_Port,Tring2_Pin,GPIO_PIN_RESET);//设置引脚Tring2为低电平
	     htim6.Instance->CNT = 0;//定时器6计数器清0
	     while(HAL_GPIO_ReadPin(Echo2_GPIO_Port,Echo2_Pin) == GPIO_PIN_RESET)
	    t21=htim6.Instance->CNT;
	    while(HAL_GPIO_ReadPin(Echo2_GPIO_Port,Echo2_Pin) == GPIO_PIN_SET)
	    t22=htim6.Instance->CNT;
	    htim6.Instance->CNT = 0;//定时器2计数器清0
	    data_2[i]=(t22-t21)*34/(float)2000;//赋值 distance
	    HAL_GPIO_WritePin(Tring2_GPIO_Port,Tring2_Pin,GPIO_PIN_RESET);//设置引脚Tring2为低电平
	    HAL_TIM_Base_Stop(&htim6);
	    delay_us(50);//延时50ms
	    i++;
	}
	     array( data_2,10);//冒泡排序
	     distance_2=sum (data_2,10)/8;//去最值后求均值
		 //排除20cm之外的数据
		 if(	distance_2>20)
		 	 	    {
		 	 	    	data[8]=0xff;
		 	 	    }
		 	 	    else
		 	 	    {
		 	 	    	 data[8]=(unsigned char)distance_2;
		 	 	    }
}

void Ultrasonic3(unsigned char *data)
{
	int i=0;
    float data_3[10]={0};
    float distance_3=0;
	while(i<10)
	{
         HAL_TIM_Base_Start(&htim6);//启动定时器6中断
	     float t31,t32=0;//定义单精度浮点数t1,t2,distance
	     HAL_GPIO_WritePin(Tring3_GPIO_Port,Tring3_Pin,GPIO_PIN_RESET);//设置引脚Tring2为低电平
	     HAL_GPIO_WritePin(Tring3_GPIO_Port,Tring3_Pin,GPIO_PIN_SET);//设置引脚Tring2为高电平
	     delay_us(20);//延时1ms
	     HAL_GPIO_WritePin(Tring3_GPIO_Port,Tring3_Pin,GPIO_PIN_RESET);//设置引脚Tring2为低电平
	     htim6.Instance->CNT = 0;//定时器6计数器清0
	     while(HAL_GPIO_ReadPin(Echo3_GPIO_Port,Echo3_Pin) == GPIO_PIN_RESET)
	    t31=htim6.Instance->CNT;
	    while(HAL_GPIO_ReadPin(Echo3_GPIO_Port,Echo3_Pin) == GPIO_PIN_SET)
	    t32=htim6.Instance->CNT;
	    htim6.Instance->CNT = 0;//定时器2计数器清0
	    data_3[i]=(t32-t31)*34/(float)2000;//赋值 distance
	    HAL_GPIO_WritePin(Tring3_GPIO_Port,Tring3_Pin,GPIO_PIN_RESET);//设置引脚Tring2为低电平
	    HAL_TIM_Base_Stop(&htim6);
	    delay_us(50);//延时50ms
	    i++;
	}
	         array( data_3,10);//冒泡排序
	         distance_3=sum (data_3,10)/8;//去最值后求均值
			 //排除20cm之外的数据
			 if(	distance_3>20)
			{
					data[9]=0xff;
			}
			else
			{
					data[9]=(unsigned char)distance_3;
			}
}

void Ultrasonic4(unsigned char *data)
{
	int i=0;
    float data_4[10]={0};
    float distance_4=0;
	while(i<10)
	{
         HAL_TIM_Base_Start(&htim6);//启动定时器6中断
	     float t41,t42=0;//定义单精度浮点数t1,t2,distance
	     HAL_GPIO_WritePin(Tring4_GPIO_Port,Tring4_Pin,GPIO_PIN_RESET);//设置引脚Tring2为低电平
	     HAL_GPIO_WritePin(Tring4_GPIO_Port,Tring4_Pin,GPIO_PIN_SET);//设置引脚Tring2为高电平
	     delay_us(20);//延时1ms
	     HAL_GPIO_WritePin(Tring4_GPIO_Port,Tring4_Pin,GPIO_PIN_RESET);//设置引脚Tring2为低电平
	     htim6.Instance->CNT = 0;//定时器6计数器清0
	     while(HAL_GPIO_ReadPin(Echo4_GPIO_Port,Echo4_Pin) == GPIO_PIN_RESET)
	    t41=htim6.Instance->CNT;
	    while(HAL_GPIO_ReadPin(Echo4_GPIO_Port,Echo4_Pin) == GPIO_PIN_SET)
	    t42=htim6.Instance->CNT;
	    htim6.Instance->CNT = 0;//定时器2计数器清0
	    data_4[i]=(t42-t41)*34/(float)2000;//赋值 distance
	    HAL_GPIO_WritePin(Tring4_GPIO_Port,Tring4_Pin,GPIO_PIN_RESET);//设置引脚Tring2为低电平
	    HAL_TIM_Base_Stop(&htim6);
	    delay_us(50);//延时50ms
	    i++;
	}
	         array( data_4,10);//冒泡排序
	         distance_4=sum (data_4,10)/8;//去最值后求均值
			 //排除20cm之外的数据
			 if(distance_4>20)
			 	 	    {
			 	 	    	data[10]=0xff;
			 	 	    }
			 	 	    else
			 	 	    {
			 	 	    	data[10]=(unsigned char)distance_4;
			 	 	    }

}
