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
