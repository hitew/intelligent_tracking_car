#include "ps2.h"
#include "stm32_ub_led.h"
#include "usart.h"		
#include "delay.h"
#include "math.h"
#include "stdlib.h"
#include "sys.h"
#include "led.h"
#include "pstwo.h"

void EXTI0_IRQHandler(void)
{
		s16 speed,speed1,speed2; 
	s16 swerve;          	  
	void SystemInit();
	{
	
	
	
	}
	ps2_init();
	UB_Led_Init();
    while(1)
    {
    	ps2_read();
    	if (ps2_segitiga() || ps2_atas() || ps2_r1()) UB_Led_On(LED_ORANGE);
    	else UB_Led_Off(LED_ORANGE);
    	if (ps2_lingkaran() || ps2_kanan() || ps2_r2()) UB_Led_On(LED_RED);
    	else UB_Led_Off(LED_RED);
    	if (ps2_silang() || ps2_bawah() || ps2_l1()) UB_Led_On(LED_BLUE);
    	else UB_Led_Off(LED_BLUE);
    	if (ps2_kotak() || ps2_kiri() || ps2_l2()) UB_Led_On(LED_GREEN);
    	else UB_Led_Off(LED_GREEN);
			if( !PS2_RedLight()) //判断手柄是否为红灯模式，是，指示灯LED点亮
		{
			delay_ms(50);	 //延时很重要不可去
			LED = 0;
			PS2_DataKey();	 //手柄按键捕获处理
			speed = PS2_AnologData(PSS_LY)-127;	   
			swerve = (PS2_AnologData(PSS_RX)-128)*2.3*((float)abs(speed)/128); //	speed取绝对值，	算数运算，得到转弯量。
			speed = -(PS2_AnologData(PSS_LY)-127)*7;	   //正：前进；  负：后退
			if(speed > 0) //向前
			{
				if(swerve < 0)//左转弯
				{
					speed1 = speed + swerve;
					speed2 = speed;
					
				}
				else          //右转弯
				{
					speed1 = speed; 
					speed2 = speed - swerve;;
					Motor_Speed_Control(speed1, speed2);
				}
			}
			else if(speed < 0)//向后
			{
				if(swerve < 0)//左转弯
				{
					speed1 = speed - swerve;
					speed2 = speed;
					Motor_Speed_Control(speed1, speed2);
				}
				else//右转弯
				{
					speed1 = speed; 
					speed2 = speed + swerve;;
					Motor_Speed_Control(speed1, speed2);
				}
			}
			else  Motor_Speed_Control(0, 0); //停止
		}
		else	//判断手柄不是红灯模式，指示灯LED熄灭
		{
			LED = 1;
			Motor_Speed_Control(0, 0);
			delay_ms(50);
		}

	}	

	 EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
}	
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //按键对应的IO口初始化
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
 

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 连接到中断线0
	
  /* 配置EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//中断事件
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//使能LINE0
  EXTI_Init(&EXTI_InitStructure);//配置
	

 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//外部中断0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//抢占优先级0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);//配置
	

	   
}


