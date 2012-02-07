#ifndef _I2C_H
#define _I2C_H

void I2cInit(void);
void ChangeState(uint8_t in_state);
void set_bits_remaining(uint8_t cnt);
enum
{
    IDLE,
    GET_ADDRESS,     
    CHECK_ADDRESS,
    SEND_DATA,
    RECEIVE_DATA,
    CHECK_DATA,
    GET_ACK,          
    CHECK_ACK
};

#define DATA_OUTPUT() {USICTL0 |= USIOE;}
#define DATA_INPUT()  {USICTL0 &= ~USIOE;}
#define CLEAR_START() {USICTL1 &= ~USISTTIFG;}
#define CLEAR_INT()   {USICTL1 &= ~USIIFG;}
#define START_ISSUED  (USICTL1 & USISTTIFG)

#define DATA_BUFFER    USISRL
#define DATA_ACK       0x00
#define DATA_NACK      0xFF
#define ADDRESS_MASK   0xFE
#define READ_BIT       0x01
#define BIT_COUNT_MASK 0x1F

#define NACK_RESPONSE  0x01


#endif // _I2C_H