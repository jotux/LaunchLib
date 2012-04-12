#include "launchlib.h"

void HardwareInit(void)
{
    IO_DIRECTION(LED1,OUTPUT);
    IO_DIRECTION(SW1,INPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();

    // Init P1.5 as ADC channel
    AdcInit(5);
    _EINT();

    while(1)
    {
        if (AdcRead(5) > 512) // P1.5 > 1.25Vdc?
        {
            LED_ON(1);
        }
        else
        {
            LED_OFF(1);
        }
    }
}
