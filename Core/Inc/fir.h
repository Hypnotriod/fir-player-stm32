
#ifndef __FIR_H__
#define __FIR_H__

#include "stm32f4xx_hal.h"
#include "audio.h"
#include <stdbool.h>

#define FIR_PACKET_SIZE         8
#define FIR_PACKET_SAMPLES_NUM  2
#define FIR_SAMPLE_IN_SIZE      2
#define FIR_SAMPLE_OUT_SIZE     4

void FIR_Init(void);
void FIR_Transfer(int16_t * pBuff);

extern volatile bool FIR_isFullTransferComplete;
extern int32_t FIR_buffer[AUDIO_CIRCULAR_BUFFER_QUARTER_SIZE];

#endif
