#include<move.h>
#include<oled.h>
u32 GROUP=0 ; //1Œ™“ª∂”£¨0Œ™∂˛∂”
u32 a=600,b=0,c=720,d=540,MAXPWM=1700;
void allahead(u32 allah)  //
{
	if(allah>MAXPWM)
	{
	TIM_SetCompare1(TIM1,0);//B6             x/1800
	TIM_SetCompare2(TIM1,0);//B7
	TIM_SetCompare3(TIM1,0);//B8
	TIM_SetCompare4(TIM1,0);//B9
		while(1)
		{
				OLED_ShowNum(26,4,0000,4,12);
		}
	}
	else
  {
	TIM_SetCompare1(TIM1,b);//B6             x/1800
	TIM_SetCompare2(TIM1,allah);//B7
	TIM_SetCompare3(TIM1,allah);//B8
	TIM_SetCompare4(TIM1,b);//B9
	}
}
void ahead(u32 ah)   //?±µ‡?˘?Ë
{
	if(ah>MAXPWM)
	{
	TIM_SetCompare1(TIM1,0);//B6             x/1800
	TIM_SetCompare2(TIM1,0);//B7
	TIM_SetCompare3(TIM1,0);//B8
	TIM_SetCompare4(TIM1,0);//B9
		while(1)
		{
				OLED_ShowNum(26,4,0000,4,12);
		}
	}
	else
	{
  TIM_SetCompare1(TIM1,b);//a8    c=720   zuo
	TIM_SetCompare2(TIM1,ah);//a9
	TIM_SetCompare3(TIM1,ah);//a10          you
	TIM_SetCompare4(TIM1,b);//a11
	}
}
void  stop(void)
{	
  TIM_SetCompare1(TIM1,0);//B6
	TIM_SetCompare2(TIM1,0);//B7
	TIM_SetCompare3(TIM1,0);//B8
	TIM_SetCompare4(TIM1,0);//B9
}


void back(u32 zuo,u32  you)
{  
	if(zuo>MAXPWM||you>MAXPWM)
	{
	TIM_SetCompare1(TIM1,0);//B6             x/1800
	TIM_SetCompare2(TIM1,0);//B7
	TIM_SetCompare3(TIM1,0);//B8
	TIM_SetCompare4(TIM1,0);//B9
		while(1)
		{
				OLED_ShowNum(26,4,0000,4,12);
		}
	}
	else
	{
	TIM_SetCompare1(TIM1,zuo);//B6
	TIM_SetCompare2(TIM1,b);//B7     540
	TIM_SetCompare3(TIM1,b);//B8    600
	TIM_SetCompare4(TIM1,you);//B9
	//delay_ms(1500);
	}
}



		
void right(u32 r)
{
			if(r>MAXPWM)
	{
	TIM_SetCompare1(TIM1,0);//B6             x/1800
	TIM_SetCompare2(TIM1,0);//B7
	TIM_SetCompare3(TIM1,0);//B8
	TIM_SetCompare4(TIM1,0);//B9
		while(1)
		{
				OLED_ShowNum(26,4,0000,4,12);
		}
	}
	else
	{
	 TIM_SetCompare1(TIM1,b);//B6
	TIM_SetCompare2(TIM1,r);//B7
	TIM_SetCompare3(TIM1,b);//B8
	TIM_SetCompare4(TIM1,r);//B9
	}
}
	
void left(u32 l)
{
				if(l>MAXPWM)
	{
	TIM_SetCompare1(TIM1,0);//B6             x/1800
	TIM_SetCompare2(TIM1,0);//B7
	TIM_SetCompare3(TIM1,0);//B8
	TIM_SetCompare4(TIM1,0);//B9
		while(1)
		{
				OLED_ShowNum(26,4,0000,4,12);
		}
	}
	else
	{
	 TIM_SetCompare1(TIM1,l);//B6   a=720
	TIM_SetCompare2(TIM1,b);//B7     b=180
	TIM_SetCompare3(TIM1,l);//B8
	TIM_SetCompare4(TIM1,b);//B9
	}
}	

void backST(u32  you)
{  
	if(you>MAXPWM)
	{
	
	TIM_SetCompare3(TIM4,0);//B8
	TIM_SetCompare4(TIM4,0);//B9
		while(1)
		{
				OLED_ShowNum(26,4,0000,4,12);
		}
	}
	else
	{

	TIM_SetCompare3(TIM4,b);//B8    600
	TIM_SetCompare4(TIM4,you);//B9
	//delay_ms(1500);
	}
}
void aheadST(u32 ah)   //?±µ‡?˘?Ë
{
	if(ah>MAXPWM)
	{
	
	TIM_SetCompare3(TIM4,0);//B8
	TIM_SetCompare4(TIM4,0);//B9
		while(1)
		{
				OLED_ShowNum(26,4,0000,4,12);
		}
	}
	else
	{
  
	TIM_SetCompare3(TIM4,ah);//B8           you
	TIM_SetCompare4(TIM4,b);//B9TIM4_CH4”√¿¥						
	}
}
