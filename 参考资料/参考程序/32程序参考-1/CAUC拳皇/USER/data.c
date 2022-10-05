//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//数据操作函数集
//编者：徐天泽
//版本：V2.0
//修改日期:2018/10/04
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#include "data.h"

/** 
	* @brief	储存设置的PWM数据
	* @since	v2.0
	*/
void Save_PWMData()
{
	STMFLASH_Write(PWM_DATA_ADDR,(u16*)&MOTOR_PWM,PWM_DATA_LENTH);
	BUZZER_Hint(1);
}



/** 
	* @brief	加载设置的PWM数据
	* @since	v2.0
	*/
void Load_PWMData()
{
	STMFLASH_Read(PWM_DATA_ADDR,(u16*)&MOTOR_PWM,PWM_DATA_LENTH);
	BUZZER_Hint(1);
}



/** 
	* @brief	重置设置的PWM数据（不存储）
	* @since	v2.0
	*/
void Reset_PWMData()
{
	MOTOR_PWM.Chess			=		PWM_C_INIT;
	MOTOR_PWM.Avoid			=		PWM_A_INIT;
	MOTOR_PWM.Straight		=		PWM_S_INIT;
	MOTOR_PWM.Turn			=		PWM_T_INIT;
	MOTOR_PWM.Default		=		PWM_D_INIT;
	MOTOR_PWM.Max			=		PWM_M_INIT;
	MOTOR_PWM.JumpX			=		PWM_JX_INIT;
	MOTOR_PWM.JumpY			=		PWM_JY_INIT;
	MOTOR_PWM.Falling		=		PWM_FALL_INIT;
}



/** 
	* @brief	重置设置的PWM数据并存储
	* @since	v2.0
	*/
void Clear_PWMData()
{
	Reset_PWMData();
	Save_PWMData();
}



/** 
	* @brief	储存设置的模拟红外数据
	* @since	v2.0
	*/
void Save_ADCData()
{
	STMFLASH_Write(ADC_DATA_ADDR,(u16*)&EYE_THRESHOLD,ADC_DATALENTH);
	Refresh_ADCData();
	BUZZER_Hint(1);
}



/** 
	* @brief	加载设置的模拟红外数据
	* @since	v2.0
	*/
void Load_ADCData()
{
	STMFLASH_Read(ADC_DATA_ADDR,(u16*)&EYE_THRESHOLD,ADC_DATALENTH);
	BUZZER_Hint(1);
}



/** 
	* @brief	重置设置的模拟红外数据（不存储）
	* @since	v2.0
	*/
void Reset_ADCData()
{
	EYE_THRESHOLD.ALL		=		ADC_THRESHOLD_INIT;
	EYE_THRESHOLD.BOL		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.BML		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.BMM		=		ADC_THRESHOLD_FBMM_INIT;
	EYE_THRESHOLD.FMM		=		ADC_THRESHOLD_FBMM_INIT;
	EYE_THRESHOLD.BMR		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.BOR		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.FOL		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.FML		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.FMR		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.FOR		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.MLB		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.MLF		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.MLM		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.MRB		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.MRF		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.MRM		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.LAST		=		EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.EXACT		=		ADC_THRESHOLD_EXACT_INIT;
}



/** 
	* @brief	重置设置的模拟红外数据并存储
	* @since	v2.0
	*/
void Clear_ADCData()
{
	Reset_ADCData();
	Save_ADCData();
}



/** 
	* @brief	将对模拟红外阈值的整体更改更新到各项
	* @since	v1.0
	*/
void Refresh_ADCData()
{
	int temp;
	temp = EYE_THRESHOLD.ALL - EYE_THRESHOLD.LAST;
	EYE_THRESHOLD.LAST = EYE_THRESHOLD.ALL;
	EYE_THRESHOLD.BOL += temp;
	EYE_THRESHOLD.BML += temp;
	EYE_THRESHOLD.BMR += temp;
	EYE_THRESHOLD.BOR += temp;
	EYE_THRESHOLD.FOL += temp;
	EYE_THRESHOLD.FML += temp;
	EYE_THRESHOLD.FMR += temp;
	EYE_THRESHOLD.FOR += temp;
	EYE_THRESHOLD.MLB += temp;
	EYE_THRESHOLD.MLF += temp;
	EYE_THRESHOLD.MLM += temp;
	EYE_THRESHOLD.MRB += temp;
	EYE_THRESHOLD.MRF += temp;
	EYE_THRESHOLD.MRM += temp;
}



