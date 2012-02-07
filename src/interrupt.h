#ifndef INTERRUPT_H
#define INTERRUPT_H

typedef void (*InterruptFn)(void);

void AttachInterrupt(uint8_t port, uint8_t pin, InterruptFn func, enum IoEdge type);
void DetachInterrupt(uint8_t port, uint8_t pin);

#endif
