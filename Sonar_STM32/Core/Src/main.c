#include "main.h"
#include "buffer_manager.h"
#include "dac_interface.h"
#include "fault_manager.h"
#include "timer.h"
#include "waveform_engine.h"

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    FaultManager_Init();

    /*
     * Initialize waveform hardware
     */
    if (Timer_Init() != HAL_OK)
    {
        Error_Handler();
    }

    if (DAC_Interface_Init() != HAL_OK)
    {
        Error_Handler();
    }

    if (WaveformEngine_Init() != HAL_OK)
    {
        Error_Handler();
    }

    /*
     * Generate:
     *
     * Frequency  = 100 kHz
     * Sample rate = 2 MHz
     * Duration    = 1 ms
     * Amplitude   = 100 %
     */

    if (WaveformEngine_GenerateSine(
            100000.0f,
            1.0f,
            2000000U,
            0.001f) != HAL_OK)
    {
        Error_Handler();
    }

    /*
     * Transmit ONE pulse.
     */
    if (WaveformEngine_Transmit() != HAL_OK)
    {
        Error_Handler();
    }

    /*
     * Do NOT retransmit.
     *
     * The system remains idle after
     * the DMA transfer completes.
     */
    while (1)
    {
        /*
         * Future:
         * ESP32 communication
         * configuration reception
         * ping scheduling
         * fault handling
         */
    }
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
}

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
