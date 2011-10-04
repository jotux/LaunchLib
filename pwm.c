#include "global.h"
#include "pwm.h"
#include "hardware.h"

void PwmInit(uint8_t channel, uint16_t period)
{
	if (period > 1023 || period == 0)
	{
		return;
	}
	switch(channel)
	{
		case 0:
			TA0CCR0 = period;
			TA0CCTL1 = OUTMOD_7;
			TA0CCR1 = 0;
			TA0CTL = TASSEL_2 + MC_1;
			break;
		case 1:
			TA1CCR0 = period;
			TA1CCTL1 = OUTMOD_7;
			TA1CCR1 = 0;
			TA1CTL = TASSEL_2 + MC_1;
			break;
		default:
			break;
	}
}

void PwmSet(uint8_t channel, uint16_t duty)
{
	switch(channel)
	{
		case 0:
			TA0CCR1 = duty;
			break;
		case 1:
			TA1CCR1 = duty;
			break;
		default:
			break;
	}	
}
