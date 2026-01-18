#include "hal/hal_pwm.h"


uint8_t Timer1_TCCR1A_val = 0; //initially setting for 10-bit fast pwm
uint8_t Timer1_TCCR1B_val = 0; //setting for clk/256 prescalar

uint16_t Timer1_OCR1A_val = 0; //intial zero after update by duty 
uint16_t Timer1_OCR1B_val = 0; //intial zero after update by duty 
uint16_t Timer1_ICR1_val = 0; //intial zero after update by frequemcy

uint16_t TOP = 0;
uint16_t duty_channel_A = 0;
uint16_t duty_channel_B = 0;
void hal_pwm_init(uint16_t frequency){
    TOP = (16000000UL/(256UL*frequency))-1;
    Timer1_ICR1_val = TOP;

    Timer1_TCCR1A_val =  0x02; //fast pwm wgm13:10 = 1110 mode 14
    Timer1_TCCR1B_val =  0x18;
    volatile uint8_t *Timer1_TCCR1A = (volatile uint8_t *)0x80;
   
    volatile uint8_t *Timer1_TCCR1B = (volatile uint8_t *)0x81;
    
    volatile uint16_t *Timer1_ICR1 = (volatile uint16_t *)0x86;
    
    *Timer1_TCCR1A = 0;
    *Timer1_TCCR1B = 0;
    
    //initializing the Fast PWM using TOP as ICR1
    
    *Timer1_ICR1 = Timer1_ICR1_val;
    *Timer1_TCCR1A = Timer1_TCCR1A_val;
    *Timer1_TCCR1B = Timer1_TCCR1B_val;
    //initializing the prescalar to 256
   
    *Timer1_TCCR1B |= 0x04 ;
    
   
}

void hal_pwm_channel_init(char channel){
    volatile uint8_t *Timer1_TCCR1A = (volatile uint8_t *)0x80;
    volatile uint8_t *DDRB   = (volatile uint8_t *)0x24;
    if(channel == 1 || channel == 'A'){
        Timer1_TCCR1A_val |= 0x80;
        *Timer1_TCCR1A = Timer1_TCCR1A_val;
        *DDRB |= (1 << 1);  
        volatile uint16_t *Timer1_OCR1A = (volatile uint16_t *)0x88;
        Timer1_OCR1A_val = 0;
        *Timer1_OCR1A = 0;
    }else if(channel == 2 || channel == 'B'){
        Timer1_TCCR1A_val |=  0x20;
        *Timer1_TCCR1A = Timer1_TCCR1A_val;
        *DDRB |= (1 << 2);  
        volatile uint16_t *Timer1_OCR1B = (volatile uint16_t *)0x8A;
        Timer1_OCR1B_val = 0;
        *Timer1_OCR1B = 0;
    }
}
void hal_pwm_set_duty(char channel,uint8_t duty){
    uint16_t OCR; 
    if(duty >= 0 && duty <= 100){
        OCR = (duty * (TOP + 1))/100;
    }else {
        OCR = 0;
    }
    if(channel == 1 || channel == 'A'){
        duty_channel_A = OCR;
    }else if(channel == 2 || channel == 'B') {
        duty_channel_B = OCR;
    }
}
void hal_pwm_start(uint8_t channel){
    if(channel == 1 || channel == 'A'){
        volatile uint16_t *Timer1_OCR1A = (volatile uint16_t *)0x88;
        *Timer1_OCR1A = duty_channel_A;
    }else if(channel == 2 || channel == 'B'){
        volatile uint16_t *Timer1_OCR1B = (volatile uint16_t *)0x8A;
        *Timer1_OCR1B = duty_channel_B;
    }
}
void hal_pwm_stop(uint8_t channel){
    if(channel == 1 || channel == 'A'){
        volatile uint16_t *Timer1_OCR1A = (volatile uint16_t *)0x88;
        *Timer1_OCR1A = 0;
    }else if(channel == 2 || channel == 'B'){
        volatile uint16_t *Timer1_OCR1B = (volatile uint16_t *)0x8A;
        *Timer1_OCR1B = 0;
    }
}