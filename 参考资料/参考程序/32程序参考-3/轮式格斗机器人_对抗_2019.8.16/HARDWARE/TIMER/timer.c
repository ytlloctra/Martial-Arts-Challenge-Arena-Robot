#include "timer.h"
#include "led.h"
#include "oled.h"
#define RIGHT_SHIFT  1//右移位数
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//通用定时器 驱动代码			   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/12/03
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 

//通用定时器中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!

unsigned char zheng_or_fan=0;
int time=0;
extern u32 temp_z1,//左一
		temp_z2,
		temp_z3,
		temp_z4,
		temp_z5,
		temp_z6,
		temp_y1,
		temp_y2,
		temp_y3,
		temp_y4,
		temp_y5,
		temp_y6,
		temp_Qz,//前上
		temp_Hz,//后中
		temp_back_H;
extern u16 value[15];
/*void TIM3_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}
*/

void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM2, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设
							 
}


void TIM2_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		//LED1=!LED1;
			//time++;
		time=ENC_Get_Electrical_Angle();	
		//	TIM_SetCounter(TIM4, 0);   // ?????CNT
		/*	if(time>20) 
			{
				GPIO_SetBits(GPIOA, GPIO_Pin_13);	 // 关闭所有LED
				GPIO_SetBits(GPIOA, GPIO_Pin_15);	 // 关闭所有LED
			}
			else 
			{
				GPIO_ResetBits(GPIOA, GPIO_Pin_13);	 // 关闭所有LED
				GPIO_SetBits(GPIOA, GPIO_Pin_15);	 // 关闭所有LED
			
			}
				if(time>40) time=0;*/
		}
}

int ENC_Get_Electrical_Angle(void)
{
 static  u16  lastCount = 0,lastdAngle=0;
 u16  curCount =TIM_GetCounter(TIM3);
  int dAngle = curCount - lastCount;
 if(dAngle<0)
	 {
   zheng_or_fan=2;//反转
  }
	 else if(dAngle>0)
		 {
   zheng_or_fan=1;//正转
 }
		 else  
{
   dAngle = 0;zheng_or_fan=0;//停
 }
 lastCount = curCount;
 if(abs(dAngle)>120) {dAngle=lastdAngle;lastCount=0;}
 lastdAngle=dAngle;
  return dAngle; 
}




void TIM5_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
//	TIM_ITConfig(  //使能或者失能指定的TIM中断
//		TIM5, //TIM2
//		TIM_IT_Update ,
//		ENABLE  //使能
//		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM5, ENABLE);  //使能TIMx外设
							 
}


void TIM5_IRQHandler(void)  {
	u8 i;

for(i=0;i<2;i++)
				{
					temp_z1=(value[5]>>RIGHT_SHIFT)+temp_z1;//   
					temp_z2=(value[4]>>RIGHT_SHIFT)+temp_z2;//    
					temp_z3=(value[3]>>RIGHT_SHIFT)+temp_z3;//   
					temp_z4=(value[2]>>RIGHT_SHIFT)+temp_z4;//    
					temp_z5=(value[1]>>RIGHT_SHIFT)+temp_z5;//     
					temp_z6=(value[0]>>RIGHT_SHIFT)+temp_z6;//      
					temp_y1=(value[6]>>RIGHT_SHIFT)+temp_y1;//     
					temp_y2=(value[7]>>RIGHT_SHIFT)+temp_y2;//  
					temp_y3=(value[8]>>RIGHT_SHIFT)+temp_y3;//   
					temp_y4=(value[9]>>RIGHT_SHIFT)+temp_y4;//  
					temp_y5=(value[10]>>RIGHT_SHIFT)+temp_y5;// 
					temp_y6=(value[11]>>RIGHT_SHIFT)+temp_y6;//
					temp_Qz=(value[13]>>RIGHT_SHIFT)+temp_Qz;//
					temp_Hz=(value[12]>>RIGHT_SHIFT)+temp_Hz;//
					temp_back_H=(value[14]>>RIGHT_SHIFT)+temp_back_H;//
				}

}




