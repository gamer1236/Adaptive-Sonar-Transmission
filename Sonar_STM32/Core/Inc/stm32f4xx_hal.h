#ifndef __STM32F4xx_HAL_H
#define __STM32F4xx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#include "stm32f411xe.h"

typedef enum
{
    HAL_OK       = 0x00U,
    HAL_ERROR    = 0x01U,
    HAL_BUSY     = 0x02U,
    HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

typedef struct
{
    uint32_t Pin;
    uint32_t Mode;
    uint32_t Pull;
    uint32_t Speed;
    uint32_t Alternate;
} GPIO_InitTypeDef;

typedef struct
{
    uint32_t OscillatorType;
    uint32_t HSIState;
    uint32_t HSICalibrationValue;
    struct {
        uint32_t PLLState;
        uint32_t PLLSource;
        uint32_t PLLM;
        uint32_t PLLN;
        uint32_t PLLP;
        uint32_t PLLQ;
    } PLL;
} RCC_OscInitTypeDef;

typedef struct
{
    uint32_t ClockType;
    uint32_t SYSCLKSource;
    uint32_t AHBCLKDivider;
    uint32_t APB1CLKDivider;
    uint32_t APB2CLKDivider;
} RCC_ClkInitTypeDef;

void SystemInit(void);
HAL_StatusTypeDef HAL_Init(void);
void HAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_Init);
void HAL_NVIC_SetPriority(IRQn_Type IRQn, uint32_t PreemptPriority, uint32_t SubPriority);
void HAL_NVIC_EnableIRQ(IRQn_Type IRQn);
HAL_StatusTypeDef HAL_RCC_OscConfig(RCC_OscInitTypeDef *RCC_OscInitStruct);
HAL_StatusTypeDef HAL_RCC_ClockConfig(RCC_ClkInitTypeDef *RCC_ClkInitStruct, uint32_t FLatency);

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_H */
