#include "global.h"
#include "delay.h"
#include "timer.h"

void Delay(uint32_t delay_time)
{
    uint32_t start_time = now;
    while(now < (start_time + delay_time));
}
