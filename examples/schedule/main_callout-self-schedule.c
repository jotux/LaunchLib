#include "src/global.h"
#include "src/hardware.h"
#include "src/schedule.h"
#include "src/interrupt.h"

void ToggleGreenLed(void);

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
    ScheduleTimerInit();
    HardwareInit();

    // call ToggleGreenLed and it will continue to reschedule itself
    ToggleGreenLed();
    _EINT();
    LPM0;
}



void ToggleGreenLed(void)
{
    static uint8_t cnt = 0;
    GREEN_LED_TOGGLE();
    if (cnt++ < 20)
    {
        CalloutRegister(ToggleGreenLed, (100ul * _millisecond));
    }
}
