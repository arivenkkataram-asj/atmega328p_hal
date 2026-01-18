#include "hal/hal_interrupt.h"
#include <stdint.h>

void hal_enable_interrupt(){
    volatile uint8_t *SREG = (volatile uint8_t *)0x5F;
    *SREG = *SREG | 0x80;
}

void hal_disable_interrupt(){
    volatile uint8_t *SREG = (volatile uint8_t *)0x5F;
    *SREG = *SREG & (~0x80);
}