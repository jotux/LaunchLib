#include "src/global.h"
#include "src/hardware.h"
#include "src/interrupt.h"

void ToggleRedLed(void);

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

    // attach function to SW1 falling edge interrupt
    AttachInterrupt(SW1_PORT,SW1_PIN,ToggleRedLed,FALLING_EDGE);

    _EINT();
    LPM0;
}

void ToggleRedLed(void)
{
    RED_LED_TOGGLE();
}
