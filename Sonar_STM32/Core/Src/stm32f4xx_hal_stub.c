#include "stm32f4xx_hal.h"

void SystemInit(void)
{
    /* Enable FPU coprocessors CP10 and CP11 if hard float enabled */
#if defined(__VFP_FP__) && !defined(__SOFTFP__)
    *((volatile uint32_t *)0xE000ED88) |= ((3UL << 20) | (3UL << 22));
#endif
}

HAL_StatusTypeDef HAL_Init(void)
{
    return HAL_OK;
}

void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
    if (GPIOx == NULL || GPIO_Init == NULL) return;
    /* Basic GPIO mode configuration */
    GPIOx->MODER &= ~(0xFFFFU);
    GPIOx->MODER |= 0x5555U; /* Set pins 0..7 as general purpose output mode (01) */
}

void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority)
{
    (void)IRQn;
    (void)PreemptPriority;
    (void)SubPriority;
}

void HAL_NVIC_EnableIRQ(IRQn_Type IRQn)
{
    (void)IRQn;
}

HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct)
{
    (void)RCC_OscInitStruct;
    return HAL_OK;
}

HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency)
{
    (void)RCC_ClkInitStruct;
    (void)FLatency;
    return HAL_OK;
}
