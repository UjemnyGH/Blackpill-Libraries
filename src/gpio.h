#ifndef __GENERAL_PURPOSE_IO_
#define __GENERAL_PURPOSE_IO_

#include "rcc.h"

struct GeneralPurposeIO {
    io32 mode;
    io32 outputType;
    io32 outputSpeed;
    io32 pull;
    io32 inputData;
    io32 outputData;
    io32 bitSetReset;
    io32 configLock;
    io32 altFuncLow;
    io32 altFuncHigh;

    #if defined(STM32_L4XX)
    io32 bitReset;
    io32 analogSwitchControl;
    #endif
};

#define GeneralPurposeIO_H ((struct GeneralPurposeIO *)GPIOH_BASE)
#define GeneralPurposeIO_E ((struct GeneralPurposeIO *)GPIOE_BASE)
#define GeneralPurposeIO_D ((struct GeneralPurposeIO *)GPIOD_BASE)
#define GeneralPurposeIO_C ((struct GeneralPurposeIO *)GPIOC_BASE)
#define GeneralPurposeIO_B ((struct GeneralPurposeIO *)GPIOB_BASE)
#define GeneralPurposeIO_A ((struct GeneralPurposeIO *)GPIOA_BASE)

#define IO_A GeneralPurposeIO_A
#define IO_B GeneralPurposeIO_B
#define IO_C GeneralPurposeIO_C
#define IO_D GeneralPurposeIO_D
#define IO_E GeneralPurposeIO_E
#define IO_H GeneralPurposeIO_H

#if defined(STM32_L4XX)
#define GeneralPurposeIO_G ((struct GeneralPurposeIO *)GPIOG_BASE)
#define GeneralPurposeIO_F ((struct GeneralPurposeIO *)GPIOF_BASE)

#define IO_F GeneralPurposeIO_F
#define IO_G GeneralPurposeIO_G
#endif

#define GPIO_MODE_INPUT         0
#define GPIO_MODE_OUTPUT        1
#define GPIO_MODE_ALT_FN        2
#define GPIO_MODE_ANALOG        3
#define GPIOA_MODE_RESET        0xa8000000
#define GPIOB_MODE_RESET        0x280
#define GPIO_MODE_RESET         0x0

#define MODE_INPUT      GPIO_MODE_INPUT
#define MODE_OUTPUT     GPIO_MODE_OUTPUT
#define MODE_ALT_FN     GPIO_MODE_ALT_FN
#define MODE_ANALOG     GPIO_MODE_ANALOG
/*
#define InitGPIO(gpio, lowPowerMode) if(gpio != GPIOH_BASE) { if(lowPowerMode == 0) { ResetClockControl->ahb1Enable |= ((GPIOB_BASE << 16) >> 16) / 0x400; } else { ResetClockControl->ahb1LowPowerEnable |= ((GPIOB_BASE << 16) >> 16) / 0x400; }} else { if(lowPowerMode == 0) { ResetClockControl->ahb1Enable |= 7; } else { ResetClockControl->ahb1LowPowerEnable |= 7; }}
*/

void InitGPIO(struct GeneralPurposeIO* io, uint8 lowPower) {
    io32* enable;

    if(!lowPower) {
        #if defined(STM32_L4XX)
        enable = &ResetClockControl->ahb2Enable;
        #elif defined(STM32_F4XX)
        enable = &ResetClockControl->ahb1Enable;
        #endif
    }
    else {
        #if defined(STM32_L4XX)
        enable = &ResetClockControl->ahb2LowPowerEnable;
        #elif defined(STM32_F4XX)
        enable = &ResetClockControl->ahb1LowPowerEnable;
        #endif
    }

    uint32 io_base = (uint32)io;

    switch(io_base) {
        case GPIOA_BASE: *enable |= 0x1; break;
        case GPIOB_BASE: *enable |= 0x2; break;
        case GPIOC_BASE: *enable |= 0x4; break;
        case GPIOD_BASE: *enable |= 0x8; break;
        case GPIOE_BASE: *enable |= 0x10; break;
        #if defined(STM32_L4XX)
        case GPIOF_BASE: *enable |= 0x20; break;
        case GPIOG_BASE: *enable |= 0x40; break;
        #endif
        case GPIOH_BASE: *enable |= 0x80; break;
        default: *enable |= 0x0; break;
    }
}

