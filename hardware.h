#ifndef HARDWARE_H
#define HARDWARE_H

// clock settings
#define CLOCK_DCO   16000000   // DCO freq
#define CLOCK_EXT   32768      // ext clock freq

// based on 0.5 millisecond timer period
#define _millisecond   2
#define _second        2000
#define _minute        120000
#define _hour          7200000

// hardware config
#ifdef BARE_LAUNCHPAD
    #define RED_LED_PORT  1
    #define RED_LED_PIN   0
    #define RED_LED_OFF()    SET_LOW(RED_LED);
    #define RED_LED_ON()     SET_HIGH(RED_LED);
    #define RED_LED_TOGGLE() TOGGLE(RED_LED);
    
    #define PWM_0_PORT 1
    #define PWM_0_PIN  2
    
    #define PWM_1_PORT 2
    #define PWM_1_PIN  1
#endif

#ifdef LINE_FOLLOWER_R1
    #define SW_1_PORT 2
    #define SW_1_PIN  3
    
    #define IR_LEFT_CORNER_PORT 1
    #define IR_LEFT_CORNER_PIN  7
    
    #define IR_LEFT_MIDDLE_PORT 1
    #define IR_LEFT_MIDDLE_PIN  6
        
    #define IR_RIGHT_CORNER_PORT 2
    #define IR_RIGHT_CORNER_PIN  4
    
    #define IR_RIGHT_MIDDLE_PORT 2
    #define IR_RIGHT_MIDDLE_PIN  5
    
    #define MOTOR_1_DIR_1_PORT 1
    #define MOTOR_1_DIR_1_PIN  5
    
    #define MOTOR_1_DIR_2_PORT 2
    #define MOTOR_1_DIR_2_PIN  0
    
    #define MOTOR_1_PWM_PORT 2
    #define MOTOR_1_PWM_PIN  1
       
    #define MOTOR_2_DIR_1_PORT 1
    #define MOTOR_2_DIR_1_PIN  4
    
    #define MOTOR_2_DIR_2_PORT 1
    #define MOTOR_2_DIR_2_PIN  3
    
    #define MOTOR_2_PWM_PORT 1
    #define MOTOR_2_PWM_PIN  2    
#endif

#ifdef LINE_FOLLOWER_R2
    #define SW_1_PORT 2
    #define SW_1_PIN  4
    
    #define IR_LEFT_CORNER_PORT 2
    #define IR_LEFT_CORNER_PIN  3
    
    #define IR_LEFT_MIDDLE_PORT 2
    #define IR_LEFT_MIDDLE_PIN  2
        
    #define IR_RIGHT_CORNER_PORT 1
    #define IR_RIGHT_CORNER_PIN  0
    
    #define IR_RIGHT_MIDDLE_PORT 1
    #define IR_RIGHT_MIDDLE_PIN  1
    
    #define MOTOR_1_DIR_1_PORT 1
    #define MOTOR_1_DIR_1_PIN  5
    
    #define MOTOR_1_DIR_2_PORT 2
    #define MOTOR_1_DIR_2_PIN  0
    
    #define MOTOR_1_PWM_PORT 2
    #define MOTOR_1_PWM_PIN  1
       
    #define MOTOR_2_DIR_1_PORT 1
    #define MOTOR_2_DIR_1_PIN  4
    
    #define MOTOR_2_DIR_2_PORT 1
    #define MOTOR_2_DIR_2_PIN  3
    
    #define MOTOR_2_PWM_PORT 1
    #define MOTOR_2_PWM_PIN  2  
#endif

#endif
