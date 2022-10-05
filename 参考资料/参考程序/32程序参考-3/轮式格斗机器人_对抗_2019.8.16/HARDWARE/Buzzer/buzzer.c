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
#include "buzzer.h"
#include "delay.h"

 /***************  配置LED用到的I/O口 *******************/

void BUZZER_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE); // 使能PC端口时钟  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_6;	//选择对应的引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  //初始化PC端口
	GPIO_Init(GPIOE, &GPIO_InitStructure);  //初始化PC端口
  GPIO_ResetBits(GPIOD, GPIO_Pin_8);
	GPIO_SetBits(GPIOD, GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11);	 // 关闭所有LED
	GPIO_SetBits(GPIOE, GPIO_Pin_6);	
	
}

void BUZZER(u8 a)
{
	        if (a)	
					{
						GPIO_SetBits(GPIOD,GPIO_Pin_8);
					//delay_ms(200);
					}
					else		
					GPIO_ResetBits(GPIOD,GPIO_Pin_8);
	

}
void  song(u8 x)
{
	if(x>100) x=100;
	GPIO_SetBits(GPIOD,GPIO_Pin_4);
	delay_ms(x);
	GPIO_ResetBits(GPIOD,GPIO_Pin_4);
	delay_ms(100-x);
}
