#include "global.h"
#include "i2c.h"
#include "hardware.h"

uint8_t cnt = 0;
uint8_t state;
uint8_t reg_to_read = 0;

#pragma vector = USI_VECTOR
__interrupt void USI_TXRX (void)
{
    if (START_ISSUED)
    {
        ChangeState(GET_ADDRESS);
    }

    switch(state)
    {
        case GET_ADDRESS:
            set_bits_remaining(8);
            CLEAR_START();
            ChangeState(CHECK_ADDRESS);
            break;
        case CHECK_ADDRESS:
            if ((DATA_BUFFER & ADDRESS_MASK) == SLAVE_ADDRESS)
            {
                ChangeState(DATA_BUFFER & READ_BIT ? SEND_DATA : RECEIVE_DATA);
                DATA_BUFFER = DATA_ACK;
            }
            else // address did not match
            {
                DATA_INPUT();
                // TODO: should we just ignore bad addresses?
                DATA_BUFFER = DATA_NACK;         // Send NAck
                ChangeState(IDLE);
            }
            set_bits_remaining(1);
            break;
        case SEND_DATA:
            DATA_OUTPUT();
            DATA_BUFFER = cnt++;
            set_bits_remaining(8);
            ChangeState(GET_ACK);
            break;
        case RECEIVE_DATA:
            DATA_INPUT();
            set_bits_remaining(8);
            ChangeState(CHECK_DATA);
            break;
        case CHECK_DATA:
            DATA_OUTPUT();
            DATA_BUFFER = DATA_ACK;
            set_bits_remaining(1);
            ChangeState(CHECK_ACK);
            break;
        case GET_ACK:
            DATA_INPUT();
            set_bits_remaining(1);
            ChangeState(CHECK_ACK);
            break;
        case CHECK_ACK:
            if (DATA_BUFFER & NACK_RESPONSE)
            {
                DATA_INPUT();
                ChangeState(IDLE);
            }
            else // ACK from master
            {
                DATA_INPUT();
                ChangeState(IDLE);
            }
            break;
        default:
            break;
    }
    CLEAR_INT();
}

void I2cInit(void)
{
    // Config IO
    SET_HIGH(I2C_DATA);
    SET_HIGH(I2C_CLK);
    SET_RUP(I2C_DATA);
    SET_RUP(I2C_CLK);
    MAKE_OUTPUT(I2C_DATA);
    MAKE_INPUT(I2C_CLK);

    USICTL0 = USIPE6 + USIPE7 + USISWRST;   // Port & USI mode setup
    USICTL1 = USII2C + USIIE + USISTTIE;    // Enable I2C mode & USI interrupts
    USICKCTL = USICKPL;                     // Setup clock polarity
    USICNT |= USIIFGCC;                     // Disable automatic clear control
    USICTL0 &= ~USISWRST;                   // Enable USI
    USICTL1 &= ~USIIFG;                     // Clear pending flag
}

void ChangeState(uint8_t in_state)
{
    state = in_state;
}

void set_bits_remaining(uint8_t cnt)
{
    USICNT |= cnt & BIT_COUNT_MASK;
}
