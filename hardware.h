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

// hardware config
#define RED_LED_PORT  1
#define RED_LED_PIN   0
#define RED_LED_OFF()    SET_LOW(RED_LED);
#define RED_LED_ON()     SET_HIGH(RED_LED);
#define RED_LED_TOGGLE() TOGGLE(RED_LED);

#define PWM_0_PORT 1
#define PWM_0_PIN  2

#define PWM_1_PORT 2
#define PWM_1_PIN  1

#endif
