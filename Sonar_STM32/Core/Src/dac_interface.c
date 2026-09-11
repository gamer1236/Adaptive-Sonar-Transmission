#include "dac_interface.h"

#define DAC_GPIO_PORT GPIOB
#define DAC_GPIO_MASK 0x00FFU

static volatile uint8_t dma_busy = 0;

HAL_StatusTypeDef DAC_Interface_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_DMA2_CLK_ENABLE();

    GPIO_InitStruct.Pin =
        GPIO_PIN_0 |
        GPIO_PIN_1 |
        GPIO_PIN_2 |
        GPIO_PIN_3 |
        GPIO_PIN_4 |
        GPIO_PIN_5 |
        GPIO_PIN_6 |
        GPIO_PIN_7;

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIOB->ODR &= ~DAC_GPIO_MASK;

    /*
     * DMA2 Stream 5, Channel 6
     * TIM1_UP request
     */

    DAC_DMA_STREAM->CR &= ~DMA_SxCR_EN;

    while (DAC_DMA_STREAM->CR & DMA_SxCR_EN)
    {
        /* Wait until disabled */
    }

    DMA2->HIFCR =
          DMA_HIFCR_CFEIF5
        | DMA_HIFCR_CDMEIF5
        | DMA_HIFCR_CTEIF5
        | DMA_HIFCR_CHTIF5
        | DMA_HIFCR_CTCIF5;

    DAC_DMA_STREAM->PAR =
        (uint32_t)&GPIOB->ODR;

    DAC_DMA_STREAM->CR =
          (6U << DMA_SxCR_CHSEL_Pos)
        | DMA_SxCR_DIR_0
        | DMA_SxCR_MINC
        | DMA_SxCR_PL_1
        | DMA_SxCR_MSIZE_0
        | DMA_SxCR_PSIZE_0
        | DMA_SxCR_TCIE
        | DMA_SxCR_TEIE
        | DMA_SxCR_DMEIE;

    DAC_DMA_STREAM->FCR = DMA_SxFCR_FEIE;

    HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

    return HAL_OK;
}

HAL_StatusTypeDef DAC_Interface_StartDMA(
    uint16_t *buffer,
    uint32_t length)
{
    if (buffer == NULL || length == 0)
    {
        return HAL_ERROR;
    }

    if (dma_busy)
    {
        return HAL_BUSY;
    }

    DAC_DMA_STREAM->CR &= ~DMA_SxCR_EN;

    while (DAC_DMA_STREAM->CR & DMA_SxCR_EN)
    {
        /* Wait */
    }

    DMA2->HIFCR =
          DMA_HIFCR_CFEIF5
        | DMA_HIFCR_CDMEIF5
        | DMA_HIFCR_CTEIF5
        | DMA_HIFCR_CHTIF5
        | DMA_HIFCR_CTCIF5;

    DAC_DMA_STREAM->PAR =
        (uint32_t)&GPIOB->ODR;

    DAC_DMA_STREAM->M0AR =
        (uint32_t)buffer;

    DAC_DMA_STREAM->NDTR = length;

    dma_busy = 1;

    DAC_DMA_STREAM->CR |= DMA_SxCR_EN;

    return HAL_OK;
}

void DAC_Interface_StopDMA(void)
{
    DAC_DMA_STREAM->CR &= ~DMA_SxCR_EN;

    GPIOB->ODR &= ~DAC_GPIO_MASK;

    dma_busy = 0;
}

void DAC_Interface_DMAComplete(void)
{
    DAC_DMA_STREAM->CR &= ~DMA_SxCR_EN;

    GPIOB->ODR &= ~DAC_GPIO_MASK;

    dma_busy = 0;
}

uint8_t DAC_Interface_IsBusy(void)
{
    return dma_busy;
}
