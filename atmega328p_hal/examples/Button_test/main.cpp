#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_pwm.h"
int main(void) { 
   hal_gpio_init(13,'O');
  hal_gpio_init(2,'I');
  hal_gpio_init(3,'I');
  hal_gpio_init(4,'I');
  hal_gpio_init(5,'I');
  hal_gpio_init(6,'I');
  hal_gpio_init(7,'I');
  for(char i=2;i<=7;i++){
    hal_gpio_pullup(i);
  }
  while(1){
    char x = hal_gpio_read(2);
    char y = hal_gpio_read(3);
    char z = hal_gpio_read(4);
    char a = hal_gpio_read(5);
    char b = hal_gpio_read(6);
    char c = hal_gpio_read(7);
    if(c == 0 || x == 0 || y == 0 || z == 0 || a == 0 || b == 0){
      hal_gpio_write(13,1);
    }else{
      hal_gpio_write(13,0);
    }
  }
  
}
