#include "exti.h"
#include "delay.h" 
#include "edge.h"
#include "motor.h"
#include "timer.h"
#include "usart.h"
#define z (800)//800
#define x (700)//900
#define y (500)//500
extern u8 zisuo,zisuo1,cmd;
//////////////////////////////////////////////////////////////////////////////////	 
 
//外部中断 驱动代码	   
//STM32F4工程-库函数版本
//淘宝店铺：http://mcudev.taobao.com									  
////////////////////////////////////////////////////////////////////////////////// 

//外部中断0服务程序
void EXTI15_10_IRQHandler(void)
{
	if(bedge1==1)
	{
		zhidong(1);
		delay_ms(100);
		if(bedge2==1)
		{
			motor(40,40);//40
			delay_ms(z);
			siqu();
			motor(50,-50);//50
			delay_ms(x);
			siqu();
		}
		else
		{
			motor(40,40);
			delay_ms(z);
			siqu();
			motor(50,-50);
			delay_ms(y);
			siqu();
		}
		cmd=0;
		zisuo=0;
		zisuo1=0;
		motor(20,20);
		return;
	}
	EXTI_ClearITPendingBit(EXTI_Line11); 
}	
//外部中断1服务程序
void EXTI3_IRQHandler(void)
{
	if(bedge2==1)
	{
		zhidong(1);
		delay_ms(100);
		if(bedge1==1)
		{
			motor(40,40);
			delay_ms(z);siqu();
			motor(-50,50);
			delay_ms(x);siqu();
		}
		else
		{
			motor(40,40);
			delay_ms(z);siqu();
			motor(-50,50);
			delay_ms(y);siqu();
		}
		cmd=0;
		zisuo=0;
		zisuo1=0;
		motor(20,20);
		return;
	}
		EXTI_ClearITPendingBit(EXTI_Line3);
}
//外部中断3服务程序
void EXTI1_IRQHandler(void)
{
	if(fedge1==1)
	{
		zhidong(1);
		delay_ms(100);
		if(fedge2==1)
		{
			motor(-40,-40);
			delay_ms(z);siqu();
			motor(50,-50);
			delay_ms(x);siqu();
		}
		else
		{
			motor(-40,-40);
			delay_ms(z);siqu();
			motor(50,-50);
			delay_ms(y);siqu();
		}
		cmd=0;
		zisuo=0;
		zisuo1=0;
		motor(20,20);
		return;
	}
	EXTI_ClearITPendingBit(EXTI_Line1); 
}
//外部中断4服务程序
void EXTI0_IRQHandler(void)
{
	if(fedge2==1)
	{
		zhidong(1);
		delay_ms(100);
		if(fedge1==1)
		{
			motor(-40,-40);
			delay_ms(z);siqu();
			motor(-50,50);
			delay_ms(x);siqu();
		}
		else
		{
			motor(-40,-40);
			delay_ms(z);siqu();
			motor(-50,50);
			delay_ms(y);siqu();
		}
		cmd=0;
		zisuo=0;
		zisuo1=0;
		motor(20,20);
		return;
	}
	EXTI_ClearITPendingBit(EXTI_Line0); 
}
	   
//外部中断初始化程序
//初始化PE2~4,PA0为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);//PE2 连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource1);//PE3 连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);//PE4 连接到中断线4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource11);//PA0 连接到中断线0
	
  /* 配置EXTI_Line0 */
  /*EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置*/
	
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line1 | EXTI_Line0 | EXTI_Line3 | EXTI_Line11;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 0变1
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//中断线使能
  EXTI_Init(&EXTI_InitStructure);//配置
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断2
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级3
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;//外部中断3
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级2
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//外部中断4
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//抢占优先级1
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	   
}













