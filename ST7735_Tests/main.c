/*
	Created with D:\C\BlackpillFun\creator.exe -name ST7735_Tests -ram 128k -rom 512k -board F4 
*/
#define STM32_L4XX

#include "../additional_libs/st7735s.h"
//#include "../src/spi.h"
// #include "test.h"

int stmMain() {
	ST7735S_SW st;
	InitGPIO(IO_A, FALSE);

	ST_BeginSingleIO(&st, 0, 1, 2, 3, 4, 5, IO_A);
	ST_PixelFormat(&st, INTERFACE_PIXEL_FORMAT_16BIT);
	ST_BacklightState(&st, LOW);

	while(1) {
		ST_DrawPixel(&st, 10, 10, 0x3f, 0x1f, 0x3f);
	}

	return 0;
}

/**
 * @brief DEFINES ONLY FOR TESTING PURPOSES, DO NOT USE IN REAL SOFTWARE!!
 * 
 */
/*#define CS_BEG	setOutputGPIO(IO_A, 0, LOW);
#define CS_END	setOutputGPIO(IO_A, 0, HIGH);
#define DC_DAT	setOutputGPIO(IO_A, 1, HIGH);
#define DC_CMD	setOutputGPIO(IO_A, 1, LOW);

void DrawPixelST7735(uint8 x, uint8 y, uint8 r, uint8 g, uint8 b) {
	r &= 0x3f;
	g &= 0x3f;
	b &= 0x3f;

	CS_BEG
	DC_CMD
	WriteDataSPI(SPI1, DISPLAY_X_ADDRESS_SET);
	DC_DAT
	WriteDataSPI(SPI1, 0);
	WriteDataSPI(SPI1, x);
	WriteDataSPI(SPI1, 0);
	WriteDataSPI(SPI1, x);
	DC_CMD
	WriteDataSPI(SPI1, DISPLAY_Y_ADDRESS_SET);
	DC_DAT
	WriteDataSPI(SPI1, 0);
	WriteDataSPI(SPI1, y);
	WriteDataSPI(SPI1, 0);
	WriteDataSPI(SPI1, y);
	
	DC_CMD
	WriteDataSPI(SPI1, DISPLAY_MEMORY_WRITE);
	DC_DAT
	WriteDataSPI(SPI1, (uint8)(r << 3) | (uint8)(g << 5));
	WriteDataSPI(SPI1, (uint8)(g << 5) | b);

	CS_END
}

int stmMain() {
	// InitGPIO(IO_C, 0);
	// InitGPIO(IO_B, 0);

	InitGPIO(IO_A, 0);	// cs
	InitGPIO(IO_A, 1);	// dc
	InitGPIO(IO_A, 2);	// rst
	InitGPIO(IO_A, 3);	// bl

	InitSPI1;

	SPI1->control1 = SPI_CONTROL1_ENABLE;
	SPI1->control2 = SPI_CONTROL2_FRAME_FORMAT_TI_MODE;

	setPinModeGPIO(IO_A, 0, MODE_OUTPUT);
	setPinModeGPIO(IO_A, 1, MODE_OUTPUT);
	setPinModeGPIO(IO_A, 2, MODE_OUTPUT);
	setPinModeGPIO(IO_A, 3, MODE_OUTPUT);

	CS_BEG
	setOutputGPIO(IO_A, 2, HIGH);
	setOutputGPIO(IO_A, 2, LOW);
	setOutputGPIO(IO_A, 2, HIGH);
	CS_END

	CS_BEG
	DC_CMD
	WriteDataSPI(SPI1, DISPLAY_SOFTWARE_RESET);
	delay(6000);
	WriteDataSPI(SPI1, DISPLAY_SLEEP_OUT_BOOSTER_ON);
	delay(2000);
	WriteDataSPI(SPI1, DISPLAY_MEMORY_DATA_ACCESS_CONTROL);
	DC_DAT
	WriteDataSPI(SPI1, MEMORY_DATA_COL_ORDER | MEMORY_DATA_ROW_ORDER);
	DC_CMD
	WriteDataSPI(SPI1, DISPLAY_INTERFACE_PIXEL_FORMAT);
	DC_DAT
	WriteDataSPI(SPI1, INTERFACE_PIXEL_FORMAT_16BIT);
	delay(40);
	DC_CMD
	WriteDataSPI(SPI1, DISPLAY_ON);
	delay(400);
	CS_END

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

	// ST7735S_SW st;
	// ST_BeginSingleIO(&st, 0, 1, 2, 3, 4, 5, IO_C);
	// ST_PixelFormat(&st, INTERFACE_PIXEL_FORMAT_16BIT);
	// ST_ResetArea(&st);

	while(1) {
		// ST7735_FillScreen(ST7735_BLACK);

		DrawPixelST7735(10, 10, 0, 0, 0x1f);

		// ST7735_DrawPixel(10, 10, ST7735_BLUE);
		// ST_BacklightState(&st, LOW);
		// ST_DrawPixel(&st, 10, 10, 0x1f, 0x0, 0x0);

		// PCD_DrawText(&pcd, "Hello", 0, 0);

		// PCD_Display(&pcd);
		// PCD_ClearDisplay(&pcd);
	}

	return 0;
}
*/