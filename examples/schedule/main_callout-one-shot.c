#include "src/global.h"
#include "src/hardware.h"
#include "src/schedule.h"
#include "src/interrupt.h"

void QueueButton(void);
void ToggleGreenLed(void);

void HardwareInit(void)
{
    IO_DIRECTION(RED_LED,OUTPUT);
    RED_LED_OFF();

    IO_DIRECTION(GREEN_LED,OUTPUT);
    GREEN_LED_OFF();

    IO_DIRECTION(SW1,INPUT);
}

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
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
    CalloutRegister(ToggleGreenLed, (5 * _second));
    CalloutRegister(ToggleGreenLed, (5 * _second) + (100 * _millisecond));
    CalloutRegister(ToggleGreenLed, (5 * _second) + (200 * _millisecond));
    CalloutRegister(ToggleGreenLed, (5 * _second) + (300 * _millisecond));
    CalloutRegister(ToggleGreenLed, (5 * _second) + (400 * _millisecond));
    CalloutRegister(ToggleGreenLed, (5 * _second) + (500 * _millisecond));
}

void ToggleGreenLed(void)
{
    GREEN_LED_TOGGLE();
}
