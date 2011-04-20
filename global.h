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

#define TRUE 1
#define FALSE 0

// macros
#define _BV(bit) (1<<bit)
#define WD_STOP() (WDTCTL = WDTPW + WDTHOLD)

//types
typedef unsigned char      UINT08;
typedef signed char        INT08;
typedef unsigned short int UINT16;
typedef signed short int   INT16;
typedef unsigned long int  UINT32;
typedef signed long int    INT32;

#endif
