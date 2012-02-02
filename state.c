#include "global.h"
#include "state.h"

// A pointer to the transition table along with a size is saved locally
transition* transition_table;
uint8_t transition_table_size;

// The event queue is a FIFO implemented as a circular buffer
uint8_t index = 0;
uint8_t size  = 0;
uint8_t queue[MAX_EVENT_NUM];

void StateMachineInit(transition *state_transitions, uint8_t size)
{
    transition_table = state_transitions;
    transition_table_size = (size / sizeof(transition));
}

uint8_t CheckEventQueue(void)
{
    return DequeueEvent();
}

int8_t EnqueueEvent(uint8_t event)
{
    // event queue full?
    if (size == MAX_EVENT_NUM)
    {
        return (-1);
    }
    // add event to queue
    queue[((index + size) == MAX_EVENT_NUM) ? 0 : (index + size)] = event;
    // adjust the size
    size++;
    return (0);
}

uint8_t DequeueEvent(void)
{
    int8_t ret = 0;

    // nothing in the queue?
    if (size == 0)
    {
        return (0);
    }
    // save the value we will return
    ret = queue[index];
    // adjust the index
    index = (index == (MAX_EVENT_NUM - 1)) ? 0 : (index + 1);
    // adjust the size
    size--;
	return ret;
}

State LookupTransition(State state, uint8_t event)
{
	uint8_t cnt;
    // if the event is 0 (idle) just return state)
    if (event == 0)
    {
        return state;
    }
    else
    {
        // if event is a new event find the transition
        for (cnt = 0;cnt < transition_table_size;cnt++)
        {
            if (transition_table[cnt].current_state == state &&
                transition_table[cnt].event_code    == event)
            {
                return transition_table[cnt].next_state;
            }
        }
    }
    // if the transition wasn't found, return the state
    return state;
}
