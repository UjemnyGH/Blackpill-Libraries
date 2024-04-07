#ifndef __SDRAM_
#define __SDRAM_

#include "../src/gpio.h"

/*
Pins on ddr ram

Power:
    VCC - 168, 157, 143, 133, 124, 110, 102, 90, 84, 73, 59, 49, 41, 40, 26, 18, 6
    GND/VSS - 162, 152, 148, 138, 127, 116, 107, 96, 85, 78, 68, 64, 54, 43, 32, 23, 12, 1

Serial:
    165 - Serial Addr 0
    166 - Serial Addr 1
    167 - Serial Addr 2
    83  - Serial clk
    82  - Serial data

Parallel:
    2  - Data 0
    3  - Data 1
    4  - Data 2
    5  - Data 3
    7  - Data 4
    8  - Data 5
    9  - Data 6
    10 - Data 7
    11 - Data 8
    13 - Data 9
    14 - Data 10
    15 - Data 11
    16 - Data 12
    17 - Data 13
    19 - Data 14
    20 - Data 15
    55 - Data 16
    56 - Data 17
    57 - Data 18
    58 - Data 19
    60 - Data 20
    65 - Data 21
    66 - Data 22
    67 - Data 23
    69 - Data 24
    70 - Data 25
    71 - Data 26
    72 - Data 27
    74 - Data 28
    75 - Data 29
    76 - Data 30
    77 - Data 31
    86 - Data 32
    87 - Data 33
    88 - Data 34
    89 - Data 35
    91 - Data 36
    92 - Data 37
    93 - Data 38
    94 - Data 39
    95 - Data 40
    97 - Data 41
    98 - Data 42
    99 - Data 43
    100 - Data 44
    101 - Data 45
    103 - Data 46
    104 - Data 47
    139	- Data 48
    140	- Data 49
    141	- Data 50
    142	- Data 51
    144	- Data 52
    149	- Data 53
    150	- Data 54
    151	- Data 55
    153	- Data 56
    154	- Data 57
    155	- Data 58
    156	- Data 59
    158	- Data 60
    159	- Data 61
    160	- Data 62
    161	- Data 63

    Btw data pins are limited to 16 pins becouse, let`s be real, it must be usefull, better yet use 2 addresses to store 32 bit value 

    81 - Write Protect

    27 - Read/Write Input

    28 - Column Address Strobe 0
    29 - Column Address Strobe 1
    46 - Column Address Strobe 2
    47 - Column Address Strobe 3
    129 - Column Address Strobe 3
    112 - Column Address Strobe 4
    113 - Column Address Strobe 5
    130	- Column Address Strobe 6
    131	- Column Address Strobe 7

    30 - Row Address Strobe 0
    45 - Row Address Strobe 2

    111 - CAS (Column Address Strobe)
    115 - RAS (Row Address Strobe)

    33 - Address 0
    34 - Address 2
    35 - Address 4
    36 - Address 6
    37 - Address 8
    38 - Address 10

    117	- Address 1
    118	- Address 3
    119	- Address 5
    120	- Address 7
    121	- Address 9
    123 - Address 11
    126	- Address 12
    132	- Address 13

Banks:
    122 - Bank Address 0
    39 - Bak Address 1

Clocks:
    42 - Clk0
    125 - Clk1
    79 - Clk2
    163 - Clk3

    63 - Clk Enable 1
    128 - Clk Enable 0

For more info refer here http://www.interfacebus.com/Memory_Modules_168Pin_DIMM_Buff_PinOut-rear-side.html

*/

/**
 * @brief Dual Inline Synchronous Dynamic Random Access Memory Module initializer struct
 * @attention For convenience DIMM SDRAM initializer uses 16 bits of data and 4 diffrent GPIOs
 * 
 */
