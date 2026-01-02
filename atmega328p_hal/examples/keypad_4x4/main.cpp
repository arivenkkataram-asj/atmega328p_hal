#include <Arduino.h>
#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "drivers/hal_4x4_keypad.h"
void setup() {
  hal_gpio_init(13,'O');
  keypad_4x4_init(2,3,4,5,6,7,8,9,'E');
  Serial.begin(9600);
  while(1){
    uint8_t read = keypad_4x4_read();
    delay_milli(10);
    Serial.println(read);
    if(read == 9){
    hal_gpio_write(13,1);
    }else{
      hal_gpio_write(13,0);
    }
  }
  
}

void loop() {
}