#include "src/global.h"
#include "src/hardware.h"
#include "src/schedule.h"

void BlinkRedLed(void);
void BlinkGreenLed(void);

void HardwareInit(void)
{
    IO_DIRECTION(RED_LED,OUTPUT);
    RED_LED_OFF();

    IO_DIRECTION(GREEN_LED,OUTPUT);
    GREEN_LED_OFF();
}

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
    HardwareInit();

    // Init the timer
    ScheduleTimerInit();
    // register functions and define their period
    CallbackRegister(BlinkRedLed,   100ul * _millisecond);
    CallbackRegister(BlinkGreenLed, 101ul * _millisecond);
    // callbacks are disabled by default, so enable them
    CallbackMode(BlinkRedLed,   ENABLED);
    CallbackMode(BlinkGreenLed, ENABLED);

    _EINT();
    LPM0;
}

void BlinkRedLed(void)
{
    RED_LED_TOGGLE();
}

void BlinkGreenLed(void)
{
    GREEN_LED_TOGGLE();
}
