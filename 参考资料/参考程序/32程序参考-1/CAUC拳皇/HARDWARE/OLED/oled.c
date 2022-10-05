//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//OLED驱动代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#include "oled.h"
#include "oledfont.h"  

/** 
	* @brief	写指令
	* @param	dat		指令内容
	* @param	cmd		写指令/写数据
	* @since	v1.0
	*/
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else 
	  OLED_DC_Clr();		  
	OLED_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}				 		  
	OLED_CS_Set();
	OLED_DC_Set();   	  
}



/** 
	* @brief	画点
	* @param	x		横坐标
	* @param	y		纵坐标
	* @since	v1.0
	*/
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f)|0x01,OLED_CMD);
}   	  



/** 
	* @brief	打开OLED
	* @since	v1.0
	*/
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD); 
	OLED_WR_Byte(0X14,OLED_CMD); 
	OLED_WR_Byte(0XAF,OLED_CMD);
}



/** 
	* @brief	关闭OLED
	* @since	v1.0
	*/
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD); 
	OLED_WR_Byte(0X10,OLED_CMD); 
	OLED_WR_Byte(0XAE,OLED_CMD); 
}		   			 



/** 
	* @brief	清屏
	* @since	v1.0
	*/
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD); 
		OLED_WR_Byte (0x02,OLED_CMD);  
		OLED_WR_Byte (0x10,OLED_CMD);  
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	}
}



/** 
	* @brief	显示字符
	* @param	x			横坐标
	* @param	y			纵坐标
	* @param	char	需要显示的字符
	* @since	v1.0
	*/
void OLED_ShowChar(u8 x,u8 y,u8 chr)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';
		if(x>Max_Column-1){x=0;y=y+2;}
		if(SIZE ==16)
		{
			OLED_Set_Pos(x,y);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
		}
		else 
		{	
			OLED_Set_Pos(x,y+1);
			for(i=0;i<6;i++)
			OLED_WR_Byte(F6x8[c][i],OLED_DATA);
		}
}



/** 
	* @brief	乘方运算
	* @param	m		底数
	* @param	n		指数
	* @return	运算结果
	* @since	v1.0
	*/
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  



/** 
	* @brief	显示数字
	* @param	x			横坐标
	* @param	y			纵坐标
	* @param	num		需要显示的数字
	* @param	len		数字长度
	* @param	size	显示的尺寸（12/16）
	* @since	v1.0
	*/
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ');
				continue;
			}else enshow=1; 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0'); 
	}
} 



/** 
	* @brief	显示字符串
	* @param	x			横坐标
	* @param	y			纵坐标
	* @param	chr		需要显示的字符串
	* @since	v1.0
	*/
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j]);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}



/** 
	* @brief	显示头文件"oledfont.h"中Chinese[][32]数组里对应序号的汉字
	* @param	x			横坐标
	* @param	y			纵坐标
	* @param	no		需要显示的字汉字序号
	* @since	v1.0
	*/
void OLED_ShowChinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
		{
				OLED_WR_Byte(Chinese[2*no][t],OLED_DATA);
				adder+=1;
     }	
		OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
			{	
				OLED_WR_Byte(Chinese[2*no+1][t],OLED_DATA);
				adder+=1;
      }	
}



/** 
	* @brief	居中显示头文件"oledfont.h"中Chinese[][32]数组里对应序号的一段文字
	* @param	line		显示的行数
	* @param	start		显示汉字起始序号
	* @param	end			显示汉字终止序号
	* @since	v1.0
	*/
void OLED_ShowText(u8 line,u8 start,u8 end)
{
	u8 i;
	for(i=start;i<=end;i++)
		OLED_ShowChinese((i-start)*16+(128-(end-start+1)*16)/2,line,i);
}



/** 
	* @brief	清屏并显示中国民航大学CAUC拳皇LOGO
	* @since	v1.0
	*/
void OLED_ShowLogo()
{
	OLED_Clear();
	OLED_ShowText(1,0,5);
	OLED_ShowText(5,6,9);
}



/** 
	* @brief	OLED初始化
	* @since	v1.0
	*/
void OLED_Init(void)
{ 	
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_6;	 
 	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOE,GPIO_Pin_6);	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
 	GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_15);	

  OLED_RST_Set();
	delay_ms(100);
	OLED_RST_Clr();
	delay_ms(100);
	OLED_RST_Set(); 
					  
	OLED_WR_Byte(0xAE,OLED_CMD);
	OLED_WR_Byte(0x02,OLED_CMD);
	OLED_WR_Byte(0x10,OLED_CMD);
	OLED_WR_Byte(0x40,OLED_CMD);
	OLED_WR_Byte(0x81,OLED_CMD);
	OLED_WR_Byte(0xCF,OLED_CMD);
	OLED_WR_Byte(0xA1,OLED_CMD);
	OLED_WR_Byte(0xC8,OLED_CMD);
	OLED_WR_Byte(0xA6,OLED_CMD);
	OLED_WR_Byte(0xA8,OLED_CMD);
	OLED_WR_Byte(0x3f,OLED_CMD);
	OLED_WR_Byte(0xD3,OLED_CMD);
	OLED_WR_Byte(0x00,OLED_CMD);
	OLED_WR_Byte(0xd5,OLED_CMD);
	OLED_WR_Byte(0x80,OLED_CMD);
	OLED_WR_Byte(0xD9,OLED_CMD);
	OLED_WR_Byte(0xF1,OLED_CMD);
	OLED_WR_Byte(0xDA,OLED_CMD);
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD);
	OLED_WR_Byte(0x40,OLED_CMD);
	OLED_WR_Byte(0x20,OLED_CMD);
	OLED_WR_Byte(0x02,OLED_CMD);
	OLED_WR_Byte(0x8D,OLED_CMD);
	OLED_WR_Byte(0x14,OLED_CMD);
	OLED_WR_Byte(0xA4,OLED_CMD);
	OLED_WR_Byte(0xA6,OLED_CMD);
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_Clear();
}
