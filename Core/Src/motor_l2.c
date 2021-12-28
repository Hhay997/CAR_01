#include <motor_l2.h>
#include "tim.h"
#include "math.h"

static float   Proportion_L_2=5;                               //比例常数 Proportional Const
static float   Integral_L_2=0.3;                                 //积分常数 Integral Const
static float   Derivative_L_2=0;                                 //无微分环节
float GetData_L_2=0;//编码器所读脉冲数
int Direction_L_2=0;//编码器所读小车运动的方向，前进：左0，右1，后退：左1，右0
float  n_L_2=0;//转速
float v_L_2=0;//线速度
float prespwm_L_2=0;//当前pwm
float outpwm_L_2=0;//pid输出的pwm
float  LastError_L_2=0;//上一次误差
float PresError_L_2=0;//当前误差
float Outpid_L_2=0;//pid输出值（pwm）
float I_acc_L_2=0; //之前误差累加和（利用积分分离）
int stotage_L_2 =0;//计算角度时储存编码器的值

//判断电机转动方向
void go_or_back_L_2(float  setpoint_L_2)
{
	if(setpoint_L_2>0)
			{
				Motor_L_2(GO);//左2电机正转
			}
		if(setpoint_L_2<0)
			{
				Motor_L_2(BACK);//左2电机反转
			}
	  	if(setpoint_L_2==0)
	  		{
	  				Motor_L_2(STOP);//左2电机停止
	  		}
}

//电机转动方向控制
void Motor_L_2(char state)
	  {
	  	if(state == GO)//左2电机前进
	  	{
	  		HAL_GPIO_WritePin(motor3_GPIO_Port,  motor3_Pin, 0);
	  		HAL_GPIO_WritePin(motor4_GPIO_Port,  motor4_Pin, 1);
	  	}
	  	if(state == BACK)//左2电机后退
	  	{
	  		HAL_GPIO_WritePin(motor3_GPIO_Port,  motor3_Pin, 1);
	  		HAL_GPIO_WritePin(motor4_GPIO_Port,  motor4_Pin, 0);
	  	}
	  	if(state == STOP)//左2电机停转
	  	{
	  		HAL_GPIO_WritePin(motor3_GPIO_Port,  motor3_Pin, 0);
	  		HAL_GPIO_WritePin(motor4_GPIO_Port,  motor4_Pin, 0);
	  	}
	  }

//编码器采集脉冲数，具体调节电机转速
float contol_L_2(float setpoint_L_2,float setpoint_R_1,float *angular)
{
		GetData_L_2 = __HAL_TIM_GET_COUNTER(&htim3);   //编码器读脉冲数
		Direction_L_2 = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim3);		// 判断正反转，前进时左为0，右为1；后退时左为1，右为0
		__HAL_TIM_SET_COUNTER(&htim3,0);//编码器读数后清零

		// 判断正反转，前进时左为0，右为1；后退时左为1，右为0
		if (Direction_L_2==1)
		{
			if(GetData_L_2==0)
			{
				GetData_L_2=0;
			}
			else
			{
				GetData_L_2=65535-GetData_L_2;
			}
		}

		//计算转角
				if (setpoint_L_2*setpoint_R_1<0)
				{
					stotage_L_2+=GetData_L_2;
					angular[1]=stotage_L_2/4680*2*3.14;
				}
				else if(setpoint_L_2*setpoint_R_1>=0)
				{
					stotage_L_2=0;
				}

		//计算转速和线速度
		n_L_2=GetData_L_2/4680*5;
		v_L_2=GetData_L_2/4680*0.2041*5;    			//v=n*2*Π*r*0.01=n*0.2041m/s  r=3.25

		//pid的系统为转速
		outpwm_L_2=PID_Calc_L_2(n_L_2,fabs(setpoint_L_2/1000.0)/0.2041);   //设定值从线速度变为转速
		prespwm_L_2+= outpwm_L_2;

		if(prespwm_L_2>=80){prespwm_L_2=80;} if(prespwm_L_2<=0){prespwm_L_2=0;}   //限幅pwm
		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_4,prespwm_L_2);//通过pwm控制电机速度

		return v_L_2;//返回线速度
}
	//位置式pid
	//PID计算公式Δu(k)=kp*e(k)+ki*[e(k)+...+e(0)]+kd[e(k)-e(k−1)]
	float PID_Calc_L_2(float PresPoint_L_2,float SetPoint_L_2)
	{
		PresError_L_2=SetPoint_L_2-PresPoint_L_2;                //误差计算
		if(PresError_L_2<0.3){I_acc_L_2+=PresError_L_2;}//误差小于0.3不进行积分控制（积分分离）
		else{I_acc_L_2=0;}

		Outpid_L_2=Proportion_L_2 *PresError_L_2                //p项
					+Integral_L_2 * I_acc_L_2     //i项
					+Derivative_L_2 *( PresError_L_2-LastError_L_2);   //d项

		LastError_L_2=PresError_L_2;                    //存储误差，用于下次计算
		return(Outpid_L_2);                                       //返回输出值（pwm）
}
