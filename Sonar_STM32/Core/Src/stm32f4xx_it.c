#include "main.h"
#include "stm32f4xx_it.h"

#include "dac_interface.h"
#include "waveform_engine.h"
#include "timer.h"
#include "fault_manager.h"

void DMA2_Stream5_IRQHandler(void)
{
    uint32_t status = DMA2->HISR;

    /* Transfer complete */
    if (status & DMA_HISR_TCIF5)
    {
        DMA2->HIFCR = DMA_HIFCR_CTCIF5 | DMA_HIFCR_CHTIF5;

        Timer_Stop();

        DAC_Interface_DMAComplete();

        WaveformEngine_TransmissionComplete();
    }
    /* Transfer error */
    else if (status & DMA_HISR_TEIF5)
    {
        DMA2->HIFCR = DMA_HIFCR_CTEIF5;

        Timer_Stop();

        DAC_Interface_StopDMA();

        WaveformEngine_TransmissionError();

        FaultManager_Set(FAULT_DMA);
    }
    /* Direct mode error */
    else if (status & DMA_HISR_DMEIF5)
    {
        DMA2->HIFCR = DMA_HIFCR_CDMEIF5;

        Timer_Stop();

        DAC_Interface_StopDMA();

        WaveformEngine_TransmissionError();

        FaultManager_Set(FAULT_DMA);
    }
    /* FIFO error */
    else if (status & DMA_HISR_FEIF5)
    {
        DMA2->HIFCR = DMA_HIFCR_CFEIF5;

        Timer_Stop();

        DAC_Interface_StopDMA();

        WaveformEngine_TransmissionError();

        FaultManager_Set(FAULT_DMA);
    }
}
