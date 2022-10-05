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
#include "adc.h"

u16 ADC_BUFF[16];

/** 
	* @brief	ADC1初始化(DMA读取)
	* @since	v1.0
	*/
void  ADC1_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_ADC1, ENABLE );

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
										 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);

	ADC_InitStructure.ADC_Mode					=	ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode			=	ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode	=	ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv		=	ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign				=	ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel			=	16;
	ADC_Init(ADC1, &ADC_InitStructure);

	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,	1,	ADC_SampleTime_239Cycles5);	//PA0
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,	2,	ADC_SampleTime_239Cycles5);	//PA1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,	3,	ADC_SampleTime_239Cycles5);	//PA2
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,	4,	ADC_SampleTime_239Cycles5);	//PA3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4,	5,	ADC_SampleTime_239Cycles5);	//PA4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5,	6,	ADC_SampleTime_239Cycles5);	//PA5
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6,	7,	ADC_SampleTime_239Cycles5);	//PA6
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7,	8,	ADC_SampleTime_239Cycles5);	//PA7
	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,	9,	ADC_SampleTime_239Cycles5);	//PB0
	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,	10,	ADC_SampleTime_239Cycles5);	//PB1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,	11,	ADC_SampleTime_239Cycles5);	//PC0
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,	12,	ADC_SampleTime_239Cycles5);	//PC1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,	13,	ADC_SampleTime_239Cycles5);	//PC2
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,	14,	ADC_SampleTime_239Cycles5);	//PC3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,	15,	ADC_SampleTime_239Cycles5);	//PC4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_15,	16,	ADC_SampleTime_239Cycles5);	//PC5

	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);

	ADC_ResetCalibration(ADC1); 
	while(ADC_GetResetCalibrationStatus(ADC1));

	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
