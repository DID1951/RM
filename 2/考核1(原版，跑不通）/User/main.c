#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Key.h"
#include "LED.h"
#include "WLED.h"
#include "PWM.h"
#include "SoftPWM.h"


uint8_t mode = 0;
uint32_t tick = 0;

uint16_t pwm_duty = 0;
int8_t pwm_dir = 1;
int8_t soft_pwm_dir = 1;

uint16_t soft_pwm_cnt = 0;
uint16_t soft_pwm_duty = 0;
extern uint8_t KeyNum;
extern uint8_t key_flag;  
uint32_t keyTick = 0;

int main(void)
{
	Key_EXTI_Init();
	LED_Init();
	PWM_Init();
	
	WLED_Init();
	SoftPWM_Init();
	
	while (1)
	{
		if(key_flag == 1)
		{
			if(SysTick_GetTick() - keyTick >= 20)
				{
					keyTick = SysTick_GetTick();
					if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0)
					{
						mode ++;
						if(mode >= 3)
						{
							mode = 0;
						}
					}
					key_flag = 0;
					
				}
			
		}
		switch(mode)
		{
			case 0:
				WLED_ALLOff();
				LED1_ON();
				break;
//			case 1:
//				LED1_OFF();
//				WLED_ALLOff();
//				PWM_SetCompare1(pwm_duty);
//				if(SysTick_GetTick() - tick >= 20)
//				{
//					tick = SysTick_GetTick();
//					pwm_duty += pwm_dir;
//					if(pwm_duty >= 100)
//					{
//						pwm_dir = -1;

//					}
//					if(pwm_duty <= 0)
//					{
//						pwm_dir = 1;

//					}

//				}
//				break;
			case 1:
				LED1_OFF();
				WLED_ALLOff();
				if(SysTick_GetTick() - tick >= 20)
				{
					tick = SysTick_GetTick();
					soft_pwm_duty += soft_pwm_dir;
					if(soft_pwm_duty >= 100)
					{
						soft_pwm_dir = -1;

					}
					if(soft_pwm_duty <= 0)
					{
						soft_pwm_dir = 1;

					}

				}
				break;
			case 2:
				LED1_OFF();
				WLED_ON();
				
				break;
			
		}
	}
}
