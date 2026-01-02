#ifndef HAL_DELAY_H
#define HAL_DELAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

volatile void delay_milli(int milli_sec);

#ifdef __cplusplus
}
#endif
#endif