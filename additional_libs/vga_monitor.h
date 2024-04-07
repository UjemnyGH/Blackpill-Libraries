#ifndef __VGA_MONITOR_
#define __VGA_MONITOR_

#include "../src/gpio.h"

/**
 * @brief Video Graphics Array struct (pins on connector below)
 * @param vsync on VGA - 14
 * @param hsync on VGA - 13
 * @param red on VGA - 1
 * @param green on VGA - 2
 * @param blue on VGA - 3
 * @param GND on VGA - 6, 7, 8, 10
 * @param NC on VGA - 4, 9, 11, (possibly 5, 12, 15)
 */
typedef struct VGA {
    uint8 redPin, greenPin, bluePin, vsyncPin, hsyncPin;
    struct GeneralPurposeIO *redIO, *greenIO, *blueIO, *vsyncIO, *hsyncIO;
    //uint8 framebuffer[640 * 480];
} VGA;

/**
 * @brief Initializes VGA struct 
 * 
 * @param pVga pointer to struct
 * @param r red pin
 * @param g green pin
 * @param b blue pin
 * @param vs vertical sync pin
 * @param hs horizontal sync pin
 * @param rio red gpio
 * @param gio green gpio
 * @param bio blue gpio
 * @param vsio vertical sync gpio
 * @param hsio horizontal sync gpio
 */
void VGA_Begin(VGA* pVga, uint8 r, uint8 g, uint8 b, uint8 vs, uint8 hs, struct GeneralPurposeIO* rio, struct GeneralPurposeIO* gio, struct GeneralPurposeIO* bio, struct GeneralPurposeIO* vsio, struct GeneralPurposeIO* hsio) {
    pVga->redPin = r;
    pVga->greenPin = g;
    pVga->bluePin = b;
    pVga->vsyncPin = vs;
    pVga->hsyncPin = hs;

    pVga->redIO = rio;
    pVga->greenIO = gio;
    pVga->blueIO = bio;
    pVga->vsyncIO = vsio;
    pVga->hsyncIO = hsio;

    setPinModeGPIO(pVga->redIO, pVga->redPin, MODE_OUTPUT);
    setPinModeGPIO(pVga->greenIO, pVga->greenPin, MODE_OUTPUT);
    setPinModeGPIO(pVga->blueIO, pVga->bluePin, MODE_OUTPUT);
    setPinModeGPIO(pVga->vsyncIO, pVga->vsyncPin, MODE_OUTPUT);
    setPinModeGPIO(pVga->hsyncIO, pVga->hsyncPin, MODE_OUTPUT);
}

/**
 * @brief Initializes VGA struct 
 * 
 * @param pVga pointer to struct
 * @param r red pin
 * @param g green pin
 * @param b blue pin
 * @param vs vertical sync pin
 * @param hs horizontal sync pin
 * @param io gpio
 */
void VGA_BeginSingleIO(VGA* pVga, uint8 r, uint8 g, uint8 b, uint8 vs, uint8 hs, struct GeneralPurposeIO* io) {
    VGA_Begin(pVga, r, g, b, vs, hs, io, io, io, io, io);
}

void VGA_HorizontalSync(VGA* pVga) {
    setOutputGPIO(pVga->hsyncIO, pVga->hsyncPin, LOW);
    delay(3);
    setOutputGPIO(pVga->hsyncIO, pVga->hsyncPin, HIGH);
    delay(2);
}

void VGA_HorizontalDisplay(VGA* pVga, uint8 color3) {
    for(int i = 0; i < 640; i++) {
        setOutputGPIO(pVga->redIO, pVga->redPin, (color3 & 0x4));
        setOutputGPIO(pVga->greenIO, pVga->greenPin, (color3 & 0x2));
        setOutputGPIO(pVga->blueIO, pVga->bluePin, (color3 & 0x1));
    }

    setOutputGPIO(pVga->redIO, pVga->redPin, 0);
    setOutputGPIO(pVga->greenIO, pVga->greenPin, 0);
    setOutputGPIO(pVga->blueIO, pVga->bluePin, 0);

    delay(1);
}

void VGA_VertialSync(VGA* pVga) {
    setOutputGPIO(pVga->vsyncIO, pVga->vsyncPin, LOW);
    delay(6);
    setOutputGPIO(pVga->vsyncIO, pVga->vsyncPin, HIGH);
    delay(1000);
}

void VGA_VerticalDisplay(VGA* pVga, uint8 color3) {
    VGA_VertialSync(pVga);

    for(int i = 0; i < 480; i++) {
        VGA_HorizontalSync(pVga);
        VGA_HorizontalDisplay(pVga, color3);
    }

    delay(300);
}

#endif