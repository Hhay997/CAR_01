/*
 * 左1电机
 * 第一版：阎宇威
 * pid采用位置式
 */

#ifndef MOTOR_L1_H
#define MOTOR_L1_H
#include "main.h"

//定义电机状态
#define GO  0 //前进
#define BACK  1//后退
#define STOP  2//停车

void go_or_back_L_1(float setpoint_L_1);//判断小车状态
void Motor_L_1 (char state);//控制电机正转反转
float contol_L_1(float setpoint_L_1,float setpoint_R_2,float *angular);//控制电机转速,判断是否转弯
float PID_Calc_L_1 (float NextPoint,float SetPoint);//pid通过转速控制pwm

#endif
