
#ifndef __IMPULSE_H__
#define __IMPULSE_H__

#include "stm32f4xx_hal.h"

#define IMPULSE_SIZE        131072
#define IMPULSE_SAMPLES_NUM 65536
#define IMPULSES_NUM        7

extern const int16_t * IMPULSE_Impulses[IMPULSES_NUM];

#endif
