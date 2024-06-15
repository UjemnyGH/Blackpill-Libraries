#ifndef __PCD8544_STM32_
#define __PCD8544_STM32_

#include "spi_software.h"
#include "string_formatting.h"

#define PCD_LCD_WIDTH   84
#define PCD_LCD_HEIGHT  48

#define PCD_FN_POWER_DOWN   0x4
#define PCD_FN_ENTRY_MODE   0x2
#define PCD_FN_EXTENDED_INSTRUCTION 0x1

#define PCD_DC_DISPLAY_BLANK    0x0
#define PCD_DC_DISPLAY_NORMAL   0x4
#define PCD_DC_DISPLAY_ALL_ON   0x1
#define PCD_DC_DISPLAY_INVERTED 0x5

#define PCD_IS_FUNCTION_SET     0x20
#define PCD_IS_DISPLAY_CONTROL  0x8
#define PCD_IS_SET_Y_ADDRESS    0x40
#define PCD_IS_SET_X_ADDRESS    0x80

#define PCD_EIS_SET_TEMPERATURE 0x4
#define PCD_EIS_SET_BIAS        0x10
#define PCD_EIS_SET_VOP         0x80

typedef struct PCD8544_Software {
    uint8 resetPin, dataCommandPin, backlightPin;
    struct GeneralPurposeIO *resetIO, *dataCommandIO, *backlightIO;
    SPI_Software_TX spiTx;
    uint8 contrast, bias, lightOn, transferingCommand;
    uint8 drawBuffer[PCD_LCD_WIDTH * PCD_LCD_HEIGHT / 8];

} PCD8544_Software;

void PCD_TransferCommand(PCD8544_Software* pcd, uint8 cmd) {
    pcd->transferingCommand = TRUE;

    if(pcd->dataCommandPin < 16 && pcd->dataCommandIO != ((void*)0)) {
        setOutputGPIO(pcd->dataCommandIO, pcd->dataCommandPin, !pcd->transferingCommand);
    }

    SPI_SW_TX_WriteByte(&pcd->spiTx, cmd);
}

void PCD_Begin(PCD8544_Software* pcd, uint8 rstPin, uint8 chipEnPin, uint8 datComPin, uint8 dataPin, uint8 clkPin, uint8 lightPin, struct GeneralPurposeIO *rstIO, struct GeneralPurposeIO * chipEnIO, struct GeneralPurposeIO *datComIO, struct GeneralPurposeIO * dataIO, struct GeneralPurposeIO * clkIO, struct GeneralPurposeIO *lightIO) {
    pcd->lightOn = FALSE;
    pcd->transferingCommand = FALSE;
    pcd->contrast = 0x6;
    pcd->bias = 0x7e;
    
    pcd->resetPin = rstPin;
    pcd->dataCommandPin = datComPin;
    pcd->backlightPin = lightPin;

    pcd->resetIO = rstIO;
    pcd->dataCommandIO = datComIO;
    pcd->backlightIO = lightIO;

    setPinModeGPIO(pcd->dataCommandIO, pcd->dataCommandPin, MODE_OUTPUT);
    setPinModeGPIO(pcd->backlightIO, pcd->backlightPin, MODE_OUTPUT);

    pcd->spiTx.frequency = 4000000;
    pcd->spiTx.chipSelectPin = chipEnPin;
    pcd->spiTx.clockPin = clkPin;
    pcd->spiTx.masterOutPin = dataPin;
    pcd->spiTx.masterInPin = -1;

    pcd->spiTx.chipSelectIO = chipEnIO;
    pcd->spiTx.clockIO = clkIO;
    pcd->spiTx.masterOutIO = dataIO;
    pcd->spiTx.masterInIO = ((struct GeneralPurposeIO*)0);
    pcd->spiTx.bitSignificance = SPI_SW_TX_MSB;

    SPI_SW_TX_Begin(&pcd->spiTx);

    if(pcd->resetPin < 16 && pcd->resetIO != ((void*)0)) {
        setPinModeGPIO(pcd->resetIO, pcd->resetPin, MODE_OUTPUT);

        setOutputGPIO(pcd->resetIO, pcd->resetPin, LOW);
        delay(1600);
        setOutputGPIO(pcd->resetIO, pcd->resetPin, HIGH);
    }

    PCD_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
    PCD_TransferCommand(pcd, PCD_IS_DISPLAY_CONTROL | PCD_DC_DISPLAY_NORMAL);
}

