#include "sumjess_pwm.h"

/*******************************************************************************
================================================================================
【平    台】stm32f103zet6_sumjess平台
【编    写】sumjess
【E-mail  】1371129880@qq.com
【软件版本】V2.0
【最后更新】2018年09月06日
【相关信息参考下列地址】
【网    站】
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
【dev.env.】MDK5.14及以上版本
【Target  】stm32f103zet6
第一次修订：2017/11/09
第二次修订：2018/01/21
第三次修订：2018/09/06
【problem 】
    （1）库内补充的不全面；
    （2）库内解释部分不全面；
    （3）库内还存在一定的bug；
【direction】
      下一步的目标就是把库继续集成！
【explain 】
      本库是根据正点原子、中景园电子、优信电子等商家改编而成，
      同时为了方便使用，我也自己写了很多的库，和优化了算法和表示方式！
【warning】
      目前程序中暂无警告 ！   
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================
********************************************************************************/	
//PWM 驱动代码
////////////////////////////////////////////////////////////////////////////////// 	  
///////映射的内容在timer.c中///////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

int a=0,b=0,c=0,d=0;


void speed_Init(void)    //TIM3_CH1->PC6 CH2->PC7 CH3->PC8 CH4->PC9
{ 
		//**********电机驱动设置************//
		TIM_OCInitTypeDef  TIM_OCInitStructure;
		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure ;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟  
		TIM_DeInit(TIM3);//初始化TIM3寄存器
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟  
		TIM_DeInit(TIM2);//初始化TIM3寄存器
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //Timer3完全重映射  TIM3_CH1->PC6 CH2->PC7 CH3->PC8 CH4->PC9
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //TIM1_CH1  //设置该引脚为复用输出功能,输出TIM3 CH1的PWM脉冲波形 GPIOC.6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO                
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;//TIM1_CH1  //设置该引脚为复用输出功能,输出TIM3 CH1的PWM脉冲波形 GPIOC.6
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO                	
		//**************************************************************************
		//  定时器1设置： 72分频，频率10KHz，向上计数,105是为了速度为100时，PWM占空比不会到100，方便电机驱动自举生压。一般PWM频率大于1K，4-10K比较好。
		//************************************************************************** 
		TIM_TimeBaseStructure.TIM_Period = 105-1;
		TIM_TimeBaseStructure.TIM_Prescaler = 71;
		TIM_TimeBaseStructure.TIM_ClockDivision = 0;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 
		// 主定时器T3为 PWM3 模式 
		TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStructure.TIM_Pulse = 0;  
		TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC1Init(TIM3, &TIM_OCInitStructure);			
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能的预装载寄存器
 
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC2Init(TIM3, &TIM_OCInitStructure); 
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能的预装载寄存器
 
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC3Init(TIM3, &TIM_OCInitStructure); 
		TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能的预装载寄存器
 
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC4Init(TIM3, &TIM_OCInitStructure); 
		TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能的预装载寄存器
 
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC3Init(TIM2, &TIM_OCInitStructure); 
		TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能的预装载寄存器
		
		TIM_OCInitStructure.TIM_Pulse = 0; 
		TIM_OC4Init(TIM2, &TIM_OCInitStructure); 
		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);//使能的预装载寄存器			
 
		TIM_ARRPreloadConfig(TIM3, ENABLE); //使能定时器3
		TIM_Cmd(TIM3, ENABLE);
		TIM_ARRPreloadConfig(TIM2, ENABLE); //使能定时器3
		TIM_Cmd(TIM2, ENABLE);
}

void drive_around(void)
{
   a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,5);
	TIM_SetCompare2(TIM3,95);
//右边
	TIM_SetCompare3(TIM3,95);
	TIM_SetCompare4(TIM3,5);

}

void drive_For_L(void)
{
     a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,30);
//右边
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,30);

}

void drive_For_M(void)
{
     a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,90);
//右边
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,90);

}

void drive_For_H(void)
{
   if(a<500)
	 {
//左边
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,55);
//右边
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,55);
		 ++a;
	 }
	 else{
//左边
	TIM_SetCompare1(TIM3,5);
	TIM_SetCompare2(TIM3,95);
//右边
	TIM_SetCompare3(TIM3,5);
	TIM_SetCompare4(TIM3,95);
	 }
}


void drive_Back_L(void)
{
	 a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,30);
	TIM_SetCompare2(TIM3,10);
//右边
	TIM_SetCompare3(TIM3,30);
	TIM_SetCompare4(TIM3,10);
}

void drive_Back_M(void)
{
	 a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,90);
	TIM_SetCompare2(TIM3,10);
//右边
	TIM_SetCompare3(TIM3,90);
	TIM_SetCompare4(TIM3,10);
}

void drive_Back_H(void)
{
	if(b<500) {
//左边
	TIM_SetCompare1(TIM3,50);
	TIM_SetCompare2(TIM3,10);
//右边
	TIM_SetCompare3(TIM3,50);
	TIM_SetCompare4(TIM3,10);
		++b;
	}
	else{
//左边
	TIM_SetCompare1(TIM3,95);
	TIM_SetCompare2(TIM3,5);
//右边
	TIM_SetCompare3(TIM3,95);
	TIM_SetCompare4(TIM3,5);
	}
	
}

void drive_Left(void)
{
	 a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,20);
//右边
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,80);
}

void drive_Right(void)
{
	 a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,80);
//右边
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,20);
}

void drive_Stop(void)
{
	 a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,10);
//右边
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,10);
}

void drive_Left_M(void)
{
	 a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,20);
//右边
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,50);
}

void drive_Right_M(void)
{
	 a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,50);
//右边
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,20);
}

void drive_Left_S(void)
{
	 a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,70);
	TIM_SetCompare2(TIM3,10);
//右边
	TIM_SetCompare3(TIM3,10);
	TIM_SetCompare4(TIM3,70);
}

void drive_Right_S(void)
{
	 a=0;b=0;
//左边
	TIM_SetCompare1(TIM3,10);
	TIM_SetCompare2(TIM3,70);
//右边
	TIM_SetCompare3(TIM3,70);
	TIM_SetCompare4(TIM3,10);
} 

