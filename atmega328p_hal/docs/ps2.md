# PS/2 interface ATmega328P - 16 MHz

## Overview
1. Implements PS/2 keyboard interface
2. Uses External Interrup INT0
3. Data sampled on falling edge of PS/2 clock
4. Returns 8-bit scan code
5. Designed for ATmega328P
6. Uses GPIO + External Interrupt

## Hardware Configuration
### Target MCU
- ATmega328P

### Pin Mapping
|Signal | MCU Pin |
|:---:|:---:|
|PS/2 Data | Pin 8|
|PS/2 Clock | Pin 2 (INT0) |

- Clock pin connected to INT0
- Internal pull-ups enabled
- Since PS/2 lines are open-collector -> require pull-ups

### Interrupt Configuration
- INT0 configured on falling edge
- Each falling edge corresponds to one bit
- ISR handles bit shifting and frame detection

### ISR Behavior
1. Reads current data bit
2. Ignore start bit
3. Collect 8 data bit
4. Shit right
5. When 11bits received:
   1. Set dataReady_flag
   2. Reset bit counter
```c
ISR(INT0_vect){
    uint8_t bit = hal_gpio_read(data_pin);
    if(bitCount > 0 && bitCount < 9){
        dataByte = dataByte >> 1;
        if(bit) dataByte |= 0x80;
    }
    bitCount++;    
    if(bitCount == 11){
        dataReady_flag = true;
        bitCount = 0;
    }
}
```

## API's
### 1. `hal_ps2_init()`
- configures data & clock pins as input
- Enables pull-ups
- Configures INT0
- Initializes state variables

### 2. `hal_ps2_available()`
- Returns 1 if scan code ready
- Non-blocking check

### 3. `hal_ps2_read_scan_code()`
- Reads received scan code
- Disbales global interrupt to protect shared data
- Clear flags
- Re-enables interrupt

## Verification
1. Verified using of the PS/2 keyboard interface
   - getting raw data
   - then maping to the letters
   - then sends through the UART communication
2. Example code is available in `atmega328p_hal/examples`
3. Tested with the simple calculator program insted or using keypad I used the PS2 keyboard.

