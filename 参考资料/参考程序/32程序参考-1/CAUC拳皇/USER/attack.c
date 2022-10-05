//////////////////////////////////////////////////////////////////////////////////
//本程序仅供学习使用，未经作者许可，不得用于其它任何用途
//
//擂台函数集
//编者：徐天泽
//版本：V1.0
//修改日期:2018/10/02
//
//组名：CAUC拳皇
//组长：史葆青
//组员：年  哲 葛  畅 徐天泽 郭景仁
//////////////////////////////////////////////////////////////////////////////////
#include "attack.h"

extern CAR_PWM			MOTOR_PWM;
extern ADC_THRESHOLD 	EYE_THRESHOLD;
extern CAR_SPEED 		ENCODER_SPEED;
extern CAR_SUNDRY 		SETTING_SUNDRY;

u16 miss_count    = 0;		//目标丢失计数变量
u8 lockchess_flag = 0;		//棋子目标锁定标志位
u8 lockcar_flag   = 0;		//车辆目标锁定标志位
u8 Avoid_flag	  = 0;		//规避边缘标志位

/**
	* @brief 	识别启动手势
	* @since	v3.0
	* @return
			1：识别到手势
			0：未识别到手势
	*/
u8 Scan_Gesture()
{
	if(SCAN(MRM))
		return 1;
	else
		return 0;
}



/**
	* @brief 	登台
	* @since	v3.0
	*/
void Jump()
{
	CAR_Jump(MOTOR_PWM.JumpX,MOTOR_PWM.JumpY,SETTING_SUNDRY.Jump_Delay_X,SETTING_SUNDRY.Jump_Delay_Y);
	CAR_Move(FORWORD,MOTOR_PWM.JumpX);
	delay_ms(500);
}



/**
	* @brief 	登台测试
	* @since	v3.0
	*/
void Jump_Test()
{
	OLED_ShowLogo();
	BUZZER_Hint(2);
	while(!Scan_Gesture());
	Jump();
	CAR_Stop();
}



/**
	* @brief 	复位跳台装置
	* @since	v3.0
	*/
void Jump_Restoration()
{
	OLED_ShowLogo();
	BUZZER_Hint(2);
	while(!KEY_Scan()&&EYE3_JP)
		TIM4->CCR3 = MOTOR_PWM.JumpY;
	TIM4->CCR3 = 0;
}



/**
	* @brief 	寻找擂台
	* @note		使车辆正对擂台
	* @return
			1：已正对擂台
			0：未正对擂台
	* @since	v3.0
	*/
u8 Find_Arena()
{
	if(SCAN(BMM))
	{
		if( ( SCAN(BOL) || SCAN(BOR) ) && SCAN(MLM) && SCAN(MRM) )
		{
			CAR_Move(RIGHT,MOTOR_PWM.Falling);
			return 0;
		}
		if( ( SCAN(BOL) || SCAN(BOR) ) && SCAN(MLM) )
		{
			if( SCAN(MRF) || SCAN(FML) || SCAN(FMR) )
			{
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
				return 0;
			}
			CAR_Move(BACKWORD,MOTOR_PWM.Falling);
			delay_ms(100);
			CAR_Stop();
			delay_ms(100);
			CAR_Move(FORWORD,MOTOR_PWM.Falling);
			delay_ms(500);
			CAR_Stop();
			return 0;
		}

		if( ( SCAN(BOL) || SCAN(BOR) ) &&  SCAN(MRM) )
		{
			if( SCAN(MLF) || SCAN(FML) || SCAN(FMR))
			{
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
				return 0;
			}
			CAR_Move(BACKWORD,MOTOR_PWM.Falling);
			delay_ms(100);
			CAR_Stop();
			delay_ms(100);
			CAR_Move(FORWORD,MOTOR_PWM.Falling);
			delay_ms(500);
			CAR_Stop();
			return 0;
		}

		if( (SCAN(BOL) && SCAN(BOR) ) || (SCAN(MLB) && SCAN(MRB) ) )
		{
			if(SCAN(FMM))
			{
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
				delay_ms(400);
				CAR_Move(FORWORD,MOTOR_PWM.Falling);
				delay_ms(500);
				CAR_Stop();
				return 0;
			}
			if(SCAN(FOL)&&SCAN(FOR))
				return 1;
		}

		if(SCAN(BOL)||SCAN(BOR))
		{
			if(SCAN(BOL))
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
			else
				CAR_Move(LEFT,MOTOR_PWM.Falling);
			return 0;
		}
		if(SCAN(MLB)||SCAN(MRB))
		{
			if(SCAN(MLB))
				CAR_Move(RIGHT,MOTOR_PWM.Falling);
			else
				CAR_Move(LEFT,MOTOR_PWM.Falling);
			return 0;
		}
		CAR_Move(RIGHT,MOTOR_PWM.Falling);
		return 0;
	}
	else
	{
		CAR_Move(RIGHT,MOTOR_PWM.Falling);
		return 0;
	}
}



