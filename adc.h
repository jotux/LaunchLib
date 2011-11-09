#ifndef ADC_H
#define ADC_H

void AdcInit(uint16_t channel_to_enable);
uint16_t AdcRead(uint16_t channel);

#define ADC_INCH_SHIFT   12
#define ADC_MASK         0x03FF
#define ADC_CHANNEL_MASK 0x0F

#endif
