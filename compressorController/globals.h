#ifndef __GLOBALS_
#define __GLOBALS_

#include "../additional_libs/pcd8544.h"

#ifdef LANG_PL
#define TEXT_YES "Tak"
#define TEXT_NO "Nie"
#define TEXT_HIGH "Wysokie"
#define TEXT_LOW "Niskie"
#define TEXT_GOOD "Dobry"
#define TEXT_BAD "Zly"
#define TEXT_PRESSURE "Cisnienie"
#define TEXT_WATER "Woda"
#define TEXT_OIL "Cisnienie oleju"
#define TEXT_RUNTIME "Czas pracy"
#define TEXT_STOP "Zatrzymaj"
#define TEXT_START "Pracuj"
#define TEXT_RUNNING "Praca"
#define TEXT_WAITING "Spoczynek"
#define TEXT_STATE "Stan"
#define TEXT_STATE_OFFSET 30
#else
#define TEXT_YES "Yes"
#define TEXT_NO "No"
#define TEXT_HIGH "High"
#define TEXT_LOW "Low"
#define TEXT_GOOD "Good"
#define TEXT_BAD "Bad"
#define TEXT_PRESSURE "Pressure"
#define TEXT_WATER "Water"
#define TEXT_OIL "Oil pressure"
#define TEXT_RUNTIME "Runtime"
#define TEXT_STOP "Stop"
#define TEXT_START "Start"
#define TEXT_RUNNING "Running"
#define TEXT_WAITING "Waiting"
#define TEXT_ERROR "Error"
#define TEXT_STATE "State"
#define TEXT_STATE_OFFSET 38
#endif

#define BTN_DOWN 0
#define BTN_SELECT 1

enum Options {
    Options_Pressure = 0,
    Options_Water = 1,
    Options_Oil = 2,
    Options_Runtime = 3,
    Options_Stop = 4,
};

PCD8544_Software gScreen;
uint8 gDownButton = 0x80;

typedef struct CompressorData {
    uint8 mOilPressure;
    uint8 mWaterTemperature;
    uint8 mPressureDone;
    uint32 mDeltaRunningTime, mLastRunningTime;

    uint8 mOilPin, mWaterPin, mPressurePin, mMotorPin;
    struct GeneralPurposeIO* mUsedIO;
} CompressorData;

CompressorData gCData;

// -----------------------
// Compressor functions
// -----------------------

void CD_Init(CompressorData* cd, uint8 oilp, uint8 watp, uint8 presp, uint8 motorp, struct GeneralPurposeIO* usedIO) {
    cd->mOilPin = oilp;
    cd->mWaterPin = watp;
    cd->mPressurePin = presp;
    cd->mMotorPin = motorp;

    cd->mOilPressure = FALSE;
    cd->mWaterTemperature = FALSE;
    cd->mPressureDone = FALSE;
    cd->mLastRunningTime = 0; 
    cd->mDeltaRunningTime = 0;
    cd->mUsedIO = usedIO;

    setPinModeGPIO(cd->mUsedIO, cd->mOilPin, MODE_INPUT);
    setPinModeGPIO(cd->mUsedIO, cd->mWaterPin, MODE_INPUT);
    setPinModeGPIO(cd->mUsedIO, cd->mPressurePin, MODE_INPUT);
    setPinModeGPIO(cd->mUsedIO, cd->mMotorPin, MODE_OUTPUT);

    setPullGPIO(cd->mUsedIO, cd->mOilPin, GPIO_PULL_DOWN);
    setPullGPIO(cd->mUsedIO, cd->mWaterPin, GPIO_PULL_DOWN);
    setPullGPIO(cd->mUsedIO, cd->mPressurePin, GPIO_PULL_DOWN);
}

void CD_CheckParameters(CompressorData* cd) {
    cd->mOilPressure = getInputGPIO(cd->mUsedIO, cd->mOilPin);
    cd->mWaterTemperature = getInputGPIO(cd->mUsedIO, cd->mWaterPin);
    cd->mPressureDone = getInputGPIO(cd->mUsedIO, cd->mPressurePin);
}

void CD_RunMotor(CompressorData* cd) {
    if(!cd->mOilPressure || !cd->mWaterTemperature) return;

    if(cd->mPressureDone == TRUE) {
        setOutputGPIO(cd->mUsedIO, cd->mMotorPin, LOW);
    }
    else {
        setOutputGPIO(cd->mUsedIO, cd->mMotorPin, HIGH);
    }
}

uint8 CD_CheckErrors(CompressorData* cd) {
    return cd->mWaterTemperature & (cd->mOilPressure << 1);
}

// -----------------------
// Button & UI functions
// -----------------------

void BTN_Init(struct GeneralPurposeIO* io) {
    setPinModeGPIO(io, BTN_DOWN, MODE_INPUT);
    setPinModeGPIO(io, BTN_SELECT, MODE_INPUT);
    setPullGPIO(io, BTN_DOWN, GPIO_PULL_DOWN);
    setPullGPIO(io, BTN_SELECT, GPIO_PULL_DOWN);
}

void BTN_Check(struct GeneralPurposeIO* io) {
    if(getInputGPIO(io, BTN_DOWN) && (gDownButton & 0x80)) {
        gDownButton &= (uint8)(~0x80);
        gDownButton++;

        if(gDownButton > Options_Stop) {
            gDownButton = 0;
        }
    }

    if(!getInputGPIO(io, BTN_DOWN) && !(gDownButton & 0x80)) {
        gDownButton |= 0x80;
    }
}

#endif