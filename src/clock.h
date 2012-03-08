/**
@file adc.h
@brief Definitions for clock config helper macros
@author Joe Brown
*/
#ifndef CLOCK_H
#define CLOCK_H

/**
@brief Configure the clocks for use
@param[in] mhz the clock speed
*/
extern inline void ClockConfig(uint8_t mhz)
{
    /** @todo should we save the DCO value somewhere? */
#ifdef __MSP430G2553__
    // Calibrated DCO values are 1,8,12,16
#define CLOCK_CASE(x)               \
    case x:                         \
        BCSCTL1 = CALBC1_##x##MHZ;  \
        DCOCTL  = CALDCO_##x##MHZ;  \
        break;

    switch(mhz)
    {
        CLOCK_CASE(1);
        CLOCK_CASE(8);
        CLOCK_CASE(12);
        CLOCK_CASE(16);
    }

#elif __MSP430FR5739__
#define FR5739_CLOCK_PASSWORD 0xA5
    // Calibrated DCO values are 5.33,6.67,8,16,20,24
    // 8,16,20,24 are avaiable here
    CSCTL0_H = FR5739_CLOCK_PASSWORD;
    switch(mhz)
    {
       case 8:
           CSCTL1 = DCOFSEL0 + DCOFSEL1;
           break;
       case 16:
           CSCTL1 = DCORSEL;
           break;
       case 20:
           CSCTL1 = DCORSEL + DCOFSEL0;
           break;
       case 24:
           CSCTL1 = DCORSEL + DCOFSEL0 + DCOFSEL1;
           break;
    }
    /** @todo Add more control over ACLK, currently only set to VLO */
    // ACLK source = VLO
    CSCTL2  = SELA_0;
    // SMCLK source = DCO
    CSCTL2 |= SELS_3;
    // MCLK source = DCO
    CSCTL2 |= SELM_3;
    // ACLK divider = 1
    CSCTL3  = DIVA_0;
    // SMCLK divider = 1
    CSCTL3 |= DIVS_0;
    // MCLK divider = 1
    CSCTL3 |= DIVM_0;
#endif

}

#endif
