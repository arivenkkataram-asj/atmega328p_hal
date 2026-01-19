# AVR HAL PWM Driver (Timer1 – Fast PWM, ICR1 as TOP)

This module implements a **hardware PWM driver** using **Timer1** on the **ATmega328P**, written as part of a **custom Hardware Abstraction Layer (HAL)**.

The implementation uses **Fast PWM mode with ICR1 as TOP (Mode 14)**, enabling **runtime-configurable frequency** and **independent duty-cycle control** on **Channel A (OC1A)** and **Channel B (OC1B)**.

The design avoids Arduino libraries and directly programs registers to reinforce **bare-metal embedded fundamentals**.

---

## Features

- Fast PWM using **Timer1 (16-bit)**
- Programmable PWM frequency
- Independent duty cycle control for:
  - Channel A (OC1A → PB1) 
  - Channel B (OC1B → PB2)
- 0–100% duty cycle abstraction
- Clean HAL-style API
- Register-level control (no Arduino core)

---

## Hardware & Configuration

### Target MCU
- ATmega328P (Arduino Uno compatible)

### Clock & Prescaler

|   Parameter  | Value |
|--------------|-------|
| System Clock | 16 MHz |
| Timer        | Timer1 (16-bit) |
| Prescaler    | 256 |
| PWM Mode     | Fast PWM |
| TOP Source   | ICR1 |

---

## PWM Mode Selection

Timer1 is configured in **Fast PWM, Mode 14**, where:

- **TOP = ICR1**
- Frequency is configurable at runtime
- Duty cycle is controlled via OCR1A / OCR1B

### Waveform Generation Mode (WGM13:0)

| WGM13 | WGM12 | WGM11 | WGM10 | Mode |
|-------|-------|-------|-------|------|
|   1   |   1   |   1   |   0   | Fast PWM (Mode 14) |

---

## PWM Frequency Calculation

```c
TOP = (F_CPU / (Prescaler × Frequency)) - 1
```

For this implementation:
```c
TOP = (16000000 / (256 × frequency)) - 1
```
This value is written to ICR1, defining the PWM period.

## Register Configuration
|Register |	Purpose |
|---------|---------|
|TCCR1A	  | Compare Output Mode + WGM bits |
|TCCR1B	  | Prescaler + WGM bits |
|ICR1	  | PWM TOP value |
|OCR1A	  | Duty cycle (Channel A)|
|OCR1B	  | Duty cycle (Channel B)|
|DDRB	  | Output pin direction|

## Pin Mapping
Channel	| AVR Pin	| Arduino Pin
OC1A	   PB1	       D9
OC1B	   PB2	       D10

## Core API
### void hal_pwm_init(uint16_t frequency)

- Initializes Timer1 in Fast PWM mode with the specified frequency.

- Configures ICR1 as TOP

- Sets prescaler to 256

- PWM outputs are disabled until channels are initialized
```c
hal_pwm_init(1000); // 1 kHz PWM
```

### void hal_pwm_channel_init(char channel)

- Initializes a PWM output channel.

- Enables non-inverting mode

- Configures pin as output

- Resets duty cycle to 0%

- Valid channel values:

1. 'A' or 1 → OC1A

2. 'B' or 2 → OC1B
```c
hal_pwm_channel_init('A');
hal_pwm_channel_init('B');
```
### void hal_pwm_set_duty(char channel, uint8_t duty)

- Sets the duty cycle for a channel.

- Duty range: 0–100 (%)

- Converts percentage to OCR value

- Does not start PWM immediately
```c
hal_pwm_set_duty('A', 50); // 50% duty
```
### void hal_pwm_start(uint8_t channel)

Starts PWM output by loading the duty value into OCR register.
```c
hal_pwm_start('A');
```
### void hal_pwm_stop(uint8_t channel)

Stops PWM output by clearing the OCR register.
```c
hal_pwm_stop('A');
```

### Duty Cycle Mapping Logic
- OCR = (duty × (TOP + 1)) / 100;

✔ Linear scaling
✔ Frequency-independent duty
✔ Clean abstraction over hardware registers

## Design Decisions & Rationale

1. ICR1 as TOP

2. Allows runtime frequency changes

3. Better than fixed 8/10-bit PWM

4. Separate set/start functions

5. Prevents glitches

6. Enables staged configuration

7. No Arduino analogWrite()

8. Full control

9. Hardware clarity

10. 16-bit timer

11. Higher resolution PWM

## Limitations

- No dead-time insertion (not required for basic PWM)

- No phase-correct mode (intentional for simplicity)

- Blocking API (no DMA / ISR-based updates)

## Intended Use Cases

- Motor control (basic)

- LED dimming

- Power control experiments

- Custom HAL development