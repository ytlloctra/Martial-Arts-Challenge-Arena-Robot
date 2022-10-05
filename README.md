# 武术擂台机器人

stm32f103vet6 + oled + 得科电机 + 驼峰胎 + 红外测距传感器

## 接线

![接线](https://image-1312312327.cos.ap-shanghai.myqcloud.com/%E6%8E%A5%E7%BA%BF.png)

传感器

Left00接PD7 

Right00接PD2

Left01接PA4

Right01接PA3

Left02接PA6

Right02接PA1

Left03接PA7

Right03接PA0

Left04接PC4

Right04接PC3 

Left05接PC5  

Right05接PC2 

Behind00接PC0

 

驱动板

左侧：

pwml1接PA9，pwml2接PA8，EN不接，两个GND中，只需将其中任意一个GND与主控板GND相连

右侧：

pwml1接PA11，pwml2接PA10，EN不接，两个GND中，只需将其中任意一个GND与主控板GND相连

 

平避障 逆时针 距离变小 顺时针 距离变大  棕正蓝负黑信号

红外测距  红正黑负黄信号

左转 左后右前  右转 左前右后

## 避障序号

![避障序号](https://image-1312312327.cos.ap-shanghai.myqcloud.com/%E9%81%BF%E9%9A%9C%E5%BA%8F%E5%8F%B7.png)

## 主要程序

![image-20221005130100939](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221005130100939.png)

```cython
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
```

## 实车

![image-20221005130142933](https://image-1312312327.cos.ap-shanghai.myqcloud.com/image-20221005130142933.png)

