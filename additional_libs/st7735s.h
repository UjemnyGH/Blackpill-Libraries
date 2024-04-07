// TODO: Fix entire library

#ifndef __ST7735S_
#define __ST7735S_

#include "spi_software.h"
#include "memory_fn.h"

/**
 * @brief For every read every first 8 bits are dummy read and we dont care about it!!!!
 * 
 */

// Commands
#define DISPLAY_NO_OPERATION        0x0
#define DISPLAY_SOFTWARE_RESET      0x1
#define READ_DISPLAY_ID     0x4             /*4B*/
#define READ_DISPLAY_STATUS 0x9             /*5B*/
#define READ_DISPLAY_POWER_MODE 0xa         /*2B*/
#define READ_DISPLAY_MEMORY_DATA_ACCESS_CONTROL 0xb             /*2B*/
#define READ_DISPLAY_PIXEL_FORMAT   0xc     /*2B*/
#define READ_DISPLAY_IMAGE_MODE 0xd         /*2B*/
#define READ_DISPLAY_SIGNAL_MODE    0xe     /*2B*/
#define READ_DISPLAY_SELF_DIAG_RES  0xf     /*2B*/

#define DISPLAY_SLEEP_IN_BOOSTER_OFF    0x10
#define DISPLAY_SLEEP_OUT_BOOSTER_ON    0x11
#define DISPLAY_PARTIAL_MODE        0x12
#define DISPLAY_NORMAL              0x13
#define DISPLAY_INVERSION_OFF       0x20
#define DISPLAY_INVERSION_ON        0x21

#define DISPLAY_GAMMA_CURVE_SELECT  0x26    /*4 bits of data*/
#define GAMMA_CURVE_1   0x1
#define GAMMA_CURVE_2   0x2
#define GAMMA_CURVE_3   0x4
#define GAMMA_CURVE_4   0x8

#define DISPLAY_OFF         0x28
#define DISPLAY_ON          0x29
#define DISPLAY_X_ADDRESS_SET   0x2a        /*16 bits of start and 16 bits of end*/
#define DISPLAY_Y_ADDRESS_SET   0x2b        /*16 bits of start and 16 bits of end*/

#define DISPLAY_MEMORY_WRITE    0x2c
#define MAX_MEMORY_WRITE_SIZE   368640
#define MAX_MEMORY_WRITE_SIZE_BYTE   46080

#define DISPLAY_RGB_SET         0x2d        /*6 bit red tone 0; blank; 6 bit red tone "a"; 6 bit gereen tone 0; blank; 6 bit green tone "b"; 6 bit blue tone 0; blank, 6 bit blue tone "c"*/
#define READ_DISPLAY_MEMORY     0x2e        /*2B*/
#define DISPLAY_PARTIAL_START_END_ADDRESS_SET   0x30    /*2B partial start; 2B partial end*/
#define DISPLAY_SCROLL_AREA_SET 0x33        /*1B blank; 1B top fixed area; 1B blank; 1B vertical scroll area; 1B blank; 1B bottom fixed area; all from 0 to 161 max*/
#define DISPLAY_TEARING_EFFECT_LINE_OFF     0x34

#define DISPLAY_TEARING_EFFECT_LINE_SET_ON  0x35    /*1 bit of data select tearing effect; mode1 = 0, mode2 = 1*/
#define TEARING_EFFECT_LINE_V_BLANKING      0x0
#define TEARING_EFFECT_LINE_V_AND_H_BLANKING    0x1

#define DISPLAY_MEMORY_DATA_ACCESS_CONTROL  0x36    /*6 last bit of data described from end: MY, MX, MV, ML, RGB, MH*/
#define MEMORY_DATA_ROW_ORDER   0x80
#define MEMORY_DATA_COL_ORDER   0x40
#define MEMORY_DATA_ROW_COL_EXCHANGE    0x20
#define MEMORY_DATA_VERTICAL_REFRESH_T_TO_B     0x0
#define MEMORY_DATA_VERTICAL_REFRESH_B_TO_T     0x10
#define MEMORY_DATA_RGB         0x0
#define MEMORY_DATA_BGR         0x8
#define MEMORY_DATA_HORIZONTAL_REFRESH_L_TO_R   0x0
#define MEMORY_DATA_HORIZONTAL_REFRESH_R_TO_L   0x4

