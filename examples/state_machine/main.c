#include "src/global.h"
#include "src/hardware.h"
#include "src/init.h"
#include "src/callback.h"
#include "src/interrupt.h"
#include "src/state.h"

// Event generating functions
void QueueButton(void);
void TimerTick(void);

// Event definitions (do NOT explicitly set values)
enum EVENT {DEFAULT_EVENTS, BUTTON_DOWN, TIMER_TICK};

// State functions (functions that consume events)
void state_idle(uint8_t event);
void state_blink_red(uint8_t event);
void state_blink_green(uint8_t event);
void state_blink_both(uint8_t event);

// Transition rules
transition rules[] =
{
    {state_idle,        BUTTON_DOWN, state_blink_red  },
    {state_blink_red,   BUTTON_DOWN, state_blink_green},
    {state_blink_green, BUTTON_DOWN, state_blink_both },
    {state_blink_both,  BUTTON_DOWN, state_idle       }
};

// Current state pointer
State state;

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
    CallbackTimerInit();
    HardwareInit();

    AttachInterrupt(1,3,QueueButton,FALLING_EDGE);
    CallbackRegister(TimerTick, 500ul * _millisecond);
    StateMachineInit(rules, sizeof(rules));
    _EINT();

    // initial state
    state = state_idle;

    while (1)
    {
        state(CheckEventQueue(state));
    }
}

void state_idle(uint8_t event)
{
    state = LookupTransition(state, event);
}

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
        default:
            break;
    }
    state = LookupTransition(state, event);
}

void state_blink_green(uint8_t event)
{
    switch(event)
    {
        case TIMER_TICK:
            GREEN_LED_TOGGLE();
            break;
        case EXIT:
            GREEN_LED_OFF();
            break;
        default:
            break;
    }
    state = LookupTransition(state, event);
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
        default:
            break;
    }
    state = LookupTransition(state, event);
}

void QueueButton(void)
{
    EnqueueEvent(BUTTON_DOWN);
}
void TimerTick(void)
{
    EnqueueEvent(TIMER_TICK);
}
