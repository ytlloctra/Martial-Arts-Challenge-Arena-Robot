#include "stm32f4xx.h"
#include "usart.h"
#include "adc.h"
#include "dma.h"	
#include "delay.h"
#include "motor.h"
#include "timer.h"
#include "exti.h"
#include "edge.h"
#include "dengtai.h"
#include "usmart.h"
 /*2017华北五省机器人大赛擂台无差别组，大司马
 端口红外测距，front左B0 ,C1，C3，B1    通道8，,11，13，9
 right sideC4，A4                通道14， 4
 back A3，A1                     通道6 1 3
 leftside C0，A0。				通道10   0
 灰度   前后左右  C2 A2 A5 C5   通道12 2 5 15
 车体光电开关后左d3 后右d2 前左 d5 前右 d4
 检测墙 7 A7
 */
 //motor control x,y  xshiyou,yshizuo
extern u8 y,cmd;
extern u16 rid;
u16 juli[14];
u16 fir[10][14];
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	//usmart_dev.init(84);
	delay_init(84);
	TIM4motor_init(100,104);//那英特电机2000hz合适   5k~10k  8k
	motor_init();
	TIM12duoji_init(100,104);
	Adc_Init();
	MYDMA_Config(DMA2_Stream0,DMA_Channel_0,(u32)&ADC1->DR,(u32)fir,140);
	ADC_SoftwareStartConv(ADC1);
	edge_init();
	while(juli[7]<2900){};
	qidong();
//	EXTIX_Init();
	TIM2_init(100-1,8399);
	TIM5_init(100-1,8399);//     100 ms
//	delay_ms(1000);
  while(1){
	 // printf("%d\r\n",juli[10]);
//	  printf("[0]%d   [1]%d  [2]%d  [3]%d  [13]%d\r\n",juli[0],juli[1],juli[2],juli[3],juli[13]);
//	  delay_ms(500);
	  //printf("%d\r\n",juli[15]);
//	if(rid<3200){motor(20,-20);delay_ms(3000);motor(20,20);delay_ms(700);}
	 // motor(10,10);
//	  if(USART_RX_STA&0x8000)
//		{
//			switch(USART_RX_BUF[0])
//			{
//				case '1':motor(20,20);break;
//				case '7':motor(-20,-20);break;
//				case '4':motor(40,-40);break;
//				case '3':motor(-40,40);break;
//				case '2':motor(0,0);break;
//			}
//			USART_RX_STA=0;
//		}
//	  printf("q %d h %d z %d y %d\r\n",juli[10],juli[11],juli[12],juli[13]);
		//printf("j1  %d\r\nj2  %d\r\nj3  %d\r\nj4  %d\r\nj5  %d\r\nj6  %d\r\nj7  %d\r\n",juli[0],juli[1],juli[2],juli[3],juli[4],juli[5],juli[6],juli[7]);
// 		if(juli[0]<2120){x=65670/((float)(juli[0])+100.9);}
// 		else if(juli[0]<2770){x=38384/((float)(juli[0])-863.31);}
// 		else {x=19560/((float)(juli[0])-1776);}
// 		printf("%.1f\r\n",x);
//		delay_ms(1000);
	}
}


