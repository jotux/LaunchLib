###A simple library for general peripheral control of MSP430 Launchpad populated with MSP430G2553.

###Current Features:
    * Callbacks (driven from 2ms watchdog timer)
        -(8 + num_callbacks * 12)b ram
        -282b flash
    * PWM generation on Timer0/1
        -12b ram
        -184b flash
    * ADC
        -n/a ram
        -88b flash
    * GPIO Interrupt handler
        -28b ram
        -270b flash
    * Basic State machine handler
        -(6 + number_of_events)b ram in module
        -(6 * num_transitions)b const in main
        -2b ram in main
        -246b flash

###TODO
 * I2C
 * UART

Code compatible with CCS and IAR.