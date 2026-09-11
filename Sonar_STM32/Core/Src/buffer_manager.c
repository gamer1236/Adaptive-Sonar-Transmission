#include "buffer_manager.h"

static uint16_t waveform_buffer[MAX_WAVEFORM_SAMPLES];
static uint32_t waveform_size = 0;

uint16_t *BufferManager_GetBuffer(void)
{
    return waveform_buffer;
}

uint32_t BufferManager_GetSize(void)
{
    return waveform_size;
}

HAL_StatusTypeDef BufferManager_SetSize(uint32_t size)
{
    if (size <= MAX_WAVEFORM_SAMPLES)
    {
        waveform_size = size;
        return HAL_OK;
    }
    return HAL_ERROR;
}

void BufferManager_Clear(void)
{
    for (uint32_t i = 0; i < MAX_WAVEFORM_SAMPLES; i++)
    {
        waveform_buffer[i] = 0;
    }

    waveform_size = 0;
}
