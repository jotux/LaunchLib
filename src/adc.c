#include "global.h"
#include "adc.h"

void AdcInit(uint16_t channel_to_enable)
{
    ADC10CTL0 &= ~ENC;                      // disable conversion
    ADC10AE0  |= _BV(channel_to_enable);    // enable the channel
    ADC10CTL0  = SREF_1;                    // Vref = Vref+ to gnd
    ADC10CTL0 |= ADC10SHT_3;                // 64 clks to sample data
    ADC10CTL0 |= REF2_5V;                   // Vref+ = 2.5V internal
    ADC10CTL0 |= REFON;                     // enable internal reference
    ADC10CTL0 |= ADC10ON;                   // enable ADC
}

uint16_t AdcRead(uint16_t channel)
{
	ADC10CTL0 &= ~ ENC;                     // disable conversion
	ADC10CTL1 |= channel << ADC_INCH_SHIFT; // select channel
    ADC10CTL0 |= ENC + ADC10SC;             // Sampling and conversion start
    while (ADC10CTL1 & ADC10BUSY);          // wait for finish
    return (ADC10MEM & ADC_MASK);
}
