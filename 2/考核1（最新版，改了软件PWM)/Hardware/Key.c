#include "stm32f10x.h"                  // Device header
#include "Delay.h"
volatile uint8_t key_flag = 0;
volatile uint32_t key_press_tick = 0;
void Key_EXTI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)
	{

		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == RESET)
		{
			key_press_tick = SysTick_GetTick();
			key_flag = 1;
			
		}
		EXTI_ClearITPendingBit(EXTI_Line12);
	}
}
uint8_t Key_GetPress(void)
{
	if(key_flag == 0)
	{
		return 0;
	}

	
	if((SysTick_GetTick() - key_press_tick) >= 30)
	{
	
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) != RESET)
		{
			key_flag = 0; 
			return 1;
		}
	}
	return 0;
}