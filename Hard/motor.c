#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	 
#include "pstwo.h"




#define go 			{IN1=1;IN2=0;IN3=0;IN4=1;}
#define back 		{IN1=0;IN2=1;IN3=1;IN4=0;}
#define stop		{IN1=1;IN2=1;IN3=1;IN4=1;}
#define turnleft		{IN1=1;IN2=1;IN3=0;IN4=1;}
#define turnright		{IN1=1;IN2=0;IN3=1;IN4=1;}

 	
 int main(void)
 {	 
	 u8 key=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(9600);	 	//串口初始化为9600
 	LED_Init();			     //LED端口初始化
	PS2_Init();			 	
  	  
		
	while(1)
	{
	
		key=PS2_DataKey();
		
		 switch(key)
		 {
			 case 5:go;break;
			 case 7:back;break;
			 case 8:turnleft;break;
			 case 6:turnright;break;
			 
			 default:stop;break;			 
		 }
		if(key!=0)                   //有按键按下
    	{
			printf("%d  is  pressed  \r\n",key);
    	}
//		printf(" %5d %5d %5d %5d\r\n",PS2_AnologData(PSS_LX),PS2_AnologData(PSS_LY),
//		                              PS2_AnologData(PSS_RX),PS2_AnologData(PSS_RY) );
       delay_ms(50);
	}	 		
 }

