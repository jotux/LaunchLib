#include "global.h"
#include "state.h"

int event = 0;

uint8_t CheckEventQueue(void)
{
    if (event)
    {
        event = 0;
        return 1;
    }
    return 0;
}

int8_t EnqueueEvent(uint8_t event)
{
	return 0;
}
int8_t DequeueEvent(uint8_t event)
{
	return 0;
}

State LookupTransition(State state, uint8_t event, transition t[], uint8_t t_size)
{
	uint8_t cnt;
    for (cnt = 0;cnt < t_size;cnt++)
    {
        if (t[cnt].current_state == state &&
            t[cnt].event_code    == event)
        {
            return t[cnt].next_state;
        }
    }
    return 0;
}
