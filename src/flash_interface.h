#ifndef __FLASH_INTERFACE_
#define __FLASH_INTERFACE_

#include "registers.h"

struct FlashInterface {
    io32 accessControl;
    io32 key;
    io32 optionKey;
    io32 status;
    io32 control;
    io32 optionControl;
};

#define FlashInterface ((struct FlashInterface *)FLASH_INTERFACE_BASE)

#endif