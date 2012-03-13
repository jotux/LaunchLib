#include "launchlib/global.h"
#include "launchlib/hardware.h"
#include "launchlib/schedule.h"
#include "launchlib/interrupt.h"
#include "launchlib/clock.h"

void QueueButton(void);
void ToggleLed2(void);

void HardwareInit(void)
{
    IO_DIRECTION(LED1,OUTPUT);
    IO_DIRECTION(LED2,OUTPUT);
    IO_DIRECTION(SW1,INPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    ScheduleTimerInit();
    HardwareInit();

    // attach function to SW1 falling edge interrupt
    InterruptAttach(SW1_PORT, SW1_PIN, QueueButton, FALLING_EDGE);
    _EINT();
    LPM0;
}

void QueueButton(void)
{
    // when the interrupt fires queue a few callouts to make the LED toggle
    CalloutRegister(ToggleLed2, (5 * _second));
    CalloutRegister(ToggleLed2, (5 * _second) + (100 * _millisecond));
    CalloutRegister(ToggleLed2, (5 * _second) + (200 * _millisecond));
    CalloutRegister(ToggleLed2, (5 * _second) + (300 * _millisecond));
    CalloutRegister(ToggleLed2, (5 * _second) + (400 * _millisecond));
    CalloutRegister(ToggleLed2, (5 * _second) + (500 * _millisecond));
}

void ToggleLed2(void)
{
    LED_TOGGLE(2);
}
