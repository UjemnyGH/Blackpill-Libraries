#ifndef __ADXL345_
#define __ADXL345_

#include "spi_software.h"

#define ADXL_ID                     0x00
#define ADXL_TAP_TRSH               0x1D
#define ADXL_OFFSET_AXIS_X          0x1E 
#define ADXL_OFFSET_AXIS_Y          0x1F 
#define ADXL_OFFSET_AXIS_Z          0x20 
#define ADXL_DUR                    0x21 
#define ADXL_TAP_LATENCY            0x22 
#define ADXL_TAP_WINDOW             0x23 
#define ADXL_THRESH_ACT             0x24 
#define ADXL_THRESH_INACT           0x25 
#define ADXL_TIME_INACT             0x26 
#define ADXL_ACT_INACT_CTL          0x27 
#define ADXL_THRESH_FREE_FALL       0x28 
#define ADXL_TIME_FREE_FALL         0x29 
#define ADXL_TAP_AXES               0x2A 
#define ADXL_ACT_TAP_STATUS         0x2B 
#define ADXL_DATA_RATE_POWER_MODE   0x2C 
#define ADXL_POWER_CTL              0x2D 
#define ADXL_INT_ENABLE             0x2E 
#define ADXL_INT_MAP                0x2F 
#define ADXL_INT_SOURCE             0x30 
#define ADXL_DATA_FORMAT            0x31 
#define ADXL_DATA_X0                0x32 
#define ADXL_DATA_X1                0x33 
#define ADXL_DATA_Y0                0x34 
#define ADXL_DATA_Y1                0x35 
#define ADXL_DATA_Z0                0x36 
#define ADXL_DATA_Z1                0x37 
#define ADXL_FIFO_CTL               0x38 
#define ADXL_FIFO_STATUS            0x39

// States
#define S_ADXL_DR_PM_CTRL_3200Hz    0xf
#define S_ADXL_DR_PM_CTRL_1600Hz    0xe
#define S_ADXL_DR_PM_CTRL_800Hz     0xd
// low power states 
#define S_ADXL_DR_PM_CTRL_400Hz     0x1c
#define S_ADXL_DR_PM_CTRL_200Hz     0x1b
#define S_ADXL_DR_PM_CTRL_100Hz     0x1a
#define S_ADXL_DR_PM_CTRL_50Hz      0x19
#define S_ADXL_DR_PM_CTRL_25Hz      0x18
#define S_ADXL_DR_PM_CTRL_12Hz      0x17
#define S_ADXL_DR_PM_CTRL_6Hz       0x16
// active/inactive control states
#define S_ADXL_ACTIVE_ADC           0x80
#define S_ADXL_ACTIVE_X             0x40
#define S_ADXL_ACTIVE_Y             0x20
#define S_ADXL_ACTIVE_Z             0x10
#define S_ADXL_INACTIVE_ADC         0x8
#define S_ADXL_INACTIVE_X           0x4
#define S_ADXL_INACTIVE_Y           0x2
#define S_ADXL_INACTIVE_Z           0x1
// Tap axis control state
#define S_ADXL_TAP_AXIS_CTRL_SUP    0x8
#define S_ADXL_TAP_AXIS_CTRL_X_EN   0x4
#define S_ADXL_TAP_AXIS_CTRL_Y_EN   0x2
#define S_ADXL_TAP_AXIS_CTRL_Z_EN   0x1
// Power control state
#define S_ADXL_POWER_CTRL_LINK      0x20
#define S_ADXL_POWER_CTRL_AUTO_SLEEP    0x10
#define S_ADXL_POWER_CTRL_MEASURE   0x8
#define S_ADXL_POWER_CTRL_SLEEP     0x4
#define S_ADXL_POWER_CTRL_WAKEUP_8Hz    0x0
#define S_ADXL_POWER_CTRL_WAKEUP_4Hz    0x1
#define S_ADXL_POWER_CTRL_WAKEUP_2Hz    0x2
#define S_ADXL_POWER_CTRL_WAKEUP_1Hz    0x3
// Active tap status state
#define S_ADXL_ACT_TAP_STAT_ACT_X_SRC   0x40
#define S_ADXL_ACT_TAP_STAT_ACT_Y_SRC   0x20
#define S_ADXL_ACT_TAP_STAT_ACT_Z_SRC   0x10
#define S_ADXL_ACT_TAP_STAT_ASLEEP  0x8
#define S_ADXL_ACT_TAP_STAT_TAP_X_SRC   0x4
#define S_ADXL_ACT_TAP_STAT_TAP_Y_SRC   0x2
#define S_ADXL_ACT_TAP_STAT_TAP_Z_SRC   0x1
// Read/Write data format state
#define S_ADXL_RW_DATA_FORMAT_SELFTEST  0x80
#define S_ADXL_RW_DATA_FORMAT_SPI   0x40
#define S_ADXL_RW_DATA_FORMAT_INT_INV   0x20
#define S_ADXL_RW_DATA_FORMAT_FULL_RES  0x8
#define S_ADXL_RW_DATA_FORMAT_JUSTIFY   0x4
#define S_ADXL_RW_DATA_FORMAT_RANGE_2G  0x0
#define S_ADXL_RW_DATA_FORMAT_RANGE_4G  0x1
#define S_ADXL_RW_DATA_FORMAT_RANGE_8G  0x2
#define S_ADXL_RW_DATA_FORMAT_RANGE_16G 0x3
// Interrupt enable/map state
#define S_ADXL_INT_DATA_READY       0x80
#define S_ADXL_INT_SINGLE_TAP       0x40
#define S_ADXL_INT_DOUBLE_TAP       0x20
#define S_ADXL_INT_ACTIVE           0x10
#define S_ADXL_INT_INACTIVE         0x8
#define S_ADXL_INT_FREE_FALL        0x4
#define S_ADXL_INT_WATERMARK        0x2
#define S_ADXL_INT_OVERRUN          0x1
// FIFO control state
#define S_ADXL_FIFO_CTRL_MBYPASS    0x0
#define S_ADXL_FIFO_CTRL_MFIFO      0x40
#define S_ADXL_FIFO_CTRL_MSTREAM    0x80
#define S_ADXL_FIFO_CTRL_MTRIGGER   0xc0
#define S_ADXL_FIFO_CTRL_TRIGGER    0x20

