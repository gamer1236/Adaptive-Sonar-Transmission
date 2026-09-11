#include "waveform_engine.h"
#include "buffer_manager.h"
#include "dac_interface.h"
#include "timer.h"
#include "fault_manager.h"

#include <math.h>

#define PI 3.14159265358979323846f

static volatile uint8_t engine_busy = 0;
static uint8_t lut_initialized = 0;
static uint32_t current_waveform_sample_rate = 2000000U;

static uint8_t sine_lut[256];

HAL_StatusTypeDef WaveformEngine_Init(void)
{
    for (uint32_t i = 0; i < 256; i++)
    {
        float angle =
            (2.0f * PI * (float)i) / 256.0f;

        float sine =
            sinf(angle);

        sine_lut[i] =
            (uint8_t)(127.5f + 127.5f * sine);
    }

    lut_initialized = 1;

    return HAL_OK;
}

HAL_StatusTypeDef WaveformEngine_GenerateSine(
    float frequency,
    float amplitude,
    uint32_t sample_rate,
    float duration)
{
    if (frequency <= 0.0f ||
        sample_rate == 0 ||
        duration <= 0.0f)
    {
        FaultManager_Set(FAULT_INVALID_CONFIG);
        return HAL_ERROR;
    }

    if (!lut_initialized)
    {
        WaveformEngine_Init();
    }

    if (amplitude < 0.0f)
        amplitude = 0.0f;

    if (amplitude > 1.0f)
        amplitude = 1.0f;

    uint32_t samples =
        (uint32_t)((float)sample_rate * duration);

    if (samples == 0 ||
        samples > MAX_WAVEFORM_SAMPLES)
    {
        FaultManager_Set(FAULT_BUFFER);
        return HAL_ERROR;
    }

    uint16_t *buffer =
        BufferManager_GetBuffer();

    /*
     * 32-bit phase accumulator.
     *
     * phase_increment =
     * frequency / sample_rate * 2^32
     */

    uint32_t phase_increment =
        (uint32_t)(
            ((double)frequency / (double)sample_rate)
            * 4294967296.0
        );

    uint32_t phase = 0;

    for (uint32_t n = 0; n < samples; n++)
    {
        uint8_t index =
            (uint8_t)(phase >> 24);

        float centered =
            ((float)sine_lut[index] - 127.5f)
            * amplitude;

        float output =
            127.5f + centered;

        if (output < 0.0f)
            output = 0.0f;

        if (output > 255.0f)
            output = 255.0f;

        buffer[n] =
            (uint16_t)output;

        phase += phase_increment;
    }

    if (BufferManager_SetSize(samples) != HAL_OK)
    {
        FaultManager_Set(FAULT_BUFFER);
        return HAL_ERROR;
    }

    current_waveform_sample_rate = sample_rate;

    return HAL_OK;
}

HAL_StatusTypeDef WaveformEngine_Transmit(void)
{
    if (engine_busy)
    {
        return HAL_BUSY;
    }

    uint16_t *buffer =
        BufferManager_GetBuffer();

    uint32_t length =
        BufferManager_GetSize();

    if (buffer == NULL || length == 0)
    {
        FaultManager_Set(FAULT_BUFFER);
        return HAL_ERROR;
    }

    if (Timer_SetSampleRate(current_waveform_sample_rate) != HAL_OK)
    {
        FaultManager_Set(FAULT_TIMER);
        return HAL_ERROR;
    }

    engine_busy = 1;

    if (DAC_Interface_StartDMA(buffer, length) != HAL_OK)
    {
        engine_busy = 0;
        FaultManager_Set(FAULT_DMA);
        return HAL_ERROR;
    }

    Timer_Start();

    return HAL_OK;
}

void WaveformEngine_Stop(void)
{
    Timer_Stop();

    DAC_Interface_StopDMA();

    engine_busy = 0;
}

void WaveformEngine_TransmissionComplete(void)
{
    engine_busy = 0;
}

void WaveformEngine_TransmissionError(void)
{
    engine_busy = 0;
    FaultManager_Set(FAULT_DMA);
}

uint8_t WaveformEngine_IsBusy(void)
{
    return engine_busy;
}
