##An easy-to-use library to help kickstart your launchpad development.
![Pew Pew Pew](http://jotux.github.com/LaunchLib/logo.png)

### MSP430G2553 currently required to use all functionality.

##Docs can be found [here](http://jotux.github.com/LaunchLib/docs/index.html)
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

##Examples
  - To run examples copy the example file to the top level director and rename it to main.c.
 
##TODO
 - I<sup>2</sup>C
 - SPI

Code compatible with CCS and IAR.