/******************* ********************
 * 文件名  ：led.c
 * 描述    ：led 应用函数库
 *          
 * 实验平台：MINI STM32开发板 基于STM32F103C8T6
 * 硬件连接：-----------------
 *          |   PC13 - LED1   |
 *          |       
 *          |                 |
 *           ----------------- 
 * 库版本  ：ST3.0.0  																										  
*********************************************************/
#include "scan.h"
#include "delay.h"

//C6 up  D15 down D14 mid D13 left  D12 right
 /***************  配置LED用到的I/O口 *******************/
void mm_scan_GPIO_Config(void)	
{
 /* GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PC端口
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PC端口*/
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口
	GPIO_ResetBits(GPIOA, GPIO_Pin_13);	 // 关闭所有LED
	GPIO_ResetBits(GPIOA, GPIO_Pin_15);	 // 关闭所有LED
 
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口

RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化PC端口

}

u8 mm_scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			   
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mm_OFF ) 
	  	  
		return mm_OFF;
		
	else
		return mm_ON;
}
u8 key_get(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mm_OFF ) 
		{	
			delay_ms(20);	
			if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mm_OFF ) 
				return mm_ON;
			//else return mm_OFF;
		}
		//return mm_OFF;
		//else
		return mm_OFF;
}
/*GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	//选择对应的引脚//GPIO_Pin_0|
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口*/
