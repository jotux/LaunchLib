/**
@file global.h
@brief Definitions and data structures for general use in all files
@author Joe Brown
*/
#ifndef GLOBAL_H
#define GLOBAL_H

// for ascii art: http://patorjk.com/software/taag/

#include "msp430.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "config.h"

enum
{
    FALSE = 0,
    TRUE = 1
};

enum
{
    SUCCESS = 0,
    FAILURE = -1
};

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                __  ___
//               /  |/  /____ _ _____ _____ ____   _____
//              / /|_/ // __ `// ___// ___// __ \ / ___/
//             / /  / // /_/ // /__ / /   / /_/ /(__  )
//            /_/  /_/ \__,_/ \___//_/    \____//____/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define _BV(bit)    (1<<(bit))
#define WD_STOP()   (WDTCTL = WDTPW + WDTHOLD)

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                   ______ __        __            __
//                  / ____// /____   / /_   ____ _ / /_____
//                 / / __ / // __ \ / __ \ / __ `// // ___/
//                / /_/ // // /_/ // /_/ // /_/ // /(__  )
//                \____//_/ \____//_.___/ \__,_//_//____/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
extern volatile uint32_t g_clock_speed;

#endif
