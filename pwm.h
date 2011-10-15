#ifndef PWM_H
#define PWM_H

void PwmInit(uint8_t channel);
void PwmSetPeriod(uint8_t channel, uint16_t frequency);
void PwmSetDuty(uint8_t channel, uint16_t duty);


typedef struct
{
	uint16_t frequency;
	uint16_t duty;
} PwmOutput;

#endif //PWM_H
