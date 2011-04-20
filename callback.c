#include "callback.h"
#include "timer.h"
#include "global.h"

UINT08 event_count = 0;

ScheduledEvent event_list[MAX_CALLBACK_CNT];

void RegisterCallback(SchedulerCallback callbackFunction, UINT08 enabled, UINT32 run_time)
{
    if (event_count < sizeof(event_list)/sizeof(SchedulerCallback))
    {
        event_list[event_count].enabled       = enabled;
        event_list[event_count].func          = callbackFunction;
        event_list[event_count].run_time      = run_time;
        event_list[event_count].next_run_time = now + run_time;
        event_count++;
    }
}

void RunCallbacks(unsigned long int current_time)
{
    UINT08 i = 0;
    for (i = 0;i < event_count;i++)
    {
        if (event_list[i].enabled == TRUE && now == event_list[i].next_run_time)
        {
            event_list[i].next_run_time = current_time + event_list[i].run_time;
            event_list[i].func();
        }
    }
}

void EnableCallback(SchedulerCallback func)
{
    UINT08 i = 0;
    for (i = 0;i < event_count;i++)
    {
        if (func == event_list[i].func)
        {
            event_list[i].enabled = TRUE;
            event_list[i].next_run_time = now + event_list[i].run_time;
            break;
        }
    }
}

void DisableCallback(SchedulerCallback func)
{
    UINT08 i = 0;
    for (i = 0;i < event_count;i++)
    {
        if (func == event_list[i].func)
        {
            event_list[i].enabled = FALSE;
            break;
        }
    }
}
