#define STM32_F4XX
#define LANG_PL
#include "pcd_text.h"

int stmMain() {
    InitGPIOA;
    InitGPIOB;
    PCD_BeginSingleIO(&gScreen, 4, 5, 6, 7, 8, 9, IO_B);
    PCD_SetBacklight(&gScreen, 1);

    CD_Init(&gCData, 0, 1, 2, 7, IO_A);

    BTN_Init(IO_B);

    while(1) {
        BTN_Check(IO_B);

        switch(gDownButton & 0x7f) {
            case Options_Pressure:
                DrawText(TEXT_PRESSURE, 0, 0);
                DrawText(TEXT_STATE, 0, 10);
                DrawText(gCData.mPressureDone == 1 ? TEXT_RUNNING : TEXT_WAITING, TEXT_STATE_OFFSET, 10);
                break;

            case Options_Water:
                DrawText(TEXT_WATER, 0, 0);
                DrawText(TEXT_STATE, 0, 10);
                DrawText(gCData.mWaterTemperature == 1 ? TEXT_GOOD : TEXT_BAD, TEXT_STATE_OFFSET, 10);
                break;
            
            case Options_Oil:
                DrawText(TEXT_OIL, 0, 0);
                DrawText(TEXT_STATE, 0, 10);
                DrawText(gCData.mOilPressure == 1 ? TEXT_GOOD : TEXT_BAD, TEXT_STATE_OFFSET, 10);
                break;

            case Options_Runtime:
                DrawText(TEXT_RUNTIME, 0, 0);
                DrawText("TODO: RUNTIME", 0, 10);
                break;

            case Options_Stop:
                // TODO: Stop
                DrawText(TEXT_STOP, 0, 0);
                DrawText("TODO: RUNTIME", 0, 10);
                break;

            default:
                // TODO: Stop
                DrawText("Error", 0, 0);
                break;
        }

        PCD_Display(&gScreen);
        PCD_ClearDisplay(&gScreen);
    }

    return 0;
}