#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"

int main(void)
{
	/*模块初始化*/
	OLED_Init();		//OLED初始化
	PWM_Init();
	IC_Init();
	/*OLED显示*/
		//4行1列显示二进制数字0xA5A5，长度为16
	OLED_ShowString(1,1,"Freq:00000Hz");
    OLED_ShowString(2,1,"Duty:00%");	//C语言无法直接写出二进制数字，故需要用十六进制表示
	PWM_SetPresCaler(7200 - 1);
	PWM_SetCompare1(80);
	while (1)
	{
		OLED_ShowNum(1, 6, IC_GetFreq(), 5);
		OLED_ShowNum(2, 6, IC_GetDuty(), 2);
	}
}
