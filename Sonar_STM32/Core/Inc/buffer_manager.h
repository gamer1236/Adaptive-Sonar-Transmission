#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include "stm32f4xx_hal.h"

#define MAX_WAVEFORM_SAMPLES 20000U

uint16_t *BufferManager_GetBuffer(void);
uint32_t BufferManager_GetSize(void);
HAL_StatusTypeDef BufferManager_SetSize(uint32_t size);
void BufferManager_Clear(void);

#endif
