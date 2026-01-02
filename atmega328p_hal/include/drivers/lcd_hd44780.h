#ifndef LCD_HD44780_H      
#define LCD_HD44780_H      

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void lcd_display_init(uint8_t d0, uint8_t d1,
                      uint8_t d2, uint8_t d3,
                      uint8_t d4, uint8_t d5,
                      uint8_t d6, uint8_t d7,
                      uint8_t rs, uint8_t en);
void out_data(uint8_t value);
void lcd_display_string(char *ptr,char line);
void string_to_ascii(char *ptr);
void command_write(uint8_t value);
void data_write(char value);
void pulse_en_signal();
void lcd_cursor_blink(uint8_t cursor,uint8_t blink);
void lcd_clear();
void lcd_cursor_return_home();
void lcd_clear_line(uint8_t line);
void display_on_off(uint8_t state);
void move_cursor(char direction);
void rotate_display(char direction);
void lcd_goto(uint8_t row, uint8_t col);
void lcd_write_char(char Character);
void lcd_entry_mode_set(char id, char shift);
void custom_character(uint8_t new_character[8][8]);
#ifdef __cplusplus
}
#endif
#endif