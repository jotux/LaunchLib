##An easy-to-use library to help kickstart your launchpad development.
![Pew Pew Pew](http://jotux.github.com/LaunchLib/logo.png)

### Support for MSP430G2553 and MSP430FR5739

##Docs can be found [here](http://jotux.github.com/LaunchLib/docs/index.html)

##Getting started

 - Get most recent Code Composer Studio (CCS) [here](http://processors.wiki.ti.com/index.php/Download_CCS)
 - Clone the Code
 - Create a new CCS project
 - Copy examples files to the top level directory and rename to main.c
 - Enjoy

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
 
## LICENSE

All code is released under the supplied (MIT) license unless otherwise stated.

##TODO
 - I<sup>2</sup>C
 - SPI
 - More hardware support

Code compatible with CCS and IAR.
