/**
@file pwm.h
@brief Definitions, data structues and prototypes for pulse width modulation
@todo It would be nice to also generate PWM on timer B
@author Joe Brown
*/
#ifndef PWM_H
#define PWM_H

/** @brief A pwm output which stores the current frequency and duty cycle of each
channel*/
typedef struct
{
    uint32_t frequency;
    uint8_t duty;
} PwmOutput;

/**
@brief Initialize the PWM hardware channel
@details
Init TIMER 0 or 1 with SMCLK as the source in UP mode. Intially set the duty
cycle and period to 0.
@param[in] channel channel to enable pwm generation
*/
extern void PwmInit(uint8_t channel);

/**
@brief Configure the period of the specified pwm channel
@details
Set the period pwm channel while maintaining the duty cycle percentage.
cycle and period to 0.
@param[in] channel channel configure
@param[in] frequency frequency in hz to oscillate
*/
extern void PwmSetPeriod(uint8_t channel, uint32_t frequency);

/**
@brief Configure the duty cycle of the specified pwm channel
@details
Set the duty cycle of the  pwm channel
@param[in] channel channel configure
@param[in] duty duty cycle in % to configure
*/
extern void PwmSetDuty(uint8_t channel, uint8_t duty);

#endif // PWM_H
