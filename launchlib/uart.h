/**
@file uart.h
@brief Definitions, data structues and prototypes for UART
@author Joe Brown
*/
#ifndef UART_H
#define UART_H
#include "hardware.h"

#ifdef __MSP430G2553__
    #define UART_INT_ENABLE     IE2
    #define UART_INT_FLAG       IFG2
    #define UART_RX_INT_VECTOR  USCIAB0RX_VECTOR
    #define UART_TX_INT_VECTOR  USCIAB0TX_VECTOR
    #define UCBRS_OFFSET        1
    #define USBRF_OFFSET        4
#elif __MSP430FR5739__
    /** @todo 5739 has USCIA0 and A1, it would be nice to target both */
    #define UART_INT_VECTOR     USCI_A0_VECTOR
    #define UART_INT_ENABLE     UCA0IE
    #define UART_INT_FLAG       UCA0IFG
    #define UCA0RXIFG           UCRXIFG
    #define UCA0TXIFG           UCTXIFG
    #define UCA0MCTL            UCA0MCTLW
    #define UCA0TXIE            UCTXIE
    #define UCA0RXIE            UCRXIE
    #define UCBRS_OFFSET        4
    #define USBRF_OFFSET        8
#endif

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
enum RX_TX {RX = 0, TX = 1};
#if defined(NON_BLOCKING_UART_RX) && defined(NON_BLOCKING_UART_RX)
    #define BUF_START(loc) ((loc) == RX ? &rx_start : &tx_start)
    #define BUF_SIZE(loc)  ((loc) == RX ? &rx_size : &tx_size)
    #define BUF_LOC(loc)   ((loc) == RX ? &rx_buf[0] : &tx_buf[0])
    #define MAX_SIZE(loc)  ((loc) == RX ? MAX_UART_RX_BUF_CNT : MAX_UART_TX_BUF_CNT)
#elif defined(NON_BLOCKING_UART_RX)
    #define BUF_START(loc) (&rx_start)
    #define BUF_SIZE(loc)  (&rx_size)
    #define BUF_LOC(loc)   (&rx_buf[0])
    #define MAX_SIZE(loc)  (MAX_UART_RX_BUF_CNT)
#elif defined(NON_BLOCKING_UART_TX)
    #define BUF_START(loc) (&tx_start)
    #define BUF_SIZE(loc)  (&tx_size)
    #define BUF_LOC(loc)   (&tx_buf[0])
    #define MAX_SIZE(loc)  (MAX_UART_TX_BUF_CNT)
#endif
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


enum NUMBER_BASE {DECIMAL, HEX};

/** @brief decimal value lookup table */
static const uint32_t decimal_table[] =
{
    1000000000, // +0
     100000000, // +1
      10000000, // +2
       1000000, // +3
        100000, // +4
         10000, // +5
          1000, // +6
           100, // +7
            10, // +8
             1, // +9
             0
};

#define hex(m) char_table[m & 0x0F]

/** @brief character lookup table */
static const uint8_t char_table[] = "0123456789ABCDEF";

/** @brief hex value lookup table */
static const uint32_t hex_table[] =
{
    0x10000000,
    0x01000000,
    0x00100000,
    0x00010000,
    0x00001000,
    0x00000100,
    0x00000010,
    0x00000001,
    0x00000000
};

/** @brief Lookup table for uart config parameters */
typedef struct
{
    uint32_t baud;
    uint32_t clock;
    uint8_t  ucbr;
    uint8_t  ucbrs;
    uint8_t  ucbrf;
} BaudRateConfig;

/**
@brief Enqueue data into the rx or tx circular buffer
@details
Take data and enqueue it in a circular buffer for retrieval.
@param rx[in] RECIEVE to enqueue in recieve buffer, otherwise will be in tx buf
@param[in] data data to enqueue
@return 0 for success -1 for failure
*/
static int8_t DataEnqueue(enum RX_TX rx, uint8_t data);

/**
@brief Remove data from the rx buffer and place it into the provided address
@details
Dequeue data from the rx buffer and then adjust the start/size values. If the
length makes the copy wrap around the end of the queue we break the copy into
two parts.
@param rx[in] RECIEVE to dequeue from recieve buffer, otherwise will be from tx
@param[out] in pointer to copy data to
@param[in] len length of data to copy
@return length of data copied to the in pointer
*/
static uint8_t DataDequeue(enum RX_TX rx, uint8_t *in, uint16_t len);

/**
@brief Interrupt routine to enqueue received data
*/
__interrupt void UartRxInt(void);

/**
@brief Interrupt routine indicating transmit is complete and we can dequeue
more data.
*/
__interrupt void UartTxInt(void);

/**
@brief Convert int to string and transmit
@details
We use two lookup tables (decimal and hex) and search through them character by
character to generate a string to transmit.
@param[in] value integer value to parse and transmit
@param[in] base number base (decimal or hex)
*/
static void UartPutIToA(uint32_t value, enum NUMBER_BASE base);

/**
@brief Initialize Uart hardware
@details
Use the lookup table to get baud rate information then configure the uart
hardware for use. Depending on if blocking/non-blocking is selected different
interrupts will also be configured. If you need more baud rate configurations
you can look them up in the userguide.
@param[in] baud_rate baud rate value (9600,19200,38400,57600,115200)
*/
extern void UartInit(uint32_t baud_rate);

/**
@brief Print string containing arbitrary number of arguments
@details
The format pointer points to a string with format specifiers that represent
arguments passed into the function. Within the function we will parse the format
string, detect format specifiers and eventually pass them to various putc
functions that are configured to our uart hardware.
@param[in] format String of arbirary length containing characters and format
specifiers
@param[in] ... a list of arguments correlating to the format specifiers
*/
extern void UartPrintf(uint8_t *format, ...);

/**
@brief Read data from the rx buffer and place it into the provided address
@details
Dequeue data from the rx buffer and then adjust the start/size values. If the
uart is configured as blocking this function will return 1 byte at a time.
@param[out] in pointer to copy data to
@param[in] len length of data to read
@return length of data copied to the in pointer
*/
extern uint8_t UartRead(uint8_t *in, uint16_t len);

/**
@brief Write data to the Uart for transmit from the provided address
@details
If the uart is configured as non-blocking we will Enqueue data in a circular
buffer for eventual transmit. If we are configured as blocking we will
immediately transmit each character.
@param[out] in pointer to copy data from
@param[in] len length of data to write
*/
extern void UartWrite(uint8_t *in, uint16_t len);

/**
@brief Read a single byte from the uart
@details
If the uart is configured as non-blocking we will try to get one byte from the
rx buffer. If we are configured as blocking we will wait for a character to be
recieved.
@return single data from rx buffer
*/
extern uint8_t UartGetC(void);

/**
@brief Write a single byte to the uart
@details
If the uart is configured as non-blocking we will enqueue one byte to the tx
buffer. If we are configured as blocking we will stuff the data and wait for the
transmit to complete
@param[in] data data to transmit
*/
extern void UartPutC(uint8_t data);

/**
@brief Write a string of bytes to the uart
@details
Performs successive calls to UartGetC until no more data is left
@param[in] s data to transmit
*/
extern void UartPutS(uint8_t *s);

/**
@brief Check to see if rx buffer is empty
@details
Check rx_size to see if any data is pending
@return 1 if empty, 0 if not empty
*/
extern uint8_t UartBufEmpty(void);

#endif // UART_H
