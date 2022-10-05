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
#include "buzzer.h"

/** 
	* @brief	蜂鸣器初始化
	* @since	v1.0
	*/
void BUZZER_Init(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  GPIO_ResetBits(GPIOD, GPIO_Pin_8);
}



/** 
	* @brief	蜂鸣器发声
	* @param	times	发声次数
	* @since	v2.0
	*/
void BUZZER_Hint(u8 times)
{
	while(times--)
	{
		BUZZER = ON;
		delay_ms(100);
		BUZZER = OFF;
		delay_ms(100);
	}
}	
