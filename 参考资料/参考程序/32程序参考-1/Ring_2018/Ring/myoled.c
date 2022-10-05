#include "myoled.h"
#include "oled.h"

void GD_oled(void)
{
	int a;
	//铲子
  a=up_for_lift;
	OLED_ShowNum( 0,0,a,1,12);
  a=up_for_right;
	OLED_ShowNum(18,0,a,1,12);
	up_back_left;
	OLED_ShowNum(36,0,a,1,12);
	a=up_back_right;
	OLED_ShowNum(54,0,a,1,12);
	
	//前
	a=for_1 ;
	OLED_ShowNum( 0,2,a,1,12);
  a=for_3;
	OLED_ShowNum(18,2,a,1,12);
	a=for_lift          ;
	OLED_ShowNum(36,2,a,1,12);
	a=for_right;
	OLED_ShowNum(54,2,a,1,12);
	
	//中
	a=left_1;
	OLED_ShowNum( 0,4,a,1,12);
  a=left_2;
	OLED_ShowNum(18,4,a,1,12);
	a=right_1;
	OLED_ShowNum(36,4,a,1,12);
	a=right_2;
	OLED_ShowNum(54,4,a,1,12);
	
	//后
	a=back_1;
	OLED_ShowNum( 0,6,a,1,12);
  a= back_2 ;
	OLED_ShowNum(18,6,a,1,12);
	a=back_lift;
	OLED_ShowNum(36,6,a,1,12);
	a= back_right;
	OLED_ShowNum(54,6,a,1,12);	
	
	delay_ms(800);//刷新时间
	OLED_Clear();//清屏
	
}
void normal_oled(void)
{
   	OLED_ShowCHinese(0,0,7);  //正
		OLED_ShowCHinese(18,0,8); //常
		OLED_ShowCHinese(36,0,9); //开
		OLED_ShowCHinese(54,0,10);//启
}
//void test_oled(void)
//{
//		OLED_ShowString(0,2,"KEY1");
//		OLED_ShowCHinese(36,2,11);//测
//		OLED_ShowCHinese(54,2,12);//试
//		OLED_ShowCHinese(72,2,13);//程
//		OLED_ShowCHinese(90,2,14);//序
//}
//void ranking_oled(void)
//{
//		OLED_ShowString(0,4,"KEY2");
//		OLED_ShowCHinese(36,4,15);//排
//		OLED_ShowCHinese(54,4,16);//位
//		OLED_ShowCHinese(72,4,17);//程
//		OLED_ShowCHinese(90,4,18);//序
//}
//void weedout_oled(void)
//{
//		OLED_ShowString(0,6,"KEY3");
//		OLED_ShowCHinese(36,6,19);//淘
//		OLED_ShowCHinese(54,6,20);//汰
//		OLED_ShowCHinese(72,6,21);//程
//		OLED_ShowCHinese(90,6,22);//序
//}
//void enter_test_oled(void)
//{
//		OLED_ShowCHinese(0,3,23);//进
//		OLED_ShowCHinese(18,3,24);//入
//		OLED_ShowCHinese(36,3,11);//测
//		OLED_ShowCHinese(54,3,12);//试
//		OLED_ShowCHinese(72,3,13);//程
//		OLED_ShowCHinese(90,3,14);//序
//}
//void enter_ranking_oled(void)
//{
//		OLED_ShowCHinese(0,3,23);//进
//		OLED_ShowCHinese(18,3,24);//入
//		OLED_ShowCHinese(36,3,15);//排
//		OLED_ShowCHinese(54,3,16);//位
//		OLED_ShowCHinese(72,3,17);//程
//		OLED_ShowCHinese(90,3,18);//序
//}
//void enter_weedout_oled(void)
//{
//		OLED_ShowCHinese(0,3,23);//进
//		OLED_ShowCHinese(18,3,24);//入
//		OLED_ShowCHinese(36,3,19);//淘
//		OLED_ShowCHinese(54,3,20);//汰
//		OLED_ShowCHinese(72,3,21);//程
//		OLED_ShowCHinese(90,3,22);//序
//}
//void pitch_oled(void)
//{
//		OLED_ShowCHinese(0,2,25);//俯
//		OLED_ShowCHinese(18,2,26);//仰
//		OLED_ShowCHinese(36,2,27);//角
//}
//void yaw_oled(void)
//{
//		OLED_ShowCHinese(0,4,28);//偏
//		OLED_ShowCHinese(18,4,29);//航
//		OLED_ShowCHinese(36,4,30);//角
//}
//void roll_oled(void)
//{
//		OLED_ShowCHinese(0,6,31);//翻
//		OLED_ShowCHinese(18,6,32);//滚
//		OLED_ShowCHinese(36,6,33);//角
//}
//void temp_oled(void)
//{
//		OLED_ShowCHinese(0,0,34);//温
//		OLED_ShowCHinese(18,0,35);//度
//}
//void zzsp_oled(void)
//{
//		OLED_ShowCHinese(0,4,36);//正
//		OLED_ShowCHinese(18,4,37);//在
//		OLED_ShowCHinese(36,4,38);//上
//		OLED_ShowCHinese(54,4,39);//坡
//}
//void cpu_oled(void)
//{
//		OLED_ShowCHinese(0,4,40);//内
//		OLED_ShowCHinese(18,4,41);//存
//		OLED_ShowCHinese(36,4,42);//占
//		OLED_ShowCHinese(54,4,43);//用
//		OLED_ShowCHinese(72,4,44);//率
//}
//void GDJC_oled(void)
//{
//	 	OLED_ShowString(0,0,"KEY1");
//		OLED_ShowCHinese(36,0,45);//光
//		OLED_ShowCHinese(54,0,46);//电
//		OLED_ShowCHinese(72,0,49);//检
//		OLED_ShowCHinese(90,0,50);//测
//}
//void FSJC_oled(void)
//{
//    OLED_ShowString(0,2,"KEY2");
//		OLED_ShowCHinese(36,2,51);//风
//		OLED_ShowCHinese(54,2,52);//扇
//		OLED_ShowCHinese(72,2,49);//检
//		OLED_ShowCHinese(90,2,50);//测
//}
//void HDJC_oled(void)
//{
//    OLED_ShowString(0,4,"KEY3");
//		OLED_ShowCHinese(36,4,53);//灰
//		OLED_ShowCHinese(54,4,54);//度
//		OLED_ShowCHinese(72,4,49);//检
//		OLED_ShowCHinese(90,4,50);//测
//}
//void enter_HDJC_oled(void)
//{
//		OLED_ShowCHinese(0,4,23);//进
//		OLED_ShowCHinese(18,4,24);//入
//		OLED_ShowCHinese(36,4,53);//灰
//		OLED_ShowCHinese(54,4,54);//度
//		OLED_ShowCHinese(72,4,49);//检
//		OLED_ShowCHinese(90,4,50);//测
//}
//void enter_GDJC_oled(void)
//{
//		OLED_ShowCHinese(0,0,23);//进
//		OLED_ShowCHinese(18,0,24);//入
//		OLED_ShowCHinese(36,0,45);//光
//		OLED_ShowCHinese(54,0,46);//电
//		OLED_ShowCHinese(72,0,49);//检
//		OLED_ShowCHinese(90,0,50);//测
//}
//void enter_FSJC_oled(void)
//{
//		OLED_ShowCHinese(0,2,23);//进
//		OLED_ShowCHinese(18,2,24);//入
//		OLED_ShowCHinese(36,2,51);//风
//		OLED_ShowCHinese(54,2,52);//扇
//		OLED_ShowCHinese(72,2,49);//检
//		OLED_ShowCHinese(90,2,50);//测
//}
//void GJMS_oled(void)
//{
//	 	OLED_ShowString(0,0,"KEY1");
//		OLED_ShowCHinese(36,0,55);//攻
//		OLED_ShowCHinese(54,0,56);//击
//		OLED_ShowCHinese(72,0,57);//模
//		OLED_ShowCHinese(90,0,58);//式
//}
//void FYMS_oled(void)
//{
//    OLED_ShowString(0,2,"KEY2");
//		OLED_ShowCHinese(36,2,59);//防
//		OLED_ShowCHinese(54,2,60);//御
//		OLED_ShowCHinese(72,2,57);//模
//		OLED_ShowCHinese(90,2,58);//式
//}
//void BBMS_oled(void)
//{
//    OLED_ShowString(0,4,"KEY3");
//		OLED_ShowCHinese(36,4,61);//半
//		OLED_ShowCHinese(54,4,62);//半
//		OLED_ShowCHinese(72,4,57);//模
//		OLED_ShowCHinese(90,4,58);//式
//}
//void enter_GJMS_oled(void)
//{
//		OLED_ShowCHinese(0,4,23);//进
//		OLED_ShowCHinese(18,4,24);//入
//		OLED_ShowCHinese(36,4,55);//攻
//		OLED_ShowCHinese(54,4,56);//击
//		OLED_ShowCHinese(72,4,57);//模
//		OLED_ShowCHinese(90,4,58);//式
//}
//void enter_FYMS_oled(void)
//{
//		OLED_ShowCHinese(0,0,23);//进
//		OLED_ShowCHinese(18,0,24);//入
//		OLED_ShowCHinese(36,0,59);//防
//		OLED_ShowCHinese(54,0,60);//御
//		OLED_ShowCHinese(72,0,57);//模
//		OLED_ShowCHinese(90,0,58);//式
//}
//void enter_BBMS_oled(void)
//{
//		OLED_ShowCHinese(0,2,23);//进
//		OLED_ShowCHinese(18,2,24);//入
//		OLED_ShowCHinese(36,2,61);//半
//		OLED_ShowCHinese(54,2,62);//半
//		OLED_ShowCHinese(72,2,57);//模
//		OLED_ShowCHinese(90,2,58);//式
//}







