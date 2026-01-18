#include <Arduino.h>
#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_pwm.h"
uint16_t a0;

void setup() { 
hal_systick_init();
hal_enable_interrupt();
hal_pwm_init(15000);
hal_pwm_channel_init(2);
hal_pwm_set_duty(2,0);
hal_pwm_channel_init(1);
hal_pwm_set_duty(1,0);
    while (1)
    {
       for(char i=0;i<=100;i++){
        hal_pwm_set_duty(2,i);
        hal_pwm_start(2);
        delay_milli(100);
       }
       hal_pwm_stop(2);
       hal_pwm_stop(1);
       hal_delay_ms(10000);
       for(char i=100;i>=0;i--){
        hal_pwm_set_duty(1,i);
        hal_pwm_start(1);
        delay_milli(100);
       }
       hal_pwm_stop(1);
        


        
    }
}
void loop() { 
}