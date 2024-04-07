#define STM32_F4XX
#include "../additional_libs/st7735s.h"

int stmMain() {
    InitGPIO(IO_B, 0);

    ST7735S_SW st;

    ST_BeginSingleIO(&st, 3, 4, 5, 6, 7, 8, IO_B);
    //ST_PixelFormat(&st, INTERFACE_PIXEL_FORMAT_16BIT);
    /*ST_Reset(&st);
    ST_SoftwareReset(&st);
    ST_SerialBusEnable(&st);

    ST_Send(&st, DISPLAY_SLEEP_OUT_BOOSTER_ON);
    delay(600);
    ST_Send(&st, DISPLAY_OFF);
    delay(2000);
    ST_Send(&st, DISPLAY_INTERFACE_PIXEL_FORMAT);
    ST_Send(&st, INTERFACE_PIXEL_FORMAT_16BIT);

    ST_Send(&st, DISPLAY_INVERSION_OFF);
    ST_Send(&st, DISPLAY_IDLE_MODE_OFF);
    delay(40);
    ST_Send(&st, DISPLAY_NORMAL);
    delay(40);
    ST_Send(&st, DISPLAY_ON);
    delay(400);

    ST_SerialBusDisable(&st);*/

    ST_ClearFrame(&st);
    ST_Display(&st);

    while(1) {
        ST_DrawPixel(&st, 20, 20, 0x3f, 0x0, 0x0);

        ST_SetPixel(&st, 10, 10, 0x3f, 0, 0);

        ST_Display(&st);
    }

    return 0;
}