/**
	* @brief 	准备登台
	* @note		使车辆处于登台合适距离
	* @since	v3.0
	*/
void Ready_Jump()
{
	CAR_Move(BACKWORD,MOTOR_PWM.Falling);
	delay_ms(SETTING_SUNDRY.Jump_Delay_B);
	CAR_Stop();
	delay_ms(100);
	CAR_Move(FORWORD,MOTOR_PWM.Falling);
	delay_ms(40);
}



/**
	* @brief 	落台测试
	* @since	v3.0
	*/
void Falling_Test()
{
	OLED_ShowLogo();
	BUZZER_Hint(2);
	delay_ms(500);
	BUZZER_Hint(1);

	while(!Find_Arena());

	Ready_Jump();
	Jump();

	CAR_Stop();
}



/**
	* @brief 	推棋子模式
	* @since	v1.0
	*/
void MODE_Attack_Chess()
{
	miss_count = 0;								//丢失目标计数值清零

	OLED_ShowLogo();							//OLED展示LOGO
	BUZZER_Hint(2);								//蜂鸣器警示车辆即将启动

	while(!Scan_Gesture());						//等待手势启动

	
	if(EYE3_DFL && EYE3_DFR && EYE3_DBM)
	{
		CAR_Move(BACKWORD,700);
		delay_ms(100);
		CAR_Stop();
		delay_ms(100);
		Jump();									//登台
	}

	while(!KEY_Scan())							//按任意键停止运行
	{
		if(Judge_State_Chess())
			Attack_Chess();
		else
			lockchess_flag=0;
	}

	CAR_Stop();									//刹车
}



/**
	* @brief 	擂台车模式
	* @since	v1.0
	*/
void MODE_Attack_Car()
{
	miss_count = 0;								//丢失目标计数值清零

	OLED_ShowLogo();							//OLED展示LOGO
	BUZZER_Hint(2);								//蜂鸣器警示车辆即将启动

	while(!Scan_Gesture());						//等待手势启动
	
	if(EYE3_DFL && EYE3_DFR && EYE3_DBM)
	{
		CAR_Move(BACKWORD,700);
		delay_ms(100);
		CAR_Stop();
		delay_ms(100);
		Jump();									//登台
	}

	while(!KEY_Scan())							//按任意键停止运行
	{
		if(Judge_State_Car())
			Attack_Car();
		else
			lockcar_flag=0;
	}

	CAR_Stop();									//刹车
}



/**
	* @brief 	擂台车模式(单铲)
	* @since	v4.0
	*/
void MODE_Attack_Car_Single()
{
	miss_count = 0;								//丢失目标计数值清零

	OLED_ShowLogo();							//OLED展示LOGO
	BUZZER_Hint(2);								//蜂鸣器警示车辆即将启动

	while(!Scan_Gesture());						//等待手势启动
	
	if(EYE3_DFL && EYE3_DFR && EYE3_DBM)
	{
		CAR_Move(BACKWORD,700);
		delay_ms(100);
		CAR_Stop();
		delay_ms(100);
		Jump();									//登台
	}

	while(!KEY_Scan())							//按任意键停止运行
	{
		if(Judge_State_Car())
			Attack_Car_Single();
		else
			lockcar_flag=0;
	}

	CAR_Stop();									//刹车
}



/**
	* @brief	推棋子模式下状态判断
	* @note		判断是否出现到达擂台边缘或落台等异常状况并作出反应
	* @return
			1：无异常状况
			0：检测到异常状况
	* @since	v3.0
	*/
