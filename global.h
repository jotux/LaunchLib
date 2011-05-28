#ifndef GLOBAL_H
#define GLOBAL_H

#include "msp430x22x4.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CLOCK_DCO   1000000                                 // DCO freq
#define CLOCK_EXT   32768                                   // ext clock freq

#define INT_CNT_DCO	((int)(0.0001 * CLOCK_DCO))
#define INT_CNT_EXT	((int)(0.01 * CLOCK_EXT))

// based on 100 microsecond timer period
#define _100micro      1
#define _millisecond   10
#define _second        10000
#define _minute        600000
#define _hour          36000000

#define TRUE 1
#define FALSE 0

// macros
#define _BV(bit) (1<<bit)
#define WD_STOP() (WDTCTL = WDTPW + WDTHOLD)

//types
typedef unsigned char      uint8_t;
typedef signed char        int8_t;
typedef unsigned short int uint16_t;
typedef signed short int   int16_t;
typedef unsigned long int  uint32_t;
typedef signed long int    int32_t;

#endif
