//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//擂台函数集
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __ATTACK_H
#define __ATTACK_H

#include "car_system.h"
#include "motor.h"
#include "sensors.h"
#include "encoder.h"

#define SCAN(ADC_NAME) EYE_##ADC_NAME>EYE_THRESHOLD.##ADC_NAME
#define SCAN_EXACT(ADC_NAME) EYE_##ADC_NAME>EYE_THRESHOLD.EXACT

u8   Scan_Gesture(void);
u8   Judge_State_Chess(void);
u8   Judge_State_Car(void);
void Attack_Car(void);
void Attack_Car_Single(void);
void Attack_Chess(void);
void MODE_Attack_Chess(void);
void MODE_Attack_Car(void);
void MODE_Attack_Car_Single(void);
void Jump(void);
void Jump_Test(void);
void Jump_Restoration(void);
void Falling_Test(void);
u8   Find_Arena(void);
void Ready_Jump(void);

#endif