u8 Judge_State_Chess()
{
	if(EYE3_DBM && EYE3_DFL && EYE3_DFR && EYE2_BL && EYE2_BR && EYE2_FL && EYE2_FR)
	{
		CAR_Stop();
		BUZZER_Hint(2);
		delay_ms(500);
	}
	if(EYE2_FR || EYE2_FL)//边缘检测
	{
		miss_count = SETTING_SUNDRY.Miss_Count;
		if(EYE2_BR && EYE2_BL)
		{
			CAR_Move(RIGHT,MOTOR_PWM.Avoid);
			return 0;
		}
		CAR_Move(BACKWORD,MOTOR_PWM.Avoid);
		Avoid_flag = RIGHT;
		return 0;
	}
	if(EYE2_BR || EYE2_BL)
	{
		miss_count = SETTING_SUNDRY.Miss_Count;
		if(EYE2_FR && EYE2_FL)
		{
			CAR_Move(RIGHT,MOTOR_PWM.Avoid);
			return 0;
		}
		CAR_Move(FORWORD,MOTOR_PWM.Avoid);
		Avoid_flag = LEFT;
		return 0;
	}
	if(Avoid_flag!=0)
		{
			CAR_Move(Avoid_flag,MOTOR_PWM.Avoid);
			delay_ms(SETTING_SUNDRY.Margin_Delay);
			Avoid_flag=0;
			return 0;
		}
	return 1;
}



/**
	* @brief	攻击棋子
	* @since	v4.0
	*/
