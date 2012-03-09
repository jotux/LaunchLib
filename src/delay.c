/** 
@file delay.c
@brief Simple delay using global timer
@author Joe Brown
*/
#include "global.h"
#include "delay.h"
#include "schedule.h"

void Delay(uint32_t delay_time)
{
    uint32_t start_time = now;
    while(now < (start_time + delay_time));
}