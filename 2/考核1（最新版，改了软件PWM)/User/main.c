#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
#include "LED.h"
#include "WLED.h"
#include "PWM.h"
#include "SoftPWM.h"

//1 = 硬件 PWM，0 = 定时器中断软件 PWM
#define USE_HARDWARE_PWM   1

uint8_t mode = 0;
uint32_t tick = 0;
uint16_t pwm_duty = 0;
int8_t pwm_dir = 1;
uint32_t keyTick = 0;

//main里一定不能调用Delay_us()， 否则会破坏 SysTick_Config(72000) 建立的 1ms 时基
int main(void)
{

	SysTick_Config(72000);
	Key_EXTI_Init();
	LED_Init();
	
#if (USE_HARDWARE_PWM == 1)
	PWM_Init();           
#else
	SoftPWM_Init();       
#endif	
	WLED_Init();

	
	while (1)
	{
		if(Key_GetPress() == 1)
		{
			mode ++;
			if(mode >= 3)
			{
				mode = 0;
			}
						
			WLED_ALLOff();        
			LED1_OFF();          
#if (USE_HARDWARE_PWM == 1)
			PWM_OFF();          
#else
			Soft_PWM_OFF();  
			if(mode == 1)              
			{
				SoftPWM_Start();
			}			
#endif
			pwm_duty = 0;         
			pwm_dir  = 1;
			tick     = SysTick_GetTick();
		}
		switch(mode)
		{
			case 0:
				
				LED1_ON();
				break;

				
			case 1:

				LED1_OFF();
				WLED_ALLOff();
#if (USE_HARDWARE_PWM == 1)
			
				{
					GPIO_InitTypeDef GPIO_InitStructure;
					GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
				}
				PWM_SetCompare3(pwm_duty);
#else
				
				
//				SoftPWM_SetDuty(10);
				SoftPWM_SetDuty(pwm_duty);
#endif
				
//				20正常，10快，40慢
				if(SysTick_GetTick() - tick >= 20)
				{
					tick = SysTick_GetTick();
					pwm_duty += pwm_dir;
					if(pwm_duty >= 99)
					{
						pwm_duty = 99;
						pwm_dir = -1;

					}
					if(pwm_duty <= 0)
					{
						pwm_duty = 0;
						pwm_dir = 1;

					}

				}
				break;

			case 2:


				LED1_OFF();
				WLED_ON();
				
				break;
			default:
				mode = 0;
				break;
		}
	}
}
