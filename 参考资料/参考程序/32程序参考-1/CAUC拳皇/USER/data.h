//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//数据操作函数集
//编者：徐天泽
//版本：V2.0
//修改日期:2018/10/04
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __DATA_H
#define __DATA_H

#include "car_system.h"
#include "flash.h"
#include "motor.h"
#include "encoder.h"
#include "buzzer.h"

/*结构体数据宽度*/
#define PWM_DATA_LENTH			9
#define ADC_DATALENTH			19
#define ENCODER_DATA_LENTH      6
#define SUNDRY_DATA_LENTH		7

/*结构体数据存储地址*/
#define PWM_DATA_ADDR			ADDR_FLASH_PAGE_60
#define ADC_DATA_ADDR 		    ADDR_FLASH_PAGE_61
#define ENCODER_DATA_ADDR       ADDR_FLASH_PAGE_62
#define SUNDRY_DATA_ADDR        ADDR_FLASH_PAGE_63

void Save_PWMData(void);
void Load_PWMData(void);
void Reset_PWMData(void);
void Clear_PWMData(void);
void Save_ADCData(void);
void Load_ADCData(void);
void Reset_ADCData(void);
void Clear_ADCData(void);
void Refresh_ADCData(void);
void Save_EncoderData(void);
void Load_EncoderData(void);
void Reset_EncoderData(void);
void Clear_EncoderData(void);
u16	 AVERAGE(u16 *array, u8 width);
u16	 Get_ErrorRange(u16 *array, u8 width);
void Auto_EncoderData(void);
void Save_SundryData(void);
void Load_SundryData(void);
void Reset_SundryData(void);
void Clear_SundryData(void);
void Save_JumpData(void);
void Save_ALLData(void);
void Load_ALLData(void);
void Reset_ALLData(void);
void Clear_Data(void);

#endif
