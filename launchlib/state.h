/**
@file state.h
@brief Definitions, data structues and prototypes for state machine handling
@author Joe Brown
*/

#ifndef STATE_H
#define STATE_H

/** @brief function pointer to a state function that accepts an event variable*/
typedef void (*State)(uint8_t);

// events (the following line is preprocessor sin)
/** @brief List of default events*/
#define DEFAULT_EVENTS IDLE,ENTER,EXIT

/** @brief A transition which holds a current state, an event, and the state
that will be entered upon receieving that event*/
typedef struct
{
    State   current_state;
    uint8_t event_code;
    State   next_state;
}Transition;

/**
@brief Check the event queue for changes.
@details If we are in the IDLE state and a state transition is going to take
place (detected by using LookupTransition) we will return EXIT. If no transition
will take then we simple dequeue the next event.

If we are currently processing an EXIT event this means the next transition in
the queue will cause a state transition, so we dequeue that event and return it
to the new state but save the transition_event as ENTER to force an ENTER event
to be sent after the event is complete.

Once the transition-causing event has been processed we return an ENTER event
to allow state intialization in the new state.
@param[in] state The current state the state machine is in
@return The event to be run by the current state
*/
static uint8_t CheckEventQueue(State state);

/**
@brief Peek at the event queue to see what the next event will be
@details
Peek at the queue without dequeueing the next item. We use this so check if a
state transition will be coming so we can pass EXIT and ENTER events.
@return If there are no events in the queue, IDLE. If there is a pending event in the
queue we will return it.
*/
static uint8_t QueuePeek(void);

/**
@brief Get the next state from the transition table
@details
Get the next state from the transition table based on the current state and the
most recent event dequeued from the event queue.
@param[in] state The current state being processed by the state machine
@param[in] event The next event dequeue from the event queue
@return The next state to be run based on transition rules
*/
static State LookupTransition(State state, uint8_t event);

/**
@brief Dequeue an event from the event queue
@details
Removes an event from the event queue and passes it to the current state.
@return The next event to tbe processed by the current state
*/
static uint8_t DequeueEvent(void);

/**
@brief State machine initialization
@details
Initializes the state machine by saving a pointer to the transition rules,
saving the size (so we can loop through it looking for state changes) and
initially publishes and ENTER event so the first state can initialize whatever
it needs.
@param state_transitions Pointer to state transitions rules table
@param t_size The size of the transition rules table (not accounting for Transition struct size)
*/
extern void StateMachineInit(Transition *state_transitions, uint8_t t_size);

/**
@brief Queue a new event
@details
Pushes a new event in to the event queue and adjust the size.
@param[in] event The event to enqueue.
@return 0 if successful, -1 for failure
*/
extern int8_t StateMachinePublishEvent(uint8_t event);

/**
@brief Run the state machine
@details
Checks the event queue for new events, processes the current state and modifies
the state based on state transitions.
@param[in] state A pointer to the current state
@return Overwrites current state pointer with next state pointer
*/
extern void StateMachineRun(State* state);

#endif // STATE_H
