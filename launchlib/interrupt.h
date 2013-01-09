/**
@file interrupt.h
@brief Definitions, data structues and prototypes for GPIO interrupt handler
@author Joe Brown
*/
#ifndef INTERRUPT_H
#define INTERRUPT_H

enum IntEdgeType
{
    FALLING,
    RISING
};

typedef void (*InterruptFn)(void);

#define GPIO(name) name##_PORT,name##_PIN

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
extern void InterruptAttach(uint8_t port, uint8_t pin, InterruptFn func, enum IntEdgeType type);

/**
@brief Detach function from GPIO pin interrupt
@details
Index into the p1 or p2 array and null the corresponding function pointer.
@param[in] port GPIO port selection
@param[in] pin GPIO pin selection
*/
extern void InterruptDetach(uint8_t port, uint8_t pin);

#endif // INTERRUPT_H
