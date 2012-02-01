#include "global.h"
#include "interrupt.h"
#include "hardware.h"

InterruptFn p1_int_table[NUM_P1_INTS];
#ifdef __MSP430G2553__
InterruptFn p2_int_table[NUM_P2_INTS];
#endif

// Note: functions called from GPIO interrupts have no access to timer-based
// facilities (like the global "now" variable used for timing). The current
// Delay() implementation will also not work as it relies on timers.
void AttachInterrupt(uint8_t port, uint8_t pin, InterruptFn func, enum edge_type type)
{
    switch (port)
    {
        case 1:
            p1_int_table[pin] = func;   // save the function pointer
            P1IE  |=  _BV(pin);         // interrupt enabled
            P1IES |=  _BV(pin) & type;  // rising/falling edge
            P1IFG &= ~_BV(pin);         // clear the flag
            break;
#ifdef __MSP430G2553__
        case 2:
            p2_int_table[pin] = func;
            P2IE  |=  _BV(pin);
            P2IES |=  _BV(pin) & type;
            P2IFG &= ~_BV(pin);
            break;
#endif
        default:
            break;
    }
}

void DetachInterrupt(uint8_t port, uint8_t pin)
{
    switch (port)
    {
        case 1:
            p1_int_table[pin] = NULL;   // null the function pointer
            P1IE  &= ~_BV(pin);         // interrupt disabled
            P1IFG &= ~_BV(pin);         // clear the flag
            break;
#ifdef __MSP430G2553__
        case 2:
            p2_int_table[pin] = NULL;
            P2IE  &=  ~_BV(pin);
            P2IFG &= ~_BV(pin);
            break;
#endif
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
    uint8_t cnt = 0;
    while(cnt++ < NUM_P1_INTS)
    {
        if ((P1IFG & _BV(cnt)) && p1_int_table[cnt] != NULL)
        {
            p1_int_table[cnt]();
            P1IFG &= ~_BV(cnt);
        }
    }
    _EINT();
}

#ifdef __MSP430G2553__
#pragma vector = PORT2_VECTOR
__interrupt void Port2(void)
{
	_DINT();
    uint8_t cnt = 0;
    while(cnt++ < NUM_P2_INTS)
    {
        if ((P2IFG & _BV(cnt)) && p2_int_table[cnt] != NULL)
        {
            p2_int_table[cnt]();
            P2IFG &= ~_BV(cnt);
        }
    }
    _EINT();
}
#endif
