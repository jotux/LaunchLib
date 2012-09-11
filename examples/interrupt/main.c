#include "../../launchlib.h"
#include "../../hw.h"

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);
    IO_DIRECTION(SW1,GPIO_INPUT);
}

void ToggleLed1(void);

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();

    // attach function to SW1 falling edge interrupt
    InterruptAttach(GPIO(SW1),ToggleLed1,FALLING);

    _EINT();
    LPM0;
}

void ToggleLed1(void)
{
    LED1_TOGGLE();
}
