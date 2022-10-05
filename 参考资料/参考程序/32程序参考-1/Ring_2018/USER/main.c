#include "delay.h"
#include "myoled.h"
#include "oled.h"
#include "optoelectronic_switch.h"
#include "myoled.h"
#include "sumjess_pwm.h"
#include "sumjess_algor.h"


int flag=1;
void gotopk(void);

int main(void)
 {	
	 delay_init();    //延时初始化
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
   OLED_Init();			//初始化OLED  
	 OLED_Clear();    //oled清屏
	 speed_Init();    //电机初始化
	 optoelect_switch();//光电开关初始化
	 normal_oled(); //初始化正常  
	 delay_ms(2000);//延时停留时间
	 OLED_Clear();    //oled清屏
  while(1)
	{
	if(flag==1)          //上台标志位
	{ gotopk();flag=0;}  //上台
	
	
	  if((for_1==0||for_2==0||for_3==0)&&(back_1==0||back_2==0))    //前后都有障碍，掉下擂台
		   if(down_1==0||down_2==0||down_3==0)	{ drive_Back_H();  delay_ms(2000);  gotopk();}		//后面对着外墙，后退，然后开始冲上去
			 else   { drive_around();   drive_Back_H();  delay_ms(2000);  gotopk();}   //前面对着墙，掉头，后面对着外墙，后退，然后开始冲上去
	  else    algor_SUM_UP();    //未掉下擂台
	}
 }


void gotopk(void)
{
		TIM_SetCompare1(TIM3,5);	 //需要根据现实进行更改				 
		TIM_SetCompare2(TIM3,95);	 //需要根据现实进行更改
		TIM_SetCompare4(TIM3,95);	 //需要根据现实进行更改			 
		TIM_SetCompare3(TIM3,5);	 //需要根据现实进行更改
		delay_ms(100);            //需要根据现实进行更改
		TIM_SetCompare4(TIM2,5);	 //需要根据现实进行更改			 
		TIM_SetCompare3(TIM2,90);	 //需要根据现实进行更改
		delay_ms(500);	           //需要根据现实进行更改
		delay_ms(500);	           //需要根据现实进行更改
	//while(back_2==1){ ;}
		TIM_SetCompare4(TIM2,0);	 //需要根据现实进行更改			 
		TIM_SetCompare3(TIM2,0);	 //需要根据现实进行更改	
}








