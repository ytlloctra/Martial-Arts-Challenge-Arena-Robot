#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"


void MYDMA_Config(DMA_Channel_TypeDef *DMA_CHx,u32 cpar,u32 cmar,u16 cndtr);//≈‰÷√DMA1_CHx
void DMA1_Channel1_IRQHandler(void);
void MYDMA_Enable(DMA_Channel_TypeDef *DMA_CHx);// πƒ‹DMA1_CHx
		   
#endif
