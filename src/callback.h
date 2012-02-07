#ifndef SCHEDULER_H
#define SCHEDULER_H

#define CALLBACK_VECTOR WDT_VECTOR
typedef void (*SchedulerCallback)(void);

typedef struct
{
    SchedulerCallback func;
    uint8_t enabled;
    uint32_t run_time;
    uint32_t next_run_time;
} ScheduledEvent;

void CallbackRegister(SchedulerCallback callback_function, uint32_t run_time);
void CallbackService(uint32_t current_time);
void CallbackMode(SchedulerCallback func, enum IoMode mode);
void CallbackDisable(SchedulerCallback func);
void CallbackTimerInit(void);
__interrupt void CallbackTimerOverflow(void);

extern volatile uint32_t now;

#define MAX_CALLBACK_CNT 1

#endif
