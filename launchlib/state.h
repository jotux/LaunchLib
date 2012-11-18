/**
@file state.h
@brief Definitions, data structues and prototypes for state machine handling
@author Joe Brown
*/

#ifndef STATE_H
#define STATE_H

#include "config.h"

/** @brief function pointer to a state function that accepts an event variable*/
typedef void (*State)(uint8_t);

/** @brief List of default events*/
#define DEFAULT_EVENTS IDLE=0,ENTER=1,EXIT=2

/** @brief A transition which holds a current state, an event, and the state
that will be entered upon receiving that event*/
typedef struct
{
    State   current_state;  /**< the current state function pointer */
    uint8_t event_code;     /**< the event that triggers a transition */
    State   next_state;     /**< the state that follows the transition */
} Transition;

/** @brief A structure that contains all information about a given state machine */
typedef struct
{
    uint8_t event_queue[MAX_EVENT_CNT]; /**< The event queue array to be malloced in init */
    uint8_t start;                  /**< Start of the circular buffer */
    uint8_t event_cnt;              /**< Number of events in the buffer */
    Transition* transitions;        /**< Pointer to transition table */
    uint8_t transition_table_size;  /**< Size of transition table */
    uint8_t transition_event;       /**< Current transition event in the state machine */
    State state;                    /**< Current state of the state machine */
} StateMachine;

/**
@brief State machine initialization
@details
Initializes the state machine by saving a pointer to the transition rules,
saving the size (so we can loop through it looking for state changes) and
initially publishes and ENTER event so the first state can initialize whatever
it needs.
@param[in] rules Pointer to state transitions rules table
@param[in] t_size The size of the transition rules table (not accounting for Transition struct size)
@param[in] state The initial state of the state machine
@return A pointer to the state machine struct
*/
extern StateMachine StateMachineCreate(Transition* rules, uint8_t t_size, State state);

/**
@brief Queue a new event
@details
Pushes a new event in to the event queue and adjust the size.
@param[in] s A pointer to state machine to publish to
@param[in] event The event to enqueue.
@return SUCCESS if event was queued, FAILURE otherwise
*/
extern int8_t StateMachinePublishEvent(StateMachine* s, uint8_t event);

/**
@brief Run the state machine
@details
Checks the event queue for new events, processes the current state and modifies
the state based on state transitions.
@param[in] s A pointer to the state machine to run
*/
extern void StateMachineRun(StateMachine* s);

#endif // STATE_H
