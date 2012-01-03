#include "global.h"
#include "hardware.h"
#include "timer.h"
#include "init.h"
#include "callback.h"
#include "pwm.h"
#include "adc.h"
#include "interrupt.h"
#include "delay.h"

void BlinkRedLed(void);
enum {MOTOR_STOP, MOTOR_FORWARD, MOTOR_REVERSE, MOTOR_BRAKE};
void SetMotor(uint8_t motor, uint8_t dir, uint8_t speed);
void Delay(uint32_t delay_time);

void main(void)
{
    WD_STOP();
    SET_CLOCK(16);
    
    CallbackTimerInit();
    HardwareInit();
    PwmInit(0);
    PwmInit(1);
	//AdcInit(3);
	
    //CallbackRegister(BlinkRedLed, 100ul * _millisecond);    
    //CallbackMode(BlinkRedLed, ENABLED);

    SET_LOW(MOTOR_1_DIR_1);
    SET_LOW(MOTOR_1_DIR_2);
    SET_LOW(MOTOR_2_DIR_1);
    SET_LOW(MOTOR_2_DIR_2);
    

    PwmSetPeriod(0,15000);
    PwmSetPeriod(1,15000);
    _EINT();
    
    while(1)
    {
        if (READ_IN(IR_LEFT_CORNER) && READ_IN(IR_RIGHT_CORNER))
        {
            SetMotor(0,MOTOR_FORWARD,30);
            SetMotor(1,MOTOR_FORWARD,30);
        }
        else if (READ_IN(IR_LEFT_CORNER))
        {
            SetMotor(0,MOTOR_FORWARD,30);
            SetMotor(1,MOTOR_FORWARD,5);
        }
        else if (READ_IN(IR_RIGHT_CORNER))
        {
            SetMotor(0,MOTOR_FORWARD,5);
            SetMotor(1,MOTOR_FORWARD,30);
        }
        else
        {
            SetMotor(0,MOTOR_STOP,5);
            SetMotor(1,MOTOR_STOP,5);
        }
    }
}


void Delay(uint32_t delay_time)
{
    volatile uint32_t start_time = now;
    while(now < start_time + delay_time)
    {
        // wait here until time has elapsed
    }
}

void BlinkRedLed(void)
{
	RED_LED_TOGGLE();
}


void SetMotor(uint8_t motor, uint8_t dir, uint8_t speed)
{
    if (motor == 0)
    {
        switch(dir)
        {
            case MOTOR_STOP:
                SET_LOW(MOTOR_1_DIR_1);
                SET_LOW(MOTOR_1_DIR_2);
                break;
            case MOTOR_FORWARD:
                SET_LOW(MOTOR_1_DIR_1);
                SET_HIGH(MOTOR_1_DIR_1);
                break;
            case MOTOR_REVERSE:
                SET_LOW(MOTOR_1_DIR_2);
                SET_HIGH(MOTOR_1_DIR_2);
                break;
            case MOTOR_BRAKE:
                SET_HIGH(MOTOR_1_DIR_1);
                SET_HIGH(MOTOR_1_DIR_2);
                break;
        }
    }
    else
    {
        switch(dir)
        {
            case MOTOR_STOP:
                SET_LOW(MOTOR_2_DIR_1);
                SET_LOW(MOTOR_2_DIR_2);
                break;
            case MOTOR_FORWARD:
                SET_LOW(MOTOR_2_DIR_1);
                SET_HIGH(MOTOR_2_DIR_2);
                break;
            case MOTOR_REVERSE:
                SET_HIGH(MOTOR_2_DIR_1);
                SET_LOW(MOTOR_2_DIR_2);
                break;
            case MOTOR_BRAKE:
                SET_HIGH(MOTOR_2_DIR_1);
                SET_HIGH(MOTOR_2_DIR_2);
                break;
        }
    }
    PwmSetDuty(motor, speed);
}