typedef struct ADXL345 {
    SPI_Software_TX mSpi;
    uint8 mInterrupt1Pin, mInterrupt2Pin;
    struct GeneralPurposeIO *mInterrupt1IO, *mInterrupt2IO; 
} ADXL345;

void ADXL_Begin(ADXL345* adxl, uint8 csp, uint8 int1p, uint8 int2p, uint8 sdop, uint8 sdap, uint8 sclkp, struct GeneralPurposeIO *csio, struct GeneralPurposeIO *int1io, struct GeneralPurposeIO *int2io, struct GeneralPurposeIO *sdoio, struct GeneralPurposeIO *sdaio, struct GeneralPurposeIO *sclkio) {
    adxl->mInterrupt1IO = int1io;
    adxl->mInterrupt2IO = int2io;

    adxl->mInterrupt1Pin = int1p;
    adxl->mInterrupt2Pin = int2p;

    setPinModeGPIO(adxl->mInterrupt1IO, adxl->mInterrupt1Pin, MODE_OUTPUT);
    setPinModeGPIO(adxl->mInterrupt2IO, adxl->mInterrupt2Pin, MODE_OUTPUT);

    adxl->mSpi.frequency = 3200;
    adxl->mSpi.chipSelectPin = csp;
    adxl->mSpi.clockPin = sclkp;
    adxl->mSpi.masterOutPin = sdap;
    adxl->mSpi.masterInPin = sdop;

    adxl->mSpi.chipSelectIO = csio;
    adxl->mSpi.clockIO = sclkio;
    adxl->mSpi.masterOutIO = sdaio;
    adxl->mSpi.masterInIO = sdoio;
    adxl->mSpi.bitSignificance = SPI_SW_TX_MSB;

    SPI_SW_TX_Begin(&adxl->mSpi);
}

void ADXL_BeginSingleIO(ADXL345* adxl, uint8 csp, uint8 int1p, uint8 int2p, uint8 sdop, uint8 sdap, uint8 sclkp, struct GeneralPurposeIO *io) {
    ADXL_Begin(adxl, csp, int1p, int2p, sdop, sdap, sclkp, io, io, io, io, io, io);
}

void ADXL_WriteData(ADXL345* adxl, uint8 address, uint8 data) {
    SPI_SW_TX_BeginTransaction(&adxl->mSpi);

    SPI_SW_TX_TransferByte(&adxl->mSpi, address & 0x3f);
    SPI_SW_TX_TransferByte(&adxl->mSpi, data);

    SPI_SW_TX_EndTransaction(&adxl->mSpi);
}

uint8 ADXL_ReadData(ADXL345* adxl, uint8 address) {
    SPI_SW_TX_BeginTransaction(&adxl->mSpi);

    SPI_SW_TX_TransferByte(&adxl->mSpi, 0xc0 | (address & 0x3f));
    uint8 result = SPI_SW_TX_TransferByte(&adxl->mSpi, 0x0);

    SPI_SW_TX_EndTransaction(&adxl->mSpi);

    return result;
}

void ADXL_Measure(ADXL345* adxl) {
    ADXL_WriteData(adxl, ADXL_POWER_CTL, S_ADXL_POWER_CTRL_MEASURE);
}

void ADXL_Range2G(ADXL345* adxl) {
    ADXL_WriteData(adxl, ADXL_DATA_FORMAT, S_ADXL_RW_DATA_FORMAT_SPI | 0x0);
}

void ADXL_Range4G(ADXL345* adxl) {
    ADXL_WriteData(adxl, ADXL_DATA_FORMAT, S_ADXL_RW_DATA_FORMAT_SPI | 0x1);
}

void ADXL_Range8G(ADXL345* adxl) {
    ADXL_WriteData(adxl, ADXL_DATA_FORMAT, S_ADXL_RW_DATA_FORMAT_SPI | 0x2);
}

void ADXL_Range16G(ADXL345* adxl) {
    ADXL_WriteData(adxl, ADXL_DATA_FORMAT, S_ADXL_RW_DATA_FORMAT_SPI | 0x3);
}

void ADXL_MaxSpeed(ADXL345* adxl) {
    ADXL_WriteData(adxl, ADXL_DATA_RATE_POWER_MODE, 0xf);
}

#endif