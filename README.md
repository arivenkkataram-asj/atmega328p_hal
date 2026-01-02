# ATmega328P HAL and Driver Architecture
This Project about for Understaing Purpose of the AVR architecture. How the Internal Funtion works and how CPU interact with external world.

## Overview
In this GIT Repo inclues the HAL of the Atmega328p and Implementaion of the Various Drivers.  To test with the Arduino UNO development board. This Project tested through the PlatformIO in VS Code. For Live testing with the Development Board.

## Project Goals
- This Project Goals to learn about the Architecture of AVR.
- How the Driver Interaction with the ATmega328p microcontroller.
- Understanding of the Bare-metal Programming

## Repository Structure
```text
.
├── .vscode/
│   └── settings.json
│
├── docs/
│   ├── delay.md
│   ├── gpio.md
│   ├── keypad_4x4.md
│   ├── lcd_hd44780.md
│   └── seven_segment.md
│
├── examples/
│   ├── button_test/
│   ├── gpio_blink/
│   ├── keypad_4x4/
│   ├── keypad_7segment_display/
│   ├── lcd_test/
│   ├── pwm_test/
│   ├── sample_main_code/
│   └── seven_segment_display/
│
├── include/
│   ├── hal/
│   │   ├── hal_gpio.h
│   │   └── hal_delay.h
│   │
│   └── drivers/
│       ├── keypad_4x4.h
│       ├── lcd_hd44780.h
│       └── seven_segment.h
│
├── src/
│   ├── hal/
│   │   └── (HAL source files)
│   │
│   ├── drivers/
│   │   └── (Driver source files)
│   │
│   └── main.cpp
│
├── test/
│   └── README.md
│
├── .gitignore
├── platformio.ini
└── README.md
```
## Architecture Overview
This project follows a layered architecture from top layer as the Application Layer --> Drivers Layer --> HAL Layer.

## Documentation Guide
For Each HAL and Driver has the Seperate `.md` file to overview and how to access the API functions to use in the Application Layer.

## How to Use This Repository 
- Download the zip file in local system and extract it.
- In VS_Code download the PlatformIo Extension.
- Open the extracted file in through the Open Project in PlatformIo
- Browse for the examples and just copy the code and paste in the main.cpp in the src folder.
- Then Build the code throught the options in the platformIo and then upload through the arduino Uno.

## Limitations 
- This project targets the ATmega328p microcontroller
- Only the basic HAL modules are implemented
- Some drivers support limited features
