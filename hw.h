/**
@file hw.h
@brief Definitions hardware config
@author Joe Brown
*/
#ifndef HW_H
#define HW_H
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//            __  __                  __
//           / / / /____ _ _____ ____/ /_      __ ____ _ _____ ___
//          / /_/ // __ `// ___// __  /| | /| / // __ `// ___// _ \
//         / __  // /_/ // /   / /_/ / | |/ |/ // /_/ // /   /  __/
//        /_/ /_/ \__,_//_/    \__,_/  |__/|__/ \__,_//_/    \___/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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
#define LED1_OFF()          IO_SET(LED1,GPIO_LOW)
#define LED1_ON()           IO_SET(LED1,GPIO_HIGH)
#define LED1_TOGGLE()       IO_SET(LED1,GPIO_TOGGLE)

#define LED2_PORT           1
#define LED2_PIN            6
#define LED2_OFF()          IO_SET(LED2,GPIO_LOW)
#define LED2_ON()           IO_SET(LED2,GPIO_HIGH)
#define LED2_TOGGLE()       IO_SET(LED2,GPIO_TOGGLE)

// PWM
#define NUM_PWM_CHANNELS    2

#define PWM0_PORT           1
#define PWM0_PIN            6

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

// OLED
#define OLED_RES_PORT       2
#define OLED_RES_PIN        1
#define OLED_RUN()          IO_SET(OLED_RES,GPIO_HIGH)
#define OLED_STOP()         IO_SET(OLED_RES,GPIO_LOW)

#define OLED_DC_PORT        2
#define OLED_DC_PIN         2
#define OLED_COMMAND_MODE() IO_SET(OLED_DC,GPIO_LOW)
#define OLED_DATA_MODE()    IO_SET(OLED_DC,GPIO_HIGH)

#define OLED_CS_PORT        2
#define OLED_CS_PIN         0
#define OLED_SELECT()       IO_SET(OLED_CS,GPIO_LOW)
#define OLED_DESELECT()     IO_SET(OLED_CS,GPIO_HIGH)

#define OLED_DO_PORT        1
#define OLED_DO_PIN         7

#define OLED_CLK_PORT       1
#define OLED_CLK_PIN        5

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
#define LED1_OFF()          IO_SET(LED1,GPIO_LOW)
#define LED1_ON()           IO_SET(LED1,GPIO_HIGH)
#define LED1_TOGGLE()       IO_SET(LED1,GPIO_TOGGLE)

#define LED2_PORT           J
#define LED2_PIN            1
#define LED2_OFF()          IO_SET(LED2,GPIO_LOW)
#define LED2_ON()           IO_SET(LED2,GPIO_HIGH)
#define LED2_TOGGLE()       IO_SET(LED2,GPIO_TOGGLE)

#define LED3_PORT           J
#define LED3_PIN            2
#define LED3_OFF()          IO_SET(LED3,GPIO_LOW)
#define LED3_ON()           IO_SET(LED3,GPIO_HIGH)
#define LED3_TOGGLE()       IO_SET(LED3,GPIO_TOGGLE)

#define LED4_PORT           J
#define LED4_PIN            3
#define LED4_OFF()          IO_SET(LED4,GPIO_LOW)
#define LED4_ON()           IO_SET(LED4,GPIO_HIGH)
#define LED4_TOGGLE()       IO_SET(LED4,GPIO_TOGGLE)

#define LED5_PORT           3
#define LED5_PIN            4
#define LED5_OFF()          IO_SET(LED5,GPIO_LOW)
#define LED5_ON()           IO_SET(LED5,GPIO_HIGH)
#define LED5_TOGGLE()       IO_SET(LED5,GPIO_TOGGLE)

#define LED6_PORT           3
#define LED6_PIN            5
#define LED6_OFF()          IO_SET(LED6,GPIO_LOW)
#define LED6_ON()           IO_SET(LED6,GPIO_HIGH)
#define LED6_TOGGLE()       IO_SET(LED6,GPIO_TOGGLE)

#define LED7_PORT           3
#define LED7_PIN            6
#define LED7_OFF()          IO_SET(LED7,GPIO_LOW)
#define LED7_ON()           IO_SET(LED7,GPIO_HIGH)
#define LED7_TOGGLE()       IO_SET(LED7,GPIO_TOGGLE)

#define LED8_PORT           3
#define LED8_PIN            7
#define LED8_OFF()          IO_SET(LED8,GPIO_LOW)
#define LED8_ON()           IO_SET(LED8,GPIO_HIGH)
#define LED8_TOGGLE()       IO_SET(LED8,GPIO_TOGGLE)

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
