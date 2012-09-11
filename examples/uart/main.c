#include "../../launchlib.h"
#include "../../hw.h"

#define BLOCKING_GETC_EXAMPLE
//#define BLOCKING_PRINTF_EXAMPLE
//#define NON_BLOCKING_GETC_EXAMPLE
//#define NON_BLOCKING_PRINTF_EXAMPLE


void HardwareInit(void)
{
#ifdef __MSP430G2553__
    IO_FUNCTION(UART_TX,GPIO_FUN_SPECIAL);
    IO_FUNCTION(UART_RX,GPIO_FUN_SPECIAL);
#endif
    IO_AUX_FUNCTION(UART_TX,GPIO_FUN_SPECIAL);
    IO_AUX_FUNCTION(UART_RX,GPIO_FUN_SPECIAL);
}

#if defined(BLOCKING_GETC_EXAMPLE)

void main(void)
{
#if defined(MAX_UART_RX_BUF_CNT) || defined(MAX_UART_TX_BUF_CNT)
    #error "Comment out MAX_UART_RX_BUF_CNT and MAX_UART_TX_BUF_CNT in config.h for this example"
#endif

    WD_STOP();
    ClockConfig(16);
    HardwareInit();
    // init uart at 115k
    UartInit(115200);

    _EINT();
    printf("\n\nEnter your name: ");
    static uint8_t buf[20];
    uint8_t* cur_char = &buf[0];
    while(1)
    {
        // The code will stop here and wait for a character to be received
        while((*cur_char++ = getchar()) == '\r')
        {
            printf("\nHello %s",buf);
        }
    }
}

#elif defined(BLOCKING_PRINTF_EXAMPLE)

void main(void)
{
#if defined(MAX_UART_TX_BUF_CNT)
    #error "Comment out MAX_UART_TX_BUF_CNT in config.h for this example"
#endif
    WD_STOP();
    ClockConfig(16);
    HardwareInit();
    // init uart at 115k
    UartInit(115200);

    _EINT();

    printf("\n\nThis is %s\n",        "a string");
    printf("Hex number(16): 0x%x\n",  60);
    printf("Hex number(32): 0x%lx\n", 100000);
    printf("Char: %c\n",              'x');
    printf("Unsigned short: %u\n",    100);
    printf("Signed short: %i\n",     -100);
    printf("Unsigned long: %lu\n",    250000);
    printf("Signed long: %li\n",     -250000);

    LPM0;
}

#elif defined(NON_BLOCKING_GETC_EXAMPLE)

void main(void)
{
#if !defined(MAX_UART_RX_BUF_CNT)
    #error "Define MAX_UART_RX_BUF_CNT > 0 in config.h for this example"
#endif

    WD_STOP();
    ClockConfig(16);
    HardwareInit();
    // init uart at 115k
    UartInit(115200);

    _EINT();

    printf("\n\nEnter your name: ");
    static uint8_t buf[30];
    uint8_t* cur_char = &buf[0];
    while(1)
    {
        // poll the rx buffer for new data
        if (!UartBufEmpty())
        {
            // pull the data out one byte at a time
            *cur_char = getchar();
            // was the last character a carriage return?
            if (*(cur_char - 1) == '\r')
            {
                printf("\nHello %s",buf);
            }
        }
    }
}

#elif defined(NON_BLOCKING_PRINTF_EXAMPLE)

void main(void)
{
#if !defined(MAX_UART_TX_BUF_CNT)
    #error "Define MAX_UART_TX_BUF_CNT > 0 in config.h for this example"
#endif
    WD_STOP();
    ClockConfig(16);
    HardwareInit();
    // init uart at 115k
    UartInit(115200);

    _EINT();

    printf("\n\nThis is %s\n",        "a string");
    printf("Hex number(16): 0x%x\n",  60);
    printf("Hex number(32): 0x%lx\n", 100000);
    printf("Char: %c\n",              'x');
    printf("Unsigned short: %u\n",    100);
    printf("Signed short: %i\n",     -100);
    printf("Unsigned long: %lu\n",    250000);
    printf("Signed long: %li\n",     -250000);
    LPM0;
}

#endif
