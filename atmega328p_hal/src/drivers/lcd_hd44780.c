
#include "drivers/lcd_hd44780.h"
#include <stdint.h>
#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
uint8_t lcd_pin_out[8][2];
uint8_t rs,en, cursor=0,blink=0;
uint8_t new_char[8][8] = {{
    //smile
    0b00000000,
    0b00001010,
    0b00001010,
    0b00000000,
    0b00010001,
    0b00001110,
    0b00000000,
    0b00000000},
    //firework
    { 
    0b00100,
    0b10101,
    0b01110,
    0b10101,
    0b00100,
    0b00000,
    0b00100,
    0b00000
    },
    //Star
    {
    0b00100,
    0b10101,
    0b01110,
    0b11111,
    0b01110,
    0b10101,
    0b00100,
    0b00000,
    },
    //heart
    {
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000,
    0b00000

    },
    //bell
    {
    0b00100,
    0b01110,
    0b01110,
    0b01110,
    0b11111,
    0b00100,
    0b00000,
    0b00100
    },
    //battery
    {
 0b01110,
 0b10001,
 0b10001,
 0b10001,
 0b10001,
 0b10001,
 0b11111,
 0b00000
    },
    //arrow
    {
    0b00100,
    0b00010,
    0b11111,
    0b00010,
    0b00100,
    0b00000,
    0b00000,
    0b00000
    },
    //flame
    {
    0b00100,
    0b01110,
    0b01110,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
    }

};
void lcd_display_init(uint8_t d0, uint8_t d1,
                      uint8_t d2, uint8_t d3,
                      uint8_t d4, uint8_t d5,
                      uint8_t d6, uint8_t d7,
                      uint8_t rs0, uint8_t en0){
    
    lcd_pin_out[0][0] = d0;
    lcd_pin_out[1][0] = d1;
    lcd_pin_out[2][0] = d2;
    lcd_pin_out[3][0] = d3;
    lcd_pin_out[4][0] = d4;
    lcd_pin_out[5][0] = d5;
    lcd_pin_out[6][0] = d6;
    lcd_pin_out[7][0] = d7;
    rs = rs0; //pin 10
    en = en0; //pin11

    for(uint8_t i=0;i<8;i++){
        hal_gpio_init(lcd_pin_out[i][0],'O');       
    }
    hal_gpio_init(rs,'O');
    hal_gpio_init(en,'O');
    delay_milli(100);
    //setting the display input - 8-bit input - 2 lines - 5x8 dots
    command_write(0x38);
    //setting the display on 
    command_write(0x0C);
    //clear display
    command_write(0x01);
    command_write(0x06);

    custom_character(new_char);
}

void out_data(uint8_t value) { //data D0 to D7 value ouput by the input of 0xFF,0x06...
    for(uint8_t i=0;i<=7;i++){ //assign value to the pin
        lcd_pin_out[i][1] = (value >> i)& (0x01);
    }
    for(uint8_t j=0;j<=7;j++){
        hal_gpio_write(lcd_pin_out[j][0],lcd_pin_out[j][1]);
    }
}

void lcd_display_string(char *ptr,char line){ //line == 0 continue with pointer
    if(line == 1){
        command_write(0x80);
        string_to_ascii(ptr);
    }
    if(line == 2){
        command_write(0xC0);
        string_to_ascii(ptr);
    }
    if(line == 0){
        string_to_ascii(ptr);        
    }
}
void string_to_ascii(char *ptr){
    while(*ptr !=  0){
        data_write(*ptr);
        ptr++;
    }
}

void command_write(uint8_t value){
    hal_gpio_write(rs,0);
    out_data(value);
    pulse_en_signal();
}
void data_write(char value){
    hal_gpio_write(rs,1);
    out_data(value);
    pulse_en_signal();
}

void pulse_en_signal(){
    hal_gpio_write(en,0);
    delay_milli(1);
    hal_gpio_write(en,1);
    delay_milli(1);
    hal_gpio_write(en,0);
}

void lcd_cursor_blink(uint8_t cur,uint8_t bk){
    cursor = cur; blink = bk;
    if(cursor == 1 && blink == 1){
        command_write(0x0F);
    }else if(cursor == 1){
        command_write(0x0E);
    }else if(blink == 1){
        command_write(0x0D);
    }else if(cursor == 0 && blink == 0){
        command_write(0x0C);
    }
}

void lcd_clear(){
    command_write(0x01);
}

void lcd_cursor_return_home(){
    command_write(0x02);
}

void lcd_clear_line(uint8_t row){
    lcd_display_string("                ",row);
    if(row == 1){
        lcd_cursor_return_home();
    } else {
        lcd_display_string("",2);
    }
}

void display_on_off(uint8_t state){
    if(state == 0){
        command_write(0x08);
    }else{
        lcd_cursor_blink(cursor,blink);
    }
}



void move_cursor(char direction){
    if(direction == 'L' || direction == 'l'){
        command_write(0x10);
    }
    else if(direction == 'R' || direction == 'r'){
        command_write(0x14);
    }
}

void rotate_display(char direction){
    if(direction == 'L' || direction == 'l'){
        command_write(0x18);
    }
    else if(direction == 'R' || direction == 'r'){
        command_write(0x1C);
    }
}

void lcd_goto(uint8_t row, uint8_t col){
    if(row == 1){
        command_write(0x80 + col);
    }
    else if(row == 2){
        command_write(0xC0 + col);
    }
}

void lcd_write_char(char Character){
    data_write(Character);    
}

void lcd_entry_mode_set(char id, char shift){
    if(id == 0 && shift == 0){
        command_write(0x04);
    }else if(id == 0 && shift == 1){
        command_write(0x05);
    }else if(id == 1 && shift == 0){
        command_write(0x06);
    }else if(id == 1 && shift == 1){
        command_write(0x07);
    }
}

void custom_character(uint8_t new_character[8][8]){
    command_write(0x40);
    for(uint8_t j=0;j<8;j++){
        for(uint8_t i=0; i<8;i++){
            data_write(new_character[j][i]);
        }
    }
    command_write(0x80);
}