#include "../../launchlib.h"
#include "../../hw.h"
#include "../../launchlib/tone.h"

#define SIMPLE_EXAMPLE
#define TONE_EXAMPLE

#if defined(SIMPLE_EXAMPLE)

void HardwareInit(void)
{
    IO_DIRECTION(SW1,GPIO_INPUT);

    IO_DIRECTION(PWM0,GPIO_OUTPUT);
    IO_FUNCTION(PWM0,GPIO_FUN_SPECIAL);

    IO_DIRECTION(PWM1,GPIO_OUTPUT);
    IO_FUNCTION(PWM1,GPIO_FUN_SPECIAL);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();

    // Init PWM channel 0 (P1.2). Pwm output pins are specific to the device
    // therefore we reference the channel number instead of the pin name
    PwmInit(0);

    // Configure period (Hz) and duty cycle (%) for the channel
    PwmSetFrequency(0,10);
    PwmSetDuty(0,50);

    _EINT();

    uint32_t cnt = 0;
    while(1)
    {
        // if P1.3 switch is down sweep frequency up to 100kHz while maintaining
        // 50% duty cycle
        if (IO_IN(SW1) && cnt < 100000)
        {
            cnt++;
        }
        // if P1.3 is up, sweep back to 10kHz while maintaining duty cycle
        else if (cnt > 10000)
        {
            cnt--;
        }
        PwmSetFrequency(0,cnt);
    }
}

#elif defined(TONE_EXAMPLE)

uint16_t tempo = 100;

enum NOTE_TYPE
{
    THIRTYSECOND = 32,
    SIXTEENTH    = 16,
    EIGHTH       = 8,
    QUARTER      = 4,
    HALF         = 2,
    WHOLE        = 1
};

void Rest(enum NOTE_TYPE type)
{
    Delay((320000 * _MILLISECOND) / (tempo * type));
}