void PCD_BeginSingleIO(PCD8544_Software* pcd, uint8 rstPin, uint8 chipEnPin, uint8 datComPin, uint8 dataPin, uint8 clkPin, uint8 lightPin, struct GeneralPurposeIO *io) {
    pcd->lightOn = FALSE;
    pcd->transferingCommand = FALSE;
    pcd->contrast = 0x6;
    pcd->bias = 0x7e;
    
    pcd->resetPin = rstPin;
    pcd->dataCommandPin = datComPin;
    pcd->backlightPin = lightPin;

    pcd->resetIO = io;
    pcd->dataCommandIO = io;
    pcd->backlightIO = io;

    setPinModeGPIO(pcd->dataCommandIO, pcd->dataCommandPin, MODE_OUTPUT);
    setPinModeGPIO(pcd->backlightIO, pcd->backlightPin, MODE_OUTPUT);

    pcd->spiTx.frequency = 4000000;
    pcd->spiTx.chipSelectPin = chipEnPin;
    pcd->spiTx.clockPin = clkPin;
    pcd->spiTx.masterOutPin = dataPin;
    pcd->spiTx.masterInPin = -1;

    pcd->spiTx.chipSelectIO = io;
    pcd->spiTx.clockIO = io;
    pcd->spiTx.masterOutIO = io;
    pcd->spiTx.masterInIO = ((struct GeneralPurposeIO*)0);
    pcd->spiTx.bitSignificance = SPI_SW_TX_MSB;

    SPI_SW_TX_Begin(&pcd->spiTx);

    if(pcd->resetPin < 16 && pcd->resetIO != ((void*)0)) {
        setPinModeGPIO(pcd->resetIO, pcd->resetPin, MODE_OUTPUT);

        setOutputGPIO(pcd->resetIO, pcd->resetPin, LOW);
        delay(1600);
        setOutputGPIO(pcd->resetIO, pcd->resetPin, HIGH);
    }

    PCD_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
    PCD_TransferCommand(pcd, PCD_IS_DISPLAY_CONTROL | PCD_DC_DISPLAY_NORMAL);
}

void PCD_ResetDisplay(PCD8544_Software* pcd) {
    if(pcd->resetPin < 16 && pcd->resetIO != ((void*)0)) {
        setPinModeGPIO(pcd->resetIO, pcd->resetPin, MODE_OUTPUT);

        setOutputGPIO(pcd->resetIO, pcd->resetPin, LOW);
        delay(1600);
        setOutputGPIO(pcd->resetIO, pcd->resetPin, HIGH);
    }

    PCD_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
    PCD_TransferCommand(pcd, PCD_IS_DISPLAY_CONTROL | PCD_DC_DISPLAY_NORMAL);
}

void PCD_ClearDisplay(PCD8544_Software* pcd) {
    for(uint32 i = 0; i < (PCD_LCD_HEIGHT * PCD_LCD_WIDTH / 8); i++) {
        pcd->drawBuffer[i] = 0;
    }
}

void PCD_SetBacklight(PCD8544_Software* pcd, uint8 state) {
    pcd->lightOn = state;

    if(pcd->backlightPin < 16 && pcd->backlightIO != ((void*)0)) {
        setOutputGPIO(pcd->backlightIO, pcd->backlightPin, pcd->lightOn);
    }
}

void PCD_SetContast(PCD8544_Software* pcd, uint8 contrast) {
    if(contrast > 0x7f) {
        pcd->contrast = 0x7f;
    }
    else {
        pcd->contrast = contrast;
    }

    PCD_TransferCommand(pcd, PCD_IS_FUNCTION_SET | PCD_FN_EXTENDED_INSTRUCTION);
    PCD_TransferCommand(pcd, PCD_EIS_SET_VOP | pcd->contrast);
    PCD_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
}

void PCD_SetBias(PCD8544_Software* pcd, uint8 bias) {
    if(bias > 0x7) {
        pcd->contrast = 0x7;
    }
    else {
        pcd->contrast = bias;
    }

    PCD_TransferCommand(pcd, PCD_IS_FUNCTION_SET | PCD_FN_EXTENDED_INSTRUCTION);
    PCD_TransferCommand(pcd, PCD_EIS_SET_BIAS | pcd->bias);
    PCD_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
}

