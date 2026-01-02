#ifndef KEYPAD_4X4_H
#define KEYPAD_4X4_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void keypad_4x4_init(uint8_t r0, uint8_t r1,
                     uint8_t r2, uint8_t r3,
                     uint8_t c0, uint8_t c1,
                     uint8_t c2, uint8_t c3, 
                     char pull_mode);
uint8_t keypad_4x4_read();

#ifdef __cplusplus
}
#endif

#endif