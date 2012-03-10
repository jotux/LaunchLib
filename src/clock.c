/**
@file clock.c
@brief Clock config data and functions
@author Joe Brown
*/
#include "global.h"
#include "clock.h"

// to be externed in global.h so it is accessible to everyone
volatile uint32_t g_clock_speed = 0;
