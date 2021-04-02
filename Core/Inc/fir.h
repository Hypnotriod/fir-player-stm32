
#ifndef __FIR_H__
#define __FIR_H__

#include "stm32f4xx_hal.h"
#include "audio.h"
#include <stdbool.h>

#define FIR_PACKET_SAMPLES_NUM  8
#define FIR_SAMPLE_IN_SIZE      2
#define FIR_SAMPLE_OUT_SIZE     4
#define FIR_PACKET_SIZE         (FIR_SAMPLE_OUT_SIZE * FIR_PACKET_SAMPLES_NUM)

void FIR_Init(void);
void FIR_Transfer(int16_t * pBuff);
void FIR_Fill(int16_t * pBuff);

extern volatile bool FIR_dataReady;

#endif
