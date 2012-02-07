#ifndef GLOBAL_H
#define GLOBAL_H

#include "msp430.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <assert.h>

enum {FALSE = 0, TRUE = 1};

// macros
#define _BV(bit) (1<<(bit))
#define SET_BIT(reg,bit)    ((reg)|= _BV(bit))
#define CLR_BIT(reg,bit)    ((reg)&=~_BV(bit))
#define TOG_BIT(reg,bit)    ((reg)^= _BV(bit))
#define WD_STOP()           (WDTCTL = WDTPW + WDTHOLD)
#define SET_CLOCK(N) BCSCTL1 = CALBC1_##N##MHZ; \
                     DCOCTL = CALDCO_##N##MHZ;

//types
typedef unsigned char      uint8_t;
typedef signed char        int8_t;
typedef unsigned short int uint16_t;
typedef signed short int   int16_t;
typedef unsigned long int  uint32_t;
typedef signed long int    int32_t;

//macros for IO config (with preprocessor abuse)
#define st(x) do{x} while(__LINE__ == -1)

enum IoDirection {INPUT = 0, OUTPUT = 1};
// Set pin direction (page 321)
#define IO_DIRECTION(name,dir)          _IO_DIRECTION(name##_PORT,name##_PIN,dir)
#define _IO_DIRECTION(port,pin,dir)     st(__IO_DIRECTION(port,pin,dir);)
#define __IO_DIRECTION(port,pin,dir)    if (dir)\
                                        {\
                                            st((P##port##DIR |= _BV(pin)););\
                                        }\
                                        else\
                                        {\
                                            st((P##port##DIR &= ~_BV(pin)););\
                                        }

enum IoFunction {IO = 0, SPECIAL = 1};
// Set pin function (page 322)
#define IO_FUNCTION(name,fun)           _IO_FUNCTION(name##_PORT,name##_PIN,fun)
#define _IO_FUNCTION(port, pin,fun)     st(__IO_FUNCTION(port,pin,fun);)
#define __IO_FUNCTION(port, pin,fun)    if (fun)\
                                        {\
                                            st((P##port##SEL |= _BV(pin)););\
                                        }\
                                        else\
                                        {\
                                            st((P##port##SEL &= ~_BV(pin)););\
                                        }

enum IoState {LOW = 0, HIGH = 1, TOGGLE = 2};
// Set pin output high or low, also used for pullup/down selection (page 321)
#define IO_SET(name,val)                _IO_SET(name##_PORT,name##_PIN,val)
#define _IO_SET(port,pin,val)           st(__IO_SET(port,pin,val);)
#define __IO_SET(port,pin,val)          if (val == TOGGLE)\
                                        {\
                                            st((P##port##OUT ^= _BV(pin)););\
                                        }\
                                        else if (val == HIGH)\
                                        {\
                                            st((P##port##OUT |= _BV(pin)););\
                                        }\
                                        else\
                                        {\
                                            st((P##port##OUT &= ~_BV(pin)););\
                                        }

enum IoMode {DISABLED = 0, ENABLED = 1};

#define IO_RESISTOR(name,ren)           _IO_RESISTOR(name##_PORT,name##_PIN,ren)
#define _IO_RESISTOR(port,pin,ren)      st(__IO_RESISTOR(port,pin,ren);)
#define __IO_RESISTOR(port,pin,ren)     if (ren)\
                                        {\
                                            st((P##port##REN |= _BV(pin)););\
                                        }\
                                        else\
                                        {\
                                            st((P##port##REN &= ~_BV(pin)););\
                                        }

enum IoResistorState {PULL_DOWN = 0, PULL_UP = 1};
// Set pin as input before calling this macro
#define IO_PULL(name,up)                IO_RESISTOR(name,ENABLED);\
                                        if (up)\
                                        {\
                                            IO_SET(name,HIGH);\
                                        }\
                                        else\
                                        {\
                                            IO_SET(name,LOW);\
                                        }


enum IoStrength {REDUCED = 0, FULL = 1};
#define IO_DRIVE(name,ds)               _IO_DRIVE(name##_PORT,name##_PIN,ds)
#define _IO_DRIVE(port,pin,ds)          st(__IO_DRIVE(port,pin,ds);)
#define __IO_DRIVE(port,pin,ds)         if (ds)\
                                        {\
                                            st((P##port##DS |= _BV(pin)););\
                                        }\
                                        else\
                                        {\
                                            st((P##port##DS &= ~_BV(pin)););\
                                        }

#define IO_IN(name)                     _IO_IN(name##_PORT,name##_PIN)
#define _IO_IN(port,pin)                __IO_IN(port,pin)
#define __IO_IN(port,pin)               !(P##port##IN & _BV(pin))

#define IO_INT_EN(name,en)              _IO_INT_EN(name##_PORT,name##_PIN,en)
#define _IO_INT_EN(port,pin,en)         st(__IO_INT_EN(port,pin,en);)
#define __IO_INT_EN(port,pin,en)        if (en)\
                                        {\
                                            st((P##port##IE |= _BV(pin)););\
                                        }\
                                        else\
                                        {\
                                            st((P##port##IE &= ~_BV(pin)););\
                                        }

enum IoEdge {RISING_EDGE = 0, FALLING_EDGE = 1};
#define IO_INT_EDGE(name,ed)            _IO_INT_EDGE(name##_PORT,name##_PIN,ed)
#define _IO_INT_EDGE(port,pin,ed)       st(__IO_INT_EDGE(port,pin,ed);)
#define __IO_INT_EDGE(port,pin,ed)      if (ed)\
                                        {\
                                            st((P##port##IES |= _BV(pin)););\
                                        }\
                                        else\
                                        {\
                                            st((P##port##IES &= ~_BV(pin)););\
                                        }

#define CLEARED 1
#define IO_INT_FLAG(name,fl)            _IO_INT_FLAG(name##_PORT,name##_PIN,fl)
#define _IO_INT_FLAG(port,pin,fl)       st(__IO_INT_FLAG(port,pin,fl);)
#define __IO_INT_FLAG(port,pin,fl)      if (fl)\
                                        {\
                                            st((P##port##IFG &= ~_BV(pin)););\
                                        }\
                                        else\
                                        {\
                                            st((P##port##IFG |= _BV(pin)););\
                                        }

#define IO_INT_STAT(name)               _IO_INT_STAT(name##_PORT,name##_PIN)
#define _IO_INT_STAT(port,pin)          __IO_INT_STAT(port,pin)
#define __IO_INT_STAT(port,pin)         (P##port##IFG & _BV(pin))
#endif
