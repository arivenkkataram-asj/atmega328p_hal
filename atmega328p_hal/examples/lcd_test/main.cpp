#include <Arduino.h>
#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "drivers/lcd_hd44780.h"
char string[] = "Wellcome"; 
void setup() {
    lcd_display_init(2,3,4,5,6,7,8,9,10,11);
    lcd_write_char(1);
    lcd_display_string("Happy New Year",0);
    lcd_write_char(1);
    lcd_display_string("    ",2);
    lcd_write_char(3);
    lcd_write_char(0);
    lcd_display_string("2026",0);
    lcd_write_char(0);
    lcd_write_char(3);

}
void loop() {
}