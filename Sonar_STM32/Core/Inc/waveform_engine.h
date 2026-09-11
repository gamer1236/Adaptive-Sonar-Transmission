#ifndef WAVEFORM_ENGINE_H
#define WAVEFORM_ENGINE_H

#include "stm32f4xx_hal.h"

HAL_StatusTypeDef WaveformEngine_Init(void);

HAL_StatusTypeDef WaveformEngine_GenerateSine(
    float frequency,
    float amplitude,
    uint32_t sample_rate,
    float duration
);

HAL_StatusTypeDef WaveformEngine_Transmit(void);

void WaveformEngine_Stop(void);

void WaveformEngine_TransmissionComplete(void);
void WaveformEngine_TransmissionError(void);

uint8_t WaveformEngine_IsBusy(void);

#endif
