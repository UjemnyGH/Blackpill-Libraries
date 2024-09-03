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

#define RCC_CONTROL_PLL_ON  0x1000000
#define RCC_CONTROL_HSE_BYPASS  0x40000
#define RCC_CONTROL_HSE_ON  0x10000
#define RCC_CONTROL_HSI_ON  1

#define RCC_PLL_CFG_USB_DIVISOR_2       0x2000000
#define RCC_PLL_CFG_USB_DIVISOR_3       0x3000000
#define RCC_PLL_CFG_USB_DIVISOR_4       0x4000000
#define RCC_PLL_CFG_USB_DIVISOR_5       0x5000000
#define RCC_PLL_CFG_USB_DIVISOR_6       0x6000000
#define RCC_PLL_CFG_USB_DIVISOR_7       0x7000000
#define RCC_PLL_CFG_USB_DIVISOR_8       0x8000000
#define RCC_PLL_CFG_USB_DIVISOR_9       0x9000000
#define RCC_PLL_CFG_USB_DIVISOR_10      0xA000000
#define RCC_PLL_CFG_USB_DIVISOR_11      0xB000000
#define RCC_PLL_CFG_USB_DIVISOR_12      0xC000000
#define RCC_PLL_CFG_USB_DIVISOR_13      0xD000000
#define RCC_PLL_CFG_USB_DIVISOR_14      0xE000000
#define RCC_PLL_CFG_USB_DIVISOR_15      0xF000000
#define RCC_PLL_CFG_I2S_SOURCE_HSE      0x400000
#define RCC_PLL_CFG_SYS_CLOCK_DIVISOR_2 0
#define RCC_PLL_CFG_SYS_CLOCK_DIVISOR_4 0x10000
#define RCC_PLL_CFG_SYS_CLOCK_DIVISOR_6 0x20000
#define RCC_PLL_CFG_SYS_CLOCK_DIVISOR_8 0x30000
/**
 * @brief Range from 50 to 432
 * 
 */
#define RCC_PLL_CFG_VCO_MULTIPLICATOR(value) (value << 6)
/**
 * @brief Range from 2 to 63
 * 
 */
#define RCC_PLL_CFG_INPUT_CLOCK_DIVISOR(value) value

#define RCC_CLOCK_CFG_MCU_CLOCK_OUTPUT2_SYS_CLK  0x0
#define RCC_CLOCK_CFG_MCU_CLOCK_OUTPUT2_PLL_I2S  0x40000000
#define RCC_CLOCK_CFG_MCU_CLOCK_OUTPUT2_HSE  0x80000000
#define RCC_CLOCK_CFG_MCU_CLOCK_OUTPUT2_PLL  0xC0000000

#define RCC_CLOCK_CFG_MCU_CLOCK_OUTPUT1_HSI  0x0
#define RCC_CLOCK_CFG_MCU_CLOCK_OUTPUT1_LSE  0x200000
#define RCC_CLOCK_CFG_MCU_CLOCK_OUTPUT1_HSE  0x400000
#define RCC_CLOCK_CFG_MCU_CLOCK_OUTPUT1_PLL  0x600000

#define ResetClockControl ((struct ResetClockControl *)RCC_BASE)

#endif