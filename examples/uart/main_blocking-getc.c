#include "launchlib.h"

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
#ifdef NON_BLOCKING_UART_RX
    #error "Comment out NON_BLOCKING_UART_RX in hardware.h for this example"
#endif

    WD_STOP();
    ClockConfig(16);
    HardwareInit();
    // init uart at 115k
    UartInit(115200);

    _EINT();
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
