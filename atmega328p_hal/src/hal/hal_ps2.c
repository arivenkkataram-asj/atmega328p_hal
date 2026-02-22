#include "hal/hal_ps2.h"
#include "avr/interrupt.h"
#include "hal/hal_gpio.h"
#include <stdbool.h>
#include "hal/hal_interrupt.h"

uint8_t data_pin = 8;
uint8_t clock_pin = 2;

volatile uint8_t bitCount = 0; 
volatile uint8_t dataByte = 0;
volatile bool dataReady_flag = false;

void hal_ps2_init(){
    hal_gpio_init(data_pin,'I');
    hal_gpio_pullup(data_pin);
    hal_gpio_init(clock_pin,'I');
    hal_gpio_pullup(clock_pin);

    //interrupt enable for INT0 falling edge
    volatile uint8_t *External_interrupt_0 = (volatile uint8_t *)0x69;
    *External_interrupt_0 = 0x02;

    volatile uint8_t *External_interrupt__mask_0 = (volatile uint8_t *)0x3D;
    *External_interrupt__mask_0 = 0x01;

    bitCount =0;
    dataByte = 0;
    dataReady_flag = 0;
}

ISR(INT0_vect){
    uint8_t bit = hal_gpio_read(data_pin);
    if(bitCount > 0 && bitCount < 9){
        dataByte = dataByte >> 1;
        if(bit) dataByte |= 0x80;
    }
    bitCount++;    
    if(bitCount == 11){
        dataReady_flag = true;
        bitCount = 0;
    }
}

uint8_t hal_ps2_available(){
    return dataReady_flag;   
}

uint8_t hal_ps2_read_scan_code(){
    if(dataReady_flag){
        hal_disable_interrupt();
        uint8_t raw_data = dataByte;
        dataReady_flag = false;
        bitCount = 0;
        dataByte = 0;
        hal_enable_interrupt();
        return raw_data;
    }
    else {
        return 0;
    }   
}

