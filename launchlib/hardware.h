/**
@file hardware.h
@brief Definitions hardware config (ports, pins, and module settings)
@author Joe Brown
*/
#ifndef HARDWARE_H
#define HARDWARE_H
//http://patorjk.com/software/taag/
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//               _____        __   __   _
//              / ___/ ___   / /_ / /_ (_)____   ____ _ _____
//              \__ \ / _ \ / __// __// // __ \ / __ `// ___/
//             ___/ //  __// /_ / /_ / // / / // /_/ /(__  )
//            /____/ \___/ \__/ \__//_//_/ /_/ \__, //____/
//                                            /____/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//           _____        __               __        __
//          / ___/ _____ / /_   ___   ____/ /__  __ / /___   _____
//          \__ \ / ___// __ \ / _ \ / __  // / / // // _ \ / ___/
//         ___/ // /__ / / / //  __// /_/ // /_/ // //  __// /
//        /____/ \___//_/ /_/ \___/ \__,_/ \__,_//_/ \___//_/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//#define DO_NOT_ADJUST_SCHEDULER_ON_CLOCK_CONFIG
#define MAX_CALLBACK_CNT    3
#define MAX_CALLOUT_CNT     6

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//    _____  __          __           __  ___              __     _
//   / ___/ / /_ ____ _ / /_ ___     /  |/  /____ _ _____ / /_   (_)____   ___
//   \__ \ / __// __ `// __// _ \   / /|_/ // __ `// ___// __ \ / // __ \ / _ \
//  ___/ // /_ / /_/ // /_ /  __/  / /  / // /_/ // /__ / / / // // / / //  __/
// /____/ \__/ \__,_/ \__/ \___/  /_/  /_/ \__,_/ \___//_/ /_//_//_/ /_/ \___/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define MAX_EVENT_CNT       10

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                       __  __ ___     ____  ______
//                      / / / //   |   / __ \/_  __/
//                     / / / // /| |  / /_/ / / /
//                    / /_/ // ___ | / _, _/ / /
//                    \____//_/  |_|/_/ |_| /_/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// When using non-blocking uart keep in mind the buffer can be filled very
// quickly and cause problems. If you want to push a lot of data over the asynch
// interface you'll need to either queue packets in software, make the
// tx_buf_cnt very large, or put delays between messages to allow the buffer to
// be emptied.
//#define NON_BLOCKING_UART_TX
//#define NON_BLOCKING_UART_RX
#define MAX_UART_RX_BUF_CNT 20
#define MAX_UART_TX_BUF_CNT 200

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//            __  __                  __
//           / / / /____ _ _____ ____/ /_      __ ____ _ _____ ___
//          / /_/ // __ `// ___// __  /| | /| / // __ `// ___// _ \
//         / __  // /_/ // /   / /_/ / | |/ |/ // /_/ // /   /  __/
//        /_/ /_/ \__,_//_/    \__,_/  |__/|__/ \__,_//_/    \___/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

#define LED_OFF(L)          LED##L##_OFF();
#define LED_ON(L)           LED##L##_ON();
#define LED_TOGGLE(L)       IO_SET(LED##L,TOGGLE);

#ifdef __MSP430G2553__
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                   ______ ___    ______ ______ _____
//                  / ____/|__ \  / ____// ____/|__  /
//                 / / __  __/ / /___ \ /___ \   /_ <
//                / /_/ / / __/ ____/ /____/ / ___/ /
//                \____/ /____//_____//_____/ /____/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define SW1_PORT            1
#define SW1_PIN             3

#define LED1_PORT           1
#define LED1_PIN            0
#define LED1_OFF()          IO_SET(LED1,LOW);
#define LED1_ON()           IO_SET(LED1,HIGH);

#define LED2_PORT           1
#define LED2_PIN            6
#define LED2_OFF()          IO_SET(LED2,LOW);
#define LED2_ON()           IO_SET(LED2,HIGH);

// PWM
#define NUM_PWM_CHANNELS    2

#define PWM0_PORT           1
#define PWM0_PIN            2

#define PWM1_PORT           2
#define PWM1_PIN            1

// interrupt config
#define NUM_P1_INTS         8
#define NUM_P2_INTS         6

// I2C
#define I2C_ADDRESS         0x0F

#define I2C_DAT_PORT        1
#define I2C_DAT_PIN         7

#define I2C_CLK_PORT        1
#define I2C_CLK_PIN         6

// UART hardware
#define UART_TX_PORT        1
#define UART_TX_PIN         1

#define UART_RX_PORT        1
#define UART_RX_PIN         2

#elif __MSP430FR5739__
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                  ______ ____   ______ _____ _____ ____
//                 / ____// __ \ / ____//__  /|__  // __ \
//                / /_   / /_/ //___ \    / /  /_ </ /_/ /
//               / __/  / _, _/____/ /   / / ___/ /\__, /
//              /_/    /_/ |_|/_____/   /_/ /____//____/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define SW1_PORT            4
#define SW1_PIN             0

#define SW2_PORT            4
#define SW2_PIN             1

#define LED1_PORT           J
#define LED1_PIN            0
#define LED1_OFF()          IO_SET(LED1,LOW);
#define LED1_ON()           IO_SET(LED1,HIGH);

#define LED2_PORT           J
#define LED2_PIN            1
#define LED2_OFF()          IO_SET(LED2,LOW);
#define LED2_ON()           IO_SET(LED2,HIGH);

#define LED3_PORT           J
#define LED3_PIN            2
#define LED3_OFF()          IO_SET(LED3,LOW);
#define LED3_ON()           IO_SET(LED3,HIGH);

#define LED4_PORT           J
#define LED4_PIN            3
#define LED4_OFF()          IO_SET(LED4,LOW);
#define LED4_ON()           IO_SET(LED4,HIGH);

#define LED5_PORT           3
#define LED5_PIN            4
#define LED5_OFF()          IO_SET(LED5,LOW);
#define LED5_ON()           IO_SET(LED5,HIGH);

#define LED6_PORT           3
#define LED6_PIN            5
#define LED6_OFF()          IO_SET(LED6,LOW);
#define LED6_ON()           IO_SET(LED6,HIGH);

#define LED7_PORT           3
#define LED7_PIN            6
#define LED7_OFF()          IO_SET(LED7,LOW);
#define LED7_ON()           IO_SET(LED7,HIGH);

#define LED8_PORT           3
#define LED8_PIN            7
#define LED8_OFF()          IO_SET(LED8,LOW);
#define LED8_ON()           IO_SET(LED8,HIGH);

// PWM
#define NUM_PWM_CHANNELS    2

#define PWM0_PORT           1
#define PWM0_PIN            0

#define PWM1_PORT           1
#define PWM1_PIN            2

// interrupt config
#define NUM_P1_INTS         8
#define NUM_P2_INTS         8
#define NUM_P3_INTS         8
#define NUM_P4_INTS         8

// I2C
#define I2C_ADDRESS         0x0F

#define I2C_DAT_PORT        1
#define I2C_DAT_PIN         7

#define I2C_CLK_PORT        1
#define I2C_CLK_PIN         6

// UART hardware
#define UART_TX_PORT        2
#define UART_TX_PIN         0

#define UART_RX_PORT        2
#define UART_RX_PIN         1
#endif

#endif
