/**
@file interrupt.h
@brief Definitions, data structues and prototypes for GPIO interrupt handler
@author Joe Brown
*/
#ifndef INTERRUPT_H
#define INTERRUPT_H

typedef void (*InterruptFn)(void);

/**
@brief Attach function to GPIO pin edge interrupt
@details
To attach a function to ann interrupt we put it into a table of function
pointers of which the port corresponds to the p1 or p2 array and the pin
corresponds to the index into that array.
@param[in] port GPIO port selection
@param[in] pin GPIO pin selection
@param[in] func function pointer to attach
@param[in] type rising or falling edge
*/
extern void InterruptAttach(uint8_t port, uint8_t pin, InterruptFn func, enum IoEdge type);

/**
@brief Detach function from GPIO pin interrupt
@details
Index into the p1 or p2 array and null the corresponding function pointer.
@param[in] port GPIO port selection
@param[in] pin GPIO pin selection
*/
extern void InterruptDetach(uint8_t port, uint8_t pin);

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

#endif // INTERRUPT_H
