//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//DMA驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __DMA_H
#define	__DMA_H

#include "sys.h"
#include "adc.h"

void DMA1_Channel1_Init(void);
void DMA1_Channel1_IRQHandler(void);
		   
#endif
