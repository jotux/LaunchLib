#include "src/global.h"
#include "src/hardware.h"
#include "src/schedule.h"
#include "src/uart.h"
#include "src/state.h"
#include "src/adc.h"
#include "src/clock.h"

// Event generating functions
void TimerTick(void);
void UartRxPoll(void);

// Event definitions (DEFAULT_EVENTS must be included)
enum
{
    DEFAULT_EVENTS,
    TIMER_TICK,
    RECIEVED_COMMAND,
    GO_BLINK_LED1,
    GO_BLINK_LED2,
    GO_READ_ADC,
    RETURN_TO_IDLE
};

// State functions
void state_idle(uint8_t event);
void state_blink_1(uint8_t event);
void state_blink_2(uint8_t event);
void state_read_adc(uint8_t event);

//Rules
Transition rules[] =
{
    {state_idle,        GO_BLINK_LED1,  state_blink_1    },
    {state_idle,        GO_BLINK_LED2,  state_blink_2    },
    {state_idle,        GO_READ_ADC,    state_read_adc   },
    {state_blink_1,     RETURN_TO_IDLE, state_idle       },
    {state_blink_2,     RETURN_TO_IDLE, state_idle       },
    {state_read_adc,    RETURN_TO_IDLE, state_idle       },
};

// Current state pointer
State state = state_idle;

// Current char in rx buffer
static uint8_t current_command;

void HardwareInit(void)
{
    IO_DIRECTION(LED1,OUTPUT);
    IO_DIRECTION(LED2,OUTPUT);

#ifdef __MSP430G2553__
    IO_FUNCTION(UART_TX,SPECIAL);
    IO_FUNCTION(UART_RX,SPECIAL);
#endif
    IO_AUX_FUNCTION(UART_TX,SPECIAL);
    IO_AUX_FUNCTION(UART_RX,SPECIAL);
}

void main(void)
{
#ifndef NON_BLOCKING_UART_RX
    #error "Define NON_BLOCKING_UART_RX in hardware.h for this example"
#endif
    WD_STOP();
    ClockConfig(16);
    HardwareInit();
    ScheduleTimerInit();
    AdcInit();
    UartInit(115200);
    StateMachineInit(rules, sizeof(rules));

    // register receive polling callback
    CallbackRegister(UartRxPoll, 50ul * _millisecond);
    CallbackMode(UartRxPoll, ENABLED);
    // register timer tick callback (for led blinking)
    CallbackRegister(TimerTick, 100ul * _millisecond);

    _EINT();
    while (1)
    {
        StateMachineRun(&state);
    }
}

void TimerTick(void)
{
    StateMachinePublishEvent(TIMER_TICK);
}

void UartRxPoll(void)
{
    // if there is a character pending
    if (!UartBufEmpty())
    {
        // stick it in the current command buffer
        UartRead(&current_command,1);
        StateMachinePublishEvent(RECIEVED_COMMAND);
    }
}

void state_idle(uint8_t event)
{
    switch(event)
    {
        case ENTER:
        CallbackMode(TimerTick, DISABLED);

        UartPrintf("\n:::::::::::::MENU::::::::::::::\n");
        UartPrintf("1 - LED1\n");
        UartPrintf("2 - LED2\n");
        UartPrintf("3 - Read ADC from P1.5\n");
        UartPrintf("Press ENTER to return to this menu\n");

        break;
        case RECIEVED_COMMAND:
            switch(current_command)
            {
                case '1':
                    StateMachinePublishEvent(GO_BLINK_LED1);
                    break;
                case '2':
                    StateMachinePublishEvent(GO_BLINK_LED2);
                    break;
                case '3':
                    StateMachinePublishEvent(GO_READ_ADC);
                    break;
            }
            break;
        case EXIT:
            CallbackMode(TimerTick, ENABLED);
            break;
    }
}

void state_blink_1(uint8_t event)
{
    switch(event)
    {
        case ENTER:
            UartPrintf("\nNow Blinking LED1. Press ENTER to return to IDLE\n");
            break;
        case RECIEVED_COMMAND:
            if(current_command == '\r')
            {
                StateMachinePublishEvent(RETURN_TO_IDLE);
            }
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
    switch(event)
    {
        case ENTER:
            UartPrintf("\nNow Blinking LED2. Press ENTER to return to IDLE\n");
            break;
        case RECIEVED_COMMAND:
            if(current_command == '\r')
            {
                StateMachinePublishEvent(RETURN_TO_IDLE);
            }
            break;
        case TIMER_TICK:
            LED_TOGGLE(2);
            break;
        case EXIT:
            LED_OFF(2);
            break;
    }
}

void state_read_adc(uint8_t event)
{
    switch(event)
    {
        case RECIEVED_COMMAND:
            if(current_command == '\r')
            {
                StateMachinePublishEvent(RETURN_TO_IDLE);
            }
            break;
        case TIMER_TICK:
            UartPrintf("Adc value = %u\n",AdcRead(0));
            break;
    }
}
