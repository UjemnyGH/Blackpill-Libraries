/*
	Created with D:\C\BlackpillFun\creator.exe -name HD_LCD_Test 
*/
#define STM32_F4XX
#include "../additional_libs/hd44780.h"

int stmMain() {
	InitGPIO(IO_B, 0);

	HD44780 hd;

	//HD_Begin4BitSingleIO(&hd, 0, 1, 0xff, 3, 4, 5, 6, IO_B);
	HD_BeginSingleIO(&hd, 0, 1, 0xff, 3, 4, 5, 6, 7, 8, 9, 10, IO_B);
	HD_Resize(&hd, 16, 2);
	HD_Clear(&hd);

	while(1) {
		HD_SetCursor(&hd, 0, 0);
		HD_Write(&hd, 'w');
		//HD_Print(&hd, "Hello world");
		//HD_SetCursor(&hd, 0, 1);
		//HD_Print(&hd, "From HD44780");
	}

	return 0;
}
