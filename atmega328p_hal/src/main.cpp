#include <Arduino.h>
#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
char string[] = "Wellcome"; 
void setup() {
    hal_gpio_init(8,'O');
    
    while (1)
    {
        hal_gpio_write(8,1);
        delay_milli(1);
        hal_gpio_write(8,0);
        delay_milli(1);
    }
        
}
void loop() {
}