#include "dengtai.h"
#include "motor.h"

#define DENGTAI (2000)




u8 k;
u16 js;
extern u16 juli[14];
void encoder_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM14????    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//??PORTF??	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //????
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//??100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;      //??????
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //??
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //???PF9
	  
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOF9??????14
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3);
	
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //?????
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //??????
	TIM_TimeBaseStructure.TIM_Period=25600;   //??????
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//??????14
	
	//???TIM14 Channel1 PWM??	 
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI1, TIM_ICPolarity_Rising ,TIM_ICPolarity_Rising);//???????3,???????
    TIM_ICStructInit(&TIM_ICInitStructure);//????????????
    TIM_ICInitStructure.TIM_ICFilter = 6;  //????????? 
    TIM_ICInit(TIM3, &TIM_ICInitStructure);//?TIM_ICInitStructure?????????TIM3
 
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; //???3??
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //?????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
   TIM_ClearFlag(TIM3, TIM_FLAG_Update);//??TIM3??????
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);//??????
    //Reset counter
    TIM3->CNT =12800;//

    TIM_Cmd(TIM3, ENABLE); 
}
void TIM3_IRQHandler(void)
{
	k++;
	if(k>5)
	{
		zhidong(0);
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}
u16 read_encoder(void)
{
	return TIM_GetCounter(TIM3);
}
void dengtai(void)
{
	while(js<DENGTAI){motor(20,-20);}
	motor(30,30);
	delay_ms(1000);
	motor(-10,-10);
	delay_ms(500);
	duoji(200);
	delay_ms(2500);
	duoji(499);
	motor(50,50);
	delay_ms(1000);
	duoji(0);
	motor(30,40);
}
void qidong(void)
{
	motor(10,10);
	delay_ms(500);
	motor(0,0);
	duoji(30);
	delay_ms(900);
	duoji(99);
	motor(90,90);
	delay_ms(1000);
	zhidong(0);
	delay_ms(800);
	siqu();
	motor(-30,30);
	delay_ms(400);siqu();
	motor(20,20);
//		motor(10,10);
//	delay_ms(500);
//	motor(0,0);
//	duoji(30);
//	delay_ms(2500);
//	duoji(99);
//	motor(90,90);
//	delay_ms(650);
//	zhidong(0);
//	delay_ms(800);
//	motor(30,-30);
//	delay_ms(1000);
//	motor(20,20);
}



