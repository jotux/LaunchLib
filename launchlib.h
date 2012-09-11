/**
@file launchlib.h
@brief Includes all launchlib libraries
@author Joe Brown
*/
#ifndef LAUNCHLIB_H
#define LAUNCHLIB_H

#include "launchlib/global.h"
#include "launchlib/hardware_init.h"
#include "launchlib/adc.h"
#include "launchlib/clock.h"
#include "launchlib/delay.h"
#include "launchlib/interrupt.h"
#include "launchlib/pwm.h"
#include "launchlib/schedule.h"
#include "launchlib/state.h"
#include "launchlib/uart.h"

#if !defined(__MSP430G2553__) && !defined(__MSP430FR5739__)
#error Launchlib is only tested to work with the MSP430G2553 and MSP430FR5939
#endif

#endif // LAUNCHLIB_H
