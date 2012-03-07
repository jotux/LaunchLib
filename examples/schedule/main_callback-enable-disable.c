#include "src/global.h"
#include "src/hardware.h"
#include "src/schedule.h"

void BlinkRedLed(void);
void ToggleBlinkRedLed(void);

void HardwareInit(void)
{
    IO_DIRECTION(RED_LED,OUTPUT);
    RED_LED_OFF();

    IO_DIRECTION(SW1,INPUT);
}

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
    HardwareInit();

    // Init the timer
    ScheduleTimerInit();
    // register a function and define its period
    CallbackRegister(BlinkRedLed,   100ul * _millisecond);
    // attach function to SW1 falling edge interrupt
    InterruptAttach(SW1_PORT,SW1_PIN,ToggleRedLed,FALLING_EDGE);

    _EINT();
    LPM0;
}

void BlinkRedLed(void)
{
    RED_LED_TOGGLE();
}

void ToggleBlinkRedLed(void)
{
    static uint8_t tog = 0;
    if (tog == FALSE)
    {
        tog = TRUE;
        CallbackMode(BlinkRedLed, ENABLED);
    }
    else
    {
        tog = FALSE;
        CallbackMode(BlinkRedLed, DISABLED);
    }
}
