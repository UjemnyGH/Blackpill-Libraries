#ifndef __SPI_STM32_
#define __SPI_STM32_

#include "rcc.h"

struct SPI {
    io32 control1;
    io32 control2;
    io32 status;
    io32 data;
    /**
     * @brief Needs SPI_CONTROL1_HARDWARE_CRC_CALC and SPI_CONTROL1_CRC_TRANSFER
     * 
     */
    io32 crcPolynomial;
    /**
     * @brief Needs SPI_CONTROL1_HARDWARE_CRC_CALC and SPI_CONTROL1_CRC_TRANSFER
     * 
     */
    io32 receiveCrc;
    /**
     * @brief Needs SPI_CONTROL1_HARDWARE_CRC_CALC and SPI_CONTROL1_CRC_TRANSFER
     * 
     */
    io32 transmitCrc;
    io32 i2sConfig;
    io32 i2sPrescaler;
};

#define InitSPI5 ResetClockControl->apb2Enable |= 0x100000
#define InitSPI4 ResetClockControl->apb2Enable |= 0x2000
#define InitSPI3 ResetClockControl->apb1Enable |= 0x8000
#define InitSPI2 ResetClockControl->apb1Enable |= 0x4000
#define InitSPI1 ResetClockControl->apb2Enable |= 0x1000

#define InitSPI5LowPower ResetClockControl->apb2LowPowerEnable |= 0x100000
#define InitSPI4LowPower ResetClockControl->apb2LowPowerEnable |= 0x2000
#define InitSPI3LowPower ResetClockControl->apb1LowPowerEnable |= 0x8000
#define InitSPI2LowPower ResetClockControl->apb1LowPowerEnable |= 0x4000
#define InitSPI1LowPower ResetClockControl->apb2LowPowerEnable |= 0x1000

/**  
 * Pins:
 * B0 - SCK
 * A12 - MISO
 * B8, A10 - MOSI
 * B1 - NSS
 */
#define SPI5 ((struct SPI *)SPI5_BASE)
/**  
 * Pins:
 * B13 - SCK
 * A11 - MISO
 * A1 - MOSI
 * B12 - NSS
 */
#define SPI4 ((struct SPI *)SPI4_BASE)
/**  
 * Pins:
 * B12, B3 - SCK
 * B4 - MISO
 * B5 - MOSI
 * A4 - NSS
 */
#define SPI3 ((struct SPI *)SPI3_BASE)
/**  
 * Pins:
 * B13, B10 - SCK
 * B14 - MISO
 * B15 - MOSI
 * B9, B12 - NSS
 */
#define SPI2 ((struct SPI *)SPI2_BASE)
/**  
 * Pins:
 * A5 - SCK
 * B4 - MISO
 * B5 - MOSI
 * A4, A15 - NSS
 */
#define SPI1 ((struct SPI *)SPI1_BASE)

#define SPI_CONTROL1_BIDIRECTIONAL_MODE  0x8000
#define SPI_CONTROL1_OUTPUT_EN_BIDIR     0x4000
#define SPI_CONTROL1_HARDWARE_CRC_CALC   0x2000
#define SPI_CONTROL1_CRC_TRANSFER        0x1000
/**
 * @brief Default is 8-bit (11 bit set to 0)
 * 
 */
#define SPI_CONTROL1_DATA_FRAME_16BIT    0x800
#define SPI_CONTROL1_RECEIVE_ONLY        0x400
#define SPI_CONTROL1_SOFTWARE_SLAVE_MANAGEMENT   0x200
#define SPI_CONTROL1_INTERNAL_SLAVE_SELECT       0x100
#define SPI_CONTROL1_FRAME_FORMAT_LSB            0x80
#define SPI_CONTROL1_ENABLE              0x40
#define SPI_CONTROL1_BAUDRATE_2          (0 << 3)
#define SPI_CONTROL1_BAUDRATE_4          0x8
#define SPI_CONTROL1_BAUDRATE_8          0x10
#define SPI_CONTROL1_BAUDRATE_16         0x18
#define SPI_CONTROL1_BAUDRATE_32         0x20
#define SPI_CONTROL1_BAUDRATE_64         0x28
#define SPI_CONTROL1_BAUDRATE_128        0x30
#define SPI_CONTROL1_BAUDRATE_256        0x38
#define SPI_CONTROL1_MASTER_SEL          0x4
#define SPI_CONTROL1_CLOCK_POLARITY      0x2
#define SPI_CONTROL1_CLOCK_PHASE_SECOND  0x1

