#include "launchlib.h"

void BlinkLed1(void);
void ToggleEnable(void);

void HardwareInit(void)
{
    IO_DIRECTION(LED1,OUTPUT);
    IO_DIRECTION(SW1,INPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();

    // Init the timer
    ScheduleTimerInit();
    // register a function and define its period
    CallbackRegister(BlinkLed1, 100ul * _MILLISECOND);
    // attach function to SW1 falling edge interrupt
    InterruptAttach(SW1_PORT,SW1_PIN,ToggleEnable,FALLING_EDGE);

    _EINT();
    LPM0;
}

void BlinkLed1(void)
{
    LED_TOGGLE(1);
}

void ToggleEnable(void)
{
    static uint8_t tog = 0;
    if (tog == FALSE)
    {
        tog = TRUE;
        CallbackMode(BlinkLed1, ENABLED);
    }
    else
    {
        tog = FALSE;
        LED_OFF(1);
        CallbackMode(BlinkLed1, DISABLED);
    }
}
