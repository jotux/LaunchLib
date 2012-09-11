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
// IO_DIRECTION(LED,OUTPUT); expands to P1DIR |= 1;
// IO_DIRECTION(LED,INPUT); expands to P1DIR &=~1;

#define CLEAR_OP    &=~
#define SET_OP      |=
#define TOGGLE_OP   ^=

#define GPIO_INPUT  CLEAR_OP
#define GPIO_OUTPUT SET_OP
/**@brief Set the direction of an IO pin as INPUT or OUTPUT */
#define IO_DIRECTION(name,dir)          _IO_DIRECTION(name##_PORT,name##_PIN,dir)
/** @cond IGNORE_DOC */
#define _IO_DIRECTION(port,pin,dir)     __IO_DIRECTION(port,pin,dir)
#define __IO_DIRECTION(port,pin,dir)    P##port##DIR dir _BV(pin)
/** @endcond */

#define GPIO_FUN_IO      CLEAR_OP
#define GPIO_FUN_SPECIAL SET_OP
/**@brief Set function of IO pin */
#define IO_FUNCTION(name,fun)           _IO_FUNCTION(name##_PORT,name##_PIN,fun)
/** @cond IGNORE_DOC */
#define _IO_FUNCTION(port, pin,fun)     __IO_FUNCTION(port,pin,fun)
#ifdef __MSP430G2553__
#define __IO_FUNCTION(port, pin,fun)    P##port##SEL fun _BV(pin)
#elif __MSP430FR5739__
#define __IO_FUNCTION(port, pin,fun)    P##port##SEL0 fun _BV(pin)
#endif
/** @endcond */


/**@brief Set auxilary function of IO pin */
#define IO_AUX_FUNCTION(name,fun)        _IO_AUX_FUNCTION(name##_PORT,name##_PIN,fun)
/** @cond IGNORE_DOC */
#define _IO_AUX_FUNCTION(port, pin,fun)  __IO_AUX_FUNCTION(port,pin,fun)
#ifdef __MSP430G2553__
#define __IO_AUX_FUNCTION(port, pin,fun) P##port##SEL2 fun _BV(pin)
#elif __MSP430FR5739__
#define __IO_AUX_FUNCTION(port, pin,fun) P##port##SEL1 fun _BV(pin)
#endif
/** @endcond */

#define GPIO_LOW    CLEAR_OP
#define GPIO_HIGH   SET_OP
#define GPIO_TOGGLE TOGGLE_OP
/**@brief Set state of IO pin */
#define IO_SET(name,dir)                _IO_SET(name##_PORT,name##_PIN,dir)
/** @cond IGNORE_DOC */
#define _IO_SET(port,pin,dir)           __IO_SET(port,pin,dir)
#define __IO_SET(port,pin,dir)          P##port##OUT dir _BV(pin)
/** @endcond */

#define GPIO_ENABLE     SET_OP
#define GPIO_DISABLE    CLEAR_OP
/**@brief Set resistor pull up or down for IO pin */
#define IO_RESISTOR(name,ren)           _IO_RESISTOR(name##_PORT,name##_PIN,ren)
/** @cond IGNORE_DOC */
#define _IO_RESISTOR(port,pin,ren)      __IO_RESISTOR(port,pin,ren)
#define __IO_RESISTOR(port,pin,ren)     P##port##REN ren _BV(pin)
/** @endcond */

#define GPIO_PULL_DOWN CLEAR_OP
#define GPIO_PULL_UP   SET_OP
// Set pin as input before calling this macro
/**@brief Set resistor polarity (up or down) for IO pin */
#define IO_PULL(name,up)                IO_RESISTOR(name,ENABLED);\
                                        IO_SET(name,up);

/**@brief Read in state of IO pin */
#define IO_IN(name)                     _IO_IN(name##_PORT,name##_PIN)
/** @cond IGNORE_DOC */
#define _IO_IN(port,pin)                __IO_IN(port,pin)
#define __IO_IN(port,pin)               !(P##port##IN & _BV(pin))
/** @endcond */

/**@brief Sent interrupt enable for IO pin */
#define IO_INT_EN(name,en)              _IO_INT_EN(name##_PORT,name##_PIN,en)
/** @cond IGNORE_DOC */
#define _IO_INT_EN(port,pin,en)         __IO_INT_EN(port,pin,en)
#define __IO_INT_EN(port,pin,en)        P##port##IE en _BV(pin)
/** @endcond */

#define GPIO_RISING_EDGE    CLEAR_OP
#define GPIO_FALLING_EDGE   SET_OP
/**@brief Set rising or falling edge interrupt for IO pin */
#define IO_INT_EDGE(name,ed)            _IO_INT_EDGE(name##_PORT,name##_PIN,ed)
/** @cond IGNORE_DOC */
#define _IO_INT_EDGE(port,pin,ed)       __IO_INT_EDGE(port,pin,ed)
#define __IO_INT_EDGE(port,pin,ed)      P##port##IES ed _BV(pin)
/** @endcond */

#define GPIO_INT_SET    SET_OP
#define GPIO_INT_CLEAR  CLEAR_OP
/**@brief Set IO pin interrupt status */
#define IO_INT_FLAG(name,fl)            _IO_INT_FLAG(name##_PORT,name##_PIN,fl)
/** @cond IGNORE_DOC */
#define _IO_INT_FLAG(port,pin,fl)       __IO_INT_FLAG(port,pin,fl)
#define __IO_INT_FLAG(port,pin,fl)      P##port##IFG fl _BV(pin)
/** @endcond */

/**@brief Read IO pin interrupt status */
#define IO_INT_STAT(name)               _IO_INT_STAT(name##_PORT,name##_PIN)
/** @cond IGNORE_DOC */
#define _IO_INT_STAT(port,pin)          __IO_INT_STAT(port,pin)
#define __IO_INT_STAT(port,pin)         (P##port##IFG & _BV(pin))
/** @endcond */

#endif // HARDWARE_INIT_H
