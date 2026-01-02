# Driver - 7 Segment Display
This is seperate 7-Segment Display driver name "seven_segment.h" using of both common Anode and Cathode type of display.

## Overview
This `seven_segment.h` currently developed for the displaying numbers with both dot and without dot.  This supports both Common Anode and Common Cathode. 

## Design Implementation
1. This uses the gpio_hal.h for interact with the pins and Write operation.
2. In this driver uses the Seperate pins for the each segment. 
3. For dot pin can be select or deselect for the operation.
4. Currently designed for the numbers only 0 to 9 and '0.' to '9.'

## Public API Description
### List of Public Function
1. seven_segment_init()
2. seven_segment_display()

#### seven_segment_init():
To assign the Pins for the LCD display from a to g and dot pin.  And set the 7-segment display is Common Anode or Cathode.

#### For Example:
```c
seven_segement_init(a,b,c,d,e,f,g,dot,type);
```
For dot user can either can assign pin or leave the pin by using '-'.
#### For Example:
```c
// For un-assign dot pin
seven_segment_init(a,b,c,d,e,f,g,'-',type);
```

#### For setting type for Common Anode/Cathode 
1. type = 'A' setting As Anode;
2. By default set as Common Cathode;
``
---
### seven_segment_display();
This used for display the number and dot.
#### For example: 
```c
seven_segment_display(num,dot);
```
#### For Dot operation to display need to enter as 1 or '.' or 'Y'
#### For Example:
```c
seven_segment_display(num,1);
```

## Limitation:
1. This driver currently supported 0 to 1
2. for the invalid numbers the compiler gives the error output.
3. By adding of external pins to connect multiple display by using of select pins.

## Related Documents:
