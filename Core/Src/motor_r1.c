#include <motor_r1.h>
#include "tim.h"
#include "math.h"
static float   Proportion_R_1=5;                               //比例常数 Proportional Const
static float   Integral_R_1=0.3;                                 //积分常数 Integral Const
static float   Derivative_R_1=0;                                 //无微分环节
float GetData_R_1=0;//编码器所读脉冲数
int Direction_R_1=0;//编码器所读小车运动的方向，前进：左0，右1，后退：左1，右0
float  n_R_1=0;//转速
float v_R_1=0;//线速度
float prespwm_R_1=0;//当前pwm
float outpwm_R_1=0;//pid输出的pwm
float  LastError_R_1=0;//上一次误差
float PresError_R_1=0;//当前误差
float Outpid_R_1=0;//pid输出值（pwm）
float I_acc_R_1=0; //之前误差累加和（利用积分分离）
int stotage_R_1 =0;//计算角度时储存编码器的值

//判断电机转动方向
void go_or_back_R_1(float  setpoint_R_1)
{
	if(setpoint_R_1>0)
			{
				Motor_R_1(GO);//右1电机正转
			}
		if(setpoint_R_1<0)
			{
				Motor_R_1(BACK);//右1电机反转
			}
		if(setpoint_R_1==0)
			{
				Motor_R_1(STOP);//右1电机停止
			}
}

//电机转动方向控制
void Motor_R_1(char state)
	  {
	  	if(state == GO)//右1电机前进
	  	{
	  		HAL_GPIO_WritePin(motor5_GPIO_Port,  motor5_Pin, 1);
	  		HAL_GPIO_WritePin(motor6_GPIO_Port,  motor6_Pin, 0);
	  	}
	  	if(state == BACK)//右1电机后退
	  	{
	  		HAL_GPIO_WritePin(motor5_GPIO_Port,  motor5_Pin, 0);
	  		HAL_GPIO_WritePin(motor6_GPIO_Port,  motor6_Pin, 1);
	  	}
	  	if(state == STOP)//右1电机停转
	  	{
	  		HAL_GPIO_WritePin(motor5_GPIO_Port,  motor5_Pin, 0);
	  		HAL_GPIO_WritePin(motor6_GPIO_Port,  motor6_Pin, 0);
	  	}
	  }

//编码器采集脉冲数，具体调节电机转速
float contol_R_1(float setpoint_R_1,float setpoint_L_2,float *angular)
{
		GetData_R_1 = __HAL_TIM_GET_COUNTER(&htim4);   //编码器读脉冲数
		Direction_R_1 = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4);		// 判断电机正反转，前进时左为0，右为1；后退时左为1，右为0
		__HAL_TIM_SET_COUNTER(&htim4,0);//编码器读数后清零

		//判断是否反转，前进时左为0，右为1；后退时左为1，右为0
		if (Direction_R_1==1)
		{
			if(GetData_R_1==0)
			{
				GetData_R_1=0;
			}
			else
			{
				GetData_R_1=65535-GetData_R_1;
			}
		}

		//计算转角
		if (setpoint_R_1*setpoint_L_2<0)
		{
			stotage_R_1+=GetData_R_1;
			angular[2]=stotage_R_1/4680*2*3.14;
		}
		else if(setpoint_R_1*setpoint_L_2>=0)
		{
			stotage_R_1=0;
		}

		//计算转速和线速度
		n_R_1=GetData_R_1/4680*5;
		v_R_1=GetData_R_1/4680*0.2041*5;    			//v=n*2*Π*r*0.01=n*0.2041m/s  r=3.25

		//pid的系统为转速
		outpwm_R_1=PID_Calc_R_1(n_R_1,fabs(setpoint_R_1/1000.0)/0.2041);   //设定值从线速度变为转速
		prespwm_R_1+= outpwm_R_1;

		if(prespwm_R_1>=80){prespwm_R_1=80;} if(prespwm_R_1<=0){prespwm_R_1=0;}   //限幅pwm
		__HAL_TIM_SET_COMPARE(&htim9,TIM_CHANNEL_1,prespwm_R_1);//通过pwm控制电机速度

		return v_R_1;//返回线速度
}

	//位置式pid
	//PID计算公式Δu(k)=kp*e(k)+ki*[e(k)+...+e(0)]+kd[e(k)-e(k−1)]
	float PID_Calc_R_1(float PresPoint_R_1,float SetPoint_R_1)
	{

		PresError_R_1=SetPoint_R_1-PresPoint_R_1;                //误差计算
		if(PresError_R_1<0.3){I_acc_R_1+=PresError_R_1;}//误差小于0.3不进行积分控制（积分分离）
		else{I_acc_R_1=0;}

		Outpid_R_1=Proportion_R_1 *PresError_R_1                 //p项
					+Integral_R_1 * I_acc_R_1     //i项
					+Derivative_R_1 *( PresError_R_1-LastError_R_1);   //d项

		LastError_R_1=PresError_R_1;                    //存储误差，用于下次计算
		return(Outpid_R_1);                                     //返回输出值（pwm）
}
