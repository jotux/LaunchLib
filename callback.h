#ifndef SCHEDULER_H
#define SCHEDULER_H

typedef void (*SchedulerCallback)(void);

enum callback_mode {DISABLED = 0, ENABLED = 1};

typedef struct
{
    SchedulerCallback func;
    uint8_t enabled;
    uint32_t run_time;
    uint32_t next_run_time;
    uint8_t location;
} ScheduledEvent;

void CallbackRegister(SchedulerCallback callback_function, uint32_t run_time);
void CallbackService(uint32_t current_time);
void CallbackMode(SchedulerCallback func, enum callback_mode mode);
void CallbackDisable(SchedulerCallback func);

#endif
