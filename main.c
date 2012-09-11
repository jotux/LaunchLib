#include "launchlib.h"
#include "hw.h"

// This is a sample main file. You can use this as a starting point for your own
// projects or take a look at the example projects for ideas on how to use
// launchlib.

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);
    IO_DIRECTION(LED2,GPIO_OUTPUT);
}

void BlinkLeds(void)
{
    LED1_TOGGLE();
    LED2_TOGGLE();
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    ScheduleTimerInit();
    HardwareInit();

    CallbackRegister(BlinkLeds, 500ul * _MILLISECOND);
    CallbackMode(BlinkLeds,ENABLED);
    _EINT();

    while (1)
    {

    }
}
