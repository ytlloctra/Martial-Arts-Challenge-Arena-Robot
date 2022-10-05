//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//ADC驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __ADC_H
#define __ADC_H

#include "sys.h"

extern u16 ADC_BUFF[16];

#define	EYE_MRM	ADC_BUFF[0]     //PA0
#define	EYE_BOR	ADC_BUFF[1]     //PA1
#define	EYE_FOR	ADC_BUFF[2]     //PA2
#define	EYE_FMR	ADC_BUFF[3]     //PA3
#define	EYE_FML	ADC_BUFF[4]     //PA4
#define	EYE_FOL	ADC_BUFF[5]     //PA5
#define	EYE_MLF	ADC_BUFF[6]     //PA6
#define	EYE_MLM	ADC_BUFF[7]     //PA7
#define	EYE_MLB	ADC_BUFF[8]     //PB0
#define	EYE_BOL	ADC_BUFF[9]     //PB1
#define	EYE_BMR	ADC_BUFF[10]    //PC0
#define	EYE_MRF	ADC_BUFF[11]    //PC1
#define	EYE_MRB	ADC_BUFF[12]    //PC2
#define	EYE_BML	ADC_BUFF[13]    //PC3
#define	EYE_BMM	ADC_BUFF[14]    //PC4
#define	EYE_FMM	ADC_BUFF[15]    //PC5

void ADC1_Init(void);

#endif 
