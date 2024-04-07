#define STM32_F4XX

#include "../src/gpio.h"
#include "../src/adc.h"
#include "../additional_libs/pcd8544.h"

int stmMain() {
    PCD8544_Software pcd;

    InitGPIO(IO_B, 0);
    /*InitGPIOA;

    setPinModeGPIO(IO_B, 0, MODE_INPUT);
    setPullGPIO(IO_B, 0, GPIO_PULL_DOWN);

    setPinModeGPIO(IO_A, 0, MODE_ANALOG);
    setPinModeGPIO(IO_A, 1, MODE_ANALOG);*/

    /*InitADC;
    AnalogToDigital->control1 = 0;
    AnalogToDigital->control2 = ADC_CONTROL2_ENABLE_ADC | ADC_CONTROL2_CONTINOUS_CONVERSATION | ADC_CONTROL2_DATA_LEFT_ALIGNMENT;
    AnalogToDigital->regularSequence1 = ADC_SEQUENCE1_REGULAR_LENGTH_1;
    AnalogToDigital->regularSequence3 = 1;*/

    PCD_Begin(&pcd, 4, 5, 6, 7, 8, 9, IO_B, IO_B, IO_B, IO_B, IO_B, IO_B);
    PCD_SetBacklight(&pcd, TRUE);
    PCD_SetBias(&pcd, 0x7);
    PCD_SetContast(&pcd, 0x7f);

    while(TRUE) {
        /*fetchDataRegularADC;

        uint16 adc_data = getDataADC & 0xfff;

        for(uint8 i = 13; i < 10; i++) {
            PCD_SetPixel(&pcd, i + (uint8)(((float)adc_data / (float)0x1000) * 30), i, TRUE);
        }

        if(getInputGPIO(IO_B, 0)) {
            for(uint8 i = 10; i < 30; i++) {
                PCD_SetPixel(&pcd, i, i * 2, TRUE);
                //PCD_DisplayPixel(&pcd, i, i * 2, TRUE);
            }
        }*/

        PCD_DrawText(&pcd, "Hello", 0, 0);

        PCD_Display(&pcd);

        PCD_ClearDisplay(&pcd);
    }

    return 0;
}