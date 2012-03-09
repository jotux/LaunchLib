#include "src/global.h"
#include "src/hardware.h"
#include "src/pwm.h"
#include "src/clock.h"
#include "src/tone.h"
#include "src/delay.h"
#include "src/schedule.h"

#define TEMPO 60 // BPM

enum NOTE_TYPE
{
    SIXTEENTH = 16,
    EIGHTH    = 8,
    QUARTER   = 4,
    HALF      = 2,
    WHOLE     = 1
};

void PlayNote(uint16_t note, enum NOTE_TYPE type)
{
    // min/max freq = 122Hz/80KHz so lowest note will be B2
    PwmSetFrequency(0,note);
    // for effect
    LED_ON(1);
    // The length of one measure is (4 / TEMPO) minutes = (4000 / TEMPO) ms
    Delay((4000 * _millisecond) / (TEMPO * type));
    PwmSetFrequency(0,0);
    LED_OFF(1);
}

void Rest(enum NOTE_TYPE type)
{
    Delay((4000 * _millisecond) / (TEMPO * type));
}

void HardwareInit(void)
{
    IO_DIRECTION(PWM0,OUTPUT);
    IO_FUNCTION(PWM0,SPECIAL);
}

void main(void)
{
    WD_STOP();
    ClockConfig(1);
    HardwareInit();
    ScheduleTimerInit();

    // Init channel 0
    PwmInit(0);

    _EINT();

    PwmSetDuty(0,50);

    // Start the music
    while(1)
    {
        PlayNote(NOTE_C4,QUARTER);
        Rest(HALF);
        PlayNote(NOTE_D4,QUARTER);
        Rest(HALF);
        PlayNote(NOTE_E4,QUARTER);
        Rest(HALF);
        PlayNote(NOTE_F4,QUARTER);
        Rest(WHOLE);
    }
    LPM0;
}
