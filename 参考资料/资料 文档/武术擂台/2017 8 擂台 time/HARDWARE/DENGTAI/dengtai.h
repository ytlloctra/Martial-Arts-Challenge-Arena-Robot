#ifndef __DENGTAI_H
#define __DENGTAI_H	
#include "sys.h" 
#include "motor.h"

void encoder_init(void);
void dengtai(void);
u16 read_encoder(void);
void qidong(void);
#endif
