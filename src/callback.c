#include "global.h"
#include "callback.h"
#include "hardware.h"

// global time
volatile uint32_t now = 0;

uint8_t event_count = 0;
ScheduledEvent event_list[MAX_CALLBACK_CNT];

void CallbackRegister(SchedulerCallback callback_function, uint32_t run_time)
{
    if (event_count < sizeof(event_list)/sizeof(SchedulerCallback))
    {
        // Callbacks are initialized disabled
        event_list[event_count].enabled       = FALSE;
        event_list[event_count].func          = callback_function;
        event_list[event_count].run_time      = run_time - 1;
        event_list[event_count].next_run_time = now + run_time;
        event_count++;
    }
}

void CallbackService(uint32_t current_time)
{
    uint8_t i = 0;
    for (i = 0;i < event_count;i++)
    {
        if (event_list[i].enabled == TRUE && now == event_list[i].next_run_time)
        {
            event_list[i].next_run_time = current_time + event_list[i].run_time;
            event_list[i].func();
        }
    }
}

void CallbackMode(SchedulerCallback func, enum IoMode mode)
{
    uint8_t i = 0;
    for (i = 0;i < event_count;i++)
    {
        if (func == event_list[i].func)
        {
            event_list[i].enabled = mode;
            if (mode)
            {
                event_list[i].next_run_time = now + event_list[i].run_time;
            }
            break;
        }
    }
}

void CallbackTimerInit(void)
{
#ifdef __MSP430G2553__
    WDTCTL = WDT_MDLY_8;  // interval = 500us @ 16Mhz
#else
	WDTCTL = WDT_MDLY_0_5; // interval = 500us @ 1Mhz
#endif
    IE1 |= WDTIE;         // Enable WDT interrupt
}

#pragma vector = CALLBACK_VECTOR
__interrupt void CallbackTimerOverflow(void)
{
    now++;
    CallbackService(now);
}
