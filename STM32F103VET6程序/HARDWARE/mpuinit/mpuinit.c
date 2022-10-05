 #include<mpuinit.h>
 
 void mpuinit(void)
 {
	 
	 MPU_Init();
  
	 

	 for(j=1000;j>0;j--)
	  {
			if( mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
			{
				if(yaw>=0)
		
		{
			OLED_ShowNum(0,0,0,4,12);
	   OLED_ShowNum(30,0,yaw*10,4,12);
		}
		else
		{
			OLED_ShowNum(0,2,1,4,12);
	   OLED_ShowNum(30,2,abs(yaw*10),4,12);
		}
	}
		}
	  
	  while(mpu_dmp_init())
 	{
		OLED_ShowNum(100,0,444,4,12);
		
	}  
	
		while(j<20)
		{
			
			MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
			MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
			mpu[0]=aacx;mpu[1]=aacy;mpu[2]=aacz;mpu[3]=gyrox;mpu[4]=gyroy;mpu[5]=gyroz;
			for(j=0;j<20;j++)
			{
				sum[0]+=mpu[0];sum[1]+=mpu[1];sum[2]+=mpu[2];sum[3]+=mpu[3];sum[4]+=mpu[4];sum[5]+=mpu[5];
			}
		}
		for(j=0;j<6;j++) sum[j]/=20;
		j=0;
   while(value[6]<3000||y==0)
	 {
		// OLED_ShowString(0,4,chr);
		 //u16 y;
		 OLED_ShowNum(0,4,1111,4,12);
			if( mpu_dmp_get_data(&pitch,&roll,&yaw)==0){}
					if(yaw>=0)
		
		{
			
			OLED_ShowNum(0,0,0,4,12);
	   OLED_ShowNum(30,0,yaw*10,4,12);
			OLED_ShowNum(0,2,1,4,12);
	   OLED_ShowNum(30,2,abs(0*10),4,12);
		}
		else
		{
			OLED_ShowNum(0,0,0,4,12);
	   OLED_ShowNum(30,0,0*10,4,12);
			OLED_ShowNum(0,2,1,4,12);
	   OLED_ShowNum(30,2,abs(yaw*10),4,12);
		}
		oldyaw=yaw;
		if(oldyaw==yaw) y=1;
		else y=0;
	 }
	 OLED_Clear()  	;
	 yawsta=yaw*10;

}

