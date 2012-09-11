/**
@file delay.h
@brief Definition of delay
@author Joe Brown
*/
#ifndef DELAY_H
#define DELAY_H

/**
@brief Delay for selected time
@details
Continuously check global now variable to see if it has passed the delay_time
@warning Do NOT call this from an interrupt, you will not like the results
@param[in] delay_time time to delay
*/
extern void Delay(uint32_t delay_time);

/**
@brief Delay for selected time
@details
Sit in a loop and wait for it to end.
@warning If you call this in an interrupt it will block interrupts until it
completes.
@param[in] delay_time time to delay
*/
extern void DumbDelay(uint32_t delay_time);

#endif // DELAY_H
