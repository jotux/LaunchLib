#include "global.h"
#include "init.h"
#include "hardware.h"

void HardwareInit(void)
{
    IO_DIRECTION(RED_LED,OUTPUT);
    RED_LED_OFF();

    IO_DIRECTION(GREEN_LED,OUTPUT);
    GREEN_LED_OFF();

    IO_DIRECTION(PWM_0,OUTPUT);
    IO_FUNCTION(PWM_0,SPECIAL);

    IO_DIRECTION(PWM_1,OUTPUT);
    IO_FUNCTION(PWM_1,SPECIAL);
}
