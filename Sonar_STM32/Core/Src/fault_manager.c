#include "fault_manager.h"

static volatile FaultCode current_fault = FAULT_NONE;

void FaultManager_Init(void)
{
    current_fault = FAULT_NONE;
}

void FaultManager_Set(FaultCode fault)
{
    current_fault = fault;
}

void FaultManager_Clear(void)
{
    current_fault = FAULT_NONE;
}

FaultCode FaultManager_Get(void)
{
    return current_fault;
}

uint8_t FaultManager_HasFault(void)
{
    return (current_fault != FAULT_NONE);
}
