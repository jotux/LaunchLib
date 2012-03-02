#ifndef SCHEDULE_H
#define SCHEDULE_H

#define SCHEDULE_VECTOR WDT_VECTOR
typedef void (*CallbackFn)(void);
typedef void (*CalloutFn)(void);

typedef struct
{
    CallbackFn func;
    uint8_t enabled;
    uint32_t run_time;
    uint32_t next_run_time;
} ScheduledEvent;

typedef struct
{
    CalloutFn func;
    uint32_t run_time;
} CalloutEvent;

extern void ScheduleTimerInit(void);
extern void CallbackRegister(CallbackFn callback_function, uint32_t run_time);
static void CallbackService(uint32_t current_time);
extern void CallbackMode(CallbackFn func, enum IoMode mode);
extern void CallbackDisable(CallbackFn func);

extern int8_t  CalloutRegister(CalloutFn func, uint32_t run_time);
static uint8_t get_callout_map_size(void);
static void    CalloutService(uint32_t current_time);

__interrupt void ScheduleTimerOverflow(void);

extern volatile uint32_t now;

#endif
