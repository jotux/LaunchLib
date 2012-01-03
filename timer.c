#include "global.h"
#include "hardware.h"
#include "timer.h"
#include "callback.h"

volatile uint32_t now = 0;

void CallbackTimerInit(void)
{
#ifdef __MSP430G2553__
    WDTCTL = WDT_MDLY_8;  // interval = 500us @ 16Mhz
#else
	WDTCTL = WDT_MDLY_0_5; // interval = 500us @ 1Mhz
#endif
    IE1 |= WDTIE;         // Enable WDT interrupt
}

#pragma vector = WDT_VECTOR
__interrupt void CallbackTimerOverflow(void)
{
    now++;
    CallbackService(now);
}

