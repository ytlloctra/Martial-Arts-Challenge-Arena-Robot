#include "exti.h"
#include "delay.h" 
#include "edge.h"
#include "motor.h"
#include "timer.h"
#include "usart.h"
extern u8 cmd;
//////////////////////////////////////////////////////////////////////////////////	 
//外部中断 驱动代码	   
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com									  
////////////////////////////////////////////////////////////////////////////////// 

//外部中断0服务程序
void EXTI9_5_IRQHandler(void)
{
	//state=1;
//	printf("gg");
//	cmd=0;
//	zhidong(1);
//	if(fedge1==1)
//	{
//		delay_ms(100);
//		if(fedge2==1)
//		{
//			motor(-30,-30);
//			delay_ms(800);
//			motor(50,-50);
//			delay_ms(1000);
//		}
//		else
//		{
//			motor(-30,-30);
//			delay_ms(800);
//			motor(50,-50);
//			delay_ms(500);
//		}
//	}
	
	EXTI_ClearITPendingBit(EXTI_Line5); 
}	
//外部中断1服务程序
void EXTI4_IRQHandler(void)
{
	//state=2;
//	printf("gg");
//	cmd=0;
//	zhidong(1);
//	if(fedge2==1)
//	{
//		delay_ms(100);
//		if(fedge1==1)
//		{
//			motor(-30,-30);
//			delay_ms(800);
//			motor(-50,50);
//			delay_ms(1000);
//		}
//		else
//		{
//			motor(-30,-30);
//			delay_ms(800);
//			motor(-50,50);
//			delay_ms(500);
//		}
//	}
		EXTI_ClearITPendingBit(EXTI_Line4);
}
//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	//state=3;
//	printf("gg");
//	cmd=0;
//	zhidong(1);
//	if(bedge1==1)
//	{
//		delay_ms(100);
//		if(bedge2==1)
//		{
//			motor(30,30);
//			delay_ms(800);
//			motor(-50,50);
//			delay_ms(1000);
//		}
//		else
//		{
//			motor(30,30);
//			delay_ms(800);
//			motor(-50,50);
//			delay_ms(500);
//		}
//	}
	EXTI_ClearITPendingBit(EXTI_Line3); 
}
//外部中断4服务程序
void EXTI2_IRQHandler(void)
{
	//state=4;
//	printf("gg");
//	cmd=0;
//	zhidong(1);
//	if(bedge2==1)
//	{
//		delay_ms(100);
//		if(bedge1==1)
//		{
//			motor(30,30);
//			delay_ms(800);
//			motor(50,-50);
//			delay_ms(1000);
//		}
//		else
//		{
//			motor(30,30);
//			delay_ms(800);
//			motor(50,-50);
//			delay_ms(500);
//		}
//	}
	EXTI_ClearITPendingBit(EXTI_Line2); 
}
	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);//PE2 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);//PE3 连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource4);//PE4 连接到中断线4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource5);//PA0 连接到中断线0
	
  /* 配置EXTI_Line0 */
  /*EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置*/
	
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4 | EXTI_Line5;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 0变1
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}













