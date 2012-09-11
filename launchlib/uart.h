/**
@file uart.h
@brief Definitions, data structues and prototypes for UART
@author Joe Brown
*/
#ifndef UART_H
#define UART_H

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
@return the data you transmitted
*/
extern uint8_t UartPutC(uint8_t data);

/**
@brief Check to see if rx buffer is empty
@details
Check rx_size to see if any data is pending
@return 1 if empty, 0 if not empty
*/
extern uint8_t UartBufEmpty(void);

#endif // UART_H