void PCD_SetPixel(PCD8544_Software* pcd, uint8 x, uint8 y, uint8 color) {
    if(x > PCD_LCD_WIDTH || y > PCD_LCD_HEIGHT) return;

    if(color) {
        pcd->drawBuffer[x + ((y / 8) * PCD_LCD_WIDTH)] |= (1 << (y % 8));
    }
    else {
        pcd->drawBuffer[x + ((y / 8) * PCD_LCD_WIDTH)] &= ~(1 << (y % 8));
    }
}

void PCD_LoadBitmap(PCD8544_Software* pcd, uint8 x, uint8 y, uint8* bitmap, uint8 width, uint8 height) {
    if(x > PCD_LCD_WIDTH || y > PCD_LCD_HEIGHT) return;

    for(uint8 _y = 0; _y < height; _y++) {
        for(uint8 _x = 0; _x < ((width / 8) == 0 ? 1 : (width / 8)); _x++) {
            uint8 image_byte = bitmap[_y * ((width / 8) == 0 ? 1 : (width / 8)) + _x];

            for(int i = 0; i < 8; i++) {
                PCD_SetPixel(pcd, x + _x + i, y + _y, !(!(image_byte & (1 << i))));
            }
        }
    }
}

void PCD_Display(PCD8544_Software* pcd) {
    PCD_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
    PCD_TransferCommand(pcd, PCD_IS_DISPLAY_CONTROL | PCD_DC_DISPLAY_NORMAL);

    for(uint8 page = 0; page < PCD_LCD_HEIGHT / 8; page++) {
        PCD_TransferCommand(pcd, PCD_IS_SET_Y_ADDRESS | page);
        PCD_TransferCommand(pcd, PCD_IS_SET_X_ADDRESS);

        setOutputGPIO(pcd->dataCommandIO, pcd->dataCommandPin, HIGH);

        SPI_SW_TX_Write(&pcd->spiTx, pcd->drawBuffer + (PCD_LCD_WIDTH * page), PCD_LCD_WIDTH);
    }

    PCD_TransferCommand(pcd, PCD_IS_SET_Y_ADDRESS);
}

void PCD_DisplayPixel(PCD8544_Software* pcd, uint8 x, uint8 y, uint8 color) {
    if(x > PCD_LCD_WIDTH || y > PCD_LCD_HEIGHT) return;

    if(color) {
        pcd->drawBuffer[x + ((y / 8) * PCD_LCD_WIDTH)] |= (1 << (y % 8));
    }
    else {
        pcd->drawBuffer[x + ((y / 8) * PCD_LCD_WIDTH)] &= ~(1 << (y % 8));
    }

    PCD_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
    PCD_TransferCommand(pcd, PCD_IS_DISPLAY_CONTROL | PCD_DC_DISPLAY_NORMAL);

    PCD_TransferCommand(pcd, PCD_IS_SET_Y_ADDRESS | (y / 8));
    PCD_TransferCommand(pcd, PCD_IS_SET_X_ADDRESS | x);

    setOutputGPIO(pcd->dataCommandIO, pcd->dataCommandPin, HIGH);

    SPI_SW_TX_WriteByte(&pcd->spiTx, 1 << (y % 8));

    PCD_TransferCommand(pcd, PCD_IS_SET_Y_ADDRESS);
}

