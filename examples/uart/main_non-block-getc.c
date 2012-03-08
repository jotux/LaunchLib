#include "src/global.h"
#include "src/hardware.h"
#include "src/delay.h"
#include "src/uart.h"
#include "src/clock.h"

void HardwareInit(void)
{
#ifdef __MSP430G2553__
    IO_FUNCTION(UART_TX,SPECIAL);
    IO_FUNCTION(UART_RX,SPECIAL);
#endif
    IO_AUX_FUNCTION(UART_TX,SPECIAL);
    IO_AUX_FUNCTION(UART_RX,SPECIAL);
}

void main(void)
{
#ifndef NON_BLOCKING_UART_RX
    #error "Define NON_BLOCKING_UART_RX in hardware.h for this example"
#endif

    WD_STOP();
    ClockConfig(16);
    HardwareInit();
    // init uart at 115k
    UartInit(115200);

    _EINT();

    UartPrintf("\n\nEnter your name: ");
    static uint8_t buf[30];
    uint8_t* cur_char = &buf[0];
    while(1)
    {
        // poll the rx buffer for new data
        if (!UartBufEmpty())
        {
            // pull the data out one byte at a time
            UartRead(cur_char++,1);
            // was the last character a carriage return?
            if (*(cur_char - 1) == '\r')
            {
                UartPrintf("\nHello %s",buf);
            }
        }
    }
}
