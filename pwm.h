#ifndef PWM_H
#define PWM_H

void PwmInit(uint8_t channel, uint16_t period);
void PwmSet(uint8_t channel, uint16_t duty);

#endif //PWM_H
