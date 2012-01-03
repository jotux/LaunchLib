#ifndef INTERRUPT_H
#define INTERRUPT_H

typedef void (*InterruptFn)(void);

enum edge_type {RISING_EDGE = 0, FALLING_EDGE = 1};

void AttachInterrupt(uint8_t port, uint8_t pin, InterruptFn func, enum edge_type type);
void DetachInterrupt(uint8_t port, uint8_t pin);

#endif
