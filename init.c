#include "global.h"
#include "init.h"
#include "hardware.h"

void HardwareInit(void)
{
    MAKE_OUTPUT(RED_LED);
    RED_LED_OFF();
    
    MAKE_OUTPUT(PWM_0);
    MAKE_SPECIAL(PWM_0);
    
    MAKE_OUTPUT(PWM_1);
    MAKE_SPECIAL(PWM_1);
}
