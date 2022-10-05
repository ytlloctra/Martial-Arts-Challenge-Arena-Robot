//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//OLED驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#ifndef __OLED_H
#define __OLED_H

#include "sys.h"
#include "stdlib.h"
#include "delay.h"

#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
				   
#define OLED_RST_Clr() GPIO_ResetBits(GPIOE,GPIO_Pin_6)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOE,GPIO_Pin_6)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_10)//DC
#define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_10)
 		     
#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_12)//CS
#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//CLK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)
 		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_WR_Byte(u8 dat,u8 cmd);	    
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);	 
void OLED_ShowChar(u8 x,u8 y,u8 chr);
u32  oled_pow(u8 m,u8 n);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p);	 
void OLED_ShowChinese(u8 x,u8 y,u8 no);
void OLED_ShowText(u8 line,u8 start,u8 end);
void OLED_ShowLogo(void);
void OLED_Init(void);

#endif
