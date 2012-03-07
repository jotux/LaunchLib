/** 
@file schedule.c
@brief Generic scheduling mechanisms
@author Joe Brown
*/
#include "global.h"
#include "schedule.h"
#include "hardware.h"

// global time
volatile uint32_t now = 0;

/** @brief number of registered callouts*/
static uint8_t event_count = 0;
/** @brief configured callback list*/
static CallbackEvent callback_store[MAX_CALLBACK_CNT];

/** @brief bit array represending occupied or vacant callouts*/
static uint8_t callout_map = 0;
/** @brief Array of function callouts. If a callout is enabled it will have a
function pointer stored and if it is disabled the pointer will be replaced
with a null*/
static CalloutEvent callout_store[MAX_CALLOUT_CNT];

void ScheduleTimerInit(void)
{
    WDTCTL = WDT_MDLY_8;  // interval = 500us @ 16Mhz
    IE1 |= WDTIE;         // Enable WDT interrupt
}

void CallbackRegister(CallbackFn func, uint32_t run_time)
{
    if (event_count < sizeof(callback_store)/sizeof(CallbackFn))
    {
        // Callbacks are initialized disabled
        callback_store[event_count].enabled       = FALSE;
        callback_store[event_count].func          = func;
        callback_store[event_count].run_time      = run_time - 1;
        callback_store[event_count].next_run_time = now + run_time;
        event_count++;
    }
}

void CallbackService(uint32_t current_time)
{
    uint8_t i = 0;
    for (i = 0;i < event_count;i++)
    {
        if (callback_store[i].enabled == TRUE &&
            current_time == callback_store[i].next_run_time)
        {
            callback_store[i].next_run_time = current_time +
                                              callback_store[i].run_time;
            callback_store[i].func();
        }
    }
}

void CallbackMode(CallbackFn func, enum IoMode mode)
{
    uint8_t i = 0;
    for (i = 0;i < event_count;i++)
    {
        if (func == callback_store[i].func)
        {
            callback_store[i].enabled = mode;
            if (mode)
            {
                callback_store[i].next_run_time = now +
                                                  callback_store[i].run_time;
            }
            break;
        }
    }
}

int8_t CalloutRegister(CalloutFn func, uint32_t run_time)
{
    int8_t ret = -1;
    // event queue full?
    if (get_callout_map_size() != MAX_CALLOUT_CNT)
    {
        uint8_t i = 0;
        for (i = 0;i < MAX_CALLOUT_CNT;i++)
        {
            // find the first open slot
            if (!(callout_map & _BV(i)))
            {
                // claim the slot
                callout_map |= _BV(i);
                // save our data
                callout_store[i].func = func;
                callout_store[i].run_time = now + run_time;
                // return success
                ret = 0;
                break;
            }
        }
    }
    return ret;
}

void CalloutCancel(CalloutFn func)
{
    uint8_t i = 0;
    for (i = 0;i < MAX_CALLOUT_CNT;i++)
    {
        // find the slot
        if (callout_store[i].func == func)
        {
            // clear
            callout_map &= ~_BV(i);
            break;
        }
    }
}

uint8_t get_callout_map_size(void)
{
    uint8_t sum = 0;
    uint8_t map = callout_map;
    for (sum = 0; map; sum++)
    {
        map &= map - 1;
    }
    return sum;
}

void CalloutService(uint32_t current_time)
{
    uint8_t i = 0;
    for (i = 0;i < MAX_CALLOUT_CNT;i++)
    {
        // find occupied slots and see if the function there is ready
        if ((callout_map & _BV(i)) && current_time == callout_store[i].run_time)
        {
            // run the function
            callout_store[i].func();
            // vacate the slot
            callout_map &= ~_BV(i);
        }
    }
}

#pragma vector = SCHEDULE_VECTOR
__interrupt void ScheduleTimerOverflow(void)
{
    now++;
    CallbackService(now);
    CalloutService(now);
}
