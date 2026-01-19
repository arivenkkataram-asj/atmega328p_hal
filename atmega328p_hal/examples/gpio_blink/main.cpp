#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_pwm.h"
int main(void) { 
    hal_gpio_init(13,'O');
    hal_gpio_init(12,'O');
    hal_gpio_init(11,'O');
    hal_gpio_init(10,'O');
    hal_gpio_init(9,'O');
    hal_gpio_init(8,'O');

    while(1){
        hal_gpio_write(12,1);
        hal_gpio_write(13,1);
        hal_gpio_write(11,0);
        hal_gpio_write(10,0);
        hal_gpio_write(9,1);
        hal_gpio_write(8,1);
        delay_milli(100);
        hal_gpio_write(13,0);
        hal_gpio_write(12,0);
        hal_gpio_write(11,1);
        hal_gpio_write(10,1);
        hal_gpio_write(9,0);
        hal_gpio_write(8,0);
        delay_milli(100);
    }
  
}
