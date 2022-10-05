//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//光电开关驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __SENSORS_H
#define __SENSORS_H

#include "sys.h"

#define EYE2_BR  PDin(0)
#define EYE2_FR  PCin(12)
#define EYE2_BL  PDin(5)
#define EYE2_FL  PDin(4)
#define EYE3_JP  PDin(6)
#define EYE3_DBM PDin(3)
#define EYE3_DFL PDin(7)
#define EYE3_DFR PDin(2)
#define EYE3_NONAME PDin(1)

void SENSORS_Init(void);

#endif
