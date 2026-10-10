#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Key.h"
extern uint32_t tick_cnt;

uint32_t lastTime = 0;
uint32_t interval = 100;
uint8_t ledIndex = 0;
void WLED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7);

}
void WLED_ALLOff(void)
{
	GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_7);
}
void WLED_Index(uint8_t idx)
{
	WLED_ALLOff();
	switch(idx)
	{
		case 0:
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
			break;
		case 1:
			GPIO_ResetBits(GPIOA, GPIO_Pin_3);
			break;
		case 2:
			GPIO_ResetBits(GPIOA, GPIO_Pin_5);
			break;
		case 3:
			GPIO_ResetBits(GPIOA, GPIO_Pin_7);
			break;
		default:
			break;
	}

}
void WLED_ON(void)
{
	uint32_t currentTime = tick_cnt;
	if(currentTime - lastTime >= interval)
	{
		lastTime = currentTime;
		WLED_Index(ledIndex);
		ledIndex ++;
		if(ledIndex >= 4)
		{
			ledIndex = 0;
		}
		
	}
}