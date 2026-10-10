#include "stm32f10x.h"                  // Device header
volatile uint16_t soft_pwm_cnt;
volatile uint16_t soft_pwm_duty;
#define PWM_PERIOD 100
void SoftPWM_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		//GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;
	TIM_TimeBaseStructure.TIM_Period = 10 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM1, ENABLE);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		soft_pwm_cnt ++;
		if(soft_pwm_cnt >= PWM_PERIOD)
		{
			soft_pwm_cnt = 0;
		}
		if(soft_pwm_cnt < soft_pwm_duty)
		{
			GPIO_SetBits(GPIOA, GPIO_Pin_10);
		}
		else
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_10);
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}

}

void Soft_PWM_OFF(void)
{
	TIM_Cmd(TIM1, DISABLE);          
	soft_pwm_cnt  = 0;
	soft_pwm_duty = 0;
	GPIO_ResetBits(GPIOA, GPIO_Pin_10);  
}
void SoftPWM_SetDuty(uint16_t duty)
{
	if(duty > 99) 
	{ 
		duty = 99; 
	}
	soft_pwm_duty = duty;
}
void SoftPWM_Start(void)
{
	soft_pwm_cnt = 0;
	TIM_Cmd(TIM1, ENABLE);
}