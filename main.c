#include "global.h"
#include "hardware.h"
#include "timer.h"
#include "init.h"
#include "callback.h"

void BlinkRedLed(void);
void BlinkGreenLed(void);

void main(void)
{
     WD_STOP();
    
    TimerAInit();
    HardwareInit();
    
    CallbackRegister(BlinkRedLed, 101ul * _millisecond);
    CallbackRegister(BlinkGreenLed, 100ul * _millisecond);
    
    CallbackMode(BlinkRedLed, ENABLED);
    CallbackMode(BlinkGreenLed, ENABLED);
    
    _EINT();
    
    while(1) { continue; }
}

void BlinkRedLed(void)
{
    RED_LED_TOGGLE();
}

void BlinkGreenLed(void)
{
    GREEN_LED_TOGGLE();
}
