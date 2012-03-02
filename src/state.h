#ifndef STATE_H
#define STATE_H

typedef void (*State)(uint8_t);

// events (the following line is preprocessor sin)
#define DEFAULT_EVENTS IDLE=0,ENTER=1,EXIT=2

typedef struct
{
    State   current_state;
    uint8_t event_code;
    State   next_state;
}Transition;

extern void    StateMachineInit(Transition *state_transitions, uint8_t t_size);
static uint8_t CheckEventQueue(State state);
static uint8_t QueuePeek(void);
static State   LookupTransition(State state, uint8_t event);
extern int8_t  EnqueueEvent(uint8_t event);
static uint8_t DequeueEvent(void);
static uint8_t DequeueTransitionEvent(void);
extern void    StateRun(State* state);

#endif
