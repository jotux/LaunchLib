/**
@file interrupt.c
@brief GPIO interrupt handler
@author Joe Brown
*/
#include "global.h"
#include "../hw.h"
#include "interrupt.h"

/** @brief table of function pointers attached to port1 GPIO pins*/
static InterruptFn p1_int_table[NUM_P1_INTS];
/** @brief table of function pointers attached to port2 GPIO pins*/
static InterruptFn p2_int_table[NUM_P2_INTS];

#ifdef __MSP430FR5739__
/** @brief table of function pointers attached to port3 GPIO pins*/
static InterruptFn p3_int_table[NUM_P3_INTS];
/** @brief table of function pointers attached to port4 GPIO pins*/
static InterruptFn p4_int_table[NUM_P4_INTS];
#endif

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
@brief Search interrupt function pointer lists and run functions corresponding
to the interrupt that fired
@details
Go through each bit in the interrupt flag to see if it is set. If it is run the
corresponding function.
@param[in] port port to search
*/
static void InterruptRunOnPort(uint8_t port);

/**
@brief Port 1 interrupt service routine
@details
Go through each bit in the interrupt flag to see if it is set. If it is run the
corresponding function.
*/
static __interrupt void Port1(void);

/**
@brief Port 2 interrupt service routine
@details
Go through each bit in the interrupt flag to see if it is set. If it is run the
corresponding function.
*/
static __interrupt void Port2(void);

/**
@brief Port 3 interrupt service routine
@details
Go through each bit in the interrupt flag to see if it is set. If it is run the
corresponding function.
*/
static __interrupt void Port3(void);

/**
@brief Port 4 interrupt service routine
@details
Go through each bit in the interrupt flag to see if it is set. If it is run the
corresponding function.
*/
static __interrupt void Port4(void);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Note: functions called from GPIO interrupts have no access to timer-based
// facilities (like the global "g_now" variable used for timing). The current
// Delay() implementation will also not work as it relies on timers.
void InterruptAttach(uint8_t port, uint8_t pin, InterruptFn func, enum IntEdgeType type)
{

#define ATTACH_CASE(x)                                                  \
    case x:                                                             \
        p##x##_int_table[pin] = func;   /* save the function pointer */ \
        P##x##IFG &= ~_BV(pin);                                         \
        P##x##IE |= _BV(pin);           /* interrupt enabled */         \
        if (type == FALLING)                                            \
        {                                                               \
            P##x##IES |= _BV(pin);                                      \
        }                                                               \
        else                                                            \
        {                                                               \
            P##x##IES &= ~_BV(pin);                                     \
        }                                                               \
        break;

    switch (port)
    {
        ATTACH_CASE(1);
        ATTACH_CASE(2);
#ifdef __MSP430FR5739__
        ATTACH_CASE(3);
        ATTACH_CASE(4);
#endif
    }
#undef ATTACH_CASE
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void InterruptDetach(uint8_t port, uint8_t pin)
{

#define DETACH_CASE(x)                                                  \
    case x:                                                             \
        p##x##_int_table[pin] = NULL;   /* null the function pointer */ \
        P##x##IE  &= ~_BV(pin);         /* interrupt disabled */        \
        P##x##IFG &= ~_BV(pin);         /* clear the flag */            \
        break;

    switch (port)
    {
        DETACH_CASE(1);
        DETACH_CASE(2);
#ifdef __MSP430FR5739__
        DETACH_CASE(3);
        DETACH_CASE(4);
#endif
    }
#undef DETACH_CASE
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Any GPIO interrupt on any port triggers a single interrupt. We will look at
// PxIFG to determine which pin actually caused the interrupt and if an attached
// function is associated with it we will call the function.
void InterruptRunOnPort(uint8_t port)
{
#define PORT_CASE(x)                                                    \
    case x:                                                             \
        {                                                               \
            uint8_t i = 0;                                              \
            for (i = 0;i < NUM_P##x##_INTS;i++)                         \
            {                                                           \
                if ((P##x##IFG & _BV(i)) && p##x##_int_table[i] != NULL)\
                {                                                       \
                    p##x##_int_table[i]();                              \
                    P##x##IFG &= ~_BV(i);                               \
                }                                                       \
            }                                                           \
        }                                                               \
        break;

    _DINT();
    switch(port)
    {
        PORT_CASE(1);
        PORT_CASE(2);
#ifdef __MSP430FR5739__
        PORT_CASE(3);
        PORT_CASE(4);
#endif
    }
    _EINT();
#undef PORT_CASE
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//        ____        __                                   __
//       /  _/____   / /_ ___   _____ _____ __  __ ____   / /_ _____
//       / / / __ \ / __// _ \ / ___// ___// / / // __ \ / __// ___/
//     _/ / / / / // /_ /  __// /   / /   / /_/ // /_/ // /_ (__  )
//    /___//_/ /_/ \__/ \___//_/   /_/    \__,_// .___/ \__//____/
//                                             /_/
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#pragma vector = PORT1_VECTOR
__interrupt void Port1(void)
{
    InterruptRunOnPort(1);
}

#pragma vector = PORT2_VECTOR
__interrupt void Port2(void)
{
    InterruptRunOnPort(2);
}

#ifdef __MSP430FR5739__
#pragma vector = PORT3_VECTOR
__interrupt void Port3(void)
{
    InterruptRunOnPort(3);
}

#pragma vector = PORT4_VECTOR
__interrupt void Port4(void)
{
    InterruptRunOnPort(4);
}
#endif
