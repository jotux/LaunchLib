#ifndef HARDWARE_H
#define HARDWARE_H

// clock settings
#define CLOCK_DCO   16000000   // DCO freq
#define CLOCK_EXT   32768      // ext clock freq

// based on 0.5 millisecond timer period
#define _millisecond   2
#define _second        2000
#define _minute        120000
#define _hour          7200000

#define RED_LED_PORT  1
#define RED_LED_PIN   0
#define RED_LED_OFF()    IO_SET(RED_LED,LOW);
#define RED_LED_ON()     IO_SET(RED_LED,HIGH);
#define RED_LED_TOGGLE() IO_SET(RED_LED,TOGGLE);

#define GREEN_LED_PORT 1
#define GREEN_LED_PIN  6
#define GREEN_LED_OFF()    IO_SET(GREEN_LED,LOW);
#define GREEN_LED_ON()     IO_SET(GREEN_LED,HIGH);
#define GREEN_LED_TOGGLE() IO_SET(GREEN_LED,TOGGLE);

// PWM
#ifdef __MSP430G2553__
#define NUM_PWM_CHANNELS 2
#else
#define NUM_PWM_CHANNELS 1
#endif

#define PWM_0_PORT 1
#define PWM_0_PIN  2

#define PWM_1_PORT 2
#define PWM_1_PIN  1

#define SW1_PORT   1
#define SW1_PIN    3

// interrupt config
#define NUM_P1_INTS 8
#ifdef __MSP430G2553__
#define NUM_P2_INTS 6
#endif

#endif
