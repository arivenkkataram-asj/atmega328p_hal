#include "hal/hal_timer.h"
#include <stdint.h>
#include "avr/interrupt.h"
#include "hal/hal_gpio.h"
#include "hal/hal_interrupt.h"

// F_CPU = 16 MHz
// Prescaler = 256
// Timer tick = 16,000,000 / 256 = 62,500 Hz
// OCRA1A = 62 --> ~1ms 
// by using logic analyzer time is 1.004ms

volatile uint32_t counter=0;
//uint8_t output = 0;
/*
    com1A initial 0x00; for the normal port operation
    com1B initial 0x00; for the normal port operation
*/
/*
    WGM13  WGM12 WGM11 WGM10
     0      0     0     0   ---> Normal
     0      0     0     1   ---> PWM,phase correct,8-bit
     0      0     1     0   ---> PWM, phase correct, 9-bit
     0      0     1     1   ---> PWM, phase correct, 10-bit
     0      1     0     0   ---> CTC
     0      1     0     1   ---> Fast PWM, 8-bit
     0      1     1     0   ---> Fast PWM, 9-bit
     0      1     1     1   ---> Fast PWM, 10-bit
     1      0     0     0   ---> PWM, phase and frequency correct
     1      0     0     1   ---> PWM, phase and frequency correct
     1      0     1     0   ---> PWM, phase correct
     1      0     1     1   ---> PWM, phase correct
     1      1     0     0   ---> CTC
     1      1     0     1   ---> (Reserved)
     1      1     1     0   ---> Fast PWM
     1      1     1     1   ---> Fast PWM
*/


/*
    CS12  CS11  CS10  Description
     0     0     0     No clock source
     0     0     1     clkI/O/1 (no prescaling)
     0     1     0     clkI/O/8 (from prescaler)
     0     1     1     clkI/O/64 (from prescaler)
     1     0     0     clkI/O/256 (from prescaler)
     1     0     1     clkI/O/1024 (from prescaler)
     1     1     0     External clock source on T1 pin. Clock on falling edge.
     1     1     1     External clock source on T1 pin. Clock on rising edge.
*/

uint8_t TCCR0A_val = 0x02; //initial value of Control Register A
uint8_t TCCR0B_val = 0x04; //initial value of Coltrol Register B
uint8_t TCNT0_val = 0x00; //start value of time counter
uint8_t TIMSK0_val = 0x02;
uint8_t compare_val = 62 ;

void hal_systick_init(){
    volatile uint8_t *Timer0_TCCR0A = (volatile uint8_t *)0x44;
    volatile uint8_t *Timer0_TCCR0B = (volatile uint8_t *)0x45;
    volatile uint8_t *Timer0_TCNT0 = (volatile uint8_t *)0x46;
    volatile uint8_t *Timer0_TIMSK0 = (volatile uint8_t *)0x6E;
    *Timer0_TCCR0A = 0;
    *Timer0_TCCR0B = 0;
    *Timer0_TCNT0 = 0;
    volatile uint8_t *Timer0_OCR0A = (volatile uint8_t *)0x47;
    *Timer0_TCNT0 = TCNT0_val;
    *Timer0_TCCR0A = TCCR0A_val;
    *Timer0_OCR0A = compare_val;
    *Timer0_TCCR0B = TCCR0B_val;
    *Timer0_TIMSK0 = TIMSK0_val;
} 


ISR(TIMER0_COMPA_vect){
   counter ++;
}


uint32_t hal_timer_get_ticks(){
    hal_disable_interrupt();
    uint32_t counters = counter;
    hal_enable_interrupt();
    return counters;
}

uint32_t hal_millis(){
    return hal_timer_get_ticks();
}

void hal_delay_ms(uint32_t ms){
    uint32_t start = hal_millis();
    while((hal_millis()- start) < ms);  
}

uint8_t hal_timeout_expired(uint32_t start,uint32_t duration){
    if((hal_millis() - start)>= duration){
        return 1;
    }
    else{
        return 0;
    }
}