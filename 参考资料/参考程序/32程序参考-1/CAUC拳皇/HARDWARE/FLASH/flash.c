//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//FLASH操作代码
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/03
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#include "flash.h"
#include "delay.h"

#define STM_SECTOR_SIZE	2048

u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];

/** 
	* @brief	读取指定地址的数据
	* @param	faddr		需要读取的数据所在地址
	* @return 对应数据
	* @since	v1.0
	*/
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}



/** 
	* @brief	不检查的写入
	* @param	WriteAddr		存储地址
	* @param	pBuffer			需要存储的数据所在地址
	* @param	NumToWrite	要写入的16位数据的个数
	* @since	v1.0
	*/
void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;
	}  
} 



/** 
	* @brief	从指定地址开始写入指定长度的数据
	* @param	WriteAddr		存储地址
	* @param	pBuffer			需要存储的数据所在地址
	* @param	NumToWrite	要写入的16位数据的个数
	* @since	v1.0
	*/
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	
	u16 secoff;	
	u16 secremain; 
 	u16 i;    
	u32 offaddr; 
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;
	FLASH_Unlock();
	offaddr=WriteAddr-STM32_FLASH_BASE;
	secpos=offaddr/STM_SECTOR_SIZE;
	secoff=(offaddr%STM_SECTOR_SIZE)/2;
	secremain=STM_SECTOR_SIZE/2-secoff;
	if(NumToWrite<=secremain)secremain=NumToWrite;
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
		for(i=0;i<secremain;i++)
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;
		}
		if(i<secremain)
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);
			for(i=0;i<secremain;i++)
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);
		}else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);
		if(NumToWrite==secremain)break;
		else
		{
			secpos++;	
			secoff=0;	
		   	pBuffer+=secremain;
			WriteAddr+=secremain;	
		   	NumToWrite-=secremain;
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;
			else secremain=NumToWrite;
		}	 
	};	
	FLASH_Lock();
}



/** 
	* @brief	从指定地址开始读出指定长度的数据
	* @param	ReadAddr		存储地址
	* @param	pBuffer			读取的数据存放地址
	* @param	NumToWrite	要写入的16位数据的个数
	* @since	v1.0
	*/
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);
		ReadAddr+=2;
	}
}
