#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_pwm.h"
#include "drivers/seven_segment.h"

int main(void) { 
   seven_segment_init(2,3,4,5,6,7,8,9,'A');
  hal_gpio_init(14,'O');
  hal_gpio_init(15,'O');
  char ones,tens;
 
  while(1){
    for(tens = 0;tens < 10;tens++){
      for(ones = 0;ones <10;ones++){
        uint8_t p =50;
        while(p){
          seven_segment_display(tens,'-');
          hal_gpio_write(14,1);
          delay_milli(1);
          hal_gpio_write(14,0);

          seven_segment_display(ones,'-');
          hal_gpio_write(15,1);
          delay_milli(1);
          hal_gpio_write(15,0);
          p--;
        }
      }
    }
  }
  
}
