#include "global.h"
#include "hardware.h"
#include "timer.h"
#include "init.h"
#include "callback.h"
#include "pwm.h"
#include "adc.h"

void BlinkRedLed(void);
void Delay(uint32_t delay_time);

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);

    CallbackTimerInit();
    HardwareInit();
    PwmInit(0);
    PwmInit(1);
	AdcInit(3);
	
    CallbackRegister(BlinkRedLed, 100ul * _millisecond);    
    CallbackMode(BlinkRedLed, ENABLED);

    PwmSetPeriod(0,1023);
    PwmSetDuty(0,512);
    PwmSetPeriod(1,1023);
    PwmSetDuty(1,512);

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
