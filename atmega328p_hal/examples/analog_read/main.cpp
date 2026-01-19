#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_adc.h"
#include "drivers/lcd_hd44780.h"


void update_LCD(uint16_t a_value){
    
    if(a_value >= 900){  //Displaying HIGH
        lcd_goto(2,7);
        char high[6] = {'H','i','g','h',' ',' '};
        for(uint8_t temp=0;temp<6;temp++){
            lcd_write_char(high[temp]);
        }
    }else if (a_value <= 100){ //Displaying LOW
        lcd_goto(2,7);
        char Low[6] = {'L','o','w',' ',' ',' '};
        for(uint8_t temp=0;temp<6;temp++){
            lcd_write_char(Low[temp]);
        }
    }else{ // Displaying Normal
        lcd_goto(2,7);
        char Normal[6] = {'N','o','r','m','a','l'};
        for(uint8_t temp=0;temp<6;temp++){
            lcd_write_char(Normal[temp]);
        }
    }
    lcd_goto(2,0);
    lcd_write_char(6);
    for(int i=1000;i>=1;i=i/10){ // Printing the analog values
        lcd_write_char(((a_value/i)%10)+'0');
    }
    
}

int main(void) { 
    hal_systick_init();
    hal_enable_interrupt();
    hal_gpio_init(13,'O');
    lcd_display_init(2,3,4,5,6,7,8,9,10,11);
    uint32_t LED_timer = 0;
    uint8_t LED_out = 0;
    uint32_t Analog_read_timer = 0;
    uint16_t Analog_value = 0;
   
    lcd_display_string("Analog Value: ",0);
    lcd_goto(2,0);
    lcd_write_char(6);
    while(1){
       
         if(hal_timeout_expired(LED_timer,100)){
                LED_timer = hal_millis();
                LED_out ^= 1;
                hal_gpio_write(13,LED_out);  
        }
        if(hal_timeout_expired(Analog_read_timer, 200)){
            Analog_read_timer = hal_millis();
            Analog_value = hal_adc_read(0); // reading Analog value in A0
            update_LCD(Analog_value);
        }
    }
  
}
