/**
@file adc.h
@brief Definitions, data structues and prototypes for analog-to-digital conversion
@author Joe Brown
*/
#ifndef ADC_H
#define ADC_H

/**
@brief Initialize the adc hardware
@details
Initialize the ADC hardware for 64-clk sample with internal 2.5V reference
*/
extern void AdcInit(void);

/**
@brief Read the analog value of a channel
@details
Start conversion on an adc channel and return the value
@param[in] channel channel to read
@return result of conversion
*/
extern uint16_t AdcRead(uint16_t channel);

#endif // ADC_H
