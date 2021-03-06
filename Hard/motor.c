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
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
 	LED_Init();			     //LED�˿ڳ�ʼ��
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
		if(key!=0)                   //�а�������
    	{
			printf("%d  is  pressed  \r\n",key);
    	}
//		printf(" %5d %5d %5d %5d\r\n",PS2_AnologData(PSS_LX),PS2_AnologData(PSS_LY),
//		                              PS2_AnologData(PSS_RX),PS2_AnologData(PSS_RY) );
       delay_ms(50);
	}	 		
 }