#define SPI_CONTROL2_TX_BUFFER_EMPTY_INT_ENABLE     0x80
#define SPI_CONTROL2_RX_BUFFER_NOT_EMPTY_INT_ENABLE 0x40
#define SPI_CONTROL2_ERROR_INT_ENABLE               0x20
#define SPI_CONTROL2_FRAME_FORMAT_TI_MODE           0x10
#define SPI_CONTROL2_SS_OUTPUT_ENABLE               0x4
#define SPI_CONTROL2_TX_BUFFER_DMA_ENABLE           0x2
#define SPI_CONTROL2_RX_BUFFER_DMA_ENABLE           0x1

/**
 * @brief FLAGS!!! THESE ARE READ-ONLY
 * 
 */
#define SPI_STATUS_FRAME_FORMAT_ERROR       0x100
/**
 * @brief FLAGS!!! THESE ARE READ-ONLY
 * 
 */
#define SPI_STATUS_BUSY                     0x80
/**
 * @brief FLAGS!!! THESE ARE READ-ONLY
 * 
 */
#define SPI_STATUS_OVERRUN                  0x40
/**
 * @brief FLAGS!!! THESE ARE READ-ONLY
 * 
 */
#define SPI_STATUS_MODE_FAULT               0x20
/**
 * @brief FLAGS!!! THESE ARE READ-ONLY
 * 
 */
#define SPI_STATUS_CRC_ERROR                0x10
/**
 * @brief FLAGS!!! THESE ARE READ-ONLY
 * 
 */
#define SPI_STATUS_UNDERRUN                 0x8
/**
 * @brief FLAGS!!! THESE ARE READ-ONLY
 * 
 */
#define SPI_STATUS_CHANNEL_SIDE             0x4
/**
 * @brief FLAGS!!! THESE ARE READ-ONLY
 * 
 */
#define SPI_STATUS_TX_BUFFER_EMPTY          0x2
/**
 * @brief FLAGS!!! THESE ARE READ-ONLY
 * 
 */
#define SPI_STATUS_RX_BUFFER_NOT_EMPTY      0x1

#define SPI_I2S_CONFIG_SELECT_I2S_MODE      0x800
#define SPI_I2S_CONFIG_I2S_ENABLE_PERIPH    0x400
#define SPI_I2S_CONFIG_SLAVE_TRANSMIT       (0 << 8)
#define SPI_I2S_CONFIG_SLAVE_RECEIVE        0x100
#define SPI_I2S_CONFIG_MASTER_TRANSMIT      0x200
#define SPI_I2S_CONFIG_MASTER_RECEIVE       0x300

#define SPI_I2S_CONFIG_PCM_LONG_FRAME_SYNC  0x80
#define SPI_I2S_CONFIG_I2S_STANDARD_PHILIPS         (0 << 4)
#define SPI_I2S_CONFIG_I2S_STANDARD_MSB_JUSTIFIED   0x10
#define SPI_I2S_CONFIG_I2S_STANDARD_LSB_JUSTIFIED   0x20
#define SPI_I2S_CONFIG_I2S_STANDARD_PCM             0x30

#define SPI_I2S_CONFIG_STEADY_STATE_CLOCK_POLARITY_HIGH_LEVEL   0x8
#define SPI_I2S_CONFIG_DATA_LENGTH_16BIT            (0 << 1)
#define SPI_I2S_CONFIG_DATA_LENGTH_24BIT            0x2
#define SPI_I2S_CONFIG_DATA_LENGTH_32BIT            0x4

#define SPI_I2S_CONFIG_CHANNEL_LENGTH_32BIT_WIDE    0x1

#define SPI_I2S_PRESCALER_MASTER_CLOCK_OUTPUT_ENABLE    0x200
#define SPI_I2S_PRESCALER_ODD_FACTOR                    0x100

#endif