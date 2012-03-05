##A simple library for general peripheral control of MSP430 Launchpad populated with MSP430G2553.

##Current Features:
### - Scheduling mechanism
  - driven from 2ms watchdog timer
  - Callbacks
     - Periodic function scheduling
  - Callouts
     - One-shot function run
     - Self-scheduling functions

### - PWM
  - Generation on Timer 0/1

### - ADC

### - GPIO Interrupt handler
  - Attach GPIO pin interrupts to functions

### - Basic State machine handler
  - Easily configurable state machines
  - Event queueing
  - Enter and Exit events for each state
  - State transisions configured by single table

### - Uart
   - Selectable blocking/non-blocking RX/TX
   - Built-in compact printf functionality
 
##TODO
 - I2C
 - SPI

Code compatible with CCS and IAR.