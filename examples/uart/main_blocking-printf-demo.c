#include "launchlib/global.h"
#include "launchlib/hardware.h"
#include "launchlib/delay.h"
#include "launchlib/uart.h"
#include "launchlib/clock.h"

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
    
    UartPrintf("\n\nThis is %s\n",        "a string");
    UartPrintf("Hex number(16): 0x%x\n",  60000);
    UartPrintf("Hex number(32): 0x%x\n",  100000);
    UartPrintf("Char: %c\n",              'x');
    UartPrintf("Unsigned short: %u\n",    100);
    UartPrintf("Signed short: %i\n",     -100);
    UartPrintf("Unsigned long: %lu\n",    250000);
    UartPrintf("Signed long: %li\n",     -250000);
    LPM0;
}
