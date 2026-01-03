#include "hal/hal_adc.h"
#include <stdint.h>
//initial_admux 
//setting as the Internal 1.1V voltage reference with external caoacitor at AREF
uint8_t REFS1 = 0x80; uint8_t REFS0 = 0x40;
uint8_t ADLAR = 0x00; //setting a the Right adjusted.

//ADCSRA - ADC Control and status Register A
/*
    ADCSRA_bit_0 -- ADPS0 = 1  |
    ADCSRA_bit_1 -- ADPS1 = 1  | for the 128 prescalar
    ADCSRA_bit_2 -- ADPS2 = 1  |
    ADCSRA_bit_3 -- ADIE = 0 For the ADC Interrupt Enable
    ADCSRA_bit_4 -- ADIF = 1 For the ADC Interrupt Flag
    ADCSRA_bit_5 -- ADATE = 0 For the ADC Auto Trigger Enable
    ADCSRA_bit_6 -- ADSC = 1 Start Conversion 
    ADCSRA_bit_7 -- ADEN = 1 ADEN Enable;
    Then ADCSRA_bit_0_7 = 0xD7;
*/
uint8_t ADCSRA_bit_0_7 = 0xD7;

uint8_t input_buffer = 0x00;
//Analog value


void disable_input_buffer(uint8_t pin){
    volatile uint8_t *didr_0 = (uint8_t *)0x7E;
    input_buffer = input_buffer | (1<<(pin));
    *didr_0 = input_buffer; 
}

void enable_input_buffer(uint8_t pin){
    volatile uint8_t *didr_0 = (uint8_t *)0x7E;
    input_buffer = input_buffer & (~(1 << pin));
    *didr_0 = input_buffer;
}

void ADMUX_init(uint8_t ch){
    volatile uint8_t *ADMUX = (uint8_t *)0x7C;
    *ADMUX = (REFS0 | REFS1 | ADLAR) | ch;
}

void ADCSRA_control_status(){
    volatile uint8_t *ADCSRA = (volatile uint8_t *)0x7A;
    *ADCSRA = ADCSRA_bit_0_7;
    uint8_t status = 1;
    while(status != 0){
        status = (*ADCSRA & 0x40) == 0x40;
    }
}

uint8_t read_ADCL(){
    volatile uint8_t *ADCL = (volatile uint8_t *)0x78;
    return *ADCL;
}

uint8_t read_ADCH(){
    volatile uint8_t *ADCH = (volatile uint8_t *)0x79;
    return *ADCH;
}


uint16_t hal_adc_read(uint8_t channel){
    if(channel >= 0 && channel <= 7){
        disable_input_buffer(channel);
        ADMUX_init(channel);
        ADCSRA_control_status();
        uint8_t ADCL_data = read_ADCL();
        uint8_t ADCH_data = read_ADCH();
        uint16_t analog_value = (ADCH_data << 8) + ADCL_data;
        return analog_value;
    }else{
        return 0;
    }
}