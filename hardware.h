#ifndef HARDWARE_H
#define HARDWARE_H

//macros
#define st(x) do{x} while(__LINE__ == -1)

#define MAKE_OUTPUT(port,pin) IO_MAKE_OUTPUT(port,pin)
#define MAKE_INPUT(port, pin) IO_MAKE_INPUT(port, pin)
#define SET_HIGH(port,pin)    IO_SET_HIGH(port,pin)
#define SET_LOW(port,pin)     IO_SET_LOW(port,pin)
#define TOGGLE(port,pin)      IO_TOG(port,pin)
#define READ_IN(port,pin)     IO_DIG_READ(port,pin)

#define IO_MAKE_OUTPUT(port,pin) st((P##port##DIR |=  _BV(pin));)
#define IO_MAKE_INPUT(port, pin) st((P##port##DIR &= ~_BV(pin));)
#define IO_SET_HIGH(port,pin)    st((P##port##OUT |=  _BV(pin));)
#define IO_SET_LOW(port,pin)     st((P##port##OUT &= ~_BV(pin));)
#define IO_TOG(port,pin)         st((P##port##OUT ^= _BV(pin));)
#define IO_DIG_READ(port,pin)    !(P##port##IN & _BV(pin))

#define RED_LED_PORT  1
#define RED_LED_PIN   0
#define RED_LED_OFF()    SET_LOW(RED_LED_PORT, RED_LED_PIN);
#define RED_LED_ON()     SET_HIGH(RED_LED_PORT, RED_LED_PIN);
#define RED_LED_TOGGLE() TOGGLE(RED_LED_PORT, RED_LED_PIN);

#endif