typedef struct SD_RAM_DIMM_Initializer {
    uint8 addressPin[14];
    uint8 dataPin[16];
    struct GeneralPurposeIO* addressIOLow;
    struct GeneralPurposeIO* addressIOHigh;
    struct GeneralPurposeIO* dataIOLow;
    struct GeneralPurposeIO* dataIOHigh;
} SD_RAM_DIMM_Initializer;

typedef struct SD_RAM_DIMM_Data {
    uint16 address;
    uint16 data;
} SD_RAM_DIMM_Data;

typedef struct SD_RAM_DIMM_168 {
    SD_RAM_DIMM_Initializer initializer;
    uint8 columnAddressPin;
    uint8 rowAddressPin;
    uint8 writeProtectPin;
    uint8 readWritePin;
    struct GeneralPurposeIO* periphIO;

    SD_RAM_DIMM_Data dataQueue[0x10];
    uint8 queuedData;
} SD_RAM_DIMM_168;

/**
 * @brief Initialize SD_RAM_DIMM_168 struct
 * 
 * @param ram DIMM SDRAM 168 Pin struct 
 * @param init ram dataIO/address initializer struct
 * @param casp column address signal pin
 * @param rasp row address signal pin
 * @param wpp write protect pin
 * @param rwp read/write pin
 * @param periphIO general defined pins GPIO
 */
void RAM168_Begin(SD_RAM_DIMM_168* ram, SD_RAM_DIMM_Initializer init, uint8 casp, uint8 rasp, uint8 wpp, uint8 rwp, struct GeneralPurposeIO* periphIO) {
    ram->initializer = init;
    ram->columnAddressPin = casp;
    ram->rowAddressPin = rasp;
    ram->writeProtectPin = wpp;
    ram->readWritePin = rwp;
    ram->periphIO = periphIO;

    setPinModeGPIO(ram->periphIO, ram->columnAddressPin, MODE_OUTPUT);
    setPinModeGPIO(ram->periphIO, ram->rowAddressPin, MODE_OUTPUT);
    setPinModeGPIO(ram->periphIO, ram->writeProtectPin, MODE_OUTPUT);
    setPinModeGPIO(ram->periphIO, ram->readWritePin, MODE_OUTPUT);

    for(uint8 i = 0; i < 7; i++) {
        setPinModeGPIO(ram->initializer.addressIOLow, ram->initializer.addressPin[i], MODE_OUTPUT);
    }

    for(uint8 i = 7; i < 14; i++) {
        setPinModeGPIO(ram->initializer.addressIOHigh, ram->initializer.addressPin[i], MODE_OUTPUT);
    }

    for(uint8 i = 0; i < 8; i++) {
        setPinModeGPIO(ram->initializer.dataIOLow, ram->initializer.dataPin[i], MODE_INPUT);
    }

    for(uint8 i = 8; i < 16; i++) {
        setPinModeGPIO(ram->initializer.dataIOHigh, ram->initializer.dataPin[i], MODE_INPUT);
    }
}

void RAM168_PrepareToWrite(SD_RAM_DIMM_168* ram) {
    for(uint8 i = 0; i < 8; i++) {
        setPinModeGPIO(ram->initializer.dataIOLow, ram->initializer.dataPin[i], MODE_OUTPUT);
    }

    for(uint8 i = 8; i < 16; i++) {
        setPinModeGPIO(ram->initializer.dataIOHigh, ram->initializer.dataPin[i], MODE_OUTPUT);
    }
}

void RAM168_PrepareToRead(SD_RAM_DIMM_168* ram) {
    for(uint8 i = 0; i < 8; i++) {
        setPinModeGPIO(ram->initializer.dataIOLow, ram->initializer.dataPin[i], MODE_INPUT);
    }

    for(uint8 i = 8; i < 16; i++) {
        setPinModeGPIO(ram->initializer.dataIOHigh, ram->initializer.dataPin[i], MODE_INPUT);
    }
}

void RAM168_Write(SD_RAM)

#endif