void Attack_Chess()
{
	if(lockcar_flag)
	{
		/*检测目标是否在前方*/
		if((EYE3_DFL || EYE3_DFR)?(SCAN(FML) || SCAN(FMR)):(SCAN_EXACT(FML) || SCAN_EXACT(FMR)))
		{
			CAR_Move(FORWORD,MOTOR_PWM.Chess);
			return;
		}

		/*检测目标是否在后方*/
		if((EYE3_DBM)?(SCAN(BML) || SCAN(BMR) || SCAN(BMM)):(SCAN_EXACT(BML) || SCAN_EXACT(BMR)))
		{
			CAR_Move(BACKWORD,MOTOR_PWM.Chess);
			return;
		}
		/*程序运行至此，说明目标丢失*/
		if(miss_count++ >= SETTING_SUNDRY.Miss_Count)
		{
			lockcar_flag=0;
			miss_count=0;
			CAR_Move(DEFAULT,MOTOR_PWM.Chess);
			LED_Show(miss_count%8);
			return;
		}
	}

	/*检测是否需要左转用前铲*/
	if( (EYE3_DFL || EYE3_DBM) ? (SCAN(FOL) || SCAN(MLF) || SCAN(MLM) ) : (SCAN_EXACT(FOL) || SCAN_EXACT(MLF) || SCAN_EXACT(MLM)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Chess);
		return;
	}

	/*检测是否需要右转用前铲*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(FOR) || SCAN(MRF) || SCAN(MRM) ) : (SCAN_EXACT(FOR) || SCAN_EXACT(MRF) || SCAN_EXACT(MRM)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Chess);
		return;
	}

	/*检测是否需要左转用后铲*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(MRB) || SCAN(BOR)) : (SCAN_EXACT(MRB) || SCAN_EXACT(BOR)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Chess);
		return;
	}

	/*检测是否需要右转用后铲*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(MLB) || SCAN(BOL)) : (SCAN_EXACT(MLB) || SCAN_EXACT(BOL)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Chess);
		return;
	}
}



/**
	* @brief	擂台模式下状态判断
	* @note		判断是否出现到达擂台边缘或落台等异常状况并作出反应
	* @return
			1：无异常状况
			0：检测到异常状况
	* @since	v3.0
	*/
u8 Judge_State_Car()
{
	if(EYE2_FR || EYE2_FL)//边缘检测
	{
		miss_count = SETTING_SUNDRY.Miss_Count;
		if(EYE2_BR && EYE2_BL)
		{
			if(Find_Arena())
			{
				Ready_Jump();
				Jump();
				return 0;
			}
			return 0;
		}
		CAR_Move(BACKWORD,MOTOR_PWM.Avoid);
		Avoid_flag = RIGHT;
		return 0;
	}
	if(EYE2_BR || EYE2_BL)
	{
		miss_count = SETTING_SUNDRY.Miss_Count;
		if(EYE2_FR && EYE2_FL)
		{
			if(Find_Arena())
			{
				Ready_Jump();
				Jump();
				return 0;
			}
			return 0;
		}
		CAR_Move(FORWORD,MOTOR_PWM.Avoid);
		Avoid_flag = LEFT;
		return 0;
	}
	if(Avoid_flag!=0)
		{
			CAR_Move(Avoid_flag,MOTOR_PWM.Avoid);
			delay_ms(SETTING_SUNDRY.Margin_Delay);
			Avoid_flag=0;
			return 0;
		}
	return 1;
}



/**
	* @brief	攻击车辆
	* @since	v4.0
	*/
void Attack_Car()
{
	if(lockcar_flag)
	{
		/*检测目标是否在前方*/
		if((EYE3_DFL || EYE3_DFR)?(SCAN(FML) || SCAN(FMR)):(SCAN_EXACT(FML) || SCAN_EXACT(FMR) || SCAN(FMM)))
		{
			if( EYE3_DFL || EYE3_DFR )
			{
				CAR_Move(FORWORD,MOTOR_PWM.Straight);
				return;
			}
			CAR_Move(FORWORD,MOTOR_PWM.Max);
			return;
		}

		/*检测目标是否在后方*/
		if((EYE3_DBM)?(SCAN(BML) || SCAN(BMR)):(SCAN_EXACT(BML) || SCAN_EXACT(BMR) || SCAN(BMM)))
		{
			if( EYE3_DBM )
			{
				CAR_Move(FORWORD,MOTOR_PWM.Straight);
				return;
			}
			CAR_Move(BACKWORD,MOTOR_PWM.Max);
			return;
		}
		/*程序运行至此，说明目标丢失*/
		if(miss_count++ >= SETTING_SUNDRY.Miss_Count)
		{
			lockcar_flag=0;
			miss_count=0;
			CAR_Move(DEFAULT,MOTOR_PWM.Default);
			LED_Show(miss_count%8);
			return;
		}
	}

	/*检测是否需要左转用前铲*/
	if( (EYE3_DFL || EYE3_DBM) ? (SCAN(FOL) || SCAN(MLF) || SCAN(MLM) ) : (SCAN_EXACT(FOL) || SCAN_EXACT(MLF) || SCAN_EXACT(MLM)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Turn);
		return;
	}

	/*检测是否需要右转用前铲*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(FOR) || SCAN(MRF) || SCAN(MRM)) : (SCAN_EXACT(FOR) || SCAN_EXACT(MRF) || SCAN_EXACT(MRM)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Turn);
		return;
	}

	/*检测是否需要左转用后铲*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(MRB) || SCAN(BOR)) : (SCAN_EXACT(MRB) || SCAN_EXACT(BOR)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Turn);
		return;
	}

	/*检测是否需要右转用后铲*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(MLB) || SCAN(BOL)) : (SCAN_EXACT(MLB) || SCAN_EXACT(BOL)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Turn);
		return;
	}
}



/**
	* @brief	单铲攻击车辆
	* @since	v4.0
	*/
void Attack_Car_Single()
{
	if(lockcar_flag)
	{
		/*检测目标是否在前方*/
		if((EYE3_DFL || EYE3_DFR)?(SCAN(FML) || SCAN(FMR)):(SCAN_EXACT(FML) || SCAN_EXACT(FMR) || SCAN(FMM)))
		{
			if( EYE3_DFL || EYE3_DFR )
			{
				CAR_Move(FORWORD,MOTOR_PWM.Straight);
				return;
			}
			CAR_Move(FORWORD,MOTOR_PWM.Max);
			return;
		}

		/*程序运行至此，说明目标丢失*/
		if(miss_count++ >= SETTING_SUNDRY.Miss_Count)
		{
			lockcar_flag=0;
			miss_count=0;
			CAR_Move(DEFAULT,MOTOR_PWM.Default);
			LED_Show(miss_count%8);
			return;
		}
	}

	/*检测是否需要左转*/
	if( (EYE3_DFL || EYE3_DBM) ? (SCAN(FOL) || SCAN(MLF) || SCAN(MLM) || SCAN(MLB) || SCAN(BOL) || SCAN(BML)) : (SCAN_EXACT(FOL) || SCAN_EXACT(MLF) || SCAN_EXACT(MLM) || SCAN_EXACT(MLB) || SCAN_EXACT(BOL) || SCAN_EXACT(BML)) )
	{
		lockcar_flag=1;
		CAR_Move(LEFT,MOTOR_PWM.Turn);
		return;
	}

	/*检测是否需要右转*/
	if( (EYE3_DFR || EYE3_DBM) ? (SCAN(FOR) || SCAN(MRF) || SCAN(MRM) || SCAN(MRB) || SCAN(BOR) || SCAN(BMR)) : (SCAN_EXACT(FOR) || SCAN_EXACT(MRF) || SCAN_EXACT(MRM) || SCAN_EXACT(MRB) || SCAN_EXACT(BOR) || SCAN_EXACT(BMR)) )
	{
		lockcar_flag=1;
		CAR_Move(RIGHT,MOTOR_PWM.Turn);
		return;
	}
}
