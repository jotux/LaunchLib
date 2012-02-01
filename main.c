#include "global.h"
#include "hardware.h"
#include "timer.h"
#include "init.h"
#include "callback.h"
#include "pwm.h"
#include "adc.h"
#include "interrupt.h"
#include "delay.h"
#include "state.h"

// State function definitions
void state_idle(uint8_t event);
void state_blink_red(uint8_t event);
void state_blink_green(uint8_t event);

// Event functions
void QueueButton(void);

// Event definitions
enum EVENT {OK = 0, BUTTON_DOWN, BUTTON_UP};

transition state_transitions[] =
{
    {state_idle,                 OK, state_idle       },
    {state_idle,        BUTTON_DOWN, state_blink_red  },
    {state_blink_red,            OK, state_blink_red  },
    {state_blink_red,   BUTTON_DOWN, state_blink_green},
    {state_blink_green,          OK, state_blink_green},
    {state_blink_green, BUTTON_DOWN, state_idle       }
};

uint8_t transition_size = (sizeof(state_transitions) / sizeof(transition));

State state;

void main(void)
{
    WD_STOP();
    SET_CLOCK(1);
    HardwareInit();
	AttachInterrupt(1,3,QueueButton,FALLING_EDGE);
    _EINT();
    state = state_idle;

    while (1)
    {
        state(CheckEventQueue());
    }
}

void state_idle(uint8_t event)
{
    RED_LED_OFF();
    GREEN_LED_OFF();
    state = LookupTransition(state, event,state_transitions, transition_size);
}

void state_blink_red(uint8_t event)
{
    RED_LED_ON();
    GREEN_LED_OFF();
    state = LookupTransition(state, event,state_transitions, transition_size);
}

void state_blink_green(uint8_t event)
{
	GREEN_LED_ON();
	RED_LED_OFF();
    state = LookupTransition(state, event,state_transitions, transition_size);
}

void QueueButton(void)
{
    event = 1;
}
