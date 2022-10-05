#ifndef __MOVE_H
#define __MOVE_H	 
#include "sys.h"
#include "delay.h"
//#include "sys.h"
#include "pwm.h"
#include "delay.h"



void duojiz(u16 dz);
void duojiy(u16 dy);
void allahead(u32 allah);
void ahead(u32 ah);
void  stop(void);
void back1(void);
void back2(void);
void back(u32 zuo,u32  you);
void diaotou(u32 d);
void diaotoul(void);
void diaotour(void);
void right(u32 r);
void left(u32 l);
void duojidown(void);
void duojiup(void);
void doorup(void);
	void doordown(void);
	void backST(u32  you);
	void aheadST(u32 ah);
#endif
