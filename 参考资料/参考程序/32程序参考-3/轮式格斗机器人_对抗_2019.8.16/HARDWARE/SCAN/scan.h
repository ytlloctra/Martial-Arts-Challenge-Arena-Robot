#ifndef __scan_H
#define	__scan_H

#include "stm32f10x.h"

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define mm_ON  1
#define mm_OFF 0

void mm_scan_GPIO_Config(void);
u8 mm_scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
u8 key_get(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);
#endif /* __scan_H */
