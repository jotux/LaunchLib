#ifndef STATE_H
#define STATE_H

typedef void (*State)(uint8_t);

#define MAX_EVENT_NUM 16

// events (the following line is preprocessor sin)
#define DEFAULT_EVENTS IDLE=0,ENTER=1,EXIT=2

typedef struct
{
    State   current_state;
    uint8_t event_code;
    State   next_state;
}transition;

void    StateMachineInit(transition *state_transitions, uint8_t t_size);
uint8_t CheckEventQueue(State state);
uint8_t QueuePeek(void);
void    QueueEvent(uint8_t event);
State   LookupTransition(State state, uint8_t event);
int8_t  EnqueueEvent(uint8_t event);
uint8_t DequeueEvent(void);
uint8_t DequeueTransitionEvent(void);

#endif
