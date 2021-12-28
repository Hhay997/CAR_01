#include "delay.h"
#include "sys.h"

//粗延时函数，1微秒
void delay_us(u16 time)
{
   u16 i=0;
   while(time--)
   {
      i=168;  //自己定义
      while(i--) ;
   }
}

//粗延时函数，1毫秒
void delay_ms(u16 time)
{
   while(time--)
   {
       u16 i=168;
      while(i--)
      {
    	 u16  j=1000;
    	  while(j--);
      }
   }
}
