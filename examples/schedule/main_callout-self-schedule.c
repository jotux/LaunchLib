#include "src/global.h"
#include "src/hardware.h"
#include "src/schedule.h"
#include "src/interrupt.h"
#include "src/clock.h"

void ToggleLed2(void);

void HardwareInit(void)
{
    IO_DIRECTION(LED1,OUTPUT);
    IO_DIRECTION(LED2,OUTPUT);
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
    LED_TOGGLE(2);
    CalloutRegister(ToggleLed2, (100ul * _millisecond));
}
