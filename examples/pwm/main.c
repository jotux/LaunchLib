#include "src/global.h"
#include "src/hardware.h"
#include "src/pwm.h"
#include "src/clock.h"

void HardwareInit(void)
{
    IO_DIRECTION(SW1,INPUT);

    IO_DIRECTION(PWM0,OUTPUT);
    IO_FUNCTION(PWM0,SPECIAL);

    IO_DIRECTION(PWM1,OUTPUT);
    IO_FUNCTION(PWM1,SPECIAL);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();

    // Init PWM channel 0 (P1.2). Pwm output pins are specific to the device
    // therefore we reference the channel number instead of the pin name
    PwmInit(0);

    // Configure period (Hz) and duty cycle (%) for the channel
    PwmSetFrequency(0,10);
    PwmSetDuty(0,50);

    _EINT();

    uint32_t cnt = 0;
    while(1)
    {
        // if P1.3 switch is down sweep frequency up to 100kHz while maintaining
        // 50% duty cycle
        if (IO_IN(SW1) && cnt < 100000)
        {
            cnt++;
        }
        // if P1.3 is up, sweep back to 10kHz while maintaining duty cycle
        else if (cnt > 10000)
        {
            cnt--;
        }
        PwmSetFrequency(0,cnt);
    }
}
