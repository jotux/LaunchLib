#include "init.h"
#include "hardware.h"
#include "global.h"

void InitHardware(void)
{
    MAKE_OUTPUT(RED_LED_PORT, RED_LED_PIN);
    RED_LED_OFF();
}
