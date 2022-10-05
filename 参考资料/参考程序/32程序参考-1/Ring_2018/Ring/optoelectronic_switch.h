#ifndef __OPTOELECTRONIC_SWITCH_H
#define __OPTOELECTRONIC_SWITCH_H	 
#include "optoelectronic_switch.h"
#include "sys.h"


#define   up_for_lift       GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define   up_for_right      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)     
#define   up_back_left      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_4)
#define   up_back_right     GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define   for_1             GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)
#define   for_2             GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)
#define   for_3             GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)
#define   back_1            GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)
#define   back_2            GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)
#define   left_1            GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)
#define   left_2            GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)
#define   right_1           GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)
#define   right_2           GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)
#define   for_lift          GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define   for_right         GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)
#define   back_lift         GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
#define   back_right        GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)
#define   down_1            GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)
#define   down_2            GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)
#define   down_3            GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)

void optoelect_switch(void);//GPIO≥ı ºªØ



#endif


