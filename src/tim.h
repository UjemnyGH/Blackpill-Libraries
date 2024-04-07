#ifndef __TIMERS_
#define __TIMERS_

#include "rcc.h"

struct Timer1 {
    io32 control1;
    io32 control2;
    io32 slaveModeControl;
    io32 dmaInterruptEnable;
    io32 status;
    io32 eventGeneration;
    io32 captureCompareMode1;
    io32 captureCompareMode2;
    io32 captureCompareEnable;
    io32 counter;
    io32 prescaler;
    io32 autoReload;
    io32 repetitionCounter;
    io32 captureCompare1;
    io32 captureCompare2;
    io32 captureCompare3;
    io32 captureCompare4;
    io32 breakAndDeadTime;
    io32 dmaControl;
    io32 dmaAddress;
};

#define Timer1  ((struct Timer1 *)TIM1_BASE)

#define InitTimer1      ResetClockControl->apb2Enable |= 0x1
#define InitTimer1LowPower      ResetClockControl->apb2LowPowerEnable |= 0x1

struct Timer2_5 {
    io32 control1;
    io32 control2;
    io32 slaveModeControl;
    io32 interruptEnable;
    io32 status;
    io32 eventGeneration;
    io32 captureCompareMode1;
    io32 captureCompareMode2;
    io32 captureCompareEnable;
    io32 counter;
    io32 prescaler;
    io32 autoReload;
    uint32 res0;
    io32 captureCompare1;
    io32 captureCompare2;
    io32 captureCompare3;
    io32 captureCompare4;
    io32 dmaControl;
    io32 dmaAddress;
    io32 option;
};

struct Timer9_11 {
    io32 control1;
    uint32 res0;
    io32 slaveModeControl;
    io32 interruptEnable;
    io32 status;
    io32 eventGeneration;
    io32 captureCompareMode1;
    uint32 res1;
    io32 captureCompareEnable;
    io32 counter;
    io32 prescaler;
    io32 autoReload;
    uint32 res2;
    io32 captureCompare1;
    io32 captureCompare2;
    uint32 res3;
    uint32 res4;
    uint32 res5;
    uint32 res6;
};

#endif