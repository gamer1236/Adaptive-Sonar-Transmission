#ifndef DAC_INTERFACE_H
#define DAC_INTERFACE_H

#include "stm32f4xx_hal.h"

#define DAC_DMA_STREAM   DMA2_Stream5
#define DAC_DMA_CHANNEL  6U

HAL_StatusTypeDef DAC_Interface_Init(void);

HAL_StatusTypeDef DAC_Interface_StartDMA(
    uint16_t *buffer,
    uint32_t length
);

void DAC_Interface_StopDMA(void);
void DAC_Interface_DMAComplete(void);

uint8_t DAC_Interface_IsBusy(void);

#endif
