/**
@file hardware_init.h
@brief Macros to init hardware
@author Joe Brown
*/
#ifndef HARDWARE_INIT_H
#define HARDWARE_INIT_H

// The macros below are an obvious abuse of the preprocessor. That said, when
// expanded they are just as efficient as writing a single-line C statement.
// Example:
// LED_PORT 1
// LED_PIN  5
// IO_DIRECTION(LED,GPIO_OUTPUT); expands to P1DIR |= 1;
// IO_DIRECTION(LED,GPIO_INPUT); expands to P1DIR &=~1;

#define _PORT(n)     n##_PORT
#define _PIN(n)      n##_PIN
#Define _REG(n,type) P##n##type

#define CLEAR_OP    &=~
#define SET_OP      |=
#define TOGGLE_OP   ^=

#define GPIO_INPUT  CLEAR_OP
#define GPIO_OUTPUT SET_OP
/**@brief Set the direction of an IO pin as INPUT or OUTPUT */
#define IO_DIRECTION(name,fun)          _IO_DIRECTION(_PORT(name),_PIN(name),fun)
/** @cond IGNORE_DOC */
#define _IO_DIRECTION(port,pin,fun)     _REG(port,DIR) fun _BV(pin)
/** @endcond */

#define GPIO_FUN_IO      CLEAR_OP
#define GPIO_FUN_SPECIAL SET_OP
/**@brief Set function of IO pin */
#define IO_FUNCTION(name,fun)           _IO_FUNCTION(_PORT(name),_PIN(name),fun)
/** @cond IGNORE_DOC */
#ifdef __MSP430G2553__
#define _IO_FUNCTION(port, pin,fun)     _REG(port,SEL) fun _BV(pin)
#elif __MSP430FR5739__
#define _IO_FUNCTION(port, pin,fun)     _REG(port,SEL0) fun _BV(pin)
#endif
/** @endcond */


/**@brief Set auxilary function of IO pin */
#define IO_AUX_FUNCTION(name,fun)       _IO_AUX_FUNCTION(_PORT(name),_PIN(name),fun)
/** @cond IGNORE_DOC */
#ifdef __MSP430G2553__
#define _IO_AUX_FUNCTION(port, pin,fun) _REG(port,SEL2) fun _BV(pin)
#elif __MSP430FR5739__
#define _IO_AUX_FUNCTION(port, pin,fun) _REG(port,SEL1) fun _BV(pin)
#endif
/** @endcond */

#define GPIO_LOW    CLEAR_OP
#define GPIO_HIGH   SET_OP
#define GPIO_TOGGLE TOGGLE_OP
/**@brief Set state of IO pin */
#define IO_SET(name,fun)                _IO_SET(_PORT(name),_PIN(name),fun)
#define _IO_SET(port,pin,fun)           _REG(port,OUT) fun _BV(pin)
/** @cond IGNORE_DOC */
/** @endcond */

#define GPIO_ENABLE     SET_OP
#define GPIO_DISABLE    CLEAR_OP
/**@brief Set resistor pull up or down for IO pin */
#define IO_RESISTOR(name,fun)           _IO_RESISTOR(_PORT(name),_PIN(name),fun)
/** @cond IGNORE_DOC */
#define _IO_RESISTOR(port,pin,fun)      _REG(port,REN) fun _BV(pin)
/** @endcond */

#define GPIO_PULL_DOWN CLEAR_OP
#define GPIO_PULL_UP   SET_OP
// Set pin as input before calling this macro
/**@brief Set resistor polarity (up or down) for IO pin */
#define IO_PULL(name,up)                IO_RESISTOR(name,GPIO_ENABLE);\
                                        IO_SET(name,up);

/**@brief Read in state of IO pin */
#define IO_IN(name)                     _IO_IN(_PORT(name),_PIN(name))
/** @cond IGNORE_DOC */
#define _IO_IN(port,pin)                _REG(port,IN) & _BV(in)
/** @endcond */

/**@brief Sent interrupt enable for IO pin */
#define IO_INT_EN(name,fun)             _IO_INT_EN(_PORT(name),_PIN(name),fun)
/** @cond IGNORE_DOC */
#define _IO_INT_EN(port,pin,fun)        _REG(port,IE) fun _BV(pin)
/** @endcond */

#define GPIO_RISING_EDGE    CLEAR_OP
#define GPIO_FALLING_EDGE   SET_OP
/**@brief Set rising or falling edge interrupt for IO pin */
#define IO_INT_EDGE(name,fun)           _IO_INT_EDGE(_PORT(name),_PIN(name),fun)
/** @cond IGNORE_DOC */
#define _IO_INT_EDGE(port,pin,fun)      _REG(port,IES) fun _BV(pin)
/** @endcond */

#define GPIO_INT_SET    SET_OP
#define GPIO_INT_CLEAR  CLEAR_OP
/**@brief Set IO pin interrupt status */
#define IO_INT_FLAG(name,fun)           _IO_INT_FLAG(_PORT(name),_PIN(name),fun)
/** @cond IGNORE_DOC */
#define _IO_INT_FLAG(port,pin,fun)      _REG(port,IFG) fun _BV(pin)
/** @endcond */

/**@brief Read IO pin interrupt status */
#define IO_INT_STAT(name)               _IO_INT_STAT(_PORT(name),_PIN(name))
/** @cond IGNORE_DOC */
#define _IO_INT_STAT(port,pin)          _REG(port,IFG) & _BV(in)
/** @endcond */

#endif // HARDWARE_INIT_H
