#include "global.h"
#include "init.h"
#include "hardware.h"

void HardwareInit(void)
{
    MAKE_OUTPUT(RED_LED_PORT, RED_LED_PIN);
    MAKE_OUTPUT(GREEN_LED_PORT, GREEN_LED_PIN);
    RED_LED_OFF();
    GREEN_LED_OFF();
}
