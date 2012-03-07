/** 
@file interrupt.c
@brief GPIO interrupt handler
@author Joe Brown
*/
#include "global.h"
#include "interrupt.h"
#include "hardware.h"

/** @brief table of function pointers attached to port1 GPIO pins*/
static InterruptFn p1_int_table[NUM_P1_INTS];
/** @brief table of function pointers attached to port2 GPIO pins*/
static InterruptFn p2_int_table[NUM_P2_INTS];

// Note: functions called from GPIO interrupts have no access to timer-based
// facilities (like the global "now" variable used for timing). The current
// Delay() implementation will also not work as it relies on timers.
void InterruptAttach(uint8_t port, uint8_t pin, InterruptFn func, enum IoEdge type)
{
    switch (port)
    {
        case 1:
            p1_int_table[pin] = func;   // save the function pointer
            P1IFG &= ~_BV(pin);
            P1IE |= _BV(pin);           // interrupt enabled
            if (type == FALLING_EDGE)
            {
                P1IES |= _BV(pin);
            }
            else
            {
                P1IES &= ~_BV(pin);
            }
            break;
        case 2:
            p2_int_table[pin] = func;
            P2IFG &= ~_BV(pin);
            P2IE |= _BV(pin);
            if (type == FALLING_EDGE)
            {
                P2IES |= _BV(pin);
            }
            else
            {
                P2IES &= ~_BV(pin);
            }
            break;
        default:
            break;
    }
}

void InterruptDetach(uint8_t port, uint8_t pin)
{
    switch (port)
    {
        case 1:
            p1_int_table[pin] = NULL;   // null the function pointer
            P1IE  &= ~_BV(pin);         // interrupt disabled
            P1IFG &= ~_BV(pin);         // clear the flag
            break;
        case 2:
            p2_int_table[pin] = NULL;
            P2IE  &=  ~_BV(pin);
            P2IFG &= ~_BV(pin);
            break;
        default:
            break;
    }
}

// Any GPIO interrupt on any port triggers a single interrupt. We will look at
// PxIFG to determine which pin actually caused the interrupt and if an attached
// function is associated with it we will call the function.
#pragma vector = PORT1_VECTOR
__interrupt void Port1(void)
{
    _DINT();
    uint8_t i = 0;
    for (i = 0;i < NUM_P1_INTS;i++)
    {
        if ((P1IFG & _BV(i)) && p1_int_table[i] != NULL)
        {
            p1_int_table[i]();
            P1IFG &= ~_BV(i);
        }
    }
    _EINT();
}

#pragma vector = PORT2_VECTOR
__interrupt void Port2(void)
{
    _DINT();
    uint8_t i = 0;
    for (i = 0;i < NUM_P2_INTS;i++)
    {
        if ((P2IFG & _BV(i)) && p2_int_table[i] != NULL)
        {
            p2_int_table[i]();
            P2IFG &= ~_BV(i);
        }
    }
    _EINT();
}
