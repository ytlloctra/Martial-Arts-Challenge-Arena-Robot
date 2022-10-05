实验器材:
	MiniSTM32F103开发板V3版本
	
实验目的:
	学习定时器的PWM功能
	
硬件资源:
	1,DS0(连接在PA8) 
	2,定时器1(TIM1),使用TIM1的通道1(CH1),开启部分重映射,将TIM1_CH1输出到PA8.
	从而实现PWM输出控制DS0亮度.
	
实验现象:
	本实验,DS0由暗到亮,再由亮到暗,再由暗到亮,依次循环.
	
注意事项:
	无.  


					正点原子@ALIENTEK
					2014-3-06
					广州市星翼电子科技有限公司
					电话：020-38271790
					传真：020-36773971
					购买：http://shop62103354.taobao.com
					http://shop62057469.taobao.com
					公司网站：www.alientek.com
					技术论坛：www.openedv.com
					
					
void bianyuanshibie() 
{
	//int b;
if(ltsbflag==0)
{

	
	
if(hui3==1&&hui4==1&&hui1==1&&hui2==1&&mm1==1&&mm2==1)  stop();
//else ahead(300);
else if(((temp1>1700&&temp7>1700)||(temp4>1700&&temp6>1700)||(temp1>1700&&(temp4>1700||temp6>1700))||(temp7>1700&&(temp4>1700||temp6>1700))||(temp3>1700&&temp4>1700&&temp9>1700)||(temp5>1700&&temp6>1700&&temp8>1700))&&ot<3)
	{
		
			//ltsbflag=1;
					ot++;
			
	}
//else if(backflag==1&&temp1>1600) 
//{
	//if(temp1<1600) backflag=0;
	//else  stop();
//}
	
else	
{

		if(mm1==1||mm2==1||hui1==1||hui2==1)

	
	
	
{

		
	 if( temp1>1600  )    // two sensor front find enemy 2  
			{		
					
					
					
			  
					if ((hui1==1||hui2==1)) 
				{
					if(temp7>1600) {left(800);x0++;}
					else	
					{
							//back(600,600);
						//if(hui1==0&&hui2==0)
						back(500,500);
						
						f++;
					}
					
				}
				
					else 
					{
						if(backflag==0)
						{
						allahead(500);
						allaheadflag=1;
						}
					}
					
				
			}
			else if(temp7>1600)  
			{
					left(800);
					x5++;
			}
		else if(  temp3>1600||temp4>1600||mm3==0||temp9>1600) //one sensor  right and right back  find enemy  and right back   2   temp3>1500 || temp4>1500  ||
			{
				
					if(temp3>1600)  right(600);
				else if(temp9>1600) right(800);
					else right(700);
				
			
			}
		else if( temp6>1600||temp5>1600||mm4==0||temp8>1600 )  //onr sensor left and left back find enemy 2    temp5>1500 ||temp6>1500 ||
			{
			
					if(temp5>1600)	left(600);
				else if(temp8>1600) left(800);
					else left(700);
				//x1++;
				
			}
		//else if(temp7>1700)  {left(720);x5++;}

	
		else	if(hui3==1&&hui4==1)
	{
				if(mm1==1||mm2==1||hui1==1||hui2==1)
		{
			 
				diaotou(500);x2++;
			
		}
				else
		{
		ahead(450);
		//ltsbflag=0;
		}
	}
		else 
	{
				if((hui1==1||hui2==1)&&(mm1==1||mm2==1)) {back(500,500);f++;}
				else 
				diaotou(500);
				x3++;
	}
	
	

	

}


else if( temp1>1600  )    // two sensor front find enemy 2  
			{		
					
					
							if(temp7>1600)  {diaotou(500);x4++;}
							else           
							{ 
						     if(backflag==0)
										{
											allahead(600);
											allaheadflag=1;
										}
							}
					
				
			}
else if(temp7>1600)  {left(900);x7++;}


else if(  temp3>1600||temp4>1600||mm3==0||temp9>1600) //one sensor  right and right back  find enemy  and right back   2   temp3>1500 || temp4>1500  ||
			{
					if(temp3>1600)  right(600);
				else if(temp9>1600) right(800);
					else right(700);
				
			}
else if( temp6>1600||temp5>1600||mm4==0||temp8>1600 )  //onr sensor left and left back find enemy 2    temp5>1500 ||temp6>1500 ||
			{
					
					if(temp5>1600)	left(600);
				else if(temp8>1600) left(800);
					else left(700);
				x6++;
			}

//else if(temp7>2000)  {left(720);x7++;}
else ahead(450);
			
}
		
}

duojiz(900);
duojiy(900);

//if(j>0&&f>0) 
	//{
 //   backflag=1;
//	}  
//	else backflag=0;
if(allaheadflag==1) 
{
	j+=4;
	if(j>300) j=300;
}
else j=0;

if(ot>2) 	{ltsbflag=1;}

}