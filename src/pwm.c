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
#define TA_INIT_CASE(x)                 \
    case x:                             \
        TA##x##CCR0 = 0;                \
        TA##x##CCTL1 = OUTMOD_7;        \
        TA##x##CCR1 = 0;                \
        TA##x##CTL = TASSEL_2 + MC_1;   \
        break;

    switch(channel)
    {
        TA_INIT_CASE(0);
        TA_INIT_CASE(1);
    }
}

// Max frequency is DCO/2 but the duty cycle is between 1-100, which means if
// you run faster than 100/DCO your duty cycle resolution will suffer.
// Min frequency is ((DCO/(8))/(2^16)) = DCO/2^18
void PwmSetFrequency(uint8_t channel, uint32_t frequency)
{
    uint16_t freq_to_set = 0;
    uint32_t input_clock = 0;
    uint8_t  is_divided = FALSE;

    if (frequency == 0)
    {
        PwmInit(channel);
        return;
    }

    // check if we need to divide the timer A clock(DCO/freq > 2^16)
    else if ((CLOCK_DCO / frequency) > 0xFFFF)
    {
        // calculate the new input clock
        input_clock = CLOCK_DCO / 8;
        is_divided = TRUE;
    }
    else
    {
        input_clock = CLOCK_DCO;
    }

    // calculate the frequency based on the DCO speed
    freq_to_set = input_clock / frequency;

    pwm_out[channel].frequency = freq_to_set;

#define TACCR0_CASE(x)              \
    case x:                         \
        if (is_divided)             \
        {                           \
            TA##x##CTL |= ID_3;     \
        }                           \
        else                        \
        {                           \
            TA##x##CTL &= ~ID_3;    \
        }                           \
        TA##x##CCR0 = freq_to_set;  \
        break;

    switch (channel)
    {
        TACCR0_CASE(0);
        TACCR0_CASE(1);
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

#define TACCR1_CASE(x)              \
    case x:                         \
        TA##x##CCR1 = duty_to_set;  \
        break;

    switch (channel)
    {
        TACCR1_CASE(0);
        TACCR1_CASE(1);
    }
}