#define DISPLAY_SCROLL_START_ADDRESS_OF_RAM 0x37    /*1B blank; 1B SSA (values 0-161) */
#define DISPLAY_IDLE_MODE_OFF       0x38
#define DISPLAY_IDLE_MODE_ON        0x39
#define DISPLAY_INTERFACE_PIXEL_FORMAT 0x3a         /*3 first bit of IFPF*/
#define INTERFACE_PIXEL_FORMAT_12BIT            0x3                     /*Refers to command DISPLAY_INTERFACE_PIXEL_FORMAT*/
#define INTERFACE_PIXEL_FORMAT_16BIT            0x5                     /*Refers to command DISPLAY_INTERFACE_PIXEL_FORMAT*/
#define INTERFACE_PIXEL_FORMAT_18BIT            0x6                     /*Refers to command DISPLAY_INTERFACE_PIXEL_FORMAT*/
#define READ_DISPLAY_ID1    0xda                    /*1B blank; 1B read parameter*/
#define READ_DISPLAY_ID2    0xdb                    /*1B blank; 1B read parameter*/
#define READ_DISPLAY_ID3    0xdc                    /*1B blank; 1B read parameter*/

#define DISPLAY_FRAMERATE_CONTROL_NORMAL    0xb1
#define DISPLAY_FRAMERATE_CONTROL_IDLE      0xb2
#define DISPLAY_FRAMERATE_CONTROL_PARTIAL   0xb3
#define FRAME_CONTROL_RESET_PARAM1          0x5
#define FRAME_CONTROL_RESET_PARAM2          0x3c
#define FRAME_CONTROL_RESET_PARAM3          0x3c

#define DISPLAY_INVERSION_CONTROL           0xb4
#define INVERSION_CONTROL_NORMAL_COLUMN     0x1
#define INVERSION_CONTROL_IDLE_COLUMN       0x2
#define INVERSION_CONTROL_PARTIAL_COLUMN    0x4
#define INVERSION_CONTROL_NORMAL_DOT        0x0
#define INVERSION_CONTROL_IDLE_DOT          0x0
#define INVERSION_CONTROL_PARTIAL_DOT       0x0

#define DISPLAY_POWER_CONTROL_SETTING1      0xc0
#define POWER_CONTROL_MODE_2X   0x0
#define POWER_CONTROL_MODE_AUTO 0x84

#define DISPLAY_POWER_CONTROL_SETTING2      0xc1
#define DISPLAY_POWER_CONTROL_SETTING_NORMAL    0xc2
#define DISPLAY_POWER_CONTROL_SETTING_IDLE      0xc3
#define DISPLAY_POWER_CONTROL_SETTING_PARTIAL   0xc4
#define DISPLAY_VCOM_CONTROL                0xc5
#define DISPLAY_VCOM_OFFSET_CONTRTOL        0xc7
#define DISPLAY_SET_LCM_VERSION_CODE        0xd1
#define DISPLAY_SET_CUSTOMER_PROJECT_CODE       0xd2
#define DISPLAY_NVM_CONTROL_STATUS          0xd9
#define DISPLAY_NVM_READ_COMMAND            0xde
#define DISPLAY_NVM_WRITE_COMMAND_ACTION        0xdf

#define DISPLAY_GAMMA_ADJUSTMENT_PLUS_POLARITY  0xe0
#define DISPLAY_GAMMA_ADJUSTMENT_MINUS_POLARITY 0xe1
#define DISPLAY_GATE_CLOCK_VAR              0xfc

#define DEFAULT_WIDTH   159
#define DEFAULT_HEIGHT  127
#define DEFAULT_XSTART  0
#define DEFAULT_YSTART  0

typedef struct ST7735S_SW {
    SPI_Software_TX spiTx;
    uint8 resetPin, dataCommandPin, backlightPin;
    struct GeneralPurposeIO *resetIO, *dataCommandIO, *backlightIO;

    uint8 width, height, xStart, yStart;
    uint8 x[2], y[2];

    uint8 frame[MAX_MEMORY_WRITE_SIZE_BYTE];
    uint8 pixelFormat;
} ST7735S_SW;

