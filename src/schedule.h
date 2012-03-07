/** 
@file schedule.h
@brief Definitions, data structues and prototypes for generic scheduling mechanisms
@author Joe Brown
*/
#ifndef SCHEDULE_H
#define SCHEDULE_H

#define SCHEDULE_VECTOR WDT_VECTOR
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

/** @brief Congiruation for callout which holds the function pointer and next
time it will run.*/
typedef struct
{
    CalloutFn func;
    uint32_t run_time;
} CalloutEvent;

/** @brief global time accessible by everyone */
extern volatile uint32_t now;

/**
@brief Check the callback list for functions that are ready to run
@details
Search the callback store for functions that enabled with a time that is equal
to the current global time. If we find the function call it and reset the
run_time based on the stored value.
@param[in] current_time current global time from now variable
*/
static void CallbackService(uint32_t current_time);

/**
@brief Check the callout list for functions that are ready to run
@details
Search the callout store for functions that enabled with a time that is equal
to the current global time. If we find the function call it and vacate the slot
in the map.
@param[in] current_time current global time from now variable
*/
static void CalloutService(uint32_t current_time);

/**
@brief Interrupt routine run by overflow of watchdog timer
@details
When the interrupt fires increment the global time and service the call*s.
*/
__interrupt void ScheduleTimerOverflow(void);

/**
@brief Return the number of occupied slots in the callout map (pending callouts)
@details
Use K&R method to run through the callout map and count the number of bits. This
represents the number of slot occupied in the callout store.
@return the number of functions pending in the callout map
*/
static uint8_t get_callout_map_size(void);

/**
@brief Initialize the schedule timer used to check callouts and callbacks
@details
Configure the watchdog timer to periodically wake up and execute. We currently
use a 2ms period and the timing in hardware.h for _millisecond, _second, and the
like are based on this time. If the period configured in this function is
changed the defintions in hardware.h will also need to be changed.
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
*/
extern void CallbackRegister(CallbackFn func, uint32_t run_time);

/**
@brief Enable or disable a function callback
@details
Search the callback store for the specified function and enable or disable it
based on the mode passed in.
@param[in] func callback function to configure
@param[in] mode enabled or disabled
*/
extern void CallbackMode(CallbackFn func, enum IoMode mode);

/**
@brief Add a callout to the store for one-time execution
@details
Take the function and run time and store them in the callout store. For callouts
we maintain a "map" of callouts in a bit array. When we store a new function we
find an empty slot (0 in the bit array) and set it. That bit corresponds to the
index of the callout store the function pointer is stored at.
@param[in] func function pointer registered to callout slot
@param[in] run_time Specific time in which to run the function
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

#endif
