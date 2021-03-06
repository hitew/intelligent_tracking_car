#ifndef __LINE_H
#define __LINE_H
#include "sys.h"


#define Y1 		GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) //PE4
#define Y2	  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)	//PE3
#define Y3	  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)	


void LINE_Init(void);//≥ı ºªØ		 				    
#endif




#ifndef __TIMER_H
#define __TIMER_H



void TIM3_PWM_Init(u32 arr,u32 psc);
void TIM5_CH1_Cap_Init(u32 arr,u16 psc);

#endif
