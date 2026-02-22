#ifndef HAL_PS2_H
#define HAL_PS2_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

void hal_ps2_init();
uint8_t hal_ps2_available();
uint8_t hal_ps2_read_scan_code();


#ifdef __cplusplus
}
#endif
#endif