/** 
	* @brief	储存设置的编码器测速数据
	* @since	v2.0
	*/
void Save_EncoderData()
{
	STMFLASH_Write(ENCODER_DATA_ADDR,(u16*)&ENCODER_VALUE,ENCODER_DATA_LENTH);
	BUZZER_Hint(1);
}



/** 
	* @brief	加载设置的编码器测速数据
	* @since	v2.0
	*/
void Load_EncoderData()
{
	STMFLASH_Read(ENCODER_DATA_ADDR,(u16*)&ENCODER_VALUE,ENCODER_DATA_LENTH);
	BUZZER_Hint(1);
}



/** 
	* @brief	重置设置的编码器测速数据（不存储）
	* @since	v2.0
	*/
void Reset_EncoderData()
{
	ENCODER_VALUE.Forword		= 0;
	ENCODER_VALUE.Backword		= 0;
	ENCODER_VALUE.Right			= 0;
	ENCODER_VALUE.Left			= 0;
	ENCODER_VALUE.ErrorRange_S	= 0;
	ENCODER_VALUE.ErrorRange_T	= 0;
}



/** 
	* @brief	重置设置的编码器测速数据并存储
	* @since	v1.0
	*/
void Clear_EncoderData()
{
	Reset_EncoderData();
	Save_EncoderData();
}



/** 
	* @brief	求数组平均值
	* @param	array	数组名
	* @param	width	数组宽度
	* @return	平均值
	* @since	v1.0
	*/
u16 AVERAGE(u16 *array, u8 width)
{
	u8 i;
	u16 sum=0;
	for(i=0;i<width;i++)
		sum+=array[i];
	return sum/width;
}



/** 
	* @brief	求数组误差范围
	* @param	array	数组名
	* @param	width	数组宽度
	* @return	最大误差
	* @since	v1.0
	*/
u16 Get_ErrorRange(u16 *array, u8 width)
{
	u8 i;
	u16 min,ave;
	ave=AVERAGE(array,width);
	for(i=0;i<width;i++)
		min=array[i]<min?array[i]:min;
	return ave-min;
}



/** 
	* @brief	通过启动车辆自动获取编码器测速值
	* @since	v2.0
	*/
void Auto_EncoderData()
{
	u8 i,max_error;
	u16 Forword[5],Backword[5],Right[5],Left[5],ErrorRange[4];
	
	/*蜂鸣器警示车辆即将启动*/
	OLED_ShowLogo();
	BUZZER_Hint(2);
	
	/*测量前进转速*/
	CAR_Move(FORWORD,MOTOR_PWM.Straight);
	delay_ms(300);
	for(i=0;i<5;i++)
	{
		Forword[i] = ENCODER;
		delay_ms(50);
	}
	ENCODER_VALUE.Forword = AVERAGE(Forword,5);
	ErrorRange[0]	=	Get_ErrorRange(Forword,5);
	delay_ms(300);
	CAR_Stop();
	delay_ms(500);
	
	/*测量后退转速*/
	CAR_Move(BACKWORD,MOTOR_PWM.Straight);
	delay_ms(300);
	for(i=0;i<5;i++)
	{
		Backword[i] = ENCODER;
		delay_ms(50);
	}
	ENCODER_VALUE.Backword = AVERAGE(Backword,5);
	ErrorRange[1]	=	Get_ErrorRange(Backword,5);
	delay_ms(300);
	CAR_Stop();
	delay_ms(500);
	
	/*测量左转转速*/
	CAR_Move(LEFT,MOTOR_PWM.Turn);
	delay_ms(300);
	for(i=0;i<5;i++)
	{
		Left[i] = ENCODER;
		delay_ms(50);
	}
	ENCODER_VALUE.Left = AVERAGE(Left,5);
	ErrorRange[2]	=	Get_ErrorRange(Left,5);
	delay_ms(300);
	CAR_Stop();
	delay_ms(500);
	
	/*测量右转转速*/
	CAR_Move(RIGHT,MOTOR_PWM.Turn);
	delay_ms(300);
	for(i=0;i<5;i++)
	{
		Right[i] = ENCODER;
		delay_ms(50);
	}
	ENCODER_VALUE.Right = AVERAGE(Right,5);
	ErrorRange[3]	=	Get_ErrorRange(Right,5);
	delay_ms(300);
	CAR_Stop();
	delay_ms(500);
	
	/*获取最大误差*/
	max_error=ErrorRange[1]>ErrorRange[0]?ErrorRange[1]:ErrorRange[0];
	ENCODER_VALUE.ErrorRange_S = max_error+5;
	max_error=ErrorRange[2]>ErrorRange[3]?ErrorRange[2]:ErrorRange[3];
	ENCODER_VALUE.ErrorRange_T = max_error+5;
	
	/*保存测量值*/
	Save_EncoderData();
}



