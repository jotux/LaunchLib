#include "../../launchlib.h"
#include "../../hw.h"

//#define SIMPLE_EXAMPLE
#define UART_EXAMPLE

#if defined(SIMPLE_EXAMPLE)

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

// State machine structure
StateMachine s;

// Transition rules
Transition rules[] =
{
    {state_idle,       BUTTON_DOWN, state_blink_1    },
    {state_blink_1,    BUTTON_DOWN, state_blink_2    },
    {state_blink_2,    TICK_EXPIRE, state_blink_both },
    {state_blink_both, BUTTON_DOWN, state_idle       }
};

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);
    IO_DIRECTION(LED2,GPIO_OUTPUT);

    IO_DIRECTION(SW1,GPIO_INPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    ScheduleTimerInit();
    HardwareInit();

    InterruptAttach(SW1_PORT, SW1_PIN, QueueButton, FALLING);
    CallbackRegister(TimerTick, 500ul * _MILLISECOND);
    s = StateMachineCreate(rules, sizeof(rules),state_idle);
    _EINT();

    while (1)
    {
        StateMachineRun(&s);
    }
}

void QueueButton(void)
{
    StateMachinePublishEvent(&s,BUTTON_DOWN);
}

void TimerTick(void)
{
    StateMachinePublishEvent(&s,TIMER_TICK);
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
            LED1_TOGGLE();
            break;
        case EXIT:
            LED1_OFF();
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
            LED2_TOGGLE();
            if (tick_cnt++ > 4)
            {
                tick_cnt = 0;
                StateMachinePublishEvent(&s,TICK_EXPIRE);
            }
            break;
        case EXIT:
            InterruptAttach(GPIO(SW1), QueueButton, FALLING);
            LED2_OFF();
            break;
    }
}

void state_blink_both(uint8_t event)
{
    switch(event)
    {
        case TIMER_TICK:
            LED1_TOGGLE();
            LED2_TOGGLE();
            break;
        case EXIT:
            LED1_OFF();
            LED2_OFF();
            CallbackMode(TimerTick, DISABLED);
            break;
    }
}

#elif defined(UART_EXAMPLE)

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

// State machine structure
StateMachine s;

//Rules
Transition rules[] =
{
    {state_idle,     GO_BLINK_LED1,  state_blink_1 },
    {state_idle,     GO_BLINK_LED2,  state_blink_2 },
    {state_idle,     GO_READ_ADC,    state_read_adc},
    {state_blink_1,  RETURN_TO_IDLE, state_idle    },
    {state_blink_2,  RETURN_TO_IDLE, state_idle    },
    {state_read_adc, RETURN_TO_IDLE, state_idle    },
};

// Current char in rx buffer
static uint8_t current_command;

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);
    IO_DIRECTION(LED2,GPIO_OUTPUT);

#ifdef __MSP430G2553__
    IO_FUNCTION(UART_TX,GPIO_FUN_SPECIAL);
    IO_FUNCTION(UART_RX,GPIO_FUN_SPECIAL);
#endif
    IO_AUX_FUNCTION(UART_TX,GPIO_FUN_SPECIAL);
    IO_AUX_FUNCTION(UART_RX,GPIO_FUN_SPECIAL);
}

void main(void)
{
#ifndef MAX_UART_RX_BUF_CNT
    #error "Define MAX_UART_RX_BUF_CNT > 0 in config.h for this example"
#endif
    WD_STOP();
    ClockConfig(16);
    HardwareInit();
    ScheduleTimerInit();
    AdcInit();
    UartInit(115200);
    s = StateMachineCreate(rules, sizeof(rules),state_idle);

    // register receive polling callback
    CallbackRegister(UartRxPoll, 50ul * _MILLISECOND);
    CallbackMode(UartRxPoll, ENABLED);
    // register timer tick callback (for led blinking)
    CallbackRegister(TimerTick, 100ul * _MILLISECOND);

    _EINT();
    while (1)
    {
        StateMachineRun(&s);
    }
}

void TimerTick(void)
{
    StateMachinePublishEvent(&s,TIMER_TICK);
}

void UartRxPoll(void)
{
    // if there is a character pending
    if (!UartBufEmpty())
    {
        // stick it in the current command buffer
        current_command = getchar();
        StateMachinePublishEvent(&s,RECIEVED_COMMAND);
    }
}

void state_idle(uint8_t event)
{
    switch(event)
    {
        case ENTER:
            CallbackMode(TimerTick, DISABLED);

            printf("\n:::::::::::::MENU::::::::::::::\n");
            printf("1 - LED1\n");
            printf("2 - LED2\n");
            printf("3 - Read ADC from P1.5\n");
            printf("Press ENTER to return to this menu\n");

            break;
        case RECIEVED_COMMAND:
            switch(current_command)
            {
                case '1':
                    StateMachinePublishEvent(&s,GO_BLINK_LED1);
                    break;
                case '2':
                    StateMachinePublishEvent(&s,GO_BLINK_LED2);
                    break;
                case '3':
                    StateMachinePublishEvent(&s,GO_READ_ADC);
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
            printf("\nNow Blinking LED1. Press ENTER to return to IDLE\n");
            break;
        case RECIEVED_COMMAND:
            if(current_command == '\r')
            {
                StateMachinePublishEvent(&s,RETURN_TO_IDLE);
            }
            break;
        case TIMER_TICK:
            LED1_TOGGLE();
            break;
        case EXIT:
            LED1_OFF();
            break;
    }
}

void state_blink_2(uint8_t event)
{
    switch(event)
    {
        case ENTER:
            printf("\nNow Blinking LED2. Press ENTER to return to IDLE\n");
            break;
        case RECIEVED_COMMAND:
            if(current_command == '\r')
            {
                StateMachinePublishEvent(&s,RETURN_TO_IDLE);
            }
            break;
        case TIMER_TICK:
            LED2_TOGGLE();
            break;
        case EXIT:
            LED2_OFF();
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
                StateMachinePublishEvent(&s,RETURN_TO_IDLE);
            }
            break;
        case TIMER_TICK:
            printf("Adc value = %u\n",AdcRead(0));
            break;
    }
}
#endif
