#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_pwm.h"
#include "drivers/seven_segment.h"

int main(void) { 
    hal_systick_init();
    hal_enable_interrupt();
    hal_gpio_init(13,'O');
    uint32_t LED_timer = 0;
    uint8_t LED_out = 0;
    while(1){
         if(hal_timeout_expired(LED_timer,250)){
                LED_timer = hal_millis();
                LED_out ^= 1;
                hal_gpio_write(13,LED_out);  
            }
    }
  
}
