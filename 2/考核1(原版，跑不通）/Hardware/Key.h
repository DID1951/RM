#ifndef __KEY_H
#define __KEY_H
extern uint8_t key_flag;
void Key_EXTI_Init(void);
void EXTI0_IRQHandler(void);


#endif
