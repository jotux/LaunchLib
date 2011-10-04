#ifndef TIMER_H
#define TIMER_H

#include "global.h"

void CallbackTimerInit(void);
__interrupt void CallbackTimerOverflow(void);

extern volatile uint32_t now;

#endif