#if defined(STM32_F4XX)
#define InitGPIOA ResetClockControl->ahb1Enable |= 0x1
#define InitGPIOB ResetClockControl->ahb1Enable |= 0x2
#define InitGPIOC ResetClockControl->ahb1Enable |= 0x4
#define InitGPIOD ResetClockControl->ahb1Enable |= 0x8
#define InitGPIOE ResetClockControl->ahb1Enable |= 0x10
#define InitGPIOH ResetClockControl->ahb1Enable |= 0x80

#define InitGPIOALowPower ResetClockControl->ahb1LowPowerEnable |= 0x1
#define InitGPIOBLowPower ResetClockControl->ahb1LowPowerEnable |= 0x2
#define InitGPIOCLowPower ResetClockControl->ahb1LowPowerEnable |= 0x4
#define InitGPIODLowPower ResetClockControl->ahb1LowPowerEnable |= 0x8
#define InitGPIOELowPower ResetClockControl->ahb1LowPowerEnable |= 0x10
#define InitGPIOHLowPower ResetClockControl->ahb1LowPowerEnable |= 0x80
#endif


#define setPinModeGPIO(gpio, pin, modeset) gpio->mode &= ~(3 << (pin * 2)); gpio->mode |= modeset << (pin * 2)

#define GPIO_OUTPUT_TYPE_PUSH_PULL      0
#define GPIO_OUTPUT_TYPE_OPEN_DRAIN     1
#define GPIO_OUTPUT_TYPE_RESET          0x0

#define setOutputTypeGPIO(gpio, pin, mode) gpio->outputType &= ~(1 << pin); gpio->outputType |= mode << pin

#define GPIO_OUTPUT_SPEED_LOW       0
#define GPIO_OUTPUT_SPEED_MEDIUM    1
#define GPIO_OUTPUT_SPEED_FAST      2
#define GPIO_OUTPUT_SPEED_HIGH      3
#define GPIOA_OUTPUT_SPEED_RESET    0x0c000000
#define GPIOB_OUTPUT_SPEED_RESET    0xc0
#define GPIO_OUTPUT_SPEED_RESET     0x0

#define setSpeedGPIO(gpio, pin, speed) gpio->outputSpeed &= ~(3 << (pin * 2)); gpio->outputSpeed |= speed << (pin * 2)

#define GPIO_PULL_NONE      0
#define GPIO_PULL_UP        1
#define GPIO_PULL_DOWN      2
#define GPIOA_PULL_RESET    0x64000000
#define GPIOB_PULL_RESET    0x100
#define GPIO_PULL_RESET     0x0

#define setPullGPIO(gpio, pin, pullset) gpio->pull &= ~(3 << (pin * 2)); gpio->pull |= pullset << (pin * 2)

#define GPIO_OUTPUT_DATA_RESET  0x0

#define getInputGPIO(gpio, pin) (gpio->inputData & (1UL << pin))
#define setOutputGPIO(gpio, pin, state) gpio->outputData &= ~(1 << pin); gpio->outputData |= (state != 0 ? 1 : 0) << pin

#define GPIO_BIT_SET(bit)       (bit)
#define GPIO_BIT_RESET(bit)     (bit << 15)

#define setBitGPIO(gpio, pin) gpio->bitSetReset |= 1 << pin
#define resetBitGPIO(gpio, pin) gpio->bitSetReset |= (1 << 16) << pin

#define GPIO_UNLOCK         0
#define GPIO_LOCK           1

#endif