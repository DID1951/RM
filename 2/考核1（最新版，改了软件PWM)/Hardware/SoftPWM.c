#include "stm32f10x.h"                  // Device header
volatile uint16_t soft_pwm_cnt = 0;
volatile uint16_t soft_pwm_duty = 0;
#define PWM_PERIOD 100
#define SOFT_PSC     (72 - 1)             
#define SOFT_ARR     (10 - 1)   
void SoftPWM_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		//GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_10);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Prescaler     = SOFT_PSC;
	TIM_TimeBaseStructure.TIM_Period        = SOFT_ARR;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
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
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}

}

void Soft_PWM_OFF(void)
{
	TIM_Cmd(TIM3, DISABLE);          
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
	
	TIM_Cmd(TIM3, ENABLE);
}