/*typedef struct PCD8544_Hardware {
    uint8 resetPin, dataCommandPin, backlightPin;
    struct GeneralPurposeIO *resetIO, *dataCommandIO, *backlightIO;
    struct SPI* spi;
    uint8 contrast, bias, lightOn, transferingCommand;
    uint8 drawBuffer[PCD_LCD_WIDTH * PCD_LCD_HEIGHT / 8];
} PCD8544_Hardware;

void PCDH_TransferCommand(PCD8544_Hardware* pcd, uint8 cmd) {
    pcd->transferingCommand = TRUE;

    if(pcd->dataCommandPin < 16 && pcd->dataCommandIO != ((void*)0)) {
        setOutputGPIO(pcd->dataCommandIO, pcd->dataCommandPin, !pcd->transferingCommand);
    }

    SPI_SW_TX_WriteByte(&pcd->spiTx, cmd);
}

void PCDH_Begin(PCD8544_Hardware* pcd, uint8 rstPin, uint8 chipEnPin, uint8 datComPin, uint8 dataPin, uint8 clkPin, uint8 lightPin, struct GeneralPurposeIO *rstIO, struct GeneralPurposeIO * chipEnIO, struct GeneralPurposeIO *datComIO, struct GeneralPurposeIO * dataIO, struct GeneralPurposeIO * clkIO, struct GeneralPurposeIO *lightIO) {
    pcd->lightOn = FALSE;
    pcd->transferingCommand = FALSE;
    pcd->contrast = 0x6;
    pcd->bias = 0x7e;
    
    pcd->resetPin = rstPin;
    pcd->dataCommandPin = datComPin;
    pcd->backlightPin = lightPin;

    pcd->resetIO = rstIO;
    pcd->dataCommandIO = datComIO;
    pcd->backlightIO = lightIO;

    setPinModeGPIO(pcd->dataCommandIO, pcd->dataCommandPin, MODE_OUTPUT);
    setPinModeGPIO(pcd->backlightIO, pcd->backlightPin, MODE_OUTPUT);

    pcd->spi->control1 |= SPI_CONTROL1_BAUDRATE_2 & SPI_CONTROL1_ENABLE & SPI_CONTROL1_OUTPUT_EN_BIDIR & SPI_CONTROL1_FRAME_FORMAT_LSB;

    //pcd->spiTx.frequency = 4000000;
    //pcd->spiTx.chipSelectPin = chipEnPin;
    //pcd->spiTx.clockPin = clkPin;
    //pcd->spiTx.masterOutPin = dataPin;
    //pcd->spiTx.masterInPin = -1;

    //pcd->spiTx.chipSelectIO = chipEnIO;
    //pcd->spiTx.clockIO = clkIO;
    //pcd->spiTx.masterOutIO = dataIO;
    //pcd->spiTx.masterInIO = ((struct GeneralPurposeIO*)0);

    //SPI_SW_TX_Begin(&pcd->spiTx);

    if(pcd->resetPin < 16 && pcd->resetIO != ((void*)0)) {
        setPinModeGPIO(pcd->resetIO, pcd->resetPin, MODE_OUTPUT);

        setOutputGPIO(pcd->resetIO, pcd->resetPin, LOW);
        delay(1600);
        setOutputGPIO(pcd->resetIO, pcd->resetPin, HIGH);
    }

    PCDH_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
    PCDH_TransferCommand(pcd, PCD_IS_DISPLAY_CONTROL | PCD_DC_DISPLAY_NORMAL);
}

void PCDH_ResetDisplay(PCD8544_Hardware* pcd) {
    if(pcd->resetPin < 16 && pcd->resetIO != ((void*)0)) {
        setPinModeGPIO(pcd->resetIO, pcd->resetPin, MODE_OUTPUT);

        setOutputGPIO(pcd->resetIO, pcd->resetPin, LOW);
        delay(1600);
        setOutputGPIO(pcd->resetIO, pcd->resetPin, HIGH);
    }

    PCDH_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
    PCDH_TransferCommand(pcd, PCD_IS_DISPLAY_CONTROL | PCD_DC_DISPLAY_NORMAL);
}

void PCDH_ClearDisplay(PCD8544_Hardware* pcd) {
    for(uint32 i = 0; i < (PCD_LCD_HEIGHT * PCD_LCD_WIDTH / 8); i++) {
        pcd->drawBuffer[i] = 0;
    }
}

void PCDH_SetBacklight(PCD8544_Hardware* pcd, uint8 state) {
    pcd->lightOn = state;

    if(pcd->backlightPin < 16 && pcd->backlightIO != ((void*)0)) {
        setOutputGPIO(pcd->backlightIO, pcd->backlightPin, pcd->lightOn);
    }
}

void PCDH_SetContast(PCD8544_Hardware* pcd, uint8 contrast) {
    if(contrast > 0x7f) {
        pcd->contrast = 0x7f;
    }
    else {
        pcd->contrast = contrast;
    }

    PCDH_TransferCommand(pcd, PCD_IS_FUNCTION_SET | PCD_FN_EXTENDED_INSTRUCTION);
    PCDH_TransferCommand(pcd, PCD_EIS_SET_VOP | pcd->contrast);
    PCDH_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
}

void PCDH_SetBias(PCD8544_Hardware* pcd, uint8 bias) {
    if(bias > 0x7) {
        pcd->contrast = 0x7;
    }
    else {
        pcd->contrast = bias;
    }

    PCDH_TransferCommand(pcd, PCD_IS_FUNCTION_SET | PCD_FN_EXTENDED_INSTRUCTION);
    PCDH_TransferCommand(pcd, PCD_EIS_SET_BIAS | pcd->bias);
    PCDH_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
}

void PCDH_SetPixel(PCD8544_Hardware* pcd, uint8 x, uint8 y, uint8 color) {
    if(x > PCD_LCD_WIDTH || y > PCD_LCD_HEIGHT) return;

    if(color) {
        pcd->drawBuffer[x + ((y / 8) * PCD_LCD_WIDTH)] |= (1 << (y % 8));
    }
    else {
        pcd->drawBuffer[x + ((y / 8) * PCD_LCD_WIDTH)] &= ~(1 << (y % 8));
    }
}

void PCDH_Display(PCD8544_Hardware* pcd) {
    PCDH_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
    PCDH_TransferCommand(pcd, PCD_IS_DISPLAY_CONTROL | PCD_DC_DISPLAY_NORMAL);

    for(uint8 page = 0; page < PCD_LCD_HEIGHT / 8; page++) {
        PCDH_TransferCommand(pcd, PCD_IS_SET_Y_ADDRESS | page);
        PCDH_TransferCommand(pcd, PCD_IS_SET_X_ADDRESS);

        setOutputGPIO(pcd->dataCommandIO, pcd->dataCommandPin, HIGH);

        SPI_SW_TX_Write(&pcd->spiTx, pcd->drawBuffer + (PCD_LCD_WIDTH * page), PCD_LCD_WIDTH);
    }

    PCDH_TransferCommand(pcd, PCD_IS_SET_Y_ADDRESS);
}

void PCDH_DisplayPixel(PCD8544_Hardware* pcd, uint8 x, uint8 y, uint8 color) {
    if(x > PCD_LCD_WIDTH || y > PCD_LCD_HEIGHT) return;

    if(color) {
        pcd->drawBuffer[x + ((y / 8) * PCD_LCD_WIDTH)] |= (1 << (y % 8));
    }
    else {
        pcd->drawBuffer[x + ((y / 8) * PCD_LCD_WIDTH)] &= ~(1 << (y % 8));
    }

    PCDh_TransferCommand(pcd, PCD_IS_FUNCTION_SET);
    PCDh_TransferCommand(pcd, PCD_IS_DISPLAY_CONTROL | PCD_DC_DISPLAY_NORMAL);

    PCDH_TransferCommand(pcd, PCD_IS_SET_Y_ADDRESS | (y / 8));
    PCDH_TransferCommand(pcd, PCD_IS_SET_X_ADDRESS | x);

    setOutputGPIO(pcd->dataCommandIO, pcd->dataCommandPin, HIGH);

    SPI_SW_TX_WriteByte(&pcd->spiTx, 1 << (y % 8));

    PCDH_TransferCommand(pcd, PCD_IS_SET_Y_ADDRESS);
}*/

