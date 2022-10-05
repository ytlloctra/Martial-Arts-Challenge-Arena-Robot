#include "timer.h"
#include "usart.h"
#include "motor.h"
#include "math.h"
#include "edge.h"
#include "debug.h"
#include "dengtai.h"

#define UPWARD (1400)//1400
#define UPWARD1 (1400)
#define FRONT (1300)//1600
#define BACK (1300)
#define SIDE (1400)
#define SCALE (3700)//huidu  1700是边缘灰度值
#define SCALE1 (2600)
//未加的，后退后转向优先级低于检测，末尾测距过于小直接加速逃跑，推人时光电检测到后退至中央
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//定时器 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/4
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
u8 cmd=0,cmd1,state=0,gg=5,np=0,i=0,step=0,test=0,attack=0,a=1;
u16 rid;
int count=0,count1=0,count2=0;
double angle;
int run=0,np1=0,np2=0;
extern u16 juli[16];
extern u8 state;
extern u8 x,y;
const u16 fazhi[11]={UPWARD,UPWARD,FRONT,FRONT,SIDE,SIDE,SIDE,SIDE,BACK,BACK,BACK};
void TIM2_init(u32 arr,u32 psc)
{		 					 
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///??TIM3??
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//???TIM3
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //?????3????
	 //?????3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //???3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x01; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}
void TIM2_IRQHandler(void)//灰度产生方向仅做参考，只是返回
{
	u8 i=0;
//	for(i=10;i<14;i++)
//		{
//			if(juli[i]<SCALE)
//			{
//				np=12;
//				break;
//			}
//			np=22;
//		}
//	rid=(juli[11]+juli[14]+juli[12]+juli[13])/4;
//	if(attack==2)
//		{
//			np=0;
//		}
//		else
//		{
			if((juli[11]<SCALE))
			{
				np=15;//12
				if((juli[11]<SCALE1)||(juli[12]<SCALE1))
					{
						if(juli[12]>juli[11]+300)
							state=1;
						else
							{if(juli[11]>juli[12]+300)state=2;}
					}
				else state=0;
			}
			else
			{
				np=30;//25
				//state=0;
			}
		
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);  //???????
}
void TIM5_init(u32 arr,u32 psc)
{		 					 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  ///??TIM3??
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//??????
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);//???TIM3
	
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //?????3????
	 //?????3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM5_IRQn; //???3??u
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM5, ENABLE);
}

void TIM5_IRQHandler(void)
{	
	if(count>0)
	{
		count--;
	}
	else
	{
		if(count1>0)
		{
			count1--;
			motor(np1,np1);
		}
		else
		{
			if(count2>0)
			  {
				count2--;
				motor(np2,-np2);
			  }
			else
			  {
				if(test)//test
					{
						switch(step)     //step
							{//2000
								case 0:if(juli[13]<2000){motor(40,-40);}else {motor(-30,-30);count=300;np1=30;count1=140;step=5;}break;//向后对向前对
								//这里分几种情况，01都没检测到，回到直行一段回到0 0或1检测到，拐直行拐，检测
								case 5:if((juli[0]>3000)&&(abs((int)(juli[1]-juli[0]))<250)){if(juli[13]<1100){motor(-30,30);count=100;}else {step=4;}}
											else 
												{
													if(juli[13]<1100){motor(-30,30);count=100;}
													else{
													if((juli[0]<1000)||(juli[1]<1000))
														{
															if(juli[6]>2500){motor(10,30);count=150;}
															else if(juli[7]>2500){motor(30,10);count=150;}
														}
													else{count=70;motor(25,25);count1=57;np1=-15;count2=10;np2=0;step=5;}
														}
												}
												break;
								case 4:if((juli[2]>2800)&&(abs((int)(juli[2]-juli[3]))<500))
											{step=1;}
										else 
										{
											if(juli[2]<1000)
												{count=130;motor(-30,30);count1=100;np1=25;count2=130;np2=30;}
												else{
											if(juli[3]<1000)
												{count=130;motor(30,-30);count1=100;np1=25;count2=130;np2=-30;}
											}
												step=5;
									};break;
								case 1:motor(0,0);duoji(60);count=50;step=6;break;
								case 6:duoji(15);count=50;step=2;break;
								case 2:motor(90,90);duoji(99);count=72;step=3;break;
								case 3:zhidong(0);motor(20,20);count=90;test=0;step=0;break;
							}
						}
				else
					{
				if(juli[0]>fazhi[0])
					{
						if(juli[10]>1400){test=1;}else {test=0;}  //此距离参考离墙最大值
						if(juli[1]>fazhi[1]){cmd=12;}
						else {cmd=1;}
					}
				else
					{
						if(juli[1]>fazhi[1]){cmd=13;}
						else 
							{
								for(i=2;i<11;i++)
									{
										if(juli[i]>fazhi[i])
											{
												cmd=i;
												break;
											}
										cmd=0;
									}
							}
					}
			switch(cmd)
			{
				case 12:motor(np+20,np+20);attack=1;break;//attack 50 50  np+30,np+30,+10
				case 0:motor(np,np);break;//normal  15,30
				case 8:motor(70,-70);count=25;attack=0;break;//count=5,70
				case 9:motor(-70,70);count=25;attack=0;break;//count=5
				case 1:motor(np+15,np+25);count=6;attack=0;break; //np+15,np+25,+5
				case 13:motor(np+25,np+15);count=6;attack=0;break;//
				case 10:motor(-70,70);count=30;attack=0;break;
				case 2:motor(70,-70);count=10;attack=0;break;//count=2  40
				case 3:motor(-70,70);count=10;attack=0;break;//count=2  40
				case 4:if(juli[5]>1500){test=1;}else {test=0;}motor(70,-70);count=20;attack=0;break;//count=3
				case 5:motor(-70,70);count=20;attack=0;break;//count=3
				case 6:motor(70,-70);count=23;attack=0;break;//count=4
				case 7:motor(-70,70);count=23;attack=0;break;//count=4
			}//此方法在寻找敌人过程中，继续检测，可以换成旋转一定角度，待实验，原来的没有转角限制，可能限制速度，停止就是前面检测到。
			switch(state)
			{
				case 0:{}break;
				case 1:
						//if(attack==1){motor(-20,-20);count=500;attack=2;}else 
						{count1=70;count2=95;np1=-45;np2=60;count=5;motor(0,0);}break;//count1=2;count2=14;np1=-40;np2=50;count=1;motor(0,0);
				case 2:count=5;motor(50,50);break;
			}
			switch(EDGE&0X80b)//EDGE&0X80b
				{
					case 0:{}break;
					case 0x808:motor(55,55);count=4;break;//count1=6;count2=7;np1=50;np2=50;count=2;
					case 0x08:motor(45,65);count=4;break;//count1=6;count2=5;np1=50;np2=-50;count=2;
					case 0x800:motor(65,45);count=4;break;//count1=6;count2=5;np1=50;np2=50;count=2;
					case 0x3:
							//if(attack==1){motor(-20,-20);count=10;attack=2;}else 
								{motor(0,0);count1=80;count2=85;np1=-45;np2=-55;count=5;}break;//count1=6;count2=7;np1=-50;np2=-50;count=2;
					case 0x02:motor(0,0);count1=75;count2=70;np1=-45;np2=55;count=5;break;//count1=6;count2=5;np1=-50;np2=-50;count=2;
					case 0x01:motor(0,0);count1=75;count2=70;np1=-45;np2=-55;count=5;break;//count1=6;count2=5;np1=-50;np2=50;count=2;
				}
			
				}
			}
		}
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);  //???????
}
	

void TIM12duoji_init(u16 arr,u32 psc)
{		 					 
	//????????IO???
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM14????    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//??PORTF??	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12); //GPIOF9??????14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//??100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //??
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //???PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseStructure.TIM_Period=arr;   //??????
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);//??????14
	
	//???TIM14 Channel1 PWM??	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //???????:TIM????????2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //????:TIM???????
	TIM_OC1Init(TIM12, &TIM_OCInitStructure);  //??T??????????TIM1 4OC1

	TIM_OC1PreloadConfig(TIM12, TIM_OCPreload_Enable);  //??TIM14?CCR1????????
 
  TIM_ARRPreloadConfig(TIM12,ENABLE);//ARPE?? 
	
	TIM_Cmd(TIM12, ENABLE);  //??TIM14
 
										  
}  
void TIM4motor_init(u16 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM14???? 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); 	//??PORTF??	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4); //GPIOF9??????14
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_TIM3);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_4|GPIO_Pin_8|GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//??100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //??
	GPIO_Init(GPIOB,&GPIO_InitStructure);              //???PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseStructure.TIM_Period=arr;   //??????
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//??????14
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	//???TIM14 Channel1 PWM??	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //???????:TIM????????2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //??????
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //????:TIM???????
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //??T??????????TIM1 4OC1
	TIM_OC1Init(TIM3, &TIM_OCInitStructure); 
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); 
	

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //??TIM14?CCR1????????
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_SetCompare1(TIM4,0);
	TIM_SetCompare1(TIM3,0);
	TIM_SetCompare3(TIM4,0);
	TIM_SetCompare4(TIM4,0);
 
  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE?? 
	TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE?? 
	
	TIM_Cmd(TIM4, ENABLE);  //??TIM14
	TIM_Cmd(TIM3, ENABLE);  //??TIM14
}


  

/*TIM_ICInitTypeDef  TIM5_ICInitStructure;

//定时器5通道1输入捕获配置
//arr：自动重装值(TIM2,TIM5是32位的!!)
//psc：时钟预分频数
void TIM5_CH1_Cap_Init(u32 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//使能PORTA时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0复用位定时器5
  
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
	

	//初始化TIM5输入捕获参数
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
  TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
  TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  TIM5_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  TIM_ICInit(TIM5, &TIM5_ICInitStructure);
		
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断	
	
  TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5

 
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、
	
	
}
//捕获状态
//[7]:0,没有成功的捕获;1,成功捕获到一次.
//[6]:0,还没捕获到低电平;1,已经捕获到低电平了.
//[5:0]:捕获低电平后溢出的次数(对于32位定时器来说,1us计数器加1,溢出时间:4294秒)
u8  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值(TIM2/TIM5是32位)
//定时器5中断服务程序	 
void TIM5_IRQHandler(void)
{ 		    

 	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{
		if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)//溢出
		{	     
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到高电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//高电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFFFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个下降沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次高电平脉宽
			  TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//获取当前的捕获值.
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
				TIM_Cmd(TIM5,DISABLE ); 	//关闭定时器5
	 			TIM_SetCounter(TIM5,0);
	 			TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling);		//CC1P=1 设置为下降沿捕获
				TIM_Cmd(TIM5,ENABLE ); 	//使能定时器5
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}*/

