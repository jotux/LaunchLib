#include "../../launchlib.h"
#include "../../hw.h"

void HardwareInit(void)
{
    IO_DIRECTION(LED1,GPIO_OUTPUT);
    IO_DIRECTION(SW1,GPIO_INPUT);
}

void main(void)
{
    WD_STOP();
    ClockConfig(16);
    HardwareInit();

    AdcInit();
    _EINT();

    while(1)
    {
        if (AdcRead(5) > 512) // P1.5 > 1.25Vdc?
        {
            LED1_ON();
        }
        else
        {
            LED1_OFF();
        }
    }
}
