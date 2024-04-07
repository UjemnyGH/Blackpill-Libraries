#ifndef __HD44780_
#define __HD44780_

#include "../src/gpio.h"
#include "string_formatting.h"

#define HD_CLEAR_DISPLAY    0x1
#define HD_RETURN_HOME      0x2
#define HD_ENTRYMODE_SET    0x4
#define HD_DISPLAY_CTRL     0x8
#define HD_CURSOR_SHIFT     0x10
#define HD_FUNC_SET         0x20
#define HD_SET_CG_RAM_ADDR  0x40
#define HD_SET_DD_RAM_ADDR  0x80

#define HD_ENTRY_RIGHT      0x0
#define HD_ENTRY_LEFT       0x2
#define HD_SHIFT_INC        0x1
#define HD_SHIFT_DEC        0x0

#define HD_DISPLAY_ON       0x4
#define HD_DISPLAY_OFF      0x0
#define HD_CURSOR_ON        0x2
#define HD_CURSOR_OFF       0x0
#define HD_BLINK_ON         0x1
#define HD_BLINK_OFF        0x0

#define HD_DISPLAY_MOVE     0x8
#define HD_CURSOR_MOVE      0x0
#define HD_MOVE_RIGHT       0x4
#define HD_MOVE_LEFT        0x0

#define HD_8BIT_MODE        0x10
#define HD_4BIT_MODE        0x0
#define HD_2LINE            0x8
#define HD_1LINE            0x0
#define HD_5X10_DOTS        0x4
#define HD_5X8_DOTS         0x0

typedef struct HD44780 {
    uint8 resetPin, enablePin, readWritePin, dataPin[8];
    struct GeneralPurposeIO* resetIO, *enableIO, *readWriteIO, *dataIO;
    uint8 bitMode;
    // 8bits - func | ctrl | mode | (init flag, rows)
    uint32 display;
    // 8bits - row 3 | row 2 | row 1 | row 0
    uint32 rowOffsets;
} HD44780;

void HD_Command(HD44780* hd, uint8 value) {
    setOutputGPIO(hd->resetIO, hd->resetPin, LOW);

    if(hd->readWriteIO != (void*)0 || hd->readWritePin < 16) {
        setOutputGPIO(hd->readWriteIO, hd->readWritePin, LOW);
    }

    if(hd->bitMode == HD_4BIT_MODE) {
        for(int i = 0; i < (hd->bitMode == HD_4BIT_MODE ? 4 : 8); i++) {
            setOutputGPIO(hd->dataIO, hd->dataPin[i], (((value >> 4) >> i) & 0x1));
        }

        setOutputGPIO(hd->enableIO, hd->enablePin, 0);
        delay(1);
        setOutputGPIO(hd->enableIO, hd->enablePin, 1);
        delay(1);
        setOutputGPIO(hd->enableIO, hd->enablePin, 0);
        delay(100);
    }

    for(int i = 0; i < (hd->bitMode == HD_4BIT_MODE ? 4 : 8); i++) {
        setOutputGPIO(hd->dataIO, hd->dataPin[i], ((value >> i) & 0x1));
    }

    setOutputGPIO(hd->enableIO, hd->enablePin, 0);
    delay(1);
    setOutputGPIO(hd->enableIO, hd->enablePin, 1);
    delay(1);
    setOutputGPIO(hd->enableIO, hd->enablePin, 0);
    delay(100);
}

void HD_Data(HD44780* hd, uint8 value) {
    setOutputGPIO(hd->resetIO, hd->resetPin, HIGH);

    if(hd->readWriteIO != (void*)0 || hd->readWritePin < 16) {
        setOutputGPIO(hd->readWriteIO, hd->readWritePin, LOW);
    }

    if(hd->bitMode == HD_4BIT_MODE) {
        for(int i = 0; i < (hd->bitMode == HD_4BIT_MODE ? 4 : 8); i++) {
            setOutputGPIO(hd->dataIO, hd->dataPin[i], (((value >> 4) >> i) & 0x1));
        }

        setOutputGPIO(hd->enableIO, hd->enablePin, 0);
        delay(1);
        setOutputGPIO(hd->enableIO, hd->enablePin, 1);
        delay(1);
        setOutputGPIO(hd->enableIO, hd->enablePin, 0);
        delay(100);
    }

    for(int i = 0; i < (hd->bitMode == HD_4BIT_MODE ? 4 : 8); i++) {
        setOutputGPIO(hd->dataIO, hd->dataPin[i], ((value >> i) & 0x1));
    }

    setOutputGPIO(hd->enableIO, hd->enablePin, 0);
    delay(1);
    setOutputGPIO(hd->enableIO, hd->enablePin, 1);
    delay(1);
    setOutputGPIO(hd->enableIO, hd->enablePin, 0);
    delay(100);
}

