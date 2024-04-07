/*
	Created with ./creator -name linux_Test 
*/
#define STM32_F4XX

#include "../additional_libs/st7735s.h"
#include "../additional_libs/pcd8544.h"
#include "../additional_libs/adxl345.h"

char* cmap[17] = {
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"11",
	"12",
	"13",
	"14",
	"15",
	"16"
};

uint8 ConvertToHex(uint8 value) {
	if(value <= 9) {
		return '0' + value;
	} 
	else if(value >= 0xa && value <= 0xf) {
		return 'A' + value;
	} 

	return 'N';
}

int stmMain() {
	InitGPIO(IO_A, 0);
	InitGPIO(IO_B, 0);

	//ST7735S_SW st;
	PCD8544_Software pcd;
	ADXL345 adxl;

	ADXL_BeginSingleIO(&adxl, 0, 1, 2, 3, 4, 5, IO_A);
	ADXL_Measure(&adxl);
	ADXL_Range4G(&adxl);

	/*setPinModeGPIO(IO_A, 0, MODE_OUTPUT);
	setPinModeGPIO(IO_A, 1, MODE_OUTPUT);
	setPinModeGPIO(IO_A, 2, MODE_OUTPUT);
	setPinModeGPIO(IO_A, 3, MODE_OUTPUT);
	setPinModeGPIO(IO_A, 4, MODE_INPUT);
	setPinModeGPIO(IO_A, 5, MODE_INPUT);
	setPinModeGPIO(IO_A, 6, MODE_INPUT);
	setPinModeGPIO(IO_A, 7, MODE_INPUT);*/

	//setPullGPIO(IO_A, 4, GPIO_PULL_DOWN);
	//setPullGPIO(IO_A, 5, GPIO_PULL_DOWN);
	//setPullGPIO(IO_A, 6, GPIO_PULL_DOWN);
	//setPullGPIO(IO_A, 7, GPIO_PULL_DOWN);

	PCD_BeginSingleIO(&pcd, 4, 5, 6, 7, 8, 9, IO_B);
	PCD_SetBacklight(&pcd, HIGH);
	PCD_SetContast(&pcd, 0xff);
	PCD_SetBias(&pcd, 0xff);	

	/*ST_BeginSingleIO(&st, 0, 1, 2, 3, 4, 5, IO_A);

	ST_ClearFrame(&st);
	ST_Display(&st);*/
	//uint8 value = 0;

	while(1) {
		uint8 read = ADXL_ReadData(&adxl, ADXL_DATA_X0);
		uint8 read2 = ADXL_ReadData(&adxl, ADXL_DATA_X1);
		uint8 data[4] = {
			ConvertToHex((read >> 4) & 0xf),
			ConvertToHex(read & 0xf),
			ConvertToHex((read2 >> 4) & 0xf),
			ConvertToHex(read2 & 0xf)
		};

		PCD_DrawText(&pcd, (char*)data, 0, 0);

		PCD_Display(&pcd);
		PCD_ClearDisplay(&pcd);

/*		value = 0;

		setOutputGPIO(IO_A, 0, HIGH);
		setOutputGPIO(IO_A, 1, LOW);
		setOutputGPIO(IO_A, 2, LOW);
		setOutputGPIO(IO_A, 3, LOW);

		if(getInputGPIO(IO_A, 4)) value = 1;
		else if(getInputGPIO(IO_A, 5)) value = 2;
		else if(getInputGPIO(IO_A, 6)) value = 3;
		else if(getInputGPIO(IO_A, 7)) value = 4;

		setOutputGPIO(IO_A, 0, LOW);
		setOutputGPIO(IO_A, 1, HIGH);
		setOutputGPIO(IO_A, 2, LOW);
		setOutputGPIO(IO_A, 3, LOW);

		if(getInputGPIO(IO_A, 4)) value = 5;
		else if(getInputGPIO(IO_A, 5)) value = 6;
		else if(getInputGPIO(IO_A, 6)) value = 7;
		else if(getInputGPIO(IO_A, 7)) value = 8;

		setOutputGPIO(IO_A, 0, LOW);
		setOutputGPIO(IO_A, 1, LOW);
		setOutputGPIO(IO_A, 2, HIGH);
		setOutputGPIO(IO_A, 3, LOW);

		if(getInputGPIO(IO_A, 4)) value = 9;
		else if(getInputGPIO(IO_A, 5)) value = 10;
		else if(getInputGPIO(IO_A, 6)) value = 11;
		else if(getInputGPIO(IO_A, 7)) value = 12;

		setOutputGPIO(IO_A, 0, LOW);
		setOutputGPIO(IO_A, 1, LOW);
		setOutputGPIO(IO_A, 2, LOW);
		setOutputGPIO(IO_A, 3, HIGH);

		if(getInputGPIO(IO_A, 4)) value = 13;
		else if(getInputGPIO(IO_A, 5)) value = 14;
		else if(getInputGPIO(IO_A, 6)) value = 15;
		else if(getInputGPIO(IO_A, 7)) value = 16;*/

		/*ST_SetPixel(&st, 10, 10, 0, 0x3f, 0);

		ST_Display(&st);*/		
	}

	return 0;
}
