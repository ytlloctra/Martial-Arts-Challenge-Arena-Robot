//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//蜂鸣器驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __BUZZER_H
#define	__BUZZER_H

#include "sys.h"
#include "delay.h"

#define ON	1
#define OFF	0

#define BUZZER PDout(8)

void BUZZER_Init(void);
void BUZZER_Hint(u8 times);

#endif
