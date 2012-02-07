#include "src/global.h"
#include "src/hardware.h"
#include "src/callback.h"
#include "src/init.h"

void BlinkRedLed(void);
void BlinkGreenLed(void);

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
    HardwareInit();

    // Init the timer run from the watchdog
    CallbackTimerInit();
    // register functions and define their period
    CallbackRegister(BlinkRedLed,   100ul * _millisecond);
    CallbackRegister(BlinkGreenLed, 101ul * _millisecond);
    // callbacks are disabled by default, so enable them
    CallbackMode(BlinkRedLed,   ENABLED);
    CallbackMode(BlinkGreenLed, ENABLED);

    _EINT();
    LPM0;
}

void BlinkRedLed(void)
{
    RED_LED_TOGGLE();
}

void BlinkGreenLed(void)
{
    GREEN_LED_TOGGLE();
}
