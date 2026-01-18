#include <Arduino.h>
#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
uint16_t a0;
void setup() { 
Serial.begin(9600);
int j=100;
hal_gpio_init(13,'O');
hal_timer_compare(1,0,10000,1);
char output = 1;
hal_enable_interrupt();

    while (1)
    {
        //Serial.println("In Loop");
        if(check_timer1_A()==1){
            Serial.println(j);
            j--;
            hal_gpio_write(13,output);
            if(output==1){
                output=0;
            }
            else{
                output=1;
            }
        } 
        
    }
}
void loop() {
}