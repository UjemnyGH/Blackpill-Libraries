/*
	Created with D:\C\BlackpillFun\creator.exe -name USB_Test 
*/
#define STM32_F4XX

#include "../additional_libs/pcd8544.h"
#include "icons.h"

#include "../src/usb_otg.h"

int stmMain() {
	InitGPIO(IO_B, 0);

	PCD8544_Software screen;

	PCD_BeginSingleIO(&screen, 4, 5, 6, 7, 8, 9, IO_B);
	PCD_SetBacklight(&screen, TRUE);
	PCD_SetContast(&screen, 0xff);
	PCD_SetBias(&screen, 0xff);

	while(1) {
		// Program loop

		PCD_LoadBitmap(&screen, 10, 20, (uint8*)gIcCheck, 5, 4);
		PCD_LoadBitmap(&screen, 10, 26, (uint8*)gIcX, 5, 5);

		PCD_DrawText(&screen, "Hello world", 0, 0);

		PCD_Display(&screen);
		PCD_ClearDisplay(&screen);
	}

	return 0;
}
