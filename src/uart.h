#ifndef UART_H
#define UART_H

#define UCBRS_OFFSET 1
#define USBRF_OFFSET 4

enum NUMBER_BASE {DECIMAL, HEX};

typedef struct
{
    uint32_t baud;
    uint32_t clock;
    uint8_t  ucbr;
    uint8_t  ucbrs;
    uint8_t  ucbrf;
} BaudRateConfig;

extern void UartInit(uint32_t baud_rate);

// to disable uart receive (like for simple uart debugging) set
// MAX_UART_RX_BUF_CNT to 0
static int8_t    UartRxBufferEnqueue(uint8_t data);
extern uint8_t   UartRxBufferDequeue(uint8_t *in, uint16_t len);
extern uint8_t   get_uart_rx_buf_size(void);
__interrupt void UartRxInt(void);
extern uint8_t   UartGetC(void);

// to disable uart transmit set MAX_UART_TX_BUF_CNT to 0
static int8_t    UartTxBufferEnqueue(uint8_t data);
static uint8_t   UartTxBufferDequeue(void);
__interrupt void UartTxInt(void);

static void UartPutC(uint8_t data);
static void UartPutS(uint8_t *s);
static void UartPutAToI(uint32_t value, enum NUMBER_BASE base);
extern void UartPrintf(uint8_t *format, ...);



#endif //PWM_H
