#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"

uint8_t KeyNum;
int8_t Speed;
int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Motor_Init();
	Motor_SetSpeed(-50);
	
	/*OLED显示*/
		//4行1列显示二进制数字0xA5A5，长度为16
											//C语言无法直接写出二进制数字，故需要用十六进制表示
	Key_Init();
	OLED_ShowString(1,1,"Speed:");
	while (1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			Speed += 20;
			if (Speed > 100)
			{
				Speed = -100;
			}
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(1,7, Speed, 3);
	}
}
