
#ifndef __AMP_H__
#define __AMP_H__

#include "stm32f4xx_hal.h"

#define AMP_VALUE_INCREMENT 0.05f

void AMP_Process(int16_t * pBuff);
void AMP_IncrementValue(void);
void AMP_DecrementValue(void);

extern float AMP_value;

#endif
