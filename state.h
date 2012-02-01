#ifndef STATE_H
#define STATE_H

typedef void (*State)(uint8_t);

typedef struct
{
    State   current_state;
    uint8_t event_code;
    State   next_state;
}transition;

uint8_t CheckEventQueue(void);
void    QueueEvent(uint8_t event);
State LookupTransition(State state, uint8_t event, transition t[], uint8_t t_size);
int8_t  EnqueueEvent(uint8_t event);
int8_t  DequeueEvent(uint8_t event);

extern int event;

#endif
