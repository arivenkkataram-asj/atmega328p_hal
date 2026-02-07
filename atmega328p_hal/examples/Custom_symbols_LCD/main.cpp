#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "drivers/lcd_hd44780.h"

int main(void) { 
    hal_systick_init();
    hal_enable_interrupt();
    hal_gpio_init(13,'O');
    lcd_display_init(2,3,4,5,6,7,8,9,10,11);
    uint32_t LED_timer = 0;
    uint8_t LED_out = 0;
    uint32_t LCD_timer = 0;
    uint8_t temp = 0;
    lcd_display_string((char *)"Custom Symbols: ", 0);
    lcd_goto(2,0);
    /*
    0 -- > smiley face
    1 -- > Twinkle
    2 -- > Star
    3 -- > Heart
    4 -- > bell
    5 -- > battery
    6 -- > right arrow
    7 -- > bell.
    */
    while(1){
       
         if(hal_timeout_expired(LED_timer,100)){
                LED_timer = hal_millis();
                LED_out ^= 1;
                hal_gpio_write(13,LED_out);  
        }
        if(hal_timeout_expired(LCD_timer, 1000)){
            LCD_timer = hal_millis();
            if(temp>7){
                temp = 0;
                lcd_clear_line(2);
            }
            
            lcd_write_char(temp);
            temp++;
        }
    }
  
}