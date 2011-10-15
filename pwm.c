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
	switch(channel)
	{
		case 0:
		    pwm_out[channel].frequency = CLOCK_DCO / frequency;		    
			TA0CCR0 = pwm_out[channel].frequency;
			// now fix the duty cycle
			
			break;
		case 1:
		    pwm_out[channel].frequency = CLOCK_DCO / frequency;	
			TA1CCR0 = pwm_out[channel].frequency;
			break;
		default:
			break;
	}	
}

void PwmSetDuty(uint8_t channel, uint16_t duty)
{
	// duty is in percent
	switch(channel)
	{
		case 0:
		    pwm_out[channel].duty = duty;
			break;
		case 1:
		    pwm_out[channel].duty = duty;
			break;
		default:
			break;
	}	
}
