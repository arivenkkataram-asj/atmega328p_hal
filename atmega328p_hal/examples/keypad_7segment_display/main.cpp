#include <Arduino.h>
#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "drivers/hal_4x4_keypad.h"
#include "drivers/hal_7_segment.h"
void setup() {
  keypad_4x4_init(2,3,4,5,6,7,8,9,'E');
  seven_segment_init(10,11,12,13,14,15,16,'-','A');
  hal_gpio_init(17,'O');
  hal_gpio_init(18,'O');
  uint8_t keypad_no = 00;
  uint8_t read_keypad;
  while(1){
    read_keypad = keypad_4x4_read();
    if(read_keypad != 0){
      keypad_no = read_keypad;
    }
    uint8_t tens = keypad_no/10;
    uint8_t ones = keypad_no%10;
    seven_segment_display(tens,'-');
    hal_gpio_write(17,1);
    delay_milli(10);
    hal_gpio_write(17,0);
    seven_segment_display(ones,'-');
    hal_gpio_write(18,1);
    delay_milli(10);
    hal_gpio_write(18,0);
  }

}

void loop() {
}