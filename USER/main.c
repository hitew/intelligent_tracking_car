#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "line.h"
#include "pstwo.h"

int PS2_LX,PS2_LY,PS2_RX,PS2_RY; 
int PS2_L2,PS2_L1; //
int a=1;
extern void PS2_SetInit(void);
u8 PS2_KEY=0;



int c=1;
#define back (PBout(6)=0,PBout(7)=1,PBout(8)=0,PBout(9)=1)
#define forward (PBout(6)=1,PBout(7)=0,PBout(8)=1,PBout(9)=0)
#define stop (PBout(6)=0,PBout(7)=0,PBout(8)=0,PBout(9)=0)
#define turnleft (PBout(6)=1,PBout(7)=0,PBout(8)=0,PBout(9)=1)
#define turnright (PBout(6)=0,PBout(7)=1,PBout(8)=1,PBout(9)=0)



int main(void)
	
{	LINE_Init();	
  delay_init(168);    
	uart_init(9600);	
                //=====主频168M
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//=====设置系统中断优先级分组2
              //=====延时初始化
	PS2_Init();									    //=====ps2驱动端口初始化
	PS2_SetInit();		 					    //=====ps2配置初始化,配置“红绿灯模式”，并选择是否可以修改
	delay_ms(500);
	
    
	while (1)
	{	
		
while(!a)
	{
	u8 key=0;
		key=PS2_DataKey();
		
		 switch(key)
		 {
			 case 5:forward;break;
			 case 7:back;break;
			 case 6:turnleft;break;
			 case 8:turnright;break;
			
			 default:stop;break;			 
		 }
		if(key!=0)                   //有按键按下
    	{
			printf("%d  is  pressed  \r\n",key);
    	}
//		printf(" %5d %5d %5d %5d\r\n",PS2_AnologData(PSS_LX),PS2_AnologData(PSS_LY),
//		                              PS2_AnologData(PSS_RX),PS2_AnologData(PSS_RY) );
       delay_ms(50);
			
		PS2_KEY=PS2_DataKey();
PS2_KEY=PS2_DataKey();

/********************************选择模式******************************************/
			if(PS2_KEY!=0)                   //有按键按下
    	{
			printf("%d  is  pressed  \r\n",PS2_KEY);
    	}

       delay_ms(50);
		switch(PS2_KEY)
		{
			case 11:a=1;break;
			case 12:a=0;break;
			default:continue;
		}
		
	   delay_ms(50);                       
		
		
	

		}
	
	while(a)
	{
	
	
	
	if(Y1==0)
			{
				if(Y3)
			{
				if(Y2)
				{
					
					stop;
					delay_ms(10);
					forward;
					delay_ms(12);
					
				}
					else
					{
						
						stop;
					delay_ms(10);
					turnright;
					delay_ms(12);}
									
			}
				else
				{
					if(Y2)
				{
					
					stop;
					delay_ms(10);
					turnleft;
					delay_ms(12);
					
				}
					else
					{
						stop;
					delay_ms(10);
					forward;
					delay_ms(12);
					}	
				}
			}
			else
			{
				
				if(c%2==0)
				{
				int i;
				for(i=30;i>0;i--)
				{
					stop;
					delay_ms(10);
					forward;
					delay_ms(12);
					while(Y3==0)
					{
						stop;
					delay_ms(10);
						turnleft;
						delay_ms(12);
					}
				}
				c=c+1;
					}
				else
				{
					int n;
					for(n=45;n>0;n--)
					{
						stop;
					delay_ms(10);
					forward;
					delay_ms(12);
					c=c+1;
				}
				}
	}

		PS2_KEY=PS2_DataKey();

/********************************选择模式******************************************/
			if(PS2_KEY!=0)                   //有按键按下
    	{
			printf("%d  is  pressed  \r\n",PS2_KEY);
    	}

       delay_ms(50);
		switch(PS2_KEY)
		{
			case 11:a=1;break;
			case 12:a=0;break;
			default:continue;
		}
		
	   delay_ms(50);                       
		
	}	
	
	
}
}
	
				
