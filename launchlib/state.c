/**
@file state.c
@brief Simple state machine handler
@author Joe Brown
*/
#include "global.h"
#include "state.h"

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                            __                        __
//                           / /   ____   _____ ____ _ / /
//                          / /   / __ \ / ___// __ `// /
//                         / /___/ /_/ // /__ / /_/ // /
//                        /_____/\____/ \___/ \__,_//_/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/** @brief Default events not enqueued by users */
enum LocalDefaults {DEFAULT_EVENTS};

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
/**
@brief Dequeue an event from the event queue
@details
Removes an event from the event queue and passes it to the current state.
@param[in] s A pointer to the state machine to dequeue an event from
@return The next event to be processed by the current state
*/
static uint8_t DequeueEvent(StateMachine* s);

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
to allow state initialization in the new state.
@param[in] s A pointer to the state machine to check for events in
@return The event to be run by the current state
*/
static uint8_t CheckEventQueue(StateMachine* s);

/**
@brief Peek at the event queue to see what the next event will be
@details
Peek at the queue without dequeuing the next item. We use this so check if a
state transition will be coming so we can pass EXIT and ENTER events.
@param[in] s A pointer to the state machine to check for events in
@return If there are no events in the queue, IDLE. If there is a pending event in the
queue we will return it.
*/
static uint8_t QueuePeek(StateMachine* s);

/**
@brief Get the next state from the transition table
@details
Get the next state from the transition table based on the current state and the
most recent event dequeued from the event queue.
@param[in] s A pointer to the state machine to look for transitions in
@param[in] event The next event dequeue from the event queue
@return The next state to be run based on transition rules
*/
static State LookupTransition(StateMachine* s, uint8_t event);

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//                            ____        _  __
//                           /  _/____   (_)/ /_
//                           / / / __ \ / // __/
//                         _/ / / / / // // /_
//                        /___//_/ /_//_/ \__/
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
StateMachine StateMachineCreate(Transition* rules, uint8_t t_size, State state)
{
    StateMachine s;
    s.start = 0;
    s.event_cnt = 0;
    s.transitions = rules;
    s.transition_table_size = (t_size / sizeof(Transition));
    s.transition_event = IDLE;
    s.state = state;
    StateMachinePublishEvent(&s, ENTER);
    return (s);
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
uint8_t CheckEventQueue(StateMachine* s)
{
    uint8_t ret_event = IDLE;

    switch (s->transition_event)
    {
        case IDLE:
        {
            // get the next event without dequeuing and peek at the table to see
            // if this event will cause a transition
            if (s->state != LookupTransition(s, QueuePeek(s)))
            {
                // if a transition will happen, return the EXIT event
                ret_event = s->transition_event = EXIT;
            }
            else
            {
                // if a transition will not happen, dequeue events normally
                ret_event = DequeueEvent(s);
            }

            break;
        }
        case ENTER:
        {
            // return ENTER and switch transition event to IDLE
            ret_event = ENTER;
            s->transition_event = IDLE;
            break;
        }
        case EXIT:
        {
            // Return ENTER event
            s->transition_event = ENTER;
            // dequeue the event that causes the transition
            // This event isn't processed by the state but used to look up the
            // transition it will cause
            ret_event = DequeueEvent(s);
            break;
        }
    }
    return ret_event;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
uint8_t QueuePeek(StateMachine* s)
{
    return s->event_cnt ? s->event_queue[s->start] : IDLE;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
int8_t StateMachinePublishEvent(StateMachine* s, uint8_t event)
{
    int8_t ret = FAILURE;

    if (s->event_cnt < MAX_EVENT_CNT)
    {
        if (s->start + s->event_cnt == MAX_EVENT_CNT)
        {
            s->event_queue[0] = event;
        }
        else
        {
            s->event_queue[s->start + s->event_cnt] = event;
        }
        s->event_cnt++;
    }
    return ret;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
uint8_t DequeueEvent(StateMachine* s)
{
    uint8_t ret = IDLE;
    if (s->event_cnt)
    {
        ret = s->event_queue[s->start];
        if (s->start == MAX_EVENT_CNT - 1)
        {
            s->start = 0;
        }
        else
        {
            s->start += 1;
        }
        s->event_cnt -= 1;
    }
    return ret;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
State LookupTransition(StateMachine* s, uint8_t event)
{
    uint8_t i = 0;
    State ret_state = s->state;

    // if the event is idle or enter/exit just return state)
    if (event != IDLE && event != ENTER && event != EXIT)
    {
        // if event is a new event find the transition
        for (i = 0; i < s->transition_table_size; i++)
        {
            if (s->transitions[i].current_state == s->state &&
                s->transitions[i].event_code    == event)
            {
                ret_state = s->transitions[i].next_state;
                break;
            }
        }
    }

    return ret_state;
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
void StateMachineRun(StateMachine* s)
{
    // get the next event
    uint8_t event = CheckEventQueue(s);
    // run the state
    (s->state)(event);
    // check for state transitions
    s->state = LookupTransition(s, event);
}
