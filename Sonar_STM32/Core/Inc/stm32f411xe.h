#ifndef STM32F411XE_H
#define STM32F411XE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

static inline void __disable_irq(void)
{
    __asm volatile ("cpsid i" : : : "memory");
}

static inline void __enable_irq(void)
{
    __asm volatile ("cpsie i" : : : "memory");
}

typedef enum
{
    NonMaskableInt_IRQn   = -14,
    HardFault_IRQn        = -13,
    MemoryManagement_IRQn = -12,
    BusFault_IRQn         = -11,
    UsageFault_IRQn       = -10,
    SVCall_IRQn           = -5,
    DebugMonitor_IRQn     = -4,
    PendSV_IRQn           = -2,
    SysTick_IRQn          = -1,
    DMA2_Stream5_IRQn     = 56
} IRQn_Type;

typedef struct
{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t RCR;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t BDTR;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
} TIM_TypeDef;

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t NDTR;
    volatile uint32_t PAR;
    volatile uint32_t M0AR;
    volatile uint32_t M1AR;
    volatile uint32_t FCR;
} DMA_Stream_TypeDef;

typedef struct
{
    volatile uint32_t LISR;
    volatile uint32_t HISR;
    volatile uint32_t LIFCR;
    volatile uint32_t HIFCR;
} DMA_TypeDef;

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    uint32_t RESERVED0;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    uint32_t RESERVED1[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    uint32_t RESERVED2;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
} RCC_TypeDef;

typedef struct
{
    volatile uint32_t CR;
    volatile uint32_t CSR;
} PWR_TypeDef;

#define PERIPH_BASE           0x40000000UL
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000UL)

#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000UL)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400UL)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800UL)
#define DMA2_BASE             (AHB1PERIPH_BASE + 0x6400UL)
#define DMA2_Stream5_BASE     (DMA2_BASE + 0x088UL)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x0000UL)
#define PWR_BASE              (APB1PERIPH_BASE + 0x7000UL)

#define GPIOA                 ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB                 ((GPIO_TypeDef *) GPIOB_BASE)
#define RCC                   ((RCC_TypeDef *) RCC_BASE)
#define DMA2                  ((DMA_TypeDef *) DMA2_BASE)
#define DMA2_Stream5          ((DMA_Stream_TypeDef *) DMA2_Stream5_BASE)
#define TIM1                  ((TIM_TypeDef *) TIM1_BASE)
#define PWR                   ((PWR_TypeDef *) PWR_BASE)

#define __HAL_RCC_GPIOB_CLK_ENABLE() do { RCC->AHB1ENR |= (1U << 1); (void)RCC->AHB1ENR; } while(0)
#define __HAL_RCC_DMA2_CLK_ENABLE()  do { RCC->AHB1ENR |= (1U << 22); (void)RCC->AHB1ENR; } while(0)
#define __HAL_RCC_TIM1_CLK_ENABLE()  do { RCC->APB2ENR |= (1U << 0); (void)RCC->APB2ENR; } while(0)
#define __HAL_RCC_PWR_CLK_ENABLE()   do { RCC->APB1ENR |= (1U << 28); (void)RCC->APB1ENR; } while(0)
#define __HAL_PWR_VOLTAGESCALING_CONFIG(scaling) do { PWR->CR |= (scaling); } while(0)

#define DMA_SxCR_EN           (1U << 0)
#define DMA_SxCR_DMEIE        (1U << 1)
#define DMA_SxCR_TEIE         (1U << 2)
#define DMA_SxCR_TCIE         (1U << 4)
#define DMA_SxCR_DIR_0        (1U << 6)
#define DMA_SxCR_MINC         (1U << 9)
#define DMA_SxCR_PSIZE_0      (1U << 11)
#define DMA_SxCR_MSIZE_0      (1U << 13)
#define DMA_SxCR_PL_1         (2U << 16)
#define DMA_SxCR_CHSEL_Pos     25U

#define DMA_SxFCR_FEIE        (1U << 7)

#define DMA_HISR_FEIF5        (1U << 6)
#define DMA_HISR_DMEIF5       (1U << 8)
#define DMA_HISR_TEIF5        (1U << 9)
#define DMA_HISR_HTIF5        (1U << 10)
#define DMA_HISR_TCIF5        (1U << 11)

#define DMA_HIFCR_CFEIF5      (1U << 6)
#define DMA_HIFCR_CDMEIF5     (1U << 8)
#define DMA_HIFCR_CTEIF5      (1U << 9)
#define DMA_HIFCR_CHTIF5      (1U << 10)
#define DMA_HIFCR_CTCIF5      (1U << 11)

#define TIM_CR1_CEN           (1U << 0)
#define TIM_DIER_UDE          (1U << 8)
#define TIM_EGR_UG            (1U << 0)

#define GPIO_PIN_0            (0x0001U)
#define GPIO_PIN_1            (0x0002U)
#define GPIO_PIN_2            (0x0004U)
#define GPIO_PIN_3            (0x0008U)
#define GPIO_PIN_4            (0x0010U)
#define GPIO_PIN_5            (0x0020U)
#define GPIO_PIN_6            (0x0040U)
#define GPIO_PIN_7            (0x0080U)

#define GPIO_MODE_OUTPUT_PP   0x00000001U
#define GPIO_NOPULL           0x00000000U
#define GPIO_SPEED_FREQ_VERY_HIGH 0x00000003U

#define FLASH_LATENCY_5       5U
#define PWR_REGULATOR_VOLTAGE_SCALE1 (3U << 14)
#define RCC_OSCILLATORTYPE_HSI 2U
#define RCC_HSI_ON            1U
#define RCC_HSICALIBRATION_DEFAULT 0x10U
#define RCC_PLL_ON            2U
#define RCC_PLLSOURCE_HSI     0U
#define RCC_PLLP_DIV2         2U
#define RCC_CLOCKTYPE_HCLK    1U
#define RCC_CLOCKTYPE_SYSCLK  2U
#define RCC_CLOCKTYPE_PCLK1   4U
#define RCC_CLOCKTYPE_PCLK2   8U
#define RCC_SYSCLKSOURCE_PLLCLK 2U
#define RCC_SYSCLK_DIV1       0U
#define RCC_HCLK_DIV4         0x1400U
#define RCC_HCLK_DIV2         0x1000U

#ifdef __cplusplus
}
#endif

#endif /* STM32F411XE_H */
