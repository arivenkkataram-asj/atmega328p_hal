# Driver Keypad 4x4
This driver used for the read the keypad pressing values for the 4x4 matrix keypad using of 8-pins.

## Overview
This keypad reads the which button is pressed and it will retun the numeric value to figure out which button is pressed. This is checks through first to last button scanning method. Multi button pressed will not recognise It just return top most button.

## Supported Features:
1. Keypad Size - 4x4
2. Currently developed for Pullup input mode.

## Non-Supported Features:
1. Multi-key Pressing.
2. Long-press detection.
3. Events of Key releases.

## Design Implementation
1. This driver checks through the top to bottom approach. For Ex. If top button is pressed without releasing the it. the bottom button is pressed then it will not recognise the bottom key.
2. It depends on the hal_gpio.h for the Integration of the Write and Read operation for the specfic pins.
3. Currently The driver works only on Pull up mode.

## Public API Description
### Public Functions:
- keypad_4x4_init();
- keypad_4x4_read();

#### keypad_4x4_init();
This function used for the initialize the pins for the Read and Write operation. by the rows and cols.
##### For Example:
```c
keypad_4x4_init(row_1,row_2,row_3,row_4,col_1,col_2, col_3,col_4, Pull_mode);
```
For the enable/Disable internal_pullup.
1. For enable `pull_mode = 'E'`
2. For disable `pull_mode = 'D'`

## Limitation:
1. If many key are pressed this keypad checks from Top to bottom this only checks Top most key.
2. This driver can only used for the Pull up mode Currently.