void HD_Write(HD44780* hd, uint8 value) {
    HD_Data(hd, value);
}

void HD_Print(HD44780* hd, const char* drawText) {
    for(uint16 i = 0; i < GetStrLen(drawText); i++) {
        HD_Write(hd, drawText[i]);
    }
}

void HD_Clear(HD44780* hd) {
    HD_Command(hd, HD_CLEAR_DISPLAY);
    delay(2000);
}

void HD_Home(HD44780* hd) {
    HD_Command(hd, HD_RETURN_HOME);
    delay(2000);
}

void HD_DisplayOff(HD44780* hd) {
    hd->display &= ~((HD_DISPLAY_ON << 16) & 0xff0000);
    HD_Command(hd, HD_DISPLAY_CTRL | ((hd->display & 0xff0000) >> 16));
}

void HD_DisplayOn(HD44780* hd) {
    hd->display |= ((HD_DISPLAY_ON << 16) & 0xff0000);
    HD_Command(hd, HD_DISPLAY_CTRL | ((hd->display & 0xff0000) >> 16));
}

void HD_SetRowOffsets(HD44780* hd, uint8 row0, uint8 row1, uint8 row2, uint8 row3) {
    hd->rowOffsets = (row0 << 24) | (row1 << 16) | (row2 << 8) | row3;
}

void HD_SetCursor(HD44780* hd, uint8 column, uint8 row) {
    if(row >= 4) row = 3;
    if(row >= (hd->display & 0xf)) row = (hd->display & 0xf) - 1;

    HD_Command(hd, HD_SET_DD_RAM_ADDR | (column + ((hd->rowOffsets >> (24 - (row * 8))) & 0xff)));
}

void HD_CursorOn(HD44780* hd) {
    hd->display |= ((HD_CURSOR_ON << 16) & 0xff0000);
    HD_Command(hd, HD_DISPLAY_CTRL | ((hd->display & 0xff0000) >> 16));
}

void HD_CursorOff(HD44780* hd) {
    hd->display &= ~((HD_CURSOR_ON << 16) & 0xff0000);
    HD_Command(hd, HD_DISPLAY_CTRL | ((hd->display & 0xff0000) >> 16));
}

void HD_BlinkOn(HD44780* hd) {
    hd->display |= ((HD_BLINK_ON << 16) & 0xff0000);
    HD_Command(hd, HD_DISPLAY_CTRL | ((hd->display & 0xff0000) >> 16));
}

void HD_BlinkOff(HD44780* hd) {
    hd->display &= ~((HD_BLINK_ON << 16) & 0xff0000);
    HD_Command(hd, HD_DISPLAY_CTRL | ((hd->display & 0xff0000) >> 16));
}

void HD_AutoscrollOn(HD44780* hd) {
    hd->display |= ((HD_SHIFT_INC << 8) & 0xff00);
    HD_Command(hd, HD_ENTRYMODE_SET | ((hd->display & 0xff00) >> 8));
}

void HD_AutoscrollOff(HD44780* hd) {
    hd->display &= ~((HD_SHIFT_INC << 8) & 0xff00);
    HD_Command(hd, HD_ENTRYMODE_SET | ((hd->display & 0xff00) >> 8));
}

void HD_LeftToRight(HD44780* hd) {
    hd->display |= ((HD_ENTRY_LEFT << 8) & 0xff00);
    HD_Command(hd, HD_ENTRYMODE_SET | ((hd->display & 0xff00) >> 8));
}

void HD_RightToLeft(HD44780* hd) {
    hd->display &= ~((HD_ENTRY_LEFT << 8) & 0xff00);
    HD_Command(hd, HD_ENTRYMODE_SET | ((hd->display & 0xff00) >> 8));
}

