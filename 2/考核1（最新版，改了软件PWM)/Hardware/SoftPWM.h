#ifndef __SOFTPWM_H
#define __SOFTPWM_H

#include "stm32f10x.h"                  // Device header


void SoftPWM_Init(void);
void SoftPWM_SetDuty(uint16_t duty);
void Soft_PWM_OFF(void);
void SoftPWM_Start(void);
#endif 