/*
 * 超声波
 * 第一版：阎宇威
 * 说明：带去最值均值滤波
 * 定时器采用tim6定时
 */

#ifndef  __ULTRASONIC_H
#define  __ULTRASONIC_H
#include "main.h"

void Ultrasonic1 (unsigned char *data);
void Ultrasonic2 (unsigned char *data);
void Ultrasonic3 (unsigned char *data);
void Ultrasonic4 (unsigned char *data);

#endif
