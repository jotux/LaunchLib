#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef void (*SchedulerCallback)(void);

#define MAX_CALLBACK_CNT 3

enum
{
    DISABLED = 0,
    ENABLED = 1
};
      
typedef struct
{
    SchedulerCallback func;
    uint8_t enabled;
    uint32_t run_time;
    uint32_t next_run_time;
    uint8_t location;
} ScheduledEvent;

void CallbackRegister(SchedulerCallback callbackFunction, uint32_t run_time);
void CallbackService(uint32_t current_time);
void CallbackMode(SchedulerCallback func, uint8_t mode);
void CallbackDisable(SchedulerCallback func);

#endif
