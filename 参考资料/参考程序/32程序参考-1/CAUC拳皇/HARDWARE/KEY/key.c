//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//五轴按键驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#include "key.h"

/** 
	* @brief	按键初始化
	* @since	v1.0
	*/
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_6|GPIO_Pin_11;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}



/** 
	* @brief	扫描五个按键
	* @return	键值
	* @since	v1.0
	*/
u8 KEY_Scan()
{
	u8 value=0;
	if ( KEY_OK == 0 || KEY_BACK == 0 || KEY_UP == 0 || KEY_LEFT == 0 || KEY_DOWN == 0 || KEY_RIGHT == 0 )
	{
		delay_ms(10);
		if (KEY_UP 		== 0)value = K_UP;		//上键
		if (KEY_DOWN 	== 0)value = K_DOWN;	//下键
		if (KEY_LEFT 	== 0)value = K_LEFT;	//左键
		if (KEY_RIGHT	== 0)value = K_RIGHT;	//右键
		if (KEY_OK 		== 0)value = K_OK;		//确认
		if (KEY_BACK	== 0)value = K_BACK;	//返回
	}
	while( KEY_OK == 0 || KEY_BACK == 0 || KEY_UP == 0 || KEY_LEFT == 0 || KEY_DOWN == 0 || KEY_RIGHT == 0 );
	return value;
}



/** 
	* @brief	检测OK键是否被按下
	* @return	
			1：被按下
			0：未按下
	* @since	v1.0
	*/
u8 KEY_OK_Scan(void)
{
	if(KEY_OK == 0)
	{
		delay_ms(10);
		if(KEY_OK==0)
		{
			while(KEY_OK == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	检测BACK键是否被按下
	* @return	
			1：被按下
			0：未按下
	* @since	v1.0
	*/
u8 KEY_BACK_Scan(void)
{
	if(KEY_BACK == 0)
	{
		delay_ms(10);
		if(KEY_BACK==0)
		{
			while(KEY_BACK == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	检测UP键是否被按下
	* @return	
			1：被按下
			0：未按下
	* @since	v1.0
	*/
u8 KEY_UP_Scan(void)
{
	if(KEY_UP == 0)
	{
		delay_ms(10);
		if(KEY_UP==0)
		{
			while(KEY_UP == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	检测DOWN键是否被按下
	* @return	
			1：被按下
			0：未按下
	* @since	v1.0
	*/
u8 KEY_DOWN_Scan(void)
{
	if(KEY_DOWN == 0)
	{
		delay_ms(10);
		if(KEY_DOWN==0)
		{
			while(KEY_DOWN == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	检测LEFT键是否被按下
	* @return	
			1：被按下
			0：未按下
	* @since	v1.0
	*/
u8 KEY_LEFT_Scan(void)
{
	if(KEY_LEFT == 0)
	{
		delay_ms(10);
		if(KEY_LEFT==0)
		{
			while(KEY_LEFT == 0);
			return 1;
		}
	}
	return 0;
}



/** 
	* @brief	检测RIGHT键是否被按下
	* @return
			1：被按下
			0：未按下
	* @since	v1.0
	*/
u8 KEY_RIGHT_Scan(void)
{
	if(KEY_RIGHT == 0)
	{
		delay_ms(10);
		if(KEY_RIGHT==0)
		{
			while(KEY_RIGHT == 0);
			return 1;
		}
	}
	return 0;
}
