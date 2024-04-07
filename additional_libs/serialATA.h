#ifndef __SERIAL_ATA_
#define __SERIAL_ATA_

#include "../src/gpio.h"

#define SATA_SOFTWARE_MEMORY_BUFFER_SIZE    8192

typedef struct SerialATA {
    struct GeneralPurposeIO* txPlusIO, *txMinusIO, *rxPlusIO, *rxMinusIO;
    uint8 txPlusPin, txMinusPin, rxPlusPin, rxMinusPin;
    uint8 softwareMemoryBuffer[SATA_SOFTWARE_MEMORY_BUFFER_SIZE];

} SerialATA;

#endif