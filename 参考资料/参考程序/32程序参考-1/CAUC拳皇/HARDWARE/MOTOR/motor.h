//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//电机驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __MOTOR_H
#define __MOTOR_H

#include "car_system.h"
#include "delay.h"
#include "sensors.h"

#define MAX_PWM     1799

#define STOP		0
#define FORWORD		1
#define BACKWORD	2
#define RIGHT		3
#define LEFT		4
#define DEFAULT		5

void MOTOR_Init(void);
void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr,u16 psc);
void CAR_Jump(u16 pwm_value_x,u16 pwm_value_y,u16 delay_time_x,u16 delay_time_y); 
void CAR_Stop(void);
void CAR_Move(u8 direction,u16 pwm_value);

#endif
