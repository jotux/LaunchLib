#include "src/global.h"
#include "src/hardware.h"
#include "src/delay.h"
#include "src/uart.h"

void HardwareInit(void)
{
    IO_FUNCTION(UART_TX,SPECIAL);
    IO_FUNCTION(UART_RX,SPECIAL);
    IO_AUX_FUNCTION(UART_TX,SPECIAL);
    IO_AUX_FUNCTION(UART_RX,SPECIAL);
}

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
    HardwareInit();
    // init uart at 115k
    UartInit(115200);

    _EINT();
    // Make sure NON_BLOCKING_UART_RX is commented out in hardware.h
    UartPrintf("\n\nEnter your name: ");
    static uint8_t buf[20];
    uint8_t* cur_char = &buf[0];
    while(1)
    {
        // The code will stop here and wait for a character to be received
        while((*cur_char++ = UartGetC()) == '\r')
        {
            UartPrintf("\nHello %s",buf);
        }
    }

}
