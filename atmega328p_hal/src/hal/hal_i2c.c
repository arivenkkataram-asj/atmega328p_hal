#include "hal/hal_i2c.h"

uint8_t start_transmitted = 0;
uint8_t repeted_start_transmitted = 0;

void hal_i2c_init(uint32_t clock_hz){
    uint8_t prescalar = 1;
    uint8_t i2c_TWBR_data = ((16000000/clock_hz) - 16)/(2*prescalar);
    
    volatile uint8_t *i2c_TWBR = (volatile uint8_t *)0xB8;
    *i2c_TWBR = i2c_TWBR_data;

    volatile uint8_t *i2c_TWSR = (volatile uint8_t *)0xB9;
    *i2c_TWSR = 0x00;  //setting prescalar

    volatile uint8_t *i2c_TWCR = (volatile uint8_t *)0xBC;
    *i2c_TWCR = 0x84;


    
}

uint8_t hal_i2c_start(uint8_t address_rw){
    volatile uint8_t *i2c_TWCR = (volatile uint8_t *)0xBC;
    *i2c_TWCR = 0xA4;
    
    while(!(*i2c_TWCR & 0x80));
    
    volatile uint8_t *i2c_TWSR = (volatile uint8_t *)0xB9;
    if((*i2c_TWSR & 0xF8)== 0x08){
        start_transmitted = 1;
    }else if((*i2c_TWSR & 0xF8)== 0x10){
        repeted_start_transmitted = 1;
    }else {
        return 0;
    }
    
    volatile uint8_t *i2c_TWDR = (volatile uint8_t *)0xBB;
    *i2c_TWDR = address_rw;

    *i2c_TWCR = 0x84;
    while(!(*i2c_TWCR & 0x80));
    
    if(((*i2c_TWSR & 0xF8)== 0x40) || ((*i2c_TWSR & 0xF8)== 0x18)){
        return 1;
    }else if(((*i2c_TWSR & 0xF8)== 0x20) || ((*i2c_TWSR & 0xF8)== 0x48)){
        return 2;
    }else {
        return 0;
    }
}


uint8_t hal_i2c_write(uint8_t data){
    volatile uint8_t *i2c_TWDR = (volatile uint8_t *)0xBB;
    *i2c_TWDR = data;

    volatile uint8_t *i2c_TWCR = (volatile uint8_t *)0xBC;
    *i2c_TWCR = 0x84;

    while(!(*i2c_TWCR & 0x80));

    volatile uint8_t *i2c_TWSR = (volatile uint8_t *)0xB9;

    if(((*i2c_TWSR & 0xF8)== 0x28)){
        return 1;
    }else if(((*i2c_TWSR & 0xF8)== 0x30)){
        return 2;
    }else {
        return 0;
    }
}

int16_t hal_i2c_read_ack(){
    volatile uint8_t *i2c_TWCR = (volatile uint8_t *)0xBC;
    *i2c_TWCR = 0xC4;

    while(!(*i2c_TWCR & 0x80));
    uint8_t data_ack = 0;
    volatile uint8_t *i2c_TWDR = (volatile uint8_t *)0xBB;
    volatile uint8_t *i2c_TWSR = (volatile uint8_t *)0xB9;
    if(((*i2c_TWSR & 0xF8)== 0x50)){
        return *i2c_TWDR;
    }else if(((*i2c_TWSR & 0xF8)== 0x58)){
        return -2;
    }else {
        return -1;
    }
   
}

int hal_i2c_read_nack(){
    volatile uint8_t *i2c_TWCR = (volatile uint8_t *)0xBC;
    *i2c_TWCR = 0x84;

    while(!(*i2c_TWCR & 0x80));
    volatile uint8_t *i2c_TWDR = (volatile uint8_t *)0xBB;
    volatile uint8_t *i2c_TWSR = (volatile uint8_t *)0xB9;
    
    if(((*i2c_TWSR & 0xF8)== 0x58)){
        return *i2c_TWDR;
    }else {
        return -1;
    }
}

void hal_i2c_stop(){
    volatile uint8_t *i2c_TWCR = (volatile uint8_t *)0xBC;
    *i2c_TWCR = 0x94;
}

void hal_i2c_set_slave_address(uint8_t addr){
    volatile uint8_t *i2c_TWAR = (volatile uint8_t *)0xBA;
    *i2c_TWAR = addr<<1;
}

uint8_t hal_i2c_slave_listen(){
    volatile uint8_t *i2c_TWCR = (volatile uint8_t *)0xBC;
    *i2c_TWCR = 0xC4;

    while(!(*i2c_TWCR & 0x80));

    volatile uint8_t *i2c_TWSR = (volatile uint8_t *)0xB9;
    if(((*i2c_TWSR & 0xF8)== 0x60)){
        return 1;
    }else if(((*i2c_TWSR & 0xF8)== 0xA8)){
        return 2;
    } else if ((*i2c_TWSR & 0xF8)== 0x70){
        return 3;
    }else {
        return 0;
    }

}

int hal_i2c_slave_read(){
    volatile uint8_t *i2c_TWCR = (volatile uint8_t *)0xBC;
    *i2c_TWCR = 0xC4;

    while(!(*i2c_TWCR & 0x80));
    
    volatile uint8_t *i2c_TWDR = (volatile uint8_t *)0xBB;
    volatile uint8_t *i2c_TWSR = (volatile uint8_t *)0xB9;
    if(((*i2c_TWSR & 0xF8)== 0x80)){
        return *i2c_TWDR;
    }else if(((*i2c_TWSR & 0xF8)== 0xA0)){
        return -2;
    }else {
        return -1; //error
    }
}

uint8_t hal_i2c_slave_write(uint8_t data){
    volatile uint8_t *i2c_TWDR = (volatile uint8_t *)0xBB;
    *i2c_TWDR = data;

    volatile uint8_t *i2c_TWCR = (volatile uint8_t *)0xBC;
    *i2c_TWCR = 0xC4;

    while(!(*i2c_TWCR & 0x80));

    volatile uint8_t *i2c_TWSR = (volatile uint8_t *)0xB9;

    if(((*i2c_TWSR & 0xF8)== 0xB8)){
        return 1;
    }else if(((*i2c_TWSR & 0xF8)== 0xC0)){
        return 2;
    }else if(((*i2c_TWSR & 0xF8)== 0xC8)){
        return 3;
    }else {
        return 0;
    }
}