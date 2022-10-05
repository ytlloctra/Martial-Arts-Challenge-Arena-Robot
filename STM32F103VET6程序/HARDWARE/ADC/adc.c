 #include "adc.h"
 #include "delay.h"
 #include "stm32f10x_dma.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//ADC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
	__IO uint32_t ADC1_Buff[10];	   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
//	DMA_InitTypeDef    DMA_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC |RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOB	, ENABLE );	  //使能ADC1通道时钟
 // RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	
/*		DMA_DeInit(DMA1_Channel1);
	 DMA_InitStructure.DMA_BufferSize=120;                                            //缓存数据个数
	 DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;                                //以外设为数据源
	 DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;                                      //不使用内存到内存
	 DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)ADC1_Buff;           //内存中存储DMA传输过来的数据基地址
	 DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;               //内存数据为半字 16位（ADC精度为12位）
	 DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;                           //内存地址要增加
	 DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;                                   //DMA工作在循环模式
	 DMA_InitStructure.DMA_PeripheralBaseAddr= (uint32_t)&ADC1->DR;                  //数据源地址  ADC数据寄存器地址
	 DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;       //DMA外设数据宽度 
	 DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;                  //外设地址增加
	 DMA_InitStructure.DMA_Priority=DMA_Priority_High; 	                             //DMA优先级高
	 DMA_Init(DMA1_Channel1, &DMA_InitStructure);                                    //DMA初始化
	 DMA_Cmd(DMA1_Channel1, ENABLE);    	                                         //使能DMA
       
 // DMA_Cmd(DMA1_Channel1,ENABLE);                          //??DMA??
	*/
	
	

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_6|GPIO_Pin_1|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//|GPIO_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 15;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   



  ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 10, ADC_SampleTime_239Cycles5);//A0
 	ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 9, ADC_SampleTime_239Cycles5);//A1
 	ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 8, ADC_SampleTime_239Cycles5);//A2
  ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 7, ADC_SampleTime_239Cycles5);//A3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4, 6, ADC_SampleTime_239Cycles5);//A4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5, 5, ADC_SampleTime_239Cycles5);//A5
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6, 4, ADC_SampleTime_239Cycles5);//A6
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7, 3, ADC_SampleTime_239Cycles5);//A7
  ADC_RegularChannelConfig(ADC1,ADC_Channel_8,14, ADC_SampleTime_239Cycles5);//B0
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_9,15, ADC_SampleTime_239Cycles5);//B1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,15, ADC_SampleTime_239Cycles5);//C0
	ADC_RegularChannelConfig(ADC1,ADC_Channel_11,13, ADC_SampleTime_239Cycles5);//C1
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,12, ADC_SampleTime_239Cycles5);//C2
	ADC_RegularChannelConfig(ADC1,ADC_Channel_13,11, ADC_SampleTime_239Cycles5);//C3
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,2, ADC_SampleTime_239Cycles5);//C4
	ADC_RegularChannelConfig(ADC1,ADC_Channel_15,1, ADC_SampleTime_239Cycles5);//C5
	/*ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_7, 10, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2, 2, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1,ADC_Channel_3, 3, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_4, 4, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_6, 5, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_5, 11, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1, 6, ADC_SampleTime_239Cycles5);
//	ADC_RegularChannelConfig(ADC1,ADC_Channel_9, 7, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(ADC1,ADC_Channel_10,7, ADC_SampleTime_239Cycles5);
	//ADC_RegularChannelConfig(ADC1,ADC_Channel_11,1, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_12,8, ADC_SampleTime_239Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_14,9, ADC_SampleTime_239Cycles5);*/
	
  ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
	
//  ADC_DMACmd(ADC1, ENABLE);                      //ADC1 DMA?????? 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	
	
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
	
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	//ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	return temp_val/times;
} 	 



























