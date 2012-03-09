#include "src/global.h"
#include "src/hardware.h"
#include "src/schedule.h"
#include "src/clock.h"

void BlinkLed1(void);
void BlinkLed1(void);

void HardwareInit(void)
{
    IO_DIRECTION(LED1,OUTPUT);
    IO_DIRECTION(LED2,OUTPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();

    // Init the timer
    ScheduleTimerInit();
    // register functions and define their period
    CallbackRegister(BlinkLed1, 100ul * _millisecond);
    CallbackRegister(BlinkLed1, 101ul * _millisecond);
    // callbacks are disabled by default, so enable them
    CallbackMode(BlinkLed1,   ENABLED);
    CallbackMode(BlinkLed2, ENABLED);

    _EINT();
    LPM0;
}

void BlinkLed1(void)
{
    LED_TOGGLE(1);
}

void BlinkLed2(void)
{
    LED_TOGGLE(2);
}