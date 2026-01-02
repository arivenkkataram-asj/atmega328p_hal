# ATMEGA328P HAL GPIO

## Overview
This HAL_GPIO does the user to initilize the pins of the atmega328p and the user can set pins of Atmega328p to be accessed by read or write operations.  It helps the user to access easy to interact with the application layer.  It hides the rigister level access from the user.

### Supported Operation
In this HAL_GPIO support the Digital Read and Write operation only. This will give access for the each pin can be used either Read/Write operation.

### Not Supported Operation
In the HAL_GPIO doesn't support the undefined pins and unsupported mode of operation
---
## Design Implementaion
### Pin numbering
This HAL_GPIO uses the Arduino-style pin numbering for the easy access through the Application layer.

### Public API Description
#### List of Public Functions
- `hal_gpio_init()`
- `hal_gpio_write()`
- `hal_gpio_pullup()`
- `hal_Gpio_read()`

#### hal_gpio_init():
This function is used for the intilize the pin either to be the Read or Write mode.
#### Examples:
For Output:
```c
hal_gpio_init(pinNumber,'O');
```
For Input:
```c
hal_gpio_init(pinNumber,'I');
```
#### hal_gpio_write();
This used for the set the Pin is High or LOW
#### Example:
For the HIGH:
```c
hal_gpio_write(pinNumber,1);
```
For the LOW:
```c
hal_gpio_write(pinNumber,0);
```

### hal_gpio_pullup();
To initiate the input pin internal pullup is active.
#### Example:
```c
hal_gpio_pullup(pinNumber);
```
#### hal_gpio_read();
To read the input pin as the digital Read.
#### Example:
```c
hal_gpio_read(pinNumber);
```

## Pin Mapping
For the Arduino UNO:
##### D0 - D13 as 0 - 13
##### A0 - A5 as 14 - 19


## Limitation
1. This HAL_GPIO doesn't include the Tx and Rx pin for the safety Purpose.
2. This supports only to enable the Pin and for the digital Read and Write purpose.


## Error Handling
1. This hal_gpio doesn't enable the port when the Undefined the Pin number and and Mode
2. For the undefined Pin for the digital read (`hal_gpio_read(undefined_pinNumber);). It will always return the zero/'0'.