void HD_ScrollLeft(HD44780* hd) {
    HD_Command(hd, HD_CURSOR_SHIFT | HD_DISPLAY_MOVE | HD_MOVE_LEFT);
}

void HD_ScrollRight(HD44780* hd) {
    HD_Command(hd, HD_CURSOR_SHIFT | HD_DISPLAY_MOVE | HD_MOVE_RIGHT);
}

void HD_CreateChar(HD44780* hd, uint8 location, const uint8* drawChars) {
    location &= 0x7;
    HD_Command(hd, HD_SET_CG_RAM_ADDR | (location << 3));

    for(uint8 i = 0; i < 8; i++) {
        HD_Data(hd, drawChars[i]);
    }
}

void HD_Resize(HD44780* hd, uint8 columns, uint8 rows) {
    if(rows > 1) {
        hd->display |= ((HD_2LINE << 24) & 0xff000000);
    }

    hd->display &= 0xfffffff0;
    hd->display |= (rows & 0xf);

    HD_SetRowOffsets(hd, 0x40, 0x0, columns, columns + 0x40);

    delay(50000);

    setOutputGPIO(hd->resetIO, hd->resetPin, 0);
    setOutputGPIO(hd->enableIO, hd->enablePin, 0);

    if(hd->readWriteIO != (void*)0 || hd->readWritePin < 16) {
        setOutputGPIO(hd->readWriteIO, hd->readWritePin, 0);
    }

    if(hd->bitMode == HD_4BIT_MODE) {
        uint8 value = 0x3;

        for(int j = 0; j < 3; j++) {
            for(int i = 0; i < (hd->bitMode == HD_4BIT_MODE ? 4 : 8); i++) {
                setOutputGPIO(hd->dataIO, hd->dataPin[i], ((value >> i) & 0x1));
            }

            setOutputGPIO(hd->enableIO, hd->enablePin, 0);
            delay(1);
            setOutputGPIO(hd->enableIO, hd->enablePin, 1);
            delay(1);
            setOutputGPIO(hd->enableIO, hd->enablePin, 0);
            delay(50);

            if(j != 2) delay(5000);
            else delay(150);
        }

        value = 0x2;

        for(int i = 0; i < (hd->bitMode == HD_4BIT_MODE ? 4 : 8); i++) {
            setOutputGPIO(hd->dataIO, hd->dataPin[i], ((value >> i) & 0x1));
        }

        setOutputGPIO(hd->enableIO, hd->enablePin, 0);
        delay(1);
        setOutputGPIO(hd->enableIO, hd->enablePin, 1);
        delay(1);
        setOutputGPIO(hd->enableIO, hd->enablePin, 0);
        delay(50);
    }
    else {
        HD_Command(hd, HD_FUNC_SET | ((hd->display & 0xff000000) >> 24));
        delay(5000);
        HD_Command(hd, HD_FUNC_SET | ((hd->display & 0xff000000) >> 24));
        delay(150);
        HD_Command(hd, HD_FUNC_SET | ((hd->display & 0xff000000) >> 24));
    }
    
    HD_Command(hd, HD_FUNC_SET | ((hd->display & 0xff000000) >> 24));

    hd->display |= ((HD_DISPLAY_ON | HD_CURSOR_OFF | HD_BLINK_ON) << 16) & 0xff0000;

    // TODO: display and clear

    HD_DisplayOn(hd);

    HD_Clear(hd);
    
    hd->display |= ((HD_ENTRY_LEFT | HD_SHIFT_DEC) << 8) & 0xff00;

    HD_Command(hd, HD_ENTRYMODE_SET | ((hd->display & 0xff00) >> 8));
}

/**
 * @brief Main HD44780 beginning function 
 * 
 * @param hd pointer to struct
 * @param rsp reset pin
 * @param enp enable pin
 * @param rwp read/write pin
 * @param d0p data 0 pin
 * @param d1p data 1 pin
 * @param d2p data 2 pin
 * @param d3p data 3 pin
 * @param d4p data 4 pin
 * @param d5p data 5 pin
 * @param d6p data 6 pin
 * @param d7p data 7 pin
 * @param rsio reset gpio
 * @param enio enable gpio
 * @param rwio read/write gpio
 * @param dxio data[0-7] gpio 
 */
void HD_Begin(HD44780* hd, uint8 rsp, uint8 enp, uint8 rwp, uint8 d0p, uint8 d1p, uint8 d2p, uint8 d3p, uint8 d4p, uint8 d5p, uint8 d6p, uint8 d7p, struct GeneralPurposeIO* rsio, struct GeneralPurposeIO* enio, struct GeneralPurposeIO* rwio, struct GeneralPurposeIO* dxio) {
    hd->resetIO = rsio;
    hd->enableIO = enio;
    hd->readWriteIO = rwio;
    hd->dataIO = dxio;

    hd->resetPin = rsp;
    hd->readWritePin = rwp;
    hd->enablePin = enp;

    hd->dataPin[0] = d0p;
    hd->dataPin[1] = d1p;
    hd->dataPin[2] = d2p;
    hd->dataPin[3] = d3p;
    hd->dataPin[4] = d4p;
    hd->dataPin[5] = d5p;
    hd->dataPin[6] = d6p;
    hd->dataPin[7] = d7p;

    setPinModeGPIO(hd->resetIO, hd->resetPin, MODE_OUTPUT);
    if(hd->readWriteIO != (void*)0 || hd->readWritePin < 16) {
        setPinModeGPIO(hd->readWriteIO, hd->readWritePin, MODE_OUTPUT);
    }
    setPinModeGPIO(hd->enableIO, hd->enablePin, MODE_OUTPUT);

    setPinModeGPIO(hd->dataIO, hd->dataPin[0], MODE_OUTPUT);
    setPinModeGPIO(hd->dataIO, hd->dataPin[1], MODE_OUTPUT);
    setPinModeGPIO(hd->dataIO, hd->dataPin[2], MODE_OUTPUT);
    setPinModeGPIO(hd->dataIO, hd->dataPin[3], MODE_OUTPUT);

    hd->bitMode = HD_4BIT_MODE;

    if(hd->dataPin[4] < 16 && hd->dataPin[5] < 16 && hd->dataPin[6] < 16 && hd->dataPin[7] < 16) {
        setPinModeGPIO(hd->dataIO, hd->dataPin[4], MODE_OUTPUT);
        setPinModeGPIO(hd->dataIO, hd->dataPin[5], MODE_OUTPUT);
        setPinModeGPIO(hd->dataIO, hd->dataPin[6], MODE_OUTPUT);
        setPinModeGPIO(hd->dataIO, hd->dataPin[7], MODE_OUTPUT);
        hd->bitMode = HD_8BIT_MODE;
    }

    hd->display |= (hd->bitMode | HD_1LINE | HD_5X8_DOTS) << 24;

    HD_Resize(hd, 16, 1);
}

void HD_BeginSingleIO(HD44780* hd, uint8 rsp, uint8 enp, uint8 rwp, uint8 d0p, uint8 d1p, uint8 d2p, uint8 d3p, uint8 d4p, uint8 d5p, uint8 d6p, uint8 d7p, struct GeneralPurposeIO* io) {
    HD_Begin(hd, rsp, enp, rwp, d0p, d1p, d2p, d3p, d4p, d5p, d6p, d7p, io, io, io, io);
}

void HD_Begin4Bit(HD44780* hd, uint8 rsp, uint8 enp, uint8 rwp, uint8 d0p, uint8 d1p, uint8 d2p, uint8 d3p, struct GeneralPurposeIO* rsio, struct GeneralPurposeIO* enio, struct GeneralPurposeIO* rwio, struct GeneralPurposeIO* dxio) {
    HD_Begin(hd, rsp, enp, rwp, d0p, d1p, d2p, d3p, 32, 32, 32, 32, rsio, enio, rwio, dxio);
}

void HD_Begin4BitSingleIO(HD44780* hd, uint8 rsp, uint8 enp, uint8 rwp, uint8 d0p, uint8 d1p, uint8 d2p, uint8 d3p, struct GeneralPurposeIO* io) {
    HD_Begin(hd, rsp, enp, rwp, d0p, d1p, d2p, d3p, 32, 32, 32, 32, io, io, io, io);
}

#endif