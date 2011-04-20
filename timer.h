#ifndef TIMER_H
#define TIMER_H

#include "global.h"

void InitTimerA(void);
__interrupt void TimerAOverflow(void);

extern volatile UINT32 now;

#endif
