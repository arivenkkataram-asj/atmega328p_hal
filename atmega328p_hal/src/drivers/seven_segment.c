#include "hal/hal_gpio.h"
#include "drivers/seven_segment.h"
#include <stdint.h>
//initilizing common cathode numbers
const uint8_t seven_segment_numbers[11] = {
    0b00111111, //0
    0b00000110, //1
    0b01011011, //2
    0b01001111, //3
    0b01100110, //4
    0b01101101, //5
    0b01111101, //6
    0b00000111, //7
    0b01111111, //8
    0b01101111  //9
};
volatile uint8_t segment[7];
volatile uint8_t init_pin_dot;
char check_mode;
void seven_segment_init(uint8_t a,uint8_t b,
                        uint8_t c,uint8_t d,
                        uint8_t e,uint8_t f,
                        uint8_t g,char dp,
                        char type){
    segment[0] = a;
    segment[1] = b;
    segment[2] = c;
    segment[3] = d;
    segment[4] = e;
    segment[5] = f;
    segment[6] = g;
    if(dp != '-'){
        init_pin_dot = (uint8_t)dp;
        hal_gpio_init(dp,'O');
    }

    if(type == 'A'){
        check_mode = 1;
    }else{
        check_mode = 0;
    }
    for(uint8_t i=0;i<=6;i++){
        hal_gpio_init(segment[i],'O');
    }
}

void display_char(uint8_t char_no){
    for(uint8_t i=0;i<=6;i++){
        uint8_t a = (seven_segment_numbers[char_no] >> i) & 0x01;
        if(check_mode == 1){
            hal_gpio_write(segment[i],!a);
        }else{
            hal_gpio_write(segment[i],a);
        }
    }
}


void seven_segment_display(uint8_t num,char dot){
    if(dot == 1 || dot == '.' || dot == 'Y' || dot == 'y'){
        hal_gpio_write(init_pin_dot, 0);
    }else{
        hal_gpio_write(init_pin_dot, 1);
    }
    display_char(num);
    
}