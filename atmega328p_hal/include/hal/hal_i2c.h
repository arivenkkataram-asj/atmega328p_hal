#ifndef HAL_I2C_H
#define HAL_I2C_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void hal_i2c_init(uint32_t clock_hz);

uint8_t hal_i2c_start(uint8_t address_rw);
uint8_t hal_i2c_write(uint8_t data);
int16_t hal_i2c_read_ack();
int hal_i2c_read_nack();
void hal_i2c_stop();

void hal_i2c_set_slave_address(uint8_t addr);
uint8_t hal_i2c_slave_listen();
int hal_i2c_slave_read();
uint8_t hal_i2c_slave_write(uint8_t data);

#ifdef __cplusplus
}
#endif

#endif