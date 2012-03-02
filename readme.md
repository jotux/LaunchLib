###A simple library for general peripheral control of MSP430 Launchpad populated with MSP430G2553.

###Current Features:
    * Scheduling mechanism (driven from 2ms watchdog timer)
        *282b flash
        *Callbacks ( Periodic function scheduling)
            *(8 + num_callbacks * 12)byte ram
        *Callouts(one-shot function run or self-scheduling functions)
            *(1 + num_callouts * 6)byte ram
    * PWM generation on Timer 0/1
        *12b ram
        *184b flash
    * ADC
        *88b flash
    * GPIO Interrupt handler (Attach GPIO pin interrupts to functions)
        *28b ram
        *270b flash
    * Basic State machine handler (easily configurable state machines)
        *(6 + number_of_events)byte ram in module
        *(6 * num_transitions)byte const in main
        *2b ram in main
        *246b flash
    * Uart (selectable blocking or non-blocking rx/tx)
        *(size_of_rx_buf + size_of_tx_buf)byte ram in module
        *764/486 byte flash for non-blocking/blocking

###TODO
 * I2C

Code compatible with CCS and IAR.