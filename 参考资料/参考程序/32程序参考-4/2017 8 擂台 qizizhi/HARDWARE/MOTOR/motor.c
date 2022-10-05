#include "sys.h"
#include "motor.h"
#include "delay.h"
void motor_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);//Ê¹ÄÜGPIOFÊ±ÖÓ

  //GPIOF9,F10³õÊ¼»¯ÉèÖÃ
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//ÆÕÍ¨Êä³öÄ£Ê½
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//ÍÆÍìÊä³ö
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//ÉÏÀ­
  GPIO_Init(GPIOA, &GPIO_InitStructure);//³õÊ¼»
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13| GPIO_Pin_14;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void motor(int zj,int zf)
{
	if(zj>0)
	{
		a1=0;
		a2=1;
		b1=0;
		b2=1;
		TIM_SetCompare1(TIM4,zj);
		TIM_SetCompare1(TIM3,zj);
	}
 else
	{
		a1=1;
		a2=0;
		b1=1;
		b2=0;
		TIM_SetCompare1(TIM4,-zj);
		TIM_SetCompare1(TIM3,-zj);
	}
	if(zf>0)//
	{
		z1=1;
		z2=0;
		x1=1;
		x2=0;
		TIM_SetCompare3(TIM4,zf);
		TIM_SetCompare4(TIM4,zf);
	}
	else
	{
		z1=0;
		z2=1;
		x1=0;
		x2=1;
		TIM_SetCompare3(TIM4,-zf);
		TIM_SetCompare4(TIM4,-zf);
	}
}
void zhidong(u8 a)
{
	if(a)
	{
		a1=0;a2=0;b1=0;b2=0;
		z1=0;z2=0;x1=0;x2=0;
	}
	else
	{
		s1=0;s2=0;
	}
}
void duoji(int pwm)
{
	s1=1;
	s2=0;
	TIM_SetCompare1(TIM12,pwm);
}
int abs(int a)
{
	if(a<0)
	{
		return -a;
	}
	return a;
}
void siqu(void)
{
	zhidong(1);
	delay_ms(10);
}

