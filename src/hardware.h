#ifndef HARDWARE_H
#define HARDWARE_H

// clock settings
#define CLOCK_DCO           16000000    // DCO freq
#define CLOCK_EXT           32768       // ext clock freq

// Schedular timing settings
#define MAX_CALLBACK_CNT    3
#define MAX_CALLOUT_CNT     6

// based on 0.5 millisecond timer period
#define _millisecond        2
#define _second             2000
#define _minute             120000
#define _hour               7200000

// State machine settings
#define MAX_EVENT_NUM       10

// On board hardware
#define SW1_PORT            1
#define SW1_PIN             3

#define RED_LED_PORT        1
#define RED_LED_PIN         0
#define RED_LED_OFF()       IO_SET(RED_LED,LOW);
#define RED_LED_ON()        IO_SET(RED_LED,HIGH);
#define RED_LED_TOGGLE()    IO_SET(RED_LED,TOGGLE);

#define GREEN_LED_PORT      1
#define GREEN_LED_PIN       6
#define GREEN_LED_OFF()     IO_SET(GREEN_LED,LOW);
#define GREEN_LED_ON()      IO_SET(GREEN_LED,HIGH);
#define GREEN_LED_TOGGLE()  IO_SET(GREEN_LED,TOGGLE);

// PWM
#ifdef __MSP430G2553__
#define NUM_PWM_CHANNELS    2
#else
#define NUM_PWM_CHANNELS    1
#endif

#define PWM_0_PORT          1
#define PWM_0_PIN           2

#define PWM_1_PORT          2
#define PWM_1_PIN           1

// interrupt config
#define NUM_P1_INTS         8
#ifdef __MSP430G2553__
#define NUM_P2_INTS         6
#endif

// I2C
#define I2C_ADDRESS         0x0F
#define I2C_CLOCK_RATE      400000
#define I2C_CLOCK_DIV       (CLOCK_DCO / I2C_CLOCK_RATE)

#define I2C_DAT_PORT        1
#define I2C_DAT_PIN         7

#define I2C_CLK_PORT        1
#define I2C_CLK_PIN         6

// UART
// When using non-blocking uart keep in mind the buffer can be filled very
// quickly and cause problems. If you want to push a lot of data over the asynch
// interface you'll need to either queue packets in software, make the
// tx_buf_cnt very large, or put delays between messages to allow the buffer to
// be emptied.
//#define NON_BLOCKING_UART_TX
//#define NON_BLOCKING_UART_RX
#define MAX_UART_RX_BUF_CNT 20
#define MAX_UART_TX_BUF_CNT 20

#define UART_TX_PORT        1
#define UART_TX_PIN         1

#define UART_RX_PORT        1
#define UART_RX_PIN         2

#endif
