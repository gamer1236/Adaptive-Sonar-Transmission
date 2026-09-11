#ifndef TIMER_H
#define TIMER_H

#include "stm32f4xx_hal.h"

#define TIM1_CLOCK_HZ 100000000UL

HAL_StatusTypeDef Timer_Init(void);
HAL_StatusTypeDef Timer_SetSampleRate(uint32_t sample_rate);

void Timer_Start(void);
void Timer_Stop(void);

uint32_t Timer_GetSampleRate(void);

#endif
