//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//华北五省机器人大赛-武术擂台程序
//编者：徐天泽
//版本：V3.3
//修改日期:2018/10/07
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#include "car_system.h"
#include "menu.h"
#include "attack.h"
#include "data.h"

/*全局变量声明*/
CAR_PWM				MOTOR_PWM;
ADC_THRESHOLD		EYE_THRESHOLD;
CAR_SPEED			ENCODER_VALUE;
CAR_SUNDRY			SETTING_SUNDRY;	
extern MENU_PAGE	HOMEPAGE;

/*主函数*/
int main()
{
	/*键值*/
	u8 key_value;

	/*初始化后台*/
	NVIC_Configuration();
	delay_init();
	LED_Init();	
	KEY_Init();	
	SENSORS_Init();	
	BUZZER_Init();
	ENCODER_Init();	
	MOTOR_Init();
	ADC1_Init();
	DMA1_Channel1_Init();

	/*初始化前台*/
	SOLGUI_Init(&HOMEPAGE);	

	/*读取flash数据*/
	Load_ALLData();	
	
	/*OLED显示LOGO*/
	OLED_ShowLogo();

	/*按任意键进入系统*/
	while(!KEY_Scan());
	
	/*建立超级循环，刷新前台GUI界面完成人机交互*/
	while(1)
	{
		key_value=KEY_Scan();
		SOLGUI_InputKey(key_value);
		SOLGUI_Menu_PageStage();
		SOLGUI_Refresh();
	}
}
