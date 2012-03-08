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
@param[in] delay_time time to delay
*/
extern void Delay(uint32_t delay_time);

#endif // DELAY_H
