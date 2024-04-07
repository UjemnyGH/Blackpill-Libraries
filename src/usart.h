#ifndef __USART_
#define __USART_

#include "registers.h"

struct USART {
    io32 state;
    io32 data;
    io32 baudRate;
    io32 control1;
    io32 control2;
    io32 control3;
    io32 guardTimeAndPrescaler;
};

#define USART_STATUS_CTS                    0x200
#define USART_STATUS_LIN_BREAK_DETECTION    0x100
#define USART_STATUS_TX_REGISTER_EMPTY      0x80
#define USART_STATUS_TRANSMIT_COMPLETE      0x40
#define USART_STATUS_RX_REGISTER_NOT_EMPTY  0x20
#define USART_STATUS_IDLE                   0x10
#define USART_STATUS_OVERRUN_ERROR          0x8
#define USART_STATUS_NOISE_DETECTED         0x4
#define USART_STATUS_FLAMING_ERROR          0x2
#define USART_STATUS_PARITY_ERROR           0x1

#define USART_BAUD_RATE_4800                0x5161
#define USART_BAUD_RATE_9600                0x28b0
#define USART_BAUD_RATE_19200               0x1458
#define USART_BAUD_RATE_38400               0xa2c
#define USART_BAUD_RATE_57600               0x6c8
#define USART_BAUD_RATE_112500              0x378
#define USART_BAUD_RATE_230400              0x1b2
#define USART_BAUD_RATE_460800              0xd9
#define USART_BAUD_RATE_921600              0x6c

// TODO: 

#endif