#include "global.h"
#include "pwm.h"
#include "hardware.h"

PwmOutput pwm_out[2];

void PwmInit(uint8_t channel)
{
	switch(channel)
	{
		case 0:
			TA0CCR0 = 0; // period
			TA0CCTL1 = OUTMOD_7;
			TA0CCR1 = 0; // duty
			TA0CTL = TASSEL_2 + MC_1;
			break;
		case 1:
			TA1CCR0 = 0;
			TA1CCTL1 = OUTMOD_7;
			TA1CCR1 = 0;
			TA1CTL = TASSEL_2 + MC_1;
			break;
		default:
			break;
	}
}

void PwmSetPeriod(uint8_t channel, uint16_t frequency)
{
    uint16_t freq_to_set = CLOCK_DCO / frequency;
    
    pwm_out[channel].frequency = freq_to_set;
    if (channel)
    {    
	    TA1CCR0 = freq_to_set;
    }
	else
    {
        TA0CCR0 = freq_to_set;
    }
    PwmSetDuty(channel,pwm_out[channel].duty);   // fix the duty cycle    
}

void PwmSetDuty(uint8_t channel, uint16_t duty)
{
    uint16_t duty_to_set = (pwm_out[channel].duty * pwm_out[channel].frequency) / 100;
    
	pwm_out[channel].duty = duty;
    if (channel)
    {
        TA1CCR1 = duty_to_set;
    }
    else
    {
        TA0CCR1 = duty_to_set;
    }
}