void PlayNote(uint16_t note, enum NOTE_TYPE type)
{
    // min/max freq = 122Hz/80KHz so lowest note will be B2
    PwmSetFrequency(0,note);
    // for effect
    LED1_ON();
    // The length of one measure is (4 / TEMPO) minutes = (4000 / TEMPO) ms
    Rest(type);
    PwmSetFrequency(0,0);
    LED1_OFF();
}

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);
    LED1_OFF();
    IO_DIRECTION(LED2,GPIO_OUTPUT);
    LED2_OFF();
    IO_DIRECTION(PWM0,GPIO_OUTPUT);
    IO_FUNCTION(PWM0,GPIO_FUN_SPECIAL);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();
    ScheduleTimerInit();

    // Init channel 0
    PwmInit(0);

    _EINT();

    PwmSetDuty(0,50);

    // Start the music
    while(1)
    {
        PlayNote(NOTE_G4,QUARTER);
        PlayNote(NOTE_D5,QUARTER);
        PlayNote(NOTE_AS4,QUARTER);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_G4,EIGHTH);
        PlayNote(NOTE_AS4,EIGHTH);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_G4,EIGHTH);
        PlayNote(NOTE_FS4,EIGHTH);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_D4,QUARTER);
        PlayNote(NOTE_G4,EIGHTH);
        PlayNote(NOTE_D4,EIGHTH);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_D4,EIGHTH);
        PlayNote(NOTE_AS4,EIGHTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_D4,EIGHTH);
        PlayNote(NOTE_G4,EIGHTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_AS4,EIGHTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_FS4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_DS5,SIXTEENTH);
        PlayNote(NOTE_F5,SIXTEENTH);
        PlayNote(NOTE_DS5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_F5,SIXTEENTH);
        PlayNote(NOTE_DS5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_CS5,SIXTEENTH);
        PlayNote(NOTE_DS5,SIXTEENTH);
        PlayNote(NOTE_D5,EIGHTH);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_D5,EIGHTH);
        PlayNote(NOTE_DS5,EIGHTH);
        PlayNote(NOTE_D4,QUARTER);
        PlayNote(NOTE_A4,QUARTER);
        PlayNote(NOTE_F4,QUARTER);
        PlayNote(NOTE_DS4,EIGHTH);
        PlayNote(NOTE_F5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_F5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_G5,EIGHTH);
        PlayNote(NOTE_F5,THIRTYSECOND);
        PlayNote(NOTE_G5,THIRTYSECOND);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_AS5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_F5,SIXTEENTH);
        PlayNote(NOTE_DS5,SIXTEENTH);
        PlayNote(NOTE_D4,EIGHTH);
        PlayNote(NOTE_F4,EIGHTH);
        PlayNote(NOTE_DS4,EIGHTH);
        PlayNote(NOTE_D4,EIGHTH);
        PlayNote(NOTE_CS4,EIGHTH);
        PlayNote(NOTE_DS4,EIGHTH);
        PlayNote(NOTE_A3,QUARTER);
        PlayNote(NOTE_F5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_CS5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_CS5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_D4,EIGHTH);
        PlayNote(NOTE_A3,EIGHTH);
        PlayNote(NOTE_DS4,EIGHTH);
        PlayNote(NOTE_A3,EIGHTH);
        PlayNote(NOTE_F4,EIGHTH);
        PlayNote(NOTE_DS4,SIXTEENTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_DS4,EIGHTH);
        PlayNote(NOTE_A3,EIGHTH);
        PlayNote(NOTE_F5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_CS5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_CS5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_CS5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_CS5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_D4,EIGHTH);
        PlayNote(NOTE_A3,SIXTEENTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_DS4,EIGHTH);
        PlayNote(NOTE_A3,SIXTEENTH);
        PlayNote(NOTE_DS4,SIXTEENTH);
        PlayNote(NOTE_F4,EIGHTH);
        PlayNote(NOTE_DS4,SIXTEENTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_DS4,SIXTEENTH);
        PlayNote(NOTE_A3,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_F5,EIGHTH);
        PlayNote(NOTE_G4,EIGHTH);
        PlayNote(NOTE_DS5,EIGHTH);
        PlayNote(NOTE_F4,EIGHTH);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_D5,EIGHTH);
        PlayNote(NOTE_F5,EIGHTH);
        PlayNote(NOTE_F4,SIXTEENTH);
        PlayNote(NOTE_DS4,SIXTEENTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_F4,SIXTEENTH);
        PlayNote(NOTE_DS4,SIXTEENTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_CS4,SIXTEENTH);
        PlayNote(NOTE_DS4,SIXTEENTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_A3,SIXTEENTH);
        PlayNote(NOTE_D4,SIXTEENTH);
        PlayNote(NOTE_DS4,SIXTEENTH);
        PlayNote(NOTE_F4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_DS5,EIGHTH);
        PlayNote(NOTE_A5,EIGHTH);
        PlayNote(NOTE_DS5,EIGHTH);
        PlayNote(NOTE_D5,EIGHTH);
        PlayNote(NOTE_G5,EIGHTH);
        PlayNote(NOTE_D5,EIGHTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_G4,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_D5,SIXTEENTH);
        PlayNote(NOTE_C5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_A5,SIXTEENTH);
        PlayNote(NOTE_AS4,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_FS5,SIXTEENTH);
        PlayNote(NOTE_G5,SIXTEENTH);
        PlayNote(NOTE_A4,SIXTEENTH);
        PlayNote(NOTE_FS5,SIXTEENTH);
        PlayNote(NOTE_DS5,SIXTEENTH);
        PlayNote(NOTE_FS5,SIXTEENTH);
        PlayNote(NOTE_A4,EIGHTH);
        PlayNote(NOTE_G4,EIGHTH);
        PlayNote(NOTE_FS4,EIGHTH);
        PlayNote(NOTE_D4,EIGHTH);
        PlayNote(NOTE_G4,QUARTER);
    }
}

#endif
