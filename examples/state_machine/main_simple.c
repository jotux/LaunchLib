#include "launchlib.h"

// Event generating functions
void QueueButton(void);
void TimerTick(void);

// Event definitions
// do NOT explicitly set values and DEFAULT_EVENTS must be first
enum Event {DEFAULT_EVENTS, BUTTON_DOWN, TIMER_TICK, TICK_EXPIRE};

// State functions (functions that consume events)
void state_idle(uint8_t event);
void state_blink_1(uint8_t event);
void state_blink_2(uint8_t event);
void state_blink_both(uint8_t event);

// Transition rules
Transition rules[] =
{
    {state_idle,       BUTTON_DOWN, state_blink_1    },
    {state_blink_1,    BUTTON_DOWN, state_blink_2    },
    {state_blink_2,    TICK_EXPIRE, state_blink_both },
    {state_blink_both, BUTTON_DOWN, state_idle       }
};



// Current state pointer
State state = state_idle;

void HardwareInit(void)
{
    IO_DIRECTION(LED1,OUTPUT);
    IO_DIRECTION(LED2,OUTPUT);

    IO_DIRECTION(SW1,INPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    ScheduleTimerInit();
    HardwareInit();

    InterruptAttach(SW1_PORT, SW1_PIN, QueueButton, FALLING_EDGE);
    CallbackRegister(TimerTick, 500ul * _MILLISECOND);
    StateMachineInit(rules, sizeof(rules));
    _EINT();

    while (1)
    {
        StateMachineRun(&state);
    }
}

void QueueButton(void)
{
    StateMachinePublishEvent(BUTTON_DOWN);
}

void TimerTick(void)
{
    StateMachinePublishEvent(TIMER_TICK);
}

void state_idle(uint8_t event){}

void state_blink_1(uint8_t event)
{
    switch(event)
    {
        case ENTER:
            CallbackMode(TimerTick, ENABLED);
            break;
        case TIMER_TICK:
            LED_TOGGLE(1);
            break;
        case EXIT:
            LED_OFF(1);
            break;
    }
}

void state_blink_2(uint8_t event)
{
    static uint8_t tick_cnt = 0;
    switch(event)
    {
        case ENTER:
            InterruptDetach(SW1_PORT, SW1_PIN);
            break;
        case TIMER_TICK:
            LED_TOGGLE(2);
            if (tick_cnt++ > 4)
            {
                tick_cnt = 0;
                StateMachinePublishEvent(TICK_EXPIRE);
            }
            break;
        case EXIT:
            InterruptAttach(SW1_PORT, SW1_PIN, QueueButton, FALLING_EDGE);
            LED_OFF(2);
            break;
    }
}

void state_blink_both(uint8_t event)
{
    switch(event)
    {
        case TIMER_TICK:
            LED_TOGGLE(1);
            LED_TOGGLE(2);
            break;
        case EXIT:
            LED_OFF(1);
            LED_OFF(2);
            CallbackMode(TimerTick, DISABLED);
            break;
    }
}
