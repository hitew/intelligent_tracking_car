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
			if( !PS2_RedLight()) //�ж��ֱ��Ƿ�Ϊ���ģʽ���ǣ�ָʾ��LED����
		{
			delay_ms(50);	 //��ʱ����Ҫ����ȥ
			LED = 0;
			PS2_DataKey();	 //�ֱ�����������
			speed = PS2_AnologData(PSS_LY)-127;	   
			swerve = (PS2_AnologData(PSS_RX)-128)*2.3*((float)abs(speed)/128); //	speedȡ����ֵ��	�������㣬�õ�ת������
			speed = -(PS2_AnologData(PSS_LY)-127)*7;	   //����ǰ����  ��������
			if(speed > 0) //��ǰ
			{
				if(swerve < 0)//��ת��
				{
					speed1 = speed + swerve;
					speed2 = speed;
					
				}
				else          //��ת��
				{
					speed1 = speed; 
					speed2 = speed - swerve;;
					Motor_Speed_Control(speed1, speed2);
				}
			}
			else if(speed < 0)//���
			{
				if(swerve < 0)//��ת��
				{
					speed1 = speed - swerve;
					speed2 = speed;
					Motor_Speed_Control(speed1, speed2);
				}
				else//��ת��
				{
					speed1 = speed; 
					speed2 = speed + swerve;;
					Motor_Speed_Control(speed1, speed2);
				}
			}
			else  Motor_Speed_Control(0, 0); //ֹͣ
		}
		else	//�ж��ֱ����Ǻ��ģʽ��ָʾ��LEDϨ��
		{
			LED = 1;
			Motor_Speed_Control(0, 0);
			delay_ms(50);
		}

	}	

	 EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
}	
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	KEY_Init(); //������Ӧ��IO�ڳ�ʼ��
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
 

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);//PA0 ���ӵ��ж���0
	
  /* ����EXTI_Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;//LINE0
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //�����ش��� 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE0
  EXTI_Init(&EXTI_InitStructure);//����
	

 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;//�ⲿ�ж�0
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//��ռ���ȼ�0
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);//����
	

	   
}


