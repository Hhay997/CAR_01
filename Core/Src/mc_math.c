#include "mc_math.h"

//冒泡排序
void array  (float *data,int len)
{


	 for( int i=0;i<len-1;i++)
	 {
	     for(int  j=0;j<len-i-1;j++)
	     {
	        if(data[j]>data[j+1])
	        {
	            float temp = data[j];
	            data[j] = data[j+1];
	            data[j+1] = temp;
	        }
	     }
	 }
}

//去最值后求均值
float sum (float *data,int len)
{
	float sum;
	for(int i=1;i<len-1;i++)
	{
		sum=data[i]+sum;
	}
    return sum;
}

