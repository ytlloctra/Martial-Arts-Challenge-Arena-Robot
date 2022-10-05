#ifndef __BUZZER_H
#define	__BUZZER_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  1
#define OFF 0

//#define BUZZER1(a)	if (a)	\
					GPIO_SetBits(GPIOC,GPIO_Pin_11);\
					else		\
					GPIO_ResetBits(GPIOC,GPIO_Pin_11)

//#define LED2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_14)



void BUZZER_GPIO_Config(void);
void BUZZER(u8 a);
void   song(u8 x);
#endif /* __BUZZER_H */
