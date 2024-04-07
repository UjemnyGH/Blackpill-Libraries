#ifndef __RESET_CLOCK_CONTROL_
#define __RESET_CLOCK_CONTROL_

#include "registers.h"

#if defined(STM32_F4XX)

struct ResetClockControl {
    io32 control;
    io32 pllConfig;
    io32 clockConfig;
    io32 clockInterrupt;
    io32 ahb1Reset;
    io32 ahb2Reset;
    uint32 res0;
    uint32 res1;
    io32 apb1Reset;
    io32 apb2Reset;
    uint32 res2;
    uint32 res3;
    io32 ahb1Enable;
    io32 ahb2Enable;
    uint32 res4;
    uint32 res5;
    io32 apb1Enable;
    io32 apb2Enable;
    uint32 res6;
    uint32 res7;
    io32 ahb1LowPowerEnable;
    io32 ahb2LowPowerEnable;
    uint32 res8;
    uint32 res9;
    io32 apb1LowPowerEnable;
    io32 apb2LowPowerEnable;
    uint32 res10;
    uint32 res11;
    io32 backupDomainControl;
    io32 clockControlStatus;
    uint32 res12;
    uint32 res13;
    io32 spreadSpectrumClockGeneration;
    io32 pllI2SConfig;
    io32 dedicatedClockConfig;
};

#elif defined(STM32_L4XX) 

struct ResetClockControl {
    io32 control;
    io32 internalClockSourcesCalibration;
    io32 clockConfig;
    io32 pllConfig;
    io32 pllSai1Config;
    io32 pllSai2Config;
    io32 clockInterruptEnable;
    io32 clockInterruptFlag;
    io32 clockInterruptClear;
    uint32 res0;
    io32 ahb1Reset;
    io32 ahb2Reset;
    io32 ahb3Reset;
    uint32 res1;
    io32 apb1Reset1;
    io32 apb1Reset2;
    io32 apb2Reset;
    uint32 res2;
    io32 ahb1Enable;
    io32 ahb2Enable;
    io32 ahb3Enable;
    uint32 res3;
    io32 apb1Enable1;
    io32 apb1Enable2;
    io32 apb2Enable;
    uint32 res4;
    io32 ahb1LowPowerEnable;
    io32 ahb2LowPowerEnable;
    io32 ahb3LowPowerEnable;
    uint32 res5;
    io32 apb1LowPowerEnable1;
    io32 apb1LowPowerEnable2;
    io32 apb2LowPowerEnable;
    uint32 res6;
    io32 periphIndependentClockConfig;
    uint32 res7;
    io32 backupDomainControl;
    io32 clockControlStatus;
};

#else

#error "Select board to use RCC"

#endif

#define ResetClockControl ((struct ResetClockControl *)RCC_BASE)

#endif