/** 
	* @brief	储存设置的杂项数据
	* @since	v2.0
	*/
void Save_SundryData()
{
	STMFLASH_Write(SUNDRY_DATA_ADDR,(u16*)&SETTING_SUNDRY,SUNDRY_DATA_LENTH);
	BUZZER_Hint(1);
}



/** 
	* @brief	加载设置的杂项数据
	* @since	v2.0
	*/
void Load_SundryData()
{
	STMFLASH_Read(SUNDRY_DATA_ADDR,(u16*)&SETTING_SUNDRY,SUNDRY_DATA_LENTH);
	BUZZER_Hint(1);
}



/** 
	* @brief	重置设置的杂项数据（不存储）
	* @since	v2.0
	*/
void Reset_SundryData()
{
	SETTING_SUNDRY.Miss_Count		=		SUNDRY_MISSCOUNT_INIT;
	SETTING_SUNDRY.Lock_Count		= 		SUNDRY_LOCKCOUNT_INIT;
	SETTING_SUNDRY.Margin_Delay		= 		SUNDRY_MARGINDELAY_INIT;
	SETTING_SUNDRY.Jump_Delay_X		= 		SUNDRY_JUMPDELAY_X_INIT;
	SETTING_SUNDRY.Jump_Delay_Y		= 		SUNDRY_JUMPDELAY_Y_INIT;
	SETTING_SUNDRY.Jump_Delay_B		= 		SUNDRY_JUMPDELAY_B_INIT;
	SETTING_SUNDRY.Jump_ADC_Value	= 		SUNDRY_JUMPADCValue_INIT;
}



/** 
	* @brief	重置设置的杂项并存储
	* @since	v2.0
	*/
void Clear_SundryData()
{
	Reset_SundryData();
	Save_SundryData();
}



/** 
	* @brief	储存设置的跳台数据
	* @since	v3.0
	*/
void Save_JumpData()
{
	Save_PWMData();
	Save_SundryData();
}



/** 
	* @brief	储存设置的所有数据
	* @since	v2.0
	*/
void Save_ALLData()
{
	Save_PWMData();
	Save_ADCData();
	Save_SundryData();
	Save_EncoderData();
}



/** 
	* @brief	加载设置的所有数据
	* @since	v2.0
	*/
void Load_ALLData()
{
	Load_PWMData();
	Load_ADCData();
	Load_SundryData();
	Load_EncoderData();
}



/** 
	* @brief	重置设置的所有数据（不存储）
	* @since	v2.0
	*/
void Reset_ALLData()
{
	Reset_PWMData();
	Reset_ADCData();
	Reset_SundryData();
	Reset_EncoderData();
}



/** 
	* @brief	重置设置的所有数据并存储
	* @since	v2.0
	*/
void Clear_Data()
{
	Reset_ALLData();
	Save_ALLData();
}
