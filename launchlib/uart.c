/**
@file uart.c
@brief Blocking and non-blocking UART interface
@author Joe Brown
*/
#include "global.h"
#include "uart.h"

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                            __                        __
//                           / /   ____   _____ ____ _ / /
//                          / /   / __ \ / ___// __ `// /
//                         / /___/ /_/ // /__ / /_/ // /
//                        /_____/\____/ \___/ \__,_//_/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#ifdef __MSP430G2553__
    #define UART_INT_ENABLE     IE2
    #define UART_INT_FLAG       IFG2
    #define UART_RX_INT_VECTOR  USCIAB0RX_VECTOR
    #define UART_TX_INT_VECTOR  USCIAB0TX_VECTOR
    #define UCBRS_OFFSET        1
    #define USBRF_OFFSET        4
    #define UART_TX_INT         UCA0TXIE
    #define UART_RX_INT         UCA0RXIE
    #define UCRXIFG             UCA0RXIFG
    #define UCTXIFG             UCA0TXIFG
#elif __MSP430FR5739__
    /** @todo 5739 has USCIA0 and A1, it would be nice to target both */
    #define UART_INT_VECTOR     USCI_A0_VECTOR
    #define UART_INT_ENABLE     UCA0IE
    #define UART_INT_FLAG       UCA0IFG
    #define UCA0MCTL            UCA0MCTLW
    #define UART_TX_INT         UCTXIE
    #define UART_RX_INT         UCRXIE
    #define UCBRS_OFFSET        4
    #define USBRF_OFFSET        8
#endif

/** @brief Lookup table for uart config parameters */
typedef struct
{
    uint32_t baud;
    uint32_t clock;
    uint8_t  ucbr;
    uint8_t  ucbrs;
    uint8_t  ucbrf;
} BaudRateConfig;

#ifdef MAX_UART_RX_BUF_CNT
/**
@brief Enqueue data into the rx buffer
@details
Take data from the hardware rx buffer and enqueue it in a circular buffer for
retrieval.
@param[in] data data to enqueue
@return 0 for success -1 for failure
*/
static int8_t RxBufferEnqueue(uint8_t data);

/**
@brief Remove data from the rx buffer and place it into the provided address
@details
Dequeue data from the rx buffer and then adjust the start/size values.
@return single byte from the rx buffer
*/
static uint8_t RxBufferDequeue(void);

/**
@brief Interrupt routine to enqueue received data
*/
static __interrupt void UartRxInt(void);
#endif // MAX_UART_RX_BUF_CNT

#ifdef MAX_UART_TX_BUF_CNT
/**
@brief Enqueue data into the tx buffer
@details
Enqueue data in a circular buffer for eventual transmit
@param[in] data data to enqueue
@return 0 for success -1 for failure
*/
static int8_t TxBufferEnqueue(uint8_t data);

/**
@brief Remove data from the tx buffer for transmit
@details
Remove single bytes from the tx buffer and return them for transmit.
@return data to be transmitted
*/
static uint8_t TxBufferDequeue(void);

/**
@brief Interrupt routine indicating transmit is complete and we can dequeue
more data.
*/
static __interrupt void UartTxInt(void);
#endif // MAX_UART_TX_BUF_CNT

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                            ____        _  __
//                           /  _/____   (_)/ /_
//                           / / / __ \ / // __/
//                         _/ / / / / // // /_
//                        /___//_/ /_//_/ \__/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
@brief baud rate lookup table
@details There are equations in the user guide(15.3.x) that explain how to
calculate these values but after calculating a few I noticed that table 15-5 had
some slight variations compared to the calculated values. I decided to hard-code
the table instead of calculating each value. The benefit to this method is that
 - It gives you an easy place to find the values when debugging
 - If you've settled on a specific baud rate you can easily find and hard-code
     the values (which is what I usually end up doing when a project matures).
