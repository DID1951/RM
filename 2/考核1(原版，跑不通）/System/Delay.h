#ifndef __DELAY_H
#define __DELAY_H

void Delay_us(uint32_t us);
void Delay_ms(uint32_t ms);
void Delay_s(uint32_t s);
void SysTick_Hander(void);
uint32_t SysTick_GetTick(void);
#endif
