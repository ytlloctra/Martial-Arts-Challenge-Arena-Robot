#include "debug.h"

u8 x,y;
extern u8 cmd,cmd1;
void change(u8 gg,u8 gg1)
{
	cmd=gg;
	x=gg1;
}
void change1(u8 gg,u8 gg1)
{
	cmd1=gg;
	y=gg1;
}
