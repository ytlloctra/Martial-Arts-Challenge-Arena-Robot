//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//编码器驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#include "encoder.h"

/** 
	* @brief	初始化编码器
	* @since	v1.0
	*/
void ENCODER_Init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;      

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
	
  GPIO_AFIODeInit();	                                                                     	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_4 |GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period 				= 359*4;
	TIM_TimeBaseStructure.TIM_Prescaler 		= 0; 
	TIM_TimeBaseStructure.TIM_ClockDivision =	TIM_CKD_DIV1 ; 
	TIM_TimeBaseStructure.TIM_CounterMode		= TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_ICFilter = 6;
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	TIM3->CNT = 0;

	TIM_Cmd(TIM3, ENABLE);
}



/** 
	* @brief	读取编码器读数
	* @return	读取到的数值
	* @since	v1.0
	*/
u16 ENCODER_Read()
{
	u16 temp=TIM3->CNT/4;
	TIM3->CNT=0;
	return temp>179?359-temp:temp;
}



/** 
	* @brief	定时器3中断服务函数
	* @since	v1.0
	*/
void TIM3_IRQHandler(void)
{                                   
	if(TIM3->SR&0X0001){}                 
	TIM3->SR&=~(1<<0);
}
