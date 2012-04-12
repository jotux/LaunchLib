#include "launchlib.h"

void BlinkLed1(void);

void HardwareInit(void)
{
    IO_DIRECTION(LED1,OUTPUT);
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
    LED_TOGGLE(1);
    CalloutRegister(BlinkLed1, (1ul * _SECOND));
}
