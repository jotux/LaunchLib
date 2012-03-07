/** 
@file pwm.c
@brief Hardware pulse width modulation handler
@author Joe Brown
*/
#include "global.h"
#include "pwm.h"
#include "hardware.h"

/** @brief table of channel configurations */
static PwmOutput pwm_out[NUM_PWM_CHANNELS];

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


// Max frequency is DCO/1 but the duty cycle is between 1-100, which means if
// you run faster than 100/DCO your duty cycle resolution will suffer. Max
// frequecy for 1% resolution is DCO/100 = 160KHz
void PwmSetPeriod(uint8_t channel, uint32_t frequency)
{
    // calculate the frequency based on the DCO speed
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
    // fix the duty cycle
    PwmSetDuty(channel,pwm_out[channel].duty);
}

// Duty cycle resolution = ((frequency * 100) / DCO) %
// Example 1, f = 10kHz,  DCO = 16MHz, (10kHz * 100)  / 16MHz = 0.0625% ~ 10bit
//         2, f = 160kHz, DCO = 16MHz, (160kHz * 100) / 16MHz = 1%      ~  6bit
//         3, f = 500kHz, DCO = 16MHz, (500kHz * 100) / 16MHz = 3.125%  ~  5bit
void PwmSetDuty(uint8_t channel, uint8_t duty)
{
    uint32_t duty_to_set = (duty * pwm_out[channel].frequency) / 100;

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
