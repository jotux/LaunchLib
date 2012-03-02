#include "src/global.h"
#include "src/hardware.h"
#include "src/adc.h"

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
    HardwareInit();

    // Init P1.5 as ADC channel
    AdcInit(5);
    _EINT();

    while(1)
    {
        if (AdcRead(5) > 512) // P1.5 > 1.25Vdc?
        {
            RED_LED_ON();
        }
        else
        {
            RED_LED_OFF();
        }
    }
}
