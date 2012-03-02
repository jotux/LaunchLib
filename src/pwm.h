#ifndef PWM_H
#define PWM_H

extern void PwmInit(uint8_t channel);
extern void PwmSetPeriod(uint8_t channel, uint32_t frequency);
extern void PwmSetDuty(uint8_t channel, uint8_t duty);


typedef struct
{
    uint32_t frequency;
    uint8_t duty;
} PwmOutput;

#endif //PWM_H
