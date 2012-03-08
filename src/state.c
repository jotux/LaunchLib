/**
@file state.c
@brief Simple state machine handler
@author Joe Brown
*/
#include "global.h"
#include "hardware.h"
#include "state.h"

/** @brief A pointer to the transition table */
static Transition* transition_table;
/** @brief The size of the transrition table */
static uint8_t transition_table_size;

// The event queue is a FIFO implemented as a circular buffer
/** @brief beginning index of the circular buffer holding events */
static uint8_t start;
/** @brief number of events in the circular event buffer */
static uint8_t size;
/** @brief published events are stored here */
static uint8_t queue[MAX_EVENT_CNT];


/** @brief event queue (published events are stored here) */
enum LocalDefaults {DEFAULT_EVENTS};

/** @brief indicator kept to store EXIT/ENTER events */
static uint8_t transition_event = IDLE;

void StateMachineInit(Transition *state_transitions, uint8_t t_size)
{
    // save a pointer to the state transition table
    transition_table = state_transitions;
    // save it's size so we can search it
    transition_table_size = (t_size / sizeof(Transition));
    // enqueue an enter event to start the idle state
    StateMachinePublishEvent(ENTER);
}

uint8_t CheckEventQueue(State state)
{
    uint8_t ret_event = IDLE;

    _DINT();
    switch (transition_event)
    {
        case IDLE:
            // get the next event without dequeuing and peek at the table to see
            // if this event will cause a transition
            if (state != LookupTransition(state, QueuePeek()))
            {
                // if a transition will happen, return the EXIT event
                ret_event = transition_event = EXIT;
            }
            else
            {
                // if a transition will not happen, dequeue events normally
                ret_event = DequeueEvent();
            }
            break;
        case ENTER:
            // return ENTER and switch transition event to IDLE
            ret_event = ENTER;
            transition_event = IDLE;
            break;
        case EXIT:
            // switch transition event to ENTER but return queued event
            transition_event = ENTER;
            ret_event = DequeueEvent();
            break;
    }
    _EINT();
    return ret_event;
}

uint8_t QueuePeek(void)
{
    return size ? queue[start] : IDLE;
}

int8_t StateMachinePublishEvent(uint8_t event)
{
    int8_t ret = -1;
    // event queue full?
    if (size < MAX_EVENT_CNT)
    {
        // add event to queue
        queue[((start + size) == MAX_EVENT_CNT) ? 0 : (start + size)] = event;
        // adjust the size
        size++;
        // return success
        ret = 0;
    }
    return ret;
}

uint8_t DequeueEvent(void)
{
    int8_t ret = IDLE;
    // are there any events?
    if (size)
    {
        // save the value we will return
        ret = queue[start];
        // adjust the start
        start = (start == (MAX_EVENT_CNT - 1)) ? 0 : (start + 1);
        // adjust the size
        size--;
    }
    return ret;
}

State LookupTransition(State state, uint8_t event)
{
    uint8_t i = 0;
    State ret_state = state;
    // if the event is idle or enter/exit just return state)
    if (event > EXIT)
    {
        // if event is a new event find the transition
        for(i = 0;i < transition_table_size;i++)
        {
            if (transition_table[i].current_state == state &&
                transition_table[i].event_code    == event)
            {
                ret_state = transition_table[i].next_state;
                break;
            }
        }
    }
    return ret_state;
}

void StateMachineRun(State* state)
{
    // get the next event
    uint8_t event = CheckEventQueue(*state);
    // run the state
    (*state)(event);
    // check for state transitions
    *state = LookupTransition(*state, event);
}