/**
 * @brief Wrapper function for SPI_SW_TX_TransferByte
 * 
 * @param st 
 * @param byte 
 */
void ST_Send(ST7735S_SW* st, uint8 byte) {
    SPI_SW_TX_TransferByte(&st->spiTx, byte);
}

void ST_Send16(ST7735S_SW* st, uint16 hword) {
    SPI_SW_TX_TransferByte(&st->spiTx, (hword >> 8) & 0xff);
    SPI_SW_TX_TransferByte(&st->spiTx, hword & 0xff);
}

void ST_Send32(ST7735S_SW* st, uint32 word) {
    SPI_SW_TX_TransferByte(&st->spiTx, (word >> 24) & 0xff);
    SPI_SW_TX_TransferByte(&st->spiTx, (word >> 16) & 0xff);
    SPI_SW_TX_TransferByte(&st->spiTx, (word >> 8) & 0xff);
    SPI_SW_TX_TransferByte(&st->spiTx, word & 0xff);
}

void ST_SendBlock(ST7735S_SW* st, uint8* data, uint16 len) {
    for(int i = 0; i < len; i++) {
        ST_Send(st, data[i]);
    }
}

void ST_SerialBusEnable(ST7735S_SW* st) {
    SPI_SW_TX_BeginTransaction(&st->spiTx);
}

void ST_SerialBusDisable(ST7735S_SW* st) {
    SPI_SW_TX_EndTransaction(&st->spiTx);
}

void ST_Command(ST7735S_SW* st) {
    setPinModeGPIO(st->dataCommandIO, st->dataCommandPin, LOW);
}

void ST_Data(ST7735S_SW* st) {
    setPinModeGPIO(st->dataCommandIO, st->dataCommandPin, HIGH);
}

void ST_TransmitCD(ST7735S_SW* st, uint8* data, uint16 len) {
    ST_Command(st);

    ST_Send(st, data[0]);

    ST_Data(st);

    for(int i = 1; i < len; i++) {
        ST_Send(st, data[i]);
    }
}

void ST_TransmitSPIDataCD(ST7735S_SW* st, SPI_Data data) {
    ST_Command(st);

    ST_Send(st, data.data[0]);

    ST_Data(st);

    ST_SendBlock(st, data.data + 1, data.len - 1);
}

void ST_Begin(ST7735S_SW* st, uint8 rstPin, uint8 chipEnPin, uint8 datComPin, uint8 dataPin, uint8 clkPin, uint8 lightPin, struct GeneralPurposeIO *rstIO, struct GeneralPurposeIO * chipEnIO, struct GeneralPurposeIO *datComIO, struct GeneralPurposeIO * dataIO, struct GeneralPurposeIO * clkIO, struct GeneralPurposeIO *lightIO) {
    st->width = DEFAULT_WIDTH;
    st->height = DEFAULT_HEIGHT;
    st->xStart = DEFAULT_XSTART;
    st->yStart = DEFAULT_YSTART;
    
    st->resetPin = rstPin;
    st->dataCommandPin = datComPin;
    st->backlightPin = lightPin;

    st->resetIO = rstIO;
    st->dataCommandIO = datComIO;
    st->backlightIO = lightIO;

    setPinModeGPIO(st->resetIO, st->resetPin, MODE_OUTPUT);
    setPinModeGPIO(st->dataCommandIO, st->dataCommandPin, MODE_OUTPUT);
    setPinModeGPIO(st->backlightIO, st->backlightPin, MODE_OUTPUT);
    /*setPullGPIO(st->backlightIO, st->backlightPin, GPIO_PULL_DOWN);
    setPullGPIO(st->dataCommandIO, st->dataCommandPin, GPIO_PULL_DOWN);
    setPullGPIO(st->resetIO, st->resetPin, GPIO_PULL_UP);*/

    st->spiTx.frequency = 40000000;
    st->spiTx.chipSelectPin = chipEnPin;
    st->spiTx.clockPin = clkPin;
    st->spiTx.masterOutPin = dataPin;
    st->spiTx.masterInPin = -1;

    st->spiTx.chipSelectIO = chipEnIO;
    st->spiTx.clockIO = clkIO;
    st->spiTx.masterOutIO = dataIO;
    st->spiTx.masterInIO = ((struct GeneralPurposeIO*)0);
    st->spiTx.bitSignificance = SPI_SW_TX_MSB;
    
    SPI_SW_TX_Begin(&st->spiTx);

    // setOutputGPIO(st->resetIO, st->resetPin, HIGH);
    ST_SerialBusEnable(st);
    // ST_Command(st);
    // setOutputGPIO(st->resetIO, st->resetPin, LOW);
    // delay(40);
    setOutputGPIO(st->resetIO, st->resetPin, HIGH);
    delay(4000);
    ST_SerialBusDisable(st);

    st->pixelFormat = INTERFACE_PIXEL_FORMAT_16BIT;

    ST_SerialBusEnable(st);
    ST_Command(st);
    ST_Send(st, DISPLAY_SOFTWARE_RESET);
    ST_SerialBusDisable(st);
    delay(6000);

    ST_SerialBusEnable(st);
    ST_Send(st, DISPLAY_SLEEP_OUT_BOOSTER_ON);
    ST_SerialBusDisable(st);
    delay(2000);

    // ST_SerialBusEnable(st);
    // ST_Send(st, DISPLAY_MEMORY_DATA_ACCESS_CONTROL);
    // ST_Data(st);
    // ST_Send(st, MEMORY_DATA_COL_ORDER | MEMORY_DATA_ROW_ORDER);
    // ST_SerialBusDisable(st);

    // ST_SerialBusEnable(st);
    // ST_Command(st);
    // ST_Send(st, DISPLAY_INTERFACE_PIXEL_FORMAT);
    // ST_Data(st);
    // ST_Send(st, st->pixelFormat);
    // ST_SerialBusDisable(st);
    // delay(40);

    ST_SerialBusEnable(st);
    ST_Command(st);
    ST_Send(st, DISPLAY_ON);
    ST_SerialBusDisable(st);
    delay(400);

    /*ST_SerialBusEnable(st);
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_SOFTWARE_RESET}, 1});
    ST_SerialBusDisable(st);
    delay(600);
    ST_SerialBusEnable(st);
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_SLEEP_OUT_BOOSTER_ON}, 1});
    ST_SerialBusDisable(st);
    delay(2000);*/
    //ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_OFF}, 1});

    /*ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_FRAMERATE_CONTROL_NORMAL, 0x1, 0x2c, 0x2d}, 4});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_FRAMERATE_CONTROL_IDLE, 0x1, 0x2c, 0x2d}, 4});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_FRAMERATE_CONTROL_PARTIAL, 0x1, 0x2c, 0x2d, 0x1, 0x2c, 0x2d}, 7});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_INVERSION_CONTROL, INVERSION_CONTROL_IDLE_COLUMN | INVERSION_CONTROL_NORMAL_COLUMN | INVERSION_CONTROL_PARTIAL_COLUMN}, 2});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_POWER_CONTROL_SETTING1, 0xa2, 0x2 // -4.6V
    , POWER_CONTROL_MODE_AUTO}, 4});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_POWER_CONTROL_SETTING2, 0xc5}, 2}); // 0xc0 orig
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_POWER_CONTROL_SETTING_NORMAL, 0xa, 0}, 3});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_POWER_CONTROL_SETTING_IDLE, 0x8a, 0x2a}, 3});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_POWER_CONTROL_SETTING_PARTIAL, 0x8a, 0xee}, 3});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_VCOM_CONTROL, 0xe}, 2});
    delay(40);
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_INVERSION_OFF}, 1});*/
    /*ST_SerialBusEnable(st);
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_MEMORY_DATA_ACCESS_CONTROL, MEMORY_DATA_COL_ORDER | MEMORY_DATA_ROW_ORDER}, 2});
    ST_SerialBusDisable(st);
    ST_SerialBusEnable(st);
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_INTERFACE_PIXEL_FORMAT, st->pixelFormat}, 2});
    ST_SerialBusDisable(st);
    delay(40);*/

    /*ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_X_ADDRESS_SET, 0, 0, 0, st->width}, 5});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_Y_ADDRESS_SET, 0, 0, 0, st->height}, 5});
    
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_GAMMA_ADJUSTMENT_PLUS_POLARITY, 0x02, 0x1c, 0x07, 0x12, 0x37, 0x32, 0x29, 0x2c, 0x29, 0x25, 0x2b, 0x39, 0x00, 0x01, 0x03, 0x10}, 17});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_GAMMA_ADJUSTMENT_MINUS_POLARITY, 0x03, 0x1d, 0x07, 0x06, 0x2E, 0x2C, 0x29, 0x2c, 0x2e, 0x2e, 0x37, 0x3f, 0x00, 0x00, 0x02, 0x10}, 17});*/

    /*ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_IDLE_MODE_OFF}, 1});
    delay(40);*/
    /*ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_NORMAL}, 1});
    delay(40);*/
    /*ST_SerialBusEnable(st);
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_ON}, 1}); 
    ST_SerialBusDisable(st);
    delay(400);*/
}

void ST_BeginSingleIO(ST7735S_SW* st, uint8 rstPin, uint8 chipEnPin, uint8 datComPin, uint8 dataPin, uint8 clkPin, uint8 lightPin, struct GeneralPurposeIO *io) {
    ST_Begin(st, rstPin, chipEnPin, datComPin, dataPin, clkPin, lightPin, io, io, io, io, io, io);
}

void ST_BacklightState(ST7735S_SW* st, uint8 state) {
    setOutputGPIO(st->backlightIO, st->backlightPin, state);
}

void ST_Reset(ST7735S_SW* st) {
    setOutputGPIO(st->resetIO, st->resetPin, HIGH);
    ST_SerialBusEnable(st);
    ST_Command(st);
    setOutputGPIO(st->resetIO, st->resetPin, LOW);
    delay(40);
    setOutputGPIO(st->resetIO, st->resetPin, HIGH);
    delay(40);
    ST_SerialBusDisable(st);
}

void ST_SoftwareReset(ST7735S_SW* st) {
    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_SOFTWARE_RESET}, 1}); ST_SerialBusDisable(st);
    delay(600);
}

void ST_Sleep(ST7735S_SW* st) {
    ST_BacklightState(st, LOW);
    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_OFF}, 1}); ST_SerialBusDisable(st);
    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_SLEEP_IN_BOOSTER_OFF}, 1}); ST_SerialBusDisable(st);
}

void ST_Wakeup(ST7735S_SW* st) {
    ST_BacklightState(st, HIGH);
    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_SLEEP_OUT_BOOSTER_ON}, 1}); ST_SerialBusDisable(st);
    delay(2000);
    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_ON}, 1}); ST_SerialBusDisable(st);
    delay(400);
}

void ST_PixelFormat(ST7735S_SW* st, uint8 pixelFormat) {
    st->pixelFormat = pixelFormat;

    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_INTERFACE_PIXEL_FORMAT, st->pixelFormat}, 2}); ST_SerialBusDisable(st);
}

void ST_Brightness(ST7735S_SW* st, uint8 brightness) {
    if(brightness > 0x1f) brightness = 0x1f;
    
    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_NVM_CONTROL_STATUS, 0x40}, 2}); ST_SerialBusDisable(st);
    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_VCOM_OFFSET_CONTRTOL, brightness}, 2}); ST_SerialBusDisable(st);
    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_NVM_CONTROL_STATUS, 0}, 2}); ST_SerialBusDisable(st);
}

void ST_UpdatedArea(ST7735S_SW* st, uint8 x, uint8 y) {
    if(x <= st->width && y <= st->height) {
        if(x < st->x[0]) st->x[0] = x;
        if(x > st->x[1]) st->x[1] = x;
        if(y < st->y[0]) st->y[0] = y;
        if(y > st->y[1]) st->y[1] = y;
    }
}

void ST_WriteArea(ST7735S_SW* st) {
    ST_SerialBusEnable(st); 

    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_X_ADDRESS_SET, 0, st->x[0], 0, st->x[1]}, 5});
    ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_Y_ADDRESS_SET, 0, st->y[0], 0, st->y[1]}, 5}); 
    
    ST_SerialBusDisable(st);
}

void ST_ResetArea(ST7735S_SW* st) {
    st->x[0] = st->width;
    st->x[1] = 0;
    st->y[0] = st->height;
    st->y[1] = 0;
}

void ST_ClearFrame(ST7735S_SW* st) {
    ST_UpdatedArea(st, 0, 0);
    ST_UpdatedArea(st, DEFAULT_WIDTH, DEFAULT_HEIGHT);

    for(int i = 0; i < MAX_MEMORY_WRITE_SIZE_BYTE; i++) {
        st->frame[i] = 0;
    }
}

/**
 * @brief Can take only 0, 90, 180 and 270 values
 * 
 * @param degrees Can take only 0, 90, 180 and 270 values
 */
void ST_SetOrientation(ST7735S_SW* st, uint16 degrees) {
    uint8 memory_ctl;

    switch(degrees) {
    case 0:
        memory_ctl = MEMORY_DATA_COL_ORDER | MEMORY_DATA_ROW_COL_EXCHANGE;
        st->width = DEFAULT_WIDTH;
        st->height = DEFAULT_HEIGHT;
        st->xStart = DEFAULT_XSTART;
        st->yStart = DEFAULT_YSTART;
        
        break;

    case 90:
        memory_ctl = MEMORY_DATA_COL_ORDER | MEMORY_DATA_ROW_ORDER;
        st->width = DEFAULT_HEIGHT;
        st->height = DEFAULT_WIDTH;
        st->xStart = DEFAULT_YSTART;
        st->yStart = DEFAULT_XSTART;
        
        break;

    case 180:
        memory_ctl = MEMORY_DATA_ROW_ORDER | MEMORY_DATA_ROW_COL_EXCHANGE;
        st->width = DEFAULT_WIDTH;
        st->height = DEFAULT_HEIGHT;
        st->xStart = DEFAULT_XSTART;
        st->yStart = DEFAULT_YSTART;
        
        break;

    case 270:
        memory_ctl = MEMORY_DATA_COL_ORDER;
        st->width = DEFAULT_HEIGHT;
        st->height = DEFAULT_WIDTH;
        st->xStart = DEFAULT_YSTART;
        st->yStart = DEFAULT_XSTART;
        
        break;

    default:
        memory_ctl = MEMORY_DATA_COL_ORDER | MEMORY_DATA_ROW_COL_EXCHANGE;
        st->width = DEFAULT_WIDTH;
        st->height = DEFAULT_HEIGHT;
        st->xStart = DEFAULT_XSTART;
        st->yStart = DEFAULT_YSTART;
        
        break;
    }

    ST_SerialBusEnable(st); ST_TransmitSPIDataCD(st, (SPI_Data){{DISPLAY_MEMORY_DATA_ACCESS_CONTROL, memory_ctl}, 2}); ST_SerialBusDisable(st);
}

void ST_SetPixel(ST7735S_SW* st, uint8 x, uint8 y, uint8 r, uint8 g, uint8 b) {
    r &= 0x3f;
    g &= 0x3f;
    b &= 0x3f;

    if(x <= st->width && y <= st->height) {
        

        switch(st->pixelFormat) {
        case INTERFACE_PIXEL_FORMAT_12BIT:
            st->frame[(st->width + 1) * y + x] = (r << 4) | g;
            st->frame[(st->width + 1) * y + x + 1] = (b << 4);

            break;

        case INTERFACE_PIXEL_FORMAT_16BIT:
            st->frame[(st->width + 1) * y + x] = (r << 3) | (g >> 5);
            st->frame[(st->width + 1) * y + x + 1] = (g << 5) | b;

            break;

        case INTERFACE_PIXEL_FORMAT_18BIT:
            st->frame[(st->width + 1) * y + x] = (r << 2);
            st->frame[(st->width + 1) * y + x + 1] = (g << 2);
            st->frame[(st->width + 1) * y + x + 2] = (b << 2);

            break;
        }

        ST_UpdatedArea(st, x, y);
    }
}

void ST_DrawPixel(ST7735S_SW* st, uint8 x, uint8 y, uint8 r, uint8 g, uint8 b) {
    r &= 0x3f;
    g &= 0x3f;
    b &= 0x3f;

    if(x >= st->x[0] && x < st->x[1] && y >= st->y[0] && y < st->y[1]) {
        ST_ResetArea(st);
        ST_UpdatedArea(st, x, y);
        ST_WriteArea(st);

        ST_SerialBusEnable(st);

        ST_Command(st);

        ST_Send(st, DISPLAY_MEMORY_WRITE);

        ST_Data(st);

        switch(st->pixelFormat) {
        case INTERFACE_PIXEL_FORMAT_12BIT:
            ST_Send(st, (r << 4) | g);
            ST_Send(st, (b << 4));

            break;

        case INTERFACE_PIXEL_FORMAT_16BIT:
            ST_Send(st, (r << 3) | (g >> 5));
            ST_Send(st, (g << 5) | b);

            break;

        case INTERFACE_PIXEL_FORMAT_18BIT:
            ST_Send(st, (r << 2));
            ST_Send(st, (g << 2));
            ST_Send(st, (b << 2));

            break;
        }

        ST_SerialBusDisable(st);
    }
}

void ST_Display(ST7735S_SW* st) {
    ST_WriteArea(st);

    ST_SerialBusEnable(st);

    ST_Command(st);

    ST_Send(st, DISPLAY_MEMORY_WRITE);

    ST_Data(st);

    /*uint16 len  = (xmax-xmin+1)*2;
    for (uint16_t y = ymin; y <= ymax; y++)
        SPI_TransmitData(len, (uint8_t *)&frame[WIDTH*y+xmin]);*/

    /*for(uint8 y = st->y[0]; y < st->y[1]; y++) {
        ST_TransmitData(st, (uint8*)&st->frame[DEFAULT_WIDTH * y + st->x[0]], (st->x[0]-st->x[1]) * 2);
    }*/

    for(uint8 y = st->y[0]; y <= st->y[1]; y++) {
        for(uint8 x = st->x[0]; x <= st->x[1]; x++) {
            //uint8 v[3] = {0, 0, 0};

            switch(st->pixelFormat) {
            case INTERFACE_PIXEL_FORMAT_12BIT:
                /*v[0] = (st->frame[st->width * y + (x * 3 + 0)] << 4) | (st->frame[st->width * y + (x * 3 + 1)]);
                v[1] = (st->frame[st->width * y + (x * 3 + 2)] << 4) | (st->frame[st->width * y + (x * 3 + 3)]);

                break;*/

            case INTERFACE_PIXEL_FORMAT_16BIT:
                //v[0] = (st->frame[st->width * y + (x * 3 + 0)] << 3) | (st->frame[st->width * y + (x * 3 + 1)] >> 3);
                //v[1] = (st->frame[st->width * y + (x * 3 + 1)] << 5) | (st->frame[st->width * y + (x * 3 + 2)]);
                ST_Send16(st, (uint16)(st->frame[(st->width + 1) * y + x] << 8) | st->frame[(st->width + 1) * y + x + 1]);

                break;

            case INTERFACE_PIXEL_FORMAT_18BIT:
                /*v[0] = ((st->frame[st->width * y + (x * 3 + 0)] << 2) & 0xfc);
                v[1] = ((st->frame[st->width * y + (x * 3 + 1)] << 2) & 0xfc);
                v[2] = ((st->frame[st->width * y + (x * 3 + 2)] << 2) & 0xfc);*/
                ST_Send(st, st->frame[(st->width + 1) * y + x]);
                ST_Send(st, st->frame[(st->width + 1) * y + x + 1]);
                ST_Send(st, st->frame[(st->width + 1) * y + x + 2]);
                
                break;
            }

            /*if(st->pixelFormat == INTERFACE_PIXEL_FORMAT_18BIT) {
                ST_SendBlock(st, v, 3);
            }
            else {
                ST_SendBlock(st, v, 2);
            }*/
        }
    }

    ST_SerialBusDisable(st);

    ST_ResetArea(st);
}

#endif