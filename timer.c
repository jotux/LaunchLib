#include "global.h"
#include "hardware.h"
#include "timer.h"
#include "callback.h"

volatile uint32_t now = 0;

void CallbackTimerInit(void)
{
    WDTCTL = WDT_MDLY_8;  // interval = 8ms @ 1Mhz, 500us @ 16Mhz
    IE1 |= WDTIE;         // Enable WDT interrupt
}

#pragma vector = WDT_VECTOR;
__interrupt void CallbackTimerOverflow(void)
{
    now++;
    CallbackService(now);
}

