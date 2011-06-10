#include "timer.h"
#include "callback.h"
#include "global.h"

volatile uint32_t now = 0;

void TimerAInit(void)
{
    TACCTL0 &= ~CCIE;           // disable ints
    TACCR0 = INT_CNT_DCO;       // set the overflow
    TACTL = TASSEL_2 + MC_1;    // smclk, up to then overflow at ccr0
    TACCTL0 = CCIE;             // enable ints
}

#pragma vector = TIMERA0_VECTOR
__interrupt void TimerAOverflow(void)
{
    now++;
    CallbackService(now);
}


