#ifndef FAULT_MANAGER_H
#define FAULT_MANAGER_H

#include "stm32f4xx_hal.h"

typedef enum
{
    FAULT_NONE = 0,

    FAULT_INVALID_CONFIG,
    FAULT_DMA,
    FAULT_TIMER,
    FAULT_DAC,
    FAULT_COMMUNICATION,
    FAULT_BUFFER

} FaultCode;

/* Initialize fault manager */
void FaultManager_Init(void);

/* Set a fault */
void FaultManager_Set(FaultCode fault);

/* Clear the current fault */
void FaultManager_Clear(void);

/* Get current fault */
FaultCode FaultManager_Get(void);

/* Check whether any fault is active */
uint8_t FaultManager_HasFault(void);

#endif /* FAULT_MANAGER_H */
