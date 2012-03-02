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
    UartPrintf("\n\nThis is %s\n",        "a string");
    UartPrintf("Hex number(16): 0x%x\n",  60000);
    UartPrintf("Hex number(32): 0x%x\n",  100000);
    UartPrintf("Char: %c\n",              'x');
    UartPrintf("Unsigned short: %u\n",    100);
    UartPrintf("Signed short: %i\n",     -100);
    UartPrintf("Unsigned long: %n\n",     250000);
    UartPrintf("Signed long: %l\n",      -250000);


    UartPrintf("\n\nEnter your name: ");
    static uint8_t buf[30];
    uint8_t* cur_char = &buf[0];
    while(1)
    {
        // poll the rx buffer for new data
        if (get_uart_rx_buf_size())
        {
            // pull the data out one byte at a time
            UartRxBufferDequeue(cur_char++,1);
            // was the last character a carriage return?
            if (*(cur_char - 1) == '\r')
            {
                UartPrintf("\nHello %s",buf);
            }
        }
    }

}
