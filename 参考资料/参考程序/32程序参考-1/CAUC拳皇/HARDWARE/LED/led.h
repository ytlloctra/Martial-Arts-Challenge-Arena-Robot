//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//LED驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __LED_H
#define	__LED_H

#include "sys.h"
#include "delay.h"

void LED_Init(void);
void LED_Show(u8 number);
void LED_Flow(u8 direction,u16 time);

#endif
