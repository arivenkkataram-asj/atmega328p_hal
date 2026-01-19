#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_pwm.h"
#include "drivers/keypad_4x4.h"

int main(void) { 
   hal_gpio_init(13,'O');
  keypad_4x4_init(2,3,4,5,6,7,8,9,'E');
  while(1){
    uint8_t read = keypad_4x4_read();
    delay_milli(10);
    if(read == 9){
    hal_gpio_write(13,1);
    }else{
      hal_gpio_write(13,0);
    }
  }
  
}
