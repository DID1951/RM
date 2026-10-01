#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"

uint8_t i;
int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	PWM_Init();
	/*OLED显示*/
		//4行1列显示二进制数字0xA5A5，长度为16
											//C语言无法直接写出二进制数字，故需要用十六进制表示
	
	while (1)
	{
		for (i = 0; i <= 100; i++)
		{
			PWM_SetCompare1(i);
			Delay_ms(10);
		}
		for (i = 0; i <= 100; i++)
		{
			PWM_SetCompare1(100 - i);
			Delay_ms(10);
		}
	}
}
