/*
	Created with D:\C\BlackpillFun\creator.exe -name ST7735_Tests -ram 128k -rom 512k -board F4 
*/
#define STM32_L4XX

#include "../additional_libs/st7735s.h"
#include "../additional_libs/pcd8544.h"
// #include "test.h"

int stmMain() {
	InitGPIO(IO_C, 0);
	// InitGPIO(IO_B, 0);

	// PCD8544_Software pcd;

	// PCD_BeginSingleIO(&pcd, 4, 5, 6, 7, 8, 9, IO_B);
	// PCD_SetBacklight(&pcd, HIGH);
	// PCD_SetContast(&pcd, 0xff);
	// PCD_SetBias(&pcd, 0xff);

	// spi.masterOutIO = IO_B;
	// spi.masterOutPin = 6;
	// spi.clockIO = IO_B;
	// spi.clockPin = 7;
	// setPinModeGPIO(ST7735_CS_GPIO_Port, ST7735_CS_Pin, MODE_OUTPUT);
    // setPinModeGPIO(ST7735_RES_GPIO_Port, ST7735_RES_Pin, MODE_OUTPUT);
    // setPinModeGPIO(ST7735_DC_GPIO_Port, ST7735_DC_Pin, MODE_OUTPUT);
	
	// SPI_SW_TX_Begin(&spi);

	// ST7735_Init();

	ST7735S_SW st;
	ST_BeginSingleIO(&st, 0, 1, 2, 3, 4, 5, IO_C);
	ST_PixelFormat(&st, INTERFACE_PIXEL_FORMAT_16BIT);
	ST_ResetArea(&st);

	while(1) {
		// ST7735_FillScreen(ST7735_BLACK);

		// ST7735_DrawPixel(10, 10, ST7735_BLUE);
		ST_BacklightState(&st, LOW);
		ST_DrawPixel(&st, 10, 10, 0x1f, 0x0, 0x0);

		// PCD_DrawText(&pcd, "Hello", 0, 0);

		// PCD_Display(&pcd);
		// PCD_ClearDisplay(&pcd);
	}

	return 0;
}
