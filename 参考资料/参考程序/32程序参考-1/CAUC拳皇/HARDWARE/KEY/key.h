//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//五轴按键驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "delay.h"

#define KEY_OK 		PDin(15)
#define KEY_BACK 	PCin(11)
#define KEY_UP 		PDin(12)
#define KEY_DOWN 	PDin(14)
#define KEY_LEFT 	PCin(6)
#define KEY_RIGHT	PDin(13)

#define K_OK 		1
#define K_BACK 	2
#define K_UP 		3
#define K_DOWN 	4
#define K_LEFT 	5
#define K_RIGHT 6

void KEY_Init(void);
u8	 KEY_Scan(void);
u8   KEY_OK_Scan(void);
u8   KEY_BACK_Scan(void);
u8   KEY_UP_Scan(void);
u8   KEY_DOWN_Scan(void);
u8   KEY_LEFT_Scan(void);
u8   KEY_RIGHT_Scan(void);

#endif
