#include "global.h"
#include "hardware.h"
#include "timer.h"
#include "init.h"
#include "callback.h"
#include "pwm.h"

void BlinkRedLed(void);
void Delay(uint32_t delay_time);

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
       
    CallbackTimerInit();
    HardwareInit();
    PwmInit(0,1023);
    PwmInit(1,1023);
    
    CallbackRegister(BlinkRedLed, 100ul * _millisecond);    
    CallbackMode(BlinkRedLed, ENABLED);
    
    PwmSet(0,0);
    PwmSet(1,256);
    
    _EINT();
}

void Delay(uint32_t delay_time)
{
    uint32_t start_time = now;
    while(now < start_time + delay_time);
}

void BlinkRedLed(void)
{
	RED_LED_TOGGLE();
}
