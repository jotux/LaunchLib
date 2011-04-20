#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "global.h"

typedef void (*SchedulerCallback)(void);

#define MAX_CALLBACK_CNT 5

#define _100micro  1
#define _10milli   100
#define _100milli  1000
#define _second    10000
#define _minute    600000
#define _hour      36000000

enum
{
    DISABLED = 0,
    ENABLED = 1
};
      
typedef struct
{
    SchedulerCallback func;
    UINT08 enabled;
    UINT32 run_time;
    UINT32 next_run_time;
    UINT08 location;
} ScheduledEvent;

void RegisterCallback(SchedulerCallback callbackFunction, UINT08 enabled, UINT32 run_time);
void RunCallbacks(UINT32 current_time);
void EnableCallback(SchedulerCallback func);
void DisableCallback(SchedulerCallback func);

#endif