*/
static const BaudRateConfig rate_table[] =
{
#ifdef __MSP430G2553__
    // see userguide table 15-5
    {  9600,  1000000,   6,    0,  8},
    { 19200,  1000000,   3,    0,  4},
    { 57600,  1000000,   1,    7,  0},
    {  9600,  8000000,  52,    0,  1},
    { 19200,  8000000,  26,    0,  1},
    { 38400,  8000000,  13,    0,  0},
    { 57600,  8000000,   8,    0, 11},
    {115200,  8000000,   4,    5,  3},
    {  9600, 12000000,  78,    0,  2},
    { 19200, 12000000,  39,    0,  1},
    { 38400, 12000000,  19,    0,  8},
    { 57600, 12000000,  13,    0,  0},
    {115200, 12000000,   6,    0,  8},
    {  9600, 16000000, 104,    0,  3},
    { 19200, 16000000,  52,    0,  1},
    { 38400, 16000000,  26,    0,  1},
    { 57600, 16000000,  17,    0,  6},
    {115200, 16000000,   8,    0, 11}
#elif __MSP430FR5739__
    // see userguide table 18-5
    {  9600,  8000000,  52, 0x49,  1},
    { 19200,  8000000,  26, 0xB6,  0},
    { 38400,  8000000,  13, 0x84,  0},
    { 57600,  8000000,   8, 0xF7, 10},
    {115200,  8000000,   4, 0x55,  5},
    {  9600, 16000000, 104, 0xD6,  2},
    { 19200, 16000000,  52, 0x49,  1},
    { 38400, 16000000,  26, 0xB6,  0},
    { 57600, 16000000,  17, 0xDD,  5},
    {115200, 16000000,   8, 0xF7, 10},
    {  9600, 20000000, 104, 0x25,  3},
    { 19200, 20000000,  52, 0xD6,  1},
    { 38400, 20000000,  26, 0xEE,  8},
    { 57600, 20000000,  17, 0x22, 11},
    {115200, 20000000,   8, 0xAD, 13},
    {  9600, 24000000, 156, 0x00,  4},
    { 19200, 24000000,  78, 0x00,  2},
    { 38400, 24000000,  39, 0x00,  1},
    { 57600, 24000000,  26, 0xD6,  0},
    {115200, 24000000,  13, 0x49,  0}
#endif
};

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void UartInit(uint32_t baud_rate)
{
    uint8_t i = 0;
    uint8_t index = 0;
    // find where the baud rate is in the table
    for(i = 0;i < sizeof(rate_table) / sizeof(BaudRateConfig);i++)
    {
        if (baud_rate == rate_table[i].baud &&
            g_clock_speed == rate_table[i].clock)
        {
            index = i;
            break;
        }
    }

    // SMCLK sources uart
    UCA0CTL1 |= UCSSEL_2;
    // set the divisor
    UCA0BR0 = rate_table[index].ucbr;
    // we always use modulation and never go below 9600 baud which means BR will
    // always be < 256
    UCA0BR1 = 0;
    // UCBRS is at bits 1-3
    UCA0MCTL = rate_table[index].ucbrs << UCBRS_OFFSET;
    // UCBRF is at bits 4-7
    UCA0MCTL |= rate_table[index].ucbrf << USBRF_OFFSET;
    // set UCOS16 to enable oversampling
    UCA0MCTL |= UCOS16;

    // Initialize USCI state machine
    UCA0CTL1 &= ~UCSWRST;
    // Enable USCI_A0 RX and TX interrupts
#ifdef MAX_UART_TX_BUF_CNT
    UART_INT_ENABLE |= UART_TX_INT;
#endif
#ifdef MAX_UART_RX_BUF_CNT
    UART_INT_ENABLE |= UART_RX_INT;
#endif
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                ____                     _
//               / __ \ ___   _____ ___   (_)_   __ ___
//              / /_/ // _ \ / ___// _ \ / /| | / // _ \
//             / _, _//  __// /__ /  __// / | |/ //  __/
//            /_/ |_| \___/ \___/ \___//_/  |___/ \___/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef MAX_UART_RX_BUF_CNT
/** @brief start index for rx queue */
static uint16_t rx_start = 0;
/** @brief size of rx queue */
static uint16_t rx_size  = 0;
/** @brief rx buffer */
static uint8_t rx_buf[MAX_UART_RX_BUF_CNT];

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int8_t RxBufferEnqueue(uint8_t data)
{
    // is the buffer full?
    if (rx_size == MAX_UART_RX_BUF_CNT)
    {
        goto error;
    }

    // stuff the data
    if((rx_start + rx_size) >= MAX_UART_RX_BUF_CNT)
    {
        rx_buf[(rx_start + rx_size) - MAX_UART_RX_BUF_CNT] = data;
    }
    else
    {
        rx_buf[(rx_start + rx_size)] = data;
    }

    // adjust the buf size
    rx_size++;

    return (SUCCESS);
error:
    return (FAILURE);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
uint8_t RxBufferDequeue(void)
{
    _DINT();
    uint8_t ret = 0;
    // is the buffer empty?
    if (rx_size)
    {
        // return data
        ret = rx_buf[rx_start];
        // adjust the start
        rx_start = (rx_start == (MAX_UART_RX_BUF_CNT - 1)) ? 0 : rx_start + 1;
        // adjust the size
        rx_size--;
    }
    _EINT();
    return ret;
}
#endif // MAX_UART_RX_BUF_CNT

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//             ______                                      _  __
//            /_  __/_____ ____ _ ____   _____ ____ ___   (_)/ /_
//             / /  / ___// __ `// __ \ / ___// __ `__ \ / // __/
//            / /  / /   / /_/ // / / /(__  )/ / / / / // // /_
//           /_/  /_/    \__,_//_/ /_//____//_/ /_/ /_//_/ \__/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef MAX_UART_TX_BUF_CNT
/** @brief start index for tx queue */
static uint16_t tx_start = 0;
/** @brief size of tx queue */
static uint16_t tx_size  = 0;
/** @brief tx buffer */
static uint8_t tx_buf[MAX_UART_TX_BUF_CNT];

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int8_t TxBufferEnqueue(uint8_t data)
{
    _DINT();
    // is the buffer full?
    if (tx_size == MAX_UART_TX_BUF_CNT)
    {
        goto error;
    }

    // make sure the interrupt is enabled if we have data
    UART_INT_ENABLE |= UART_TX_INT;

    // stuff the data
    // although we only dequeue and queue single bytes at a time (because that's
    // all the hardware supports) we still need to deal with multi-byte boundary
    // crossing as we may be filling the queue faster than the tx interrupt can
    // pull it out.
    if ((tx_start + tx_size) >= MAX_UART_TX_BUF_CNT)
    {
        tx_buf[(tx_start + tx_size) - MAX_UART_TX_BUF_CNT] = data;
    }
    else
    {
        tx_buf[(tx_start + tx_size)] = data;
    }

    // adjust the buf size
    tx_size++;

    _EINT();
    return (SUCCESS);
error:
    _EINT();
    return (FAILURE);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
uint8_t TxBufferDequeue(void)
{
    uint8_t ret = 0;
    // is the buffer empty?
    if (tx_size)
    {
        // return data
        ret = tx_buf[tx_start];
        // adjust the start
        tx_start = (tx_start == (MAX_UART_TX_BUF_CNT - 1)) ? 0 : tx_start + 1;
        // adjust the size
        tx_size--;
    }
    else
    {
        // if we've emptied the buffer disable the interrupt
        UART_INT_ENABLE &= ~UART_TX_INT;
    }
    return ret;
}
#endif // MAX_UART_TX_BUF_CNT

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//        ____        __                                   __
//       /  _/____   / /_ ___   _____ _____ __  __ ____   / /_ _____
//       / / / __ \ / __// _ \ / ___// ___// / / // __ \ / __// ___/
//     _/ / / / / // /_ /  __// /   / /   / /_/ // /_/ // /_ (__  )
//    /___//_/ /_/ \__/ \___//_/   /_/    \__,_// .___/ \__//____/
//                                             /_/
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef __MSP430G2553__
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef MAX_UART_RX_BUF_CNT
#pragma vector=UART_RX_INT_VECTOR
__interrupt void UartRxInt(void)
{
    RxBufferEnqueue(UCA0RXBUF);
}
#endif // MAX_UART_RX_BUF_CNT

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef MAX_UART_TX_BUF_CNT
#pragma vector = UART_TX_INT_VECTOR
__interrupt void UartTxInt(void)
{
    UCA0TXBUF = TxBufferDequeue();
}
#endif // MAX_UART_TX_BUF_CNT
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#elif __MSP430FR5739__
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#if defined MAX_UART_RX_BUF_CNT || defined MAX_UART_TX_BUF_CNT
#pragma vector=UART_INT_VECTOR
__interrupt void UartInt(void)
{
    switch(__even_in_range(UCA0IV,0x08))
    {
        case 0: // no interrupt
            break;
        case 2: // RXIFG
#ifdef MAX_UART_RX_BUF_CNT
            RxBufferEnqueue(UCA0RXBUF);
#endif
            break;
        case 4: // TXIFG
#ifdef MAX_UART_TX_BUF_CNT
            UCA0TXBUF = TxBufferDequeue();
#endif
            break;
        default:
            break;
    }
}
#endif // defined MAX_UART_RX_BUF_CNT || defined MAX_UART_TX_BUF_CNT

#endif // __MSP430FR5739__

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//            ____        __               ____
//           /  _/____   / /_ ___   _____ / __/____ _ _____ ___
//           / / / __ \ / __// _ \ / ___// /_ / __ `// ___// _ \
//         _/ / / / / // /_ /  __// /   / __// /_/ // /__ /  __/
//        /___//_/ /_/ \__/ \___//_/   /_/   \__,_/ \___/ \___/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
uint8_t UartGetC(void)
{
#ifdef MAX_UART_RX_BUF_CNT
    return RxBufferDequeue();
#else
    while (!(UART_INT_FLAG & UCRXIFG));    // RX a byte?
    return UCA0RXBUF;
#endif
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
uint8_t UartPutC(uint8_t data)
{
#ifdef MAX_UART_TX_BUF_CNT
    TxBufferEnqueue(data);
#else
    while (!(UART_INT_FLAG & UCTXIFG));    // TX buffer ready?
    UCA0TXBUF = data;
#endif
    return data;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#ifdef MAX_UART_RX_BUF_CNT
uint8_t UartBufEmpty(void)
{
    return !(rx_size);
}
#endif

#ifndef TEST
// Use small printf formatter in IAR
int putchar(int c)
{
    return UartPutC(c);
}

int getchar(void)
{
    return UartGetC();
}
#endif