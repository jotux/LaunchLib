#include "src/global.h"
#include "src/hardware.h"
#include "src/interrupt.h"
#include "src/clock.h"

void ToggleLed1(void);

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

    // attach function to SW1 falling edge interrupt
    InterruptAttach(SW1_PORT,SW1_PIN,ToggleLed1,FALLING_EDGE);

    _EINT();
    LPM0;
}

void ToggleLed1(void)
{
    LED_TOGGLE(1);
}
