#include <motor_l1.h>
#include "tim.h"
#include "math.h"

static float   Proportion_L_1=5;                               //比例常数 Proportional Const
static float   Integral_L_1=0.3;                                 //积分常数 Integral Const
static float   Derivative_L_1=0;                                 //无微分环节
float GetData_L_1=0;//编码器所读脉冲数
int Direction_L_1=0;//编码器所读小车运动的方向，前进：左0，右1，后退：左1，右0
float  n_L_1=0;//转速
float v_L_1=0;//线速度
float prespwm_L_1=0;//当前pwm
float outpwm_L_1=0;//pid输出的pwm
float  LastError_L_1=0;//上一次误差
float PresError_L_1=0;//当前误差
float Outpid_L_1=0;//pid输出值（pwm）
float I_acc_L_1=0; //之前误差累加和（利用积分分离）
int stotage_L_1 =0;//计算角度时储存编码器的值

//判断电机转动方向
void go_or_back_L_1(float  setpoint_L_1)
{
	if(setpoint_L_1>0)
			{
				Motor_L_1(GO);//左2电机正转
			}
		if(setpoint_L_1<0)
			{
				Motor_L_1(BACK);//左2电机反转
			}
	  	if(setpoint_L_1==0)
	  		{
	  				Motor_L_1(STOP);//左2电机停止
	  		}
}

//电机转动方向控制
void Motor_L_1(char state)
	  {
	  	if(state == GO)//左1电机前进
	  	{
	  		HAL_GPIO_WritePin(motor1_GPIO_Port,  motor1_Pin, 0);
	  		HAL_GPIO_WritePin(motor2_GPIO_Port,  motor2_Pin, 1);
	  	}
	  	if(state == BACK)//左1电机后退
	  	{
	  		HAL_GPIO_WritePin(motor1_GPIO_Port,  motor1_Pin, 1);
	  		HAL_GPIO_WritePin(motor2_GPIO_Port,  motor2_Pin, 0);
	  	}
	  	if(state == STOP)//左1电机停转
	  	{
	  		HAL_GPIO_WritePin(motor1_GPIO_Port,  motor1_Pin, 0);
	  		HAL_GPIO_WritePin(motor2_GPIO_Port,  motor2_Pin, 0);
	  	}
	  }

//编码器采集脉冲数，具体调节电机转速
float contol_L_1(float setpoint_L_1,float setpoint_R_2,float *angular)
{
		GetData_L_1 = __HAL_TIM_GET_COUNTER(&htim2);   //编码器读脉冲数
		Direction_L_1 = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);		// 判断正反转，前进时左为0，右为1；后退时左为1，右为0
		__HAL_TIM_SET_COUNTER(&htim2,0);//编码器读数后清零

		// 判断正反转，前进时左为0，右为1；后退时左为1，右为0
		if (Direction_L_1==1)
		{
			if(GetData_L_1==0)
			{
				GetData_L_1=0;
			}
			else
			{
				GetData_L_1=65535-GetData_L_1;
			}
		}

		//计算转角
		if (setpoint_L_1*setpoint_R_2<0)
		{
			stotage_L_1+=GetData_L_1;
			angular[0]=stotage_L_1/4680*2*3.14;
		}
		else if(setpoint_L_1*setpoint_R_2>=0)
		{
			stotage_L_1=0;
		}

		//计算转速和线速度
		n_L_1=GetData_L_1/4680*5;
		v_L_1=GetData_L_1/4680*0.2041*5;    			//v=n*2*Π*r*0.01=n*0.2041m/s  r=3.25

		//pid的系统为转速
		outpwm_L_1=PID_Calc_L_1(n_L_1,fabs(setpoint_L_1/1000.0)/0.2041);   //设定值从线速度变为转速
		prespwm_L_1+= outpwm_L_1;

		if(prespwm_L_1>=80){prespwm_L_1=80;} if(prespwm_L_1<=0){prespwm_L_1=0;}   //限幅pwm
		__HAL_TIM_SET_COMPARE(&htim5,TIM_CHANNEL_3,prespwm_L_1);//通过pwm控制电机速度


		return v_L_1;//返回线速度
}
	//位置式pid
	//PID计算公式Δu(k)=kp*e(k)+ki*[e(k)+...+e(0)]+kd[e(k)-e(k−1)]
	float PID_Calc_L_1(float PresPoint_L_1,float SetPoint_L_1)
	{
		PresError_L_1=SetPoint_L_1-PresPoint_L_1;                //误差计算
		if(PresError_L_1<0.3){I_acc_L_1+=PresError_L_1;}//误差小于0.3不进行积分控制（积分分离）
		else{I_acc_L_1=0;}

		Outpid_L_1=Proportion_L_1 *PresError_L_1                //p项
					+Integral_L_1 * I_acc_L_1     //i项
					+Derivative_L_1 *( PresError_L_1-LastError_L_1);   //d项

		LastError_L_1=PresError_L_1;                    //存储误差，用于下次计算
		return(Outpid_L_1);                                       //返回输出值（pwm）
}
