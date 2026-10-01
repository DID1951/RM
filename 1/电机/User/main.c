#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"
1
uint8_t KeyNum;
float Angle;
int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	Servo_Init();
	Key_Init;
	
	OLED_ShowString(1, 1, "Angle:");
	
	/*OLED显示*/
		//4行1列显示二进制数字0xA5A5，长度为16
											//C语言无法直接写出二进制数字，故需要用十六进制表示
	Servo_SetAngle(90);
	while (1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			Angle += 30;
			if (Angle > 100)
			{
				Angle = 0;
			}
		}
		Servo_SetAngle(Angle);
		OLED_ShowNum(1, 7, Angle, 3);

	}
}
