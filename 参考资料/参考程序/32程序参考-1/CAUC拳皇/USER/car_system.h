//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//系统全局宏定义、全局变量声明
//编者：徐天泽
//版本：V2.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __CAR_SYSTEM_H
#define __CAR_SYSTEM_H

#include "sys.h"
#include "delay.h"
#include "oled.h"
#include "buzzer.h"
#include "adc.h"
#include "led.h"
#include "key.h"
#include "flash.h"
#include "dma.h"

/*默认参数设置*/
#define ADC_THRESHOLD_INIT			1300	//ADC整体阈值
#define ADC_THRESHOLD_EXACT_INIT	1100	//ADC极限阈值
#define ADC_THRESHOLD_FBMM_INIT		900		//后传感器阈值

#define SUNDRY_MISSCOUNT_INIT 		10		//丢失目标计数
#define SUNDRY_LOCKCOUNT_INIT		20		//锁定目标计数
#define SUNDRY_MARGINDELAY_INIT		150		//避障延时
#define SUNDRY_JUMPDELAY_X_INIT		10		//跳台冲刺时间
#define SUNDRY_JUMPDELAY_Y_INIT		100		//跳台电机运转时间
#define SUNDRY_JUMPDELAY_B_INIT		100		//落台保持安全距离后撤时间
#define SUNDRY_JUMPADCValue_INIT	300		//跳台对台ADC允许误差

#define PWM_C_INIT					600		//推棋子模式PWM
#define PWM_A_INIT					1100	//避障PWM
#define PWM_S_INIT					700		//擂台模式直线PWM
#define PWM_T_INIT					800		//擂台模式转向PWM
#define PWM_D_INIT					500		//擂台模式扫台PWM
#define PWM_M_INIT					1299	//擂台模式满转PWM
#define PWM_JX_INIT					800		//跳台冲刺PWM
#define PWM_JY_INIT					1400	//跳台电机PWM
#define PWM_FALL_INIT				500		//落台寻台PWM

/*布尔型标识符定义*/
#define TRUE	1
#define FALSE	0

/*车辆电机PWM占空比结构体定义*/
typedef struct{
	u16 Chess;			//推棋子时的PWM占空比
	u16 Avoid;			//避障时的PWM占空比
	u16 Straight;		//直线运行时的PWM占空比
	u16 Turn;			//转向时的PWM占空比
	u16 Default;		//丢失目标时的PWM占空比
	u16 Max;			//僵持时的PWM占空比
	u16 JumpX;			//登台时直行电机的PWM占空比
	u16 JumpY;			//登台时登台电机的PWM占空比
	u16 Falling;		//落台时的PWM占空比
}	CAR_PWM;

/*车辆电机转速结构体定义*/
typedef struct{
	u16 Forword;		//前进时的转速
	u16 Backword;		//后退时的转速
	u16 Right;			//右转时的转速
	u16 Left;			//左转时的转速
	u8 	ErrorRange_S;	//直行误差范围
	u8 	ErrorRange_T;	//转向误差范围
}	CAR_SPEED;

/*车辆ADC阈值结构体定义*/
typedef struct{
	u16 ALL;		//所有ADC的阈值
	u16 MRF;		//车辆中部右侧前方ADC的阈值
	u16 MRM;		//车辆中部右侧中部ADC的阈值
	u16 MRB;		//车辆中部右侧后方ADC的阈值
	u16 MLF;		//车辆中部左侧前方ADC的阈值
	u16 MLM;		//车辆中部左侧中部ADC的阈值
	u16 MLB;		//车辆中部左侧后方ADC的阈值
	u16 FOR;		//车辆前方外部右侧ADC的阈值
	u16 FOL;		//车辆前方外部左侧ADC的阈值
	u16 FMR;		//车辆前方中部右侧ADC的阈值
	u16 FMM;		//车辆前方中部中部ADC的阈值
	u16 FML;		//车辆前方中部左侧ADC的阈值
	u16 BOR;		//车辆后方外部右侧ADC的阈值
	u16 BOL;		//车辆后方外部左侧ADC的阈值
	u16 BML;		//车辆后方中部左侧ADC的阈值
	u16 BMM;		//车辆后方中部中部ADC的阈值
	u16 BMR;		//车辆后方中部右侧ADC的阈值
	u16 EXACT;		//车辆ADC精确阈值
	u16 LAST;		//所有ADC的阈值
}	ADC_THRESHOLD;

/*杂项结构体定义*/
typedef struct{
	u16 Miss_Count;		//丢失目标后的计数值
	u16	Lock_Count;		//锁定目标后的计数值
	u16 Margin_Delay;	//规避边缘时转向延时
	u16 Jump_Delay_X;	//登台时冲刺时间
	u16 Jump_Delay_Y;	//登台时上台电机运转时间
	u16 Jump_Delay_B;	//落台后为保持安全距离的后撤时间
	u16 Jump_ADC_Value;	//落台后ADC对台误差
}	CAR_SUNDRY;

/*全局变量声明*/
extern CAR_PWM			MOTOR_PWM;
extern ADC_THRESHOLD 	EYE_THRESHOLD;
extern CAR_SPEED 		ENCODER_VALUE;
extern CAR_SUNDRY 		SETTING_SUNDRY;
extern u16 				miss_count;

#endif
