#include "launchlib.h"

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
    CalloutRegister(ToggleLed2, (5 * _SECOND));
    CalloutRegister(ToggleLed2, (5 * _SECOND) + (100 * _MILLISECOND));
    CalloutRegister(ToggleLed2, (5 * _SECOND) + (200 * _MILLISECOND));
    CalloutRegister(ToggleLed2, (5 * _SECOND) + (300 * _MILLISECOND));
    CalloutRegister(ToggleLed2, (5 * _SECOND) + (400 * _MILLISECOND));
    CalloutRegister(ToggleLed2, (5 * _SECOND) + (500 * _MILLISECOND));
}

void ToggleLed2(void)
{
    LED_TOGGLE(2);
}
