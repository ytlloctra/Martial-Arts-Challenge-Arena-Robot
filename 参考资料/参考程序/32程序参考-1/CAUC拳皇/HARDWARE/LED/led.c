//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//LED驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#include "led.h"

/** 
	* @brief	LED初始化
	* @since	v1.0
	*/
void  LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  GPIO_ResetBits(GPIOD,GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11); 
}



/** 
	* @brief	LED亮起某一盏灯
	* @param	number	需要亮起的灯序号
	* @since	v1.0
	*/
void LED_Show(u8 number)
{
	switch(number)
	{
		case 1:
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_SetBits(GPIOD,GPIO_Pin_9);
		break;
		case 2:
		GPIO_ResetBits(GPIOD,GPIO_Pin_11); 
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_SetBits(GPIOD,GPIO_Pin_9);
		break;  
		case 3:
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);
		GPIO_SetBits(GPIOD,GPIO_Pin_9);
		break;  
		case 4:
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);
		GPIO_SetBits(GPIOD,GPIO_Pin_9);
		break;  
		case 5:
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_9);
		break; 
		case 6:
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_9);
		break;  
		case 7:
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_9);
		break;   
		case 8:
		GPIO_ResetBits(GPIOD,GPIO_Pin_11);
		GPIO_ResetBits(GPIOD,GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,GPIO_Pin_9);
		break;  
		default:
		GPIO_SetBits(GPIOD,GPIO_Pin_11);
		GPIO_SetBits(GPIOD,GPIO_Pin_10);
		GPIO_SetBits(GPIOD,GPIO_Pin_9);
		break;
	}
}



/** 
	* @brief	LED流水灯提示
	* @param	direction	流水灯方向
	* @param	time			流水灯时间
	* @since	v1.0
	*/
void LED_Flow(u8 direction,u16 time)
{
	char i;
	if(direction==0)
		for(i=1;i<=8;i++)
		{
			LED_Show(i);
			delay_ms(time/8);
		}
	else
		for(i=8;i>=1;i--)
		{
			LED_Show(i);
			delay_ms(time/8);
		}
}
