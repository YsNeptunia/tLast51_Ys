#ifndef __ULN2003D_H_
#define __ULN2003D_H_

#include "System.h"

// 定义步进电机控制引脚
sbit IN1 = P1^0;
sbit IN2 = P1^1;
sbit IN3 = P1^2;
sbit IN4 = P1^3;

// 定义步进电机参数
#define STEPS_PER_REV 2048  // 每转步数

// 函数声明
void Stepper_Init(void);
void Stepper_Step(int dir);
void Stepper_Turn(int steps, int dir);
void Open_Door(void);

#endif