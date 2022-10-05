#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"



#define a1 PAout(11)
#define a2 PAout(12)
#define b1 PAout(13)
#define b2 PAout(14)
#define z1 PCout(11)
#define z2 PCout(12)
#define x1 PCout(13)
#define x2 PCout(14)
#define s1 PCout(9)
#define s2 PCout(10)
void zhidong(u8 a);
void motor_init(void);
void motor(int zj,int zf);
void duoji(int pwm);
int abs(int a);
void siqu(void);
#endif

