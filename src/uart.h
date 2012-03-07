/** 
@file uart.h
@brief Definitions, data structues and prototypes for UART
@author Joe Brown
*/
#ifndef UART_H
#define UART_H

#define UCBRS_OFFSET 1
#define USBRF_OFFSET 4

enum NUMBER_BASE {DECIMAL, HEX};

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
Dequeue data from the rx buffer and then adjust the start/size values. If the
length makes the copy wrap around the end of the queue we break the copy into
two parts.
@param[out] in pointer to copy data to
@param[in] len length of data to copy
@return length of data copied to the in pointer
*/
static uint8_t RxBufferDequeue(uint8_t *in, uint16_t len);

/**
@brief Interrupt routine to enqueue received data
*/
__interrupt void UartRxInt(void);

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

#endif //UART_H
