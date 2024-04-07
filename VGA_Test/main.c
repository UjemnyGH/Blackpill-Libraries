/*
	Created with D:\C\BlackpillFun\creator.exe -name VGA_Test 
*/
#define STM32_F4XX

#include "../additional_libs/vga_monitor.h"

int stmMain() {
	InitGPIO(IO_B, 0);

	VGA vga;

	VGA_BeginSingleIO(&vga, 0, 1, 2, 3, 4, IO_B);

	while(1) {
		// Program loop

		VGA_VerticalDisplay(&vga, 0b100);
	}

	return 0;
}
