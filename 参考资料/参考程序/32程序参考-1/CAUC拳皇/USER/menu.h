//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//菜单页面函数集
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __MENU_H
#define __MENU_H

#include "SOLGUI_Include.h"

#define SOLGUI_Widget_ShowEYE(X,Y,ADC_NAME) \
SOLGUI_Widget_Text\
(X,Y,EYE_##ADC_NAME>EYE_THRESHOLD.##ADC_NAME?R4X6:F4X6,\
"%04d",EYE_##ADC_NAME);

#define SOLGUI_Widget_ShowEYE_EXACT(X,Y,ADC_NAME) \
SOLGUI_Widget_Text\
(X,Y,EYE_##ADC_NAME>EYE_THRESHOLD.EXACT?R4X6:F4X6,\
"%04d",EYE_##ADC_NAME);


#endif
