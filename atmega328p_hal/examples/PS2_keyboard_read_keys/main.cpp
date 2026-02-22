#include "hal/hal_gpio.h"
#include "hal/hal_delay.h"
#include "hal/hal_timer.h"
#include "hal/hal_interrupt.h"
#include "hal/hal_uart.h"
#include "hal/hal_i2c.h"
#include "hal/hal_ps2.h"

void uint8_to_hex(uint8_t value, char *hex_data){
    const char hex_chars[]="0123456789ABCDEF";
    hex_data[0] = hex_chars[(value>>4) & 0x0F];
    hex_data[1] = hex_chars[value & 0x0F];
    hex_data[2] = '\0';
}

bool shift_key = false;
bool ctrl_key = false;
bool alt_key = false;
bool break_pending = false;
bool extended_pending = false;

char normalMap[128] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,'`',0,
  0,0,0,0,0,'q','1',0,0,0,'z','s','a','w','2',0,
  0,'c','x','d','e','4','3',0,0,' ','v','f','t','r','5',0,
  0,'n','b','h','g','y','6',0,0,0,'m','j','u','7','8',0,
  0,',','k','i','o','0','9',0,0,'.','/','l',';','p','-',0,
  0,0,'\'',0,'[','=',0,0,0,0,'\n',']',0,'\\',0,0,
  0,0,0,0,0,0,'\b',0,0,0,0,0,0,0,0,0
};

char shiftMap[128] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,'~',0,
  0,0,0,0,0,'Q','!',0,0,0,'Z','S','A','W','@',0,
  0,'C','X','D','E','$','#',0,0,' ','V','F','T','R','%',0,
  0,'N','B','H','G','Y','^',0,0,0,'M','J','U','&','*',0,
  0,'<','K','I','O',')','(',0,0,'>','?','L',':','P','_',0,
  0,0,'"',0,'{','+',0,0,0,0,'\n','}',0,'|',0,0,
  0,0,0,0,0,0,'\b',0,0,0,0,0,0,0,0,0
};

void handleKey(uint8_t code){
  if(code == 0xF0) {break_pending = true;return;}
  if(code == 0xE0) {extended_pending = true;return;}

  //modifier keys to false state of code
  if (code == 0x12 || code == 0x59){shift_key = !break_pending; goto end;}
  if (code == 0x14) { ctrl_key = !break_pending; goto end;}
  if(code == 0x11) {alt_key = !break_pending; goto end;}

  if(!break_pending){
    if(extended_pending){
      switch (code)
      {
        case 0x75: hal_Serial_println("[UP]"); break;
        case 0x72: hal_Serial_println("[Down]");break;
        case 0x6B: hal_Serial_println("[Left]");break;
        case 0x74: hal_Serial_println("[Right]");break;
      }
    }
    else {
      switch(code){
        case 0x05: hal_Serial_println("[F1]");break;
        case 0x06: hal_Serial_println("[F2]");break;
        case 0x04: hal_Serial_println("[F3]");break;
        case 0x0C: hal_Serial_println("[F4]");break;
        case 0x03: hal_Serial_println("[F5]");break;
        case 0x0B: hal_Serial_println("[F6]");break;
        case 0x83: hal_Serial_println("[F7]");break;
        case 0x0A: hal_Serial_println("[F8]");break;
        case 0x01: hal_Serial_println("[F9]");break;
        case 0x09: hal_Serial_println("[F10]");break;
        case 0x78: hal_Serial_println("[F11]");break;
        case 0x07: hal_Serial_println("[F12]");break;
      }
      char c[2];
      c[1] = '\0';
      c[0] = shift_key ? shiftMap[code] : normalMap [code];
      if(c[0]) {hal_Serial_print(c);};
    }
  }
  end:
    break_pending = false;
    extended_pending = false;
}

int main(void){
  hal_systick_init();
  hal_ps2_init();
  hal_enable_interrupt();
  hal_gpio_init(13,'O');
  hal_uart_init(9600);
  hal_i2c_init(100000);

  uint32_t LED_timer = 0;
  uint8_t LED_state = 0;
  uint8_t keyboard_data;
  char hex_data[3];
  hal_Serial_println("PS2 keyboard is Ready");
  while(1){
    if(hal_timeout_expired(LED_timer,1000)){ //blink LED every 1000ms and data transmit
      LED_timer = hal_millis();
      LED_state ^= 1;
      hal_gpio_write(13,LED_state);
      
    }
    keyboard_data = hal_ps2_read_scan_code();
    if(keyboard_data){
      //uint8_to_hex(keyboard_data,hex_data);
     // hal_Serial_println(hex_data);
     handleKey(keyboard_data);
    }



  }
}
