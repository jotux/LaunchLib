#include "../../launchlib.h"
#include "../../hw.h"
#include "../../launchlib/tone.h"

#define SIMPLE_EXAMPLE
//#define ENABLE_DISABLE_EXAMPLE
//#define VARYING_CLOCK_EXAMPLE
//#define ONE_SHOT_EXAMPLE
//#define SELF_SCHEDULE_EXAMPLE

#if defined(SIMPLE_EXAMPLE)

void BlinkLed1(void);
void BlinkLed2(void);

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);
    IO_DIRECTION(LED2,GPIO_OUTPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();

    // Init the timer
    ScheduleTimerInit();
    // register functions and define their period
    CallbackRegister(BlinkLed1, 100ul * _MILLISECOND);
    CallbackRegister(BlinkLed2, 101ul * _MILLISECOND);
    // callbacks are disabled by default, so enable them
    CallbackMode(BlinkLed1, ENABLED);
    CallbackMode(BlinkLed2, ENABLED);

    _EINT();
    LPM0;
}

void BlinkLed1(void)
{
    LED1_TOGGLE();
}

void BlinkLed2(void)
{
    LED2_TOGGLE();
}

#elif defined(ENABLE_DISABLE_EXAMPLE)

void BlinkLed1(void);
void ToggleEnable(void);

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);
    IO_DIRECTION(SW1,GPIO_INPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();

    // Init the timer
    ScheduleTimerInit();
    // register a function and define its period
    CallbackRegister(BlinkLed1, 100ul * _MILLISECOND);
    // attach function to SW1 falling edge interrupt
    InterruptAttach(GPIO(SW1),ToggleEnable,FALLING);

    _EINT();
    LPM0;
}

void BlinkLed1(void)
{
    LED1_TOGGLE();
}

void ToggleEnable(void)
{
    static uint8_t tog = 0;
    if (tog == FALSE)
    {
        tog = TRUE;
        CallbackMode(BlinkLed1, ENABLED);
    }
    else
    {
        tog = FALSE;
        LED1_OFF();
        CallbackMode(BlinkLed1, DISABLED);
    }
}

#elif defined(VARYING_CLOCK_EXAMPLE)

void BlinkLed1(void);

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);

    // configure 1.4 to output the DCO for observation
    P1DIR |= 0x10;
    P1SEL |= 0x10;
}

void main(void)
{
    WD_STOP();
    ClockConfig(1);
    HardwareInit();

    ScheduleTimerInit();
    BlinkLed1();
    _EINT();
    LPM0;
}

void BlinkLed1(void)
{
    static int i = 0;
    switch (i++)
    {
        case 1:
            ClockConfig(1);
            break;
        case 10:
            ClockConfig(8);
            break;
        case 20:
            ClockConfig(12);
            break;
        case 30:
            ClockConfig(16);
            break;
        case 40:
            i = 0;
            break;
    }
    LED1_TOGGLE();
    CalloutRegister(BlinkLed1, 1000);
}

#elif defined(ONE_SHOT_EXAMPLE)

void QueueButton(void);
void ToggleLed2(void);

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

    // attach function to SW1 falling edge interrupt
    InterruptAttach(GPIO(SW1), QueueButton, FALLING);
    _EINT();
    LPM0;
}

void QueueButton(void)
{
    // when the interrupt fires queue a few callouts to make the LED toggle
    CalloutRegister(ToggleLed2, 5000ul * _MILLISECOND);
    CalloutRegister(ToggleLed2, 5100ul * _MILLISECOND);
    CalloutRegister(ToggleLed2, 5200ul * _MILLISECOND);
    CalloutRegister(ToggleLed2, 5300ul * _MILLISECOND);
    CalloutRegister(ToggleLed2, 5400ul * _MILLISECOND);
    CalloutRegister(ToggleLed2, 5500ul * _MILLISECOND);
}

void ToggleLed2(void)
{
    LED2_TOGGLE();
}

#elif defined(SELF_SCHEDULE_EXAMPLE)

void ToggleLed2(void);

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);
    IO_DIRECTION(LED2,GPIO_OUTPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    ScheduleTimerInit();
    HardwareInit();

    // call ToggleLed2 and it will continue to reschedule itself forever
    ToggleLed2();
    _EINT();
    LPM0;
}



void ToggleLed2(void)
{
    LED2_TOGGLE();
    CalloutRegister(ToggleLed2, 100);
}

#endif
