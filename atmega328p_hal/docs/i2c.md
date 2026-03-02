# HAL I2C ATmega328P
## Overview:
1. This implements TWI (Two Wire Interface) / I2C protocol
2. Supports:
  - Master Transmit
  - Master Receive
  - Slave Transmit
  - Slave Receive
3. Polling-based (no interrupt-driven state machine)
4. Uses status-code verification from TWSR
5. Uses status-code verification from TWSR

Note: Designed for ATmega328P and 16MHz system clock.

## I2C Clock Configuration
### Formula for Clock Configuration:
```c
SCL = FCPU/ (16+(2*TWBR*Prescalar))
```

## Operation Mode:
1. Polling-based
2. Uses TWINT flag to wait for completion
3. Validated communication using TWSR Status codes.
4. No interrupt-driven TWI

## Master Mode API 
### 1. `hal_i2c_start(uint8_t address_rw)`
- Sends START condition
- Waits for TWINT
- Checks TWSR for:
  - 0x08 -> START transmitted
  - 0x10 -> Repeted Start transmitted
- Sends SLA+R/W
- Validates:
  - 0x18 -> SLA + W ACK
  - 0x40 -> SLA + R ACK
  - 0x20 -> SLA + W NACK
  - 0x48 -> SLA + R NACK
- Return values
  | Return | Meaning |
  |:-----:|:------:|
  |1      | ACK recived|
  |2       | NACK recived|
  |0     | Error| 

### 2. `hal_i2c_write(uint8_t data)`
- Lods TWDR
- Clears TWINT
- Waits for completion
- Checks:
  - 0x28 -> Data ACK
  - 0x30 -> Data NACK

### 3. `hal_i2c_read_ack()`
- Sends ACK after receiving byte
- Used for multi-byte reception
- Validated:
  - ox50 -> Data received + ACK
  - 0x58 -> Data received + NACK

### 4. `hal_i2c_read_nack()`
- Used for last byte reception
- Sends NACK
- Checks 0x58

### 5. `hal_i2c_stop()`
- Sets TWSTO bit
- Releases bus

## Slave Mode API 
### 1. `hal_i2c_set_slave_address(uint8_t addr)`
- Sets TWAR
- Left shifts address (7-bit address)

### 2.  `hal_i2c_slave_listen()`
- Waits for address match
- Validated:
  - 0x60 -> SLA+W received
  - 0xA8 -> SLA+R received
  - 0x70 -> General call received

### 3. `hal_i2c_slave_read()`
- Received data from master
- Checks:
  - 0x80 -> Data received + ACK
  - 0xA0 -> STOP condition

### 4. `hal_i2c_slave_write(uint8+t data)
- Sends data to master
- Checks:
  - 0xB8 -> Data transmitted + ACK
  - 0xC0 -> Data transmitted + NACK

## Verification
1. Tested with two similar type microcontroller - ATmega328P
  - Observed the data transmission and receiving with Locgic Analyzer.
2. No timeout in while loops
  - This creates the bus hang for some time or continuous untill the reset button is pressed.
  - This can be reduced buy using timeout in while loops.

   
