#include "src/global.h"
#include "src/hardware.h"
#include "src/schedule.h"
#include "src/uart.h"
#include "src/state.h"
#include "src/adc.h"

// Event generating functions
void TimerTick(void);
void UartRxPoll(void);

// Event definitions (DEFAULT_EVENTS must be included)
enum
{
    DEFAULT_EVENTS,
    TIMER_TICK,
    RECIEVED_COMMAND,
    GO_BLINK_RED,
    GO_BLINK_GREEN,
    GO_READ_ADC,
    RETURN_TO_IDLE
};

// State functions
void state_idle(uint8_t event);
void state_blink_red(uint8_t event);
void state_blink_green(uint8_t event);
void state_read_adc(uint8_t event);

//Rules
Transition rules[] =
{
    {state_idle,        GO_BLINK_RED,   state_blink_red  },
    {state_idle,        GO_BLINK_GREEN, state_blink_green},
    {state_idle,        GO_READ_ADC,    state_read_adc   },
    {state_blink_red,   RETURN_TO_IDLE, state_idle       },
    {state_blink_green, RETURN_TO_IDLE, state_idle       },
    {state_read_adc,    RETURN_TO_IDLE, state_idle       },
};

// Current state pointer
State state = state_idle;

// Current char in rx buffer
static uint8_t current_command;

void HardwareInit(void)
{
    IO_DIRECTION(RED_LED,OUTPUT);
    RED_LED_OFF();

    IO_DIRECTION(GREEN_LED,OUTPUT);
    GREEN_LED_OFF();

    IO_DIRECTION(SW1,INPUT);

    IO_FUNCTION(UART_TX,SPECIAL);
    IO_FUNCTION(UART_RX,SPECIAL);
    IO_AUX_FUNCTION(UART_TX,SPECIAL);
    IO_AUX_FUNCTION(UART_RX,SPECIAL);
}

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
    HardwareInit();
    ScheduleTimerInit();
    AdcInit(5);
    // Make sure NON_BLOCKING_UART_RX is defined in hardware.h
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
        UartPrintf("1 - Blink Red LED\n");
        UartPrintf("2 - Blink Green LED\n");
        UartPrintf("3 - Read ADC from P1.5\n");
        UartPrintf("Press ENTER to return to this menu\n");

        break;
        case RECIEVED_COMMAND:
            switch(current_command)
            {
                case '1':
                    StateMachinePublishEvent(GO_BLINK_RED);
                    break;
                case '2':
                    StateMachinePublishEvent(GO_BLINK_GREEN);
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

void state_blink_red(uint8_t event)
{
    switch(event)
    {
        case ENTER:
            UartPrintf("\nNow Blinking RED LED. Press ENTER to return to IDLE\n");
            break;
        case RECIEVED_COMMAND:
            if(current_command == '\r')
            {
                StateMachinePublishEvent(RETURN_TO_IDLE);
            }
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
    switch(event)
    {
        case ENTER:
            UartPrintf("\nNow Blinking GREEN LED. Press ENTER to return to IDLE\n");
            break;
        case RECIEVED_COMMAND:
            if(current_command == '\r')
            {
                StateMachinePublishEvent(RETURN_TO_IDLE);
            }
            break;
        case TIMER_TICK:
            GREEN_LED_TOGGLE();
            break;
        case EXIT:
            GREEN_LED_OFF();
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
            UartPrintf("Adc value = %u\n",AdcRead(5));
            break;
    }
}
