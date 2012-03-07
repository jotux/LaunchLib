#include "src/global.h"
#include "src/hardware.h"
#include "src/schedule.h"
#include "src/interrupt.h"
#include "src/state.h"

// Event generating functions
void QueueButton(void);
void TimerTick(void);

// Event definitions
// do NOT explicitly set values and DEFAULT_EVENTS must be first
enum Event {DEFAULT_EVENTS, BUTTON_DOWN, TIMER_TICK, TICK_EXPIRE};

// State functions (functions that consume events)
void state_idle(uint8_t event);
void state_blink_red(uint8_t event);
void state_blink_green(uint8_t event);
void state_blink_both(uint8_t event);

// Transition rules
Transition rules[] =
{
    {state_idle,        BUTTON_DOWN, state_blink_red  },
    {state_blink_red,   BUTTON_DOWN, state_blink_green},
    {state_blink_green, TICK_EXPIRE, state_blink_both },
    {state_blink_both,  BUTTON_DOWN, state_idle       }
};



// Current state pointer
State state = state_idle;

void HardwareInit(void)
{
    IO_DIRECTION(RED_LED,OUTPUT);
    RED_LED_OFF();

    IO_DIRECTION(GREEN_LED,OUTPUT);
    GREEN_LED_OFF();

    IO_DIRECTION(SW1,INPUT);
}

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
    ScheduleTimerInit();
    HardwareInit();

    InterruptAttach(SW1_PORT, SW1_PIN, QueueButton, FALLING_EDGE);
    CallbackRegister(TimerTick, 500ul * _millisecond);
    StateMachineInit(rules, sizeof(rules));
    _EINT();

    while (1)
    {
        StateRun(&state);
    }
}

void QueueButton(void)
{
    EnqueueEvent(BUTTON_DOWN);
}

void TimerTick(void)
{
    EnqueueEvent(TIMER_TICK);
}

void state_idle(uint8_t event){}

void state_blink_red(uint8_t event)
{
    switch(event)
    {
        case ENTER:
            CallbackMode(TimerTick, ENABLED);
            break;
        case TIMER_TICK:
            RED_LED_TOGGLE();
            break;
        case EXIT:
            RED_LED_OFF();
            break;
    }
}

void state_blink_green(uint8_t event)
{
    static uint8_t tick_cnt = 0;
    switch(event)
    {
        case ENTER:
            InterruptDetach(SW1_PORT, SW1_PIN);
            break;
        case TIMER_TICK:
            GREEN_LED_TOGGLE();
            if (tick_cnt++ > 4)
            {
                tick_cnt = 0;
                EnqueueEvent(TICK_EXPIRE);
            }
            break;
        case EXIT:
            InterruptAttach(SW1_PORT, SW1_PIN, QueueButton, FALLING_EDGE);
            GREEN_LED_OFF();
            break;
    }
}

void state_blink_both(uint8_t event)
{
    switch(event)
    {
        case TIMER_TICK:
            GREEN_LED_TOGGLE();
            RED_LED_TOGGLE();
            break;
        case EXIT:
            GREEN_LED_OFF();
            RED_LED_OFF();
            CallbackMode(TimerTick, DISABLED);
            break;
    }
}
