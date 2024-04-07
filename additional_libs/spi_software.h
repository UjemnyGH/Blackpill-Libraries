#ifndef __SPI_SOFRWARE_
#define __SPI_SOFRWARE_

#include "../src/gpio.h"
#include "../src/spi.h"

#define SPI_SW_TX_LSB 0x0
#define SPI_SW_TX_MSB 0x1

// Not longer than 0xffff
#define SPI_COMMAND_DATA_SIZE       64

typedef struct SPI_Data {
    uint8 data[SPI_COMMAND_DATA_SIZE];
    uint16 len;
} SPI_Data;

typedef struct SPI_Software_TX {
    uint8 masterOutPin, masterInPin, clockPin, chipSelectPin, bitSignificance;
    struct GeneralPurposeIO *masterOutIO, *masterInIO, *clockIO, *chipSelectIO;
    uint32 frequency;
} SPI_Software_TX;

void SPI_SW_TX_Begin(SPI_Software_TX* spiTx) {
    if(spiTx->masterOutPin < 16) { setPinModeGPIO(spiTx->masterOutIO, spiTx->masterOutPin, MODE_OUTPUT); }
    if(spiTx->masterInPin < 16) { setPinModeGPIO(spiTx->masterInIO, spiTx->masterInPin, MODE_INPUT); }
    if(spiTx->clockPin < 16) { setPinModeGPIO(spiTx->clockIO, spiTx->clockPin, MODE_OUTPUT); }
    if(spiTx->chipSelectPin < 16) { setPinModeGPIO(spiTx->chipSelectIO, spiTx->chipSelectPin, MODE_OUTPUT); }
}

void SPI_SW_TX_BeginTransaction(SPI_Software_TX* spiTx) {
    if(spiTx->chipSelectPin < 16 && spiTx->chipSelectIO != ((void*)0)) {
        setOutputGPIO(spiTx->chipSelectIO, spiTx->chipSelectPin, LOW);
    }
}

void SPI_SW_TX_EndTransaction(SPI_Software_TX* spiTx) {
    if(spiTx->chipSelectPin < 16 && spiTx->chipSelectIO != ((void*)0)) {
        setOutputGPIO(spiTx->chipSelectIO, spiTx->chipSelectPin, HIGH);
    }
}

uint8 SPI_SW_TX_TransferByte(SPI_Software_TX* spiTx, uint8 byte) {
    uint8 delay_us = (1000000 / spiTx->frequency) / 2;

    uint8 start_bit = 0x1, reply = 0;

    if(spiTx->bitSignificance == SPI_SW_TX_MSB) start_bit = 0x80;

    uint8 to_write, last_mosi = !(byte & start_bit);

    for(uint8 b = start_bit; b != 0; b = (spiTx->bitSignificance == SPI_SW_TX_LSB) ? b << 1 : b >> 1) {
        if(delay_us) delay(delay_us);

        to_write = !(!(byte & b));

        if((spiTx->masterOutPin < 16 && spiTx->masterOutIO != ((void*)0)) && !last_mosi != !to_write) {
            setOutputGPIO(spiTx->masterOutIO, spiTx->masterOutPin, to_write);

            last_mosi = to_write;
        }

        setOutputGPIO(spiTx->clockIO, spiTx->clockPin, HIGH);

        if(delay_us) delay(delay_us);

        if(spiTx->masterInPin < 16 && spiTx->masterInIO != ((void*)0)) {
            if(!(!(getInputGPIO(spiTx->masterInIO, spiTx->masterInPin)))) {
                reply |= b;
            }
        }

        setOutputGPIO(spiTx->clockIO, spiTx->clockPin, LOW);
    }

    return reply;
}

void SPI_SW_TX_TransferData(SPI_Software_TX* spiTx, SPI_Data data) {
    for(uint16 i = 0; i < data.len; i++) {
        SPI_SW_TX_TransferByte(spiTx, data.data[i]); 
    }
}

uint8 SPI_SW_TX_WriteByte(SPI_Software_TX* spiTx, uint8 byte) {
    SPI_SW_TX_BeginTransaction(spiTx);

    uint8 result = SPI_SW_TX_TransferByte(spiTx, byte);

    SPI_SW_TX_EndTransaction(spiTx);

    return result;
}

void SPI_SW_TX_Write(SPI_Software_TX* spiTx, uint8* bytes, uint32 length) {
    SPI_SW_TX_BeginTransaction(spiTx);

    for(uint32 i = 0; i < length; i++) 
        SPI_SW_TX_TransferByte(spiTx, bytes[i]);

    SPI_SW_TX_EndTransaction(spiTx);
}

#endif