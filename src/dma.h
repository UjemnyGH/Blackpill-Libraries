#ifndef __DIRECT_MEMORY_ACCESS_
#define __DIRECT_MEMORY_ACCESS_

#include "rcc.h"

struct DirectMemoryAccess {
    io32 loIntStatus;
    io32 hiIntStatus;
    io32 loIntFlagClear;
    io32 hiIntFlagClear;

    io32 streamConfig0;
    io32 streamDataNumber0;
    io32 streamPeriphAddress0;
    io32 streamMemory0Address0;
    io32 streamMemory1Address0;
    io32 streamFIFOCtrl0;

    io32 streamConfig1;
    io32 streamDataNumber1;
    io32 streamPeriphAddress1;
    io32 streamMemory0Address1;
    io32 streamMemory1Address1;
    io32 streamFIFOCtrl1;

    io32 streamConfig2;
    io32 streamDataNumber2;
    io32 streamPeriphAddress2;
    io32 streamMemory0Address2;
    io32 streamMemory1Address2;
    io32 streamFIFOCtrl2;

    io32 streamConfig3;
    io32 streamDataNumber3;
    io32 streamPeriphAddress3;
    io32 streamMemory0Address3;
    io32 streamMemory1Address3;
    io32 streamFIFOCtrl3;

    io32 streamConfig4;
    io32 streamDataNumber4;
    io32 streamPeriphAddress4;
    io32 streamMemory0Address4;
    io32 streamMemory1Address4;
    io32 streamFIFOCtrl4;

    io32 streamConfig5;
    io32 streamDataNumber5;
    io32 streamPeriphAddress5;
    io32 streamMemory0Address5;
    io32 streamMemory1Address5;
    io32 streamFIFOCtrl5;

    io32 streamConfig6;
    io32 streamDataNumber6;
    io32 streamPeriphAddress6;
    io32 streamMemory0Address6;
    io32 streamMemory1Address6;
    io32 streamFIFOCtrl6;

    io32 streamConfig7;
    io32 streamDataNumber7;
    io32 streamPeriphAddress7;
    io32 streamMemory0Address7;
    io32 streamMemory1Address7;
    io32 streamFIFOCtrl7;
};

#define DirectMemoryAccess1     ((struct DirectMemoryAccess *)DMA1_BASE)
#define DirectMemoryAccess2     ((struct DirectMemoryAccess *)DMA2_BASE)

#define InitDirectMemoryAccess1 ResetClockControl->ahb1Enable |= 0x200000
#define InitDirectMemoryAccess2 ResetClockControl->ahb1Enable |= 0x400000

#define InitDirectMemoryAccess1LowPower ResetClockControl->ahb1LowPowerEnable |= 0x200000
#define InitDirectMemoryAccess2LowPower ResetClockControl->ahb1LowPowerEnable |= 0x400000

#endif