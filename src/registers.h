#ifndef __REGISTERS_
#define __REGISTERS_

typedef unsigned int uint32;
typedef volatile uint32 io32;
typedef unsigned char uint8;
typedef short int8;
typedef unsigned short uint16;

inline void delay(int sec) {
    while(sec--) asm("nop");
}

#if defined(STM32_F4XX)
// AHB2
#define USB_OTG_FS_BASE         0x50000000
// AHB1
#define DMA2_BASE               0x40026400
#define DMA1_BASE               0x40026000
#define FLASH_INTERFACE_BASE    0x40023c00
#define RCC_BASE                0x40023800
#define CRC_BASE                0x40023000
#define GPIOH_BASE              0x40021c00
#define GPIOE_BASE              0x40021000
#define GPIOD_BASE              0x40020c00
#define GPIOC_BASE              0x40020800
#define GPIOB_BASE              0x40020400
#define GPIOA_BASE              0x40020000
// APB2
#define SPI5_BASE               0x40015000
#define TIM11_BASE              0x40014800
#define TIM10_BASE              0x40014400
#define TIM9_BASE               0x40014000
#define EXTI_BASE               0x40013c00
#define SYSCFG_BASE             0x40013800
#define SPI4_BASE               0x40013400
#define SPI1_BASE               0x40013000
#define SDIO_BASE               0x40012c00
#define ADC1_BASE               0x40012000
#define USART6_BASE             0x40011400
#define USART1_BASE             0x40011000
#define TIM1_BASE               0x40010000
// APB1
#define PWR_BASE                0x40007000
#define I2C3_BASE               0x40005c00
#define I2C2_BASE               0x40005800
#define I2C1_BASE               0x40005400
#define USART2_BASE             0x40004400
#define I2S3EXT_BASE            0x40004000
#define SPI3_BASE               0x40003c00
#define SPI2_BASE               0x40003800
#define I2S2EXT_BASE            0x40003400
#define IWDG_BASE               0x40003000
#define WWDG_BASE               0x40002c00
#define RTC_BASE                0x40002800
#define TIM5_BASE               0x40000c00
#define TIM4_BASE               0x40000800
#define TIM3_BASE               0x40000400
#define TIM2_BASE               0x40000000

#elif defined(STM32_L4XX)
// AHB2
#define RNG_BASE                0x50060800
#define AES_BASE                0x50060000
#define ADC_BASE                0x50040000
#define OTG_FS_BASE             0x50000000
#define GPIOH_BASE              0x48001C00
#define GPIOG_BASE              0x48001800
#define GPIOF_BASE              0x48001400
#define GPIOE_BASE              0x48001000
#define GPIOD_BASE              0x48000C00
#define GPIOC_BASE              0x48000800
#define GPIOB_BASE              0x48000400
#define GPIOA_BASE              0x48000000
// AHB1
#define TSC_BASE                0x40024000
#define CRC_BASE                0x40023000
#define FLASH_BASE              0x40022000
#define RCC_BASE                0x40021000
#define DMA2_BASE               0x40020400
#define DMA1_BASE               0x40020000
// ABP2
#define DFSDM1_BASE             0x40016000
#define SAI2_BASE               0x40015800
#define SAI1_BASE               0x40015400
#define TIM17_BASE              0x40014800
#define TIM16_BASE              0x40014400
#define TIM15_BASE              0x40014000
#define USART1_BASE             0x40013800
#define TIM8_BASE               0x40013400
#define SPI1_BASE               0x40013000
#define TIM1_BASE               0x40012C00
#define SDMMC1_BASE             0x40012800
#define FIREWALL_BASE           0x40011C00
#define EXTI_BASE               0x40010400
#define COMP_BASE               0x40010200
#define VREFBUF_BASE            0x40010030
#define SYSCFG_BASE             0x40010000
// ABP1
#define LPTIM2_BASE             0x40009400
#define SWPMI1_BASE             0x40008800
#define LPUART1_BASE            0x40008000
#define LPTIM1_BASE             0x40007C00
#define OPAMP_BASE              0x40007800
#define DAC1_BASE               0x40007400
#define PWR_BASE                0x40007000
#define CAN1_BASE               0x40006400
#define I2C3_BASE               0x40005C00
#define I2C2_BASE               0x40005800
#define I2C1_BASE               0x40005400
#define UART5_BASE              0x40005000
#define UART4_BASE              0x40004C00
#define USART3_BASE             0x40004800
#define USART2_BASE             0x40004400
#define SPI3_BASE               0x40003C00
#define SPI2_BASE               0x40003800
#define IWDG_BASE               0x40003000
#define WWDG_BASE               0x40002C00
#define RTC_BASE                0x40002800
#define LCD_BASE                0x40002400
#define TIM7_BASE               0x40001400
#define TIM6_BASE               0x40001000
#define TIM5_BASE               0x40000C00
#define TIM4_BASE               0x40000800
#define TIM3_BASE               0x40000400
#define TIM2_BASE               0x40000000

#else

#error Board not defined (use #define STM32_L4XX or #define STM32_F4XX)

#endif

#define FALSE   0
#define TRUE    1
#define LOW     0
#define HIGH    1

#endif