/**
@file schedule.h
@brief Definitions, data structues and prototypes for generic scheduling mechanisms
@author Joe Brown
*/
#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "hardware_init.h"
#include "config.h"

/** @brief timing multiplier to allow regular interval scheduling with varying
clock speeds */
extern volatile uint8_t g_timing_multiplier;

// Timing divisors for scheduling
// The base time millisecond will always be 1.024ms due to the watchdog timer
// divisors. For that reason we will multiply _SECOND by slightly less than 1000
// to account for it and make subsequent multipliers slightly more accurate
#define _MILLISECOND        g_timing_multiplier

/** @brief function pointer to a callback*/
typedef void (*CallbackFn)(void);
/** @brief function pointer to a callout*/
typedef void (*CalloutFn)(void);

/** @brief Configuration for callback which holds the function pointer,
run time (period), next time it will run, and whether or not it is enabled*/
typedef struct
{
    CallbackFn func;
    uint8_t    enabled;
    uint32_t   run_time;
    uint32_t   next_run_time;
} CallbackEvent;

enum ScheduleMode
{
    ENABLED  = 1,
    DISABLED = 0
};

/** @brief global time accessible by everyone */
extern volatile uint32_t g_now;

/**
@brief Initialize the schedule timer used to check callouts and callbacks
@details
Configure the watchdog timer to periodically wake up and service the scheduler
tasks. We currently use a 0.5 ms period and save the multiplier to
g_timing_multiplier. This is used in the definition of _MILLISECOND to give
flexible timing.
*/
extern void ScheduleTimerInit(void);

/**
@brief Add a callback to the store for periodic execution
@details
Take the function and run time and store them in the callback store. Intially
set the enabled flag to false to keep us from accidentally calling a function
before it is expected.
@param[in] func function pointer registered to callback
@param[in] run_time period on which to run the callback function
@return SUCCESS if callback registered successfully, FAILURE otherwise
*/
extern int8_t CallbackRegister(CallbackFn func, uint32_t run_time);

/**
@brief Enable or disable a function callback
@details
Search the callback store for the specified function and enable or disable it
based on the mode passed in.
@param[in] func callback function to configure
@param[in] mode enabled or disabled
*/
extern void CallbackMode(CallbackFn func, enum ScheduleMode mode);

/**
@brief Add a callout to the store for one-time execution
@details
Take the function and run time and store them in the callout store. For callouts
we maintain a "map" of callouts in a bit array. When we store a new function we
find an empty slot (0 in the bit array) and set it. That bit corresponds to the
index of the callout store the function pointer is stored at.
@param[in] func function pointer registered to callout slot
@param[in] run_time Specific time in which to run the function
@return SUCCESS if callback registered successfully, FAILURE otherwise
*/
extern int8_t CalloutRegister(CalloutFn func, uint32_t run_time);

/**
@brief Disable a function callout before it has run
@details
Search the callout store for the specific function. If we find it go clear the
map to indicate the slot is vacant.
@param[in] func function pointer to search for and cancel
*/
extern void CalloutCancel(CalloutFn func);

#endif // SCHEDULE_H
