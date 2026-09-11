#include "timer.h"

static uint32_t current_sample_rate = 0;

HAL_StatusTypeDef Timer_Init(void)
{
    __HAL_RCC_TIM1_CLK_ENABLE();

    TIM1->CR1 = 0;
    TIM1->CR2 = 0;
    TIM1->DIER = 0;

    TIM1->PSC = 0;
    TIM1->RCR = 0;

    if (Timer_SetSampleRate(2000000U) != HAL_OK)
    {
        return HAL_ERROR;
    }

    return HAL_OK;
}

HAL_StatusTypeDef Timer_SetSampleRate(uint32_t sample_rate)
{
    if (sample_rate == 0 || sample_rate > TIM1_CLOCK_HZ)
    {
        return HAL_ERROR;
    }

    uint32_t arr = (TIM1_CLOCK_HZ / sample_rate) - 1U;

    if (arr > 0xFFFFU)
    {
        return HAL_ERROR;
    }

    TIM1->CR1 &= ~TIM_CR1_CEN;

    TIM1->PSC = 0;
    TIM1->ARR = (uint16_t)arr;

    TIM1->DIER |= TIM_DIER_UDE;

    TIM1->EGR = TIM_EGR_UG;

    current_sample_rate =
        TIM1_CLOCK_HZ / ((TIM1->PSC + 1U) * (TIM1->ARR + 1U));

    return HAL_OK;
}

void Timer_Start(void)
{
    TIM1->CNT = 0;
    TIM1->CR1 |= TIM_CR1_CEN;
}

void Timer_Stop(void)
{
    TIM1->CR1 &= ~TIM_CR1_CEN;
}

uint32_t Timer_GetSampleRate(void)
{
    return current_sample_rate;
}
