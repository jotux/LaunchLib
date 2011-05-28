#ifndef TIMER_H
#define TIMER_H

#include "global.h"

void TimerAInit(void);
__interrupt void TimerAOverflow(void);

extern volatile uint32_t now;

#endif