const uint8 gFont[97][6] = {
    /*{0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
    {0x0, 0x0, 0x0, 0x0, 0x0, 0x0},*/
    {0x08, 0x08, 0x08, 0x08, 0x00, 0x08},
    {0x14, 0x14, 0x00, 0x00, 0x00, 0x00},
    {0x48, 0xff, 0x24, 0x24, 0xff, 0x12},
    {0x3c, 0x52, 0x1c, 0x30, 0x52, 0x3c},
    {0x42, 0x25, 0x12, 0x48, 0xa4, 0x42},
    {0x18, 0x24, 0x18, 0xa4, 0x64, 0x58},
    {0x08, 0x08, 0x00, 0x00, 0x00, 0x00},
    {0x10, 0x08, 0x04, 0x04, 0x08, 0x10},
    {0x04, 0x08, 0x10, 0x10, 0x08, 0x04},
    {0x08, 0x1c, 0x14, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x08, 0x1c, 0x08, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x08, 0x04},
    {0x00, 0x00, 0x00, 0x1c, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x04},
    {0x10, 0x10, 0x08, 0x08, 0x04, 0x04},
    {0x18, 0x24, 0x24, 0x24, 0x24, 0x18},
    {0x08, 0x0c, 0x08, 0x08, 0x08, 0x1c},
    {0x18, 0x24, 0x10, 0x08, 0x04, 0x3c},
    {0x18, 0x24, 0x10, 0x20, 0x24, 0x18},
    {0x10, 0x18, 0x14, 0x3c, 0x10, 0x10},
    {0x3c, 0x04, 0x1c, 0x20, 0x20, 0x1c},
    {0x18, 0x24, 0x04, 0x1c, 0x24, 0x18},
    {0x3c, 0x20, 0x10, 0x10, 0x08, 0x08},
    {0x18, 0x24, 0x18, 0x24, 0x24, 0x18},
    {0x18, 0x24, 0x38, 0x20, 0x20, 0x18},
    {0x00, 0x08, 0x00, 0x00, 0x08, 0x00},
    {0x00, 0x08, 0x00, 0x00, 0x08, 0x04},
    {0x60, 0x18, 0x06, 0x06, 0x18, 0x60},
    {0x00, 0x00, 0x1c, 0x00, 0x1c, 0x00},
    {0x06, 0x18, 0x60, 0x60, 0x18, 0x06},
    {0x18, 0x24, 0x20, 0x10, 0x00, 0x10},
    {0x3c, 0x5a, 0x66, 0x66, 0x7a, 0x1c},
    //Letters Upper
    {0x18, 0x24, 0x24, 0x3c, 0x24, 0x24},
    {0x18, 0x24, 0x1c, 0x24, 0x24, 0x1c},
    {0x18, 0x24, 0x04, 0x04, 0x24, 0x18},
    {0x1c, 0x24, 0x24, 0x24, 0x24, 0x1c},
    {0x3c, 0x04, 0x04, 0x1c, 0x04, 0x3c},
    {0x3c, 0x04, 0x04, 0x1c, 0x04, 0x04},
    {0x18, 0x24, 0x04, 0x34, 0x24, 0x18},
    {0x24, 0x24, 0x24, 0x3c, 0x24, 0x24},
    {0x1c, 0x08, 0x08, 0x08, 0x08, 0x1c},
    {0x78, 0x20, 0x20, 0x20, 0x24, 0x18},
    {0x24, 0x24, 0x14, 0x0c, 0x14, 0x24},
    {0x04, 0x04, 0x04, 0x04, 0x04, 0x3c},
    {0x22, 0x36, 0x2a, 0x22, 0x22, 0x22},
    {0x22, 0x26, 0x2a, 0x2a, 0x32, 0x22},
    {0x1c, 0x22, 0x22, 0x22, 0x22, 0x1c},
    {0x0e, 0x12, 0x12, 0x0e, 0x02, 0x02},
    {0x1c, 0x22, 0x22, 0x22, 0x22, 0x7c},
    {0x0e, 0x12, 0x12, 0x0e, 0x0a, 0x12},
    {0x18, 0x24, 0x08, 0x10, 0x24, 0x18},
    {0x3e, 0x08, 0x08, 0x08, 0x08, 0x08},
    {0x22, 0x22, 0x22, 0x22, 0x22, 0x1c},
    {0x22, 0x22, 0x22, 0x14, 0x14, 0x08},
    {0x22, 0x22, 0x22, 0x2a, 0x36, 0x22},
    {0x14, 0x14, 0x14, 0x08, 0x14, 0x14},
    {0x22, 0x22, 0x14, 0x08, 0x08, 0x08},
    {0x3c, 0x20, 0x10, 0x08, 0x04, 0x3c},
    {0x1c, 0x04, 0x04, 0x04, 0x04, 0x1c},
    {0x04, 0x04, 0x08, 0x08, 0x10, 0x10},
    {0x1c, 0x10, 0x10, 0x10, 0x10, 0x1c},
    {0x08, 0x14, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x7e},
    {0x04, 0x08, 0x00, 0x00, 0x00, 0x00}
};

void PCD_DrawText(PCD8544_Software *pcd, const char* text, uint8 x, uint8 y) {
    int next_line = 0;
    int to_start = 0;

    for(uint16 i = 0; i < GetStrLen(text); i++) {
        if(text[i] == 10) {
            next_line += 8;
            to_start = (i + 1) * 8;

            continue;
        }

        if(text[i] == '\t') {
            to_start = -2;

            continue;
        }

        for(uint8 my = 0; my < 6; my++) {
            for(uint8 mx = 0; mx < 8; mx++) {
                if(text[i] != 10) {
                    PCD_SetPixel(pcd, x + mx + ((i * 6) - to_start), y + (my + next_line), gFont[ToUpper(text[i]) - 33][my] & (0x1 << mx));
                }
            }
        }
    }
}


#endif