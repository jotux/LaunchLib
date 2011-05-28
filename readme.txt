A simple library for flexible task scheduling.

Current code works in IAR for MSP43fx2xx.

To use register the function with CallbackRegister() and enabled it with CallbackMode(ptr, ENABLED). Make sure your time is configured to 100microsecond period. If you change the timer period be sure to adjust the timing multipliers in global.h to match.