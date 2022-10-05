#include "sumjess_algor.h"
#include "optoelectronic_switch.h"
#include "sumjess_pwm.h"
#include "delay.h"

/*******************************************************************************
================================================================================
【平    台】stm32f103zet6_sumjess平台
【编    写】sumjess
【E-mail  】1371129880@qq.com
【软件版本】V2.0
【最后更新】2018年09月06日
【相关信息参考下列地址】
【网    站】
           https://blog.csdn.net/qq_38351824
           http://www.openedv.com/
           http://www.stmcu.org/
					 http://www.firebbs.cn/forum.php
---------------------------------------------------------------------------------
【dev.env.】MDK5.14及以上版本
【Target  】stm32f103zet6
第一次修订：2017/11/09
第二次修订：2018/01/21
第三次修订：2018/09/06
【problem 】
    （1）库内补充的不全面；
    （2）库内解释部分不全面；
    （3）库内还存在一定的bug；
【direction】
      下一步的目标就是把库继续集成！
【explain 】
      本库是根据正点原子、中景园电子、优信电子等商家改编而成，
      同时为了方便使用，我也自己写了很多的库，和优化了算法和表示方式！
【warning】
      目前程序中暂无警告 ！   
---------------------------------------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug！
================================================================================   */
#define delays 380
void algor_SUM_UP(void)
{

	
	
      if(up_for_lift==0&&up_for_right==0&&up_back_left==0&&up_back_right==0)//没有掉落危险
      {
				/////////////////////////////////////后侧检测
        if(back_1==0||back_2==0)//后侧
          {
              delay_us(200);//去抖
              if(back_1==0||back_2==0)//确定后侧
              {
                  drive_Back_H();//高速倒车

              }
          }
         else
              {
                  ;
              }
					/////////////////////////////////////前面检测
        if(for_1==0||for_2==0||for_3==0)//前面
         {
						delay_us(200);
						if(for_1==0||for_2==0||for_3==0)//确定前面
						{
							drive_For_H();//高速直行
						}
					}
				else
					{
							;
					}
					/////////////////////////////////////后侧检测--如果没有，那么直行
				if(back_1==0||back_2==0)//后侧
				{
					delay_us(200);
					if(back_1==0||back_2==0)//确定后侧
					{
						drive_Back_H();//高速后退
					}
				
				}
				else
						{
							drive_For_L();//低速直行
						}
					/////////////////////////////////////前面检测--如果确实有，那么高速直行；如果没有，看最下面的else2；如果一瞬间有，看下看面的else1；
				if(for_1==0||for_2==0||for_3==0)//前面
				{
					delay_us(200);
					if(for_1==0||for_2==0||for_3==0)//确定前面
					{
						drive_For_H();//高速直行
					}
					else//else1，检测左边，如果有左转；如果一瞬间有，看下面的else3；
					{
              if(left_1==0||left_2==0||for_lift==0||back_lift==0)//左侧
              {
                delay_us(200);
                if(left_1==0||left_2==0||for_lift==0||back_lift==0)//确定左侧
                  {
                    drive_Left_S();//超级左转
                    delay_ms(delays);
										
										
                   }
							}
              else//else3，如果有右转；如果一瞬间有低速直行；
                  {
                        if(right_1==0||right_2==0||for_right==0||back_right==0)//右侧
                        {
                            delay_us(200);
                            if(right_1==0||right_2==0||for_right==0||back_right==0)//确定右侧
                              {
                                    drive_Right_S();//超级右转
                                    delay_ms(delays);
                              }
                             else
                             {
                               drive_For_L();//低速直行
                             }
                         }
                  }
              
       }


  }
				
  else//检测左侧，如果有左转；如果一瞬间有，检测右侧；如果右侧确实有，右转；如果右侧一瞬间有，那么低速直行；
  {
             if(left_1==0||left_2==0||for_lift==0||back_lift==0)//左侧
              {
                delay_us(200);
                if(left_1==0||left_2==0||for_lift==0||back_lift==0)//确定左侧
                  {
                        drive_Left_S();//左转
                        delay_ms(delays);
                   }
							}
              else
                  {
                        if(right_1==0||right_2==0||for_right==0||back_right==0)//右侧
                        {
                            delay_us(200);
                            if(right_1==0||right_2==0||for_right==0||back_right==0)//确定右侧
                                  {
                                    drive_Right_S();//右转
                                    delay_ms(delays);
                                   }
                             else
                             {
                               drive_For_L();//低速直行
                             }
                         }
                  }
             
  }
}
			      else
      {
        if(up_for_lift==1||up_for_right==1)//前方有掉落危险
        {
          delay_us(200);
          if(up_for_lift==1||up_for_right==1)//确定有掉落危险
          {

            drive_Stop();//停下驱动
            drive_Back_H();//高速倒车
            delay_ms(700);//300ms
            drive_Right();//右转（可以设置向左向右算法）
            delay_ms(500);//250ms
          }
        }
        if(up_back_left==1||up_back_right==1)//后方有掉落危险
        {
          delay_us(200);
          if(up_back_left==1||up_back_right==1)//确定有掉落危险
          {
						drive_Stop();//停下驱动J
            drive_For_M();//快速直行
            delay_ms(700);//300msJ
            drive_Right();//右转（可以设置向左向右算法）J
            delay_ms(500);//250msJ
          }
        }
			}
		}

