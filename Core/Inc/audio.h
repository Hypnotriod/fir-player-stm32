
#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "stm32f4xx_hal.h"
#include "i2s.h"
#include <stdbool.h>

#define AUDIO_CIRCULAR_BUFFER_SIZE          32
#define AUDIO_CIRCULAR_BUFFER_HALF_SIZE     (AUDIO_CIRCULAR_BUFFER_SIZE / 2)
#define AUDIO_CIRCULAR_BUFFER_QUARTER_SIZE  (AUDIO_CIRCULAR_BUFFER_SIZE / 4)
#define AUDIO_SAMPLE_RATE                   44100

void AUDIO_Init(void);
void AUDIO_Start(void);
void AUDIO_ClearBuffer(void);
void AUDIO_ClearBufferFirstHalf(void);
void AUDIO_ClearBufferSecondHalf(void);

void DMA1_Stream5_IRQHandler(void);

extern int16_t AUDIO_circularBuffer[AUDIO_CIRCULAR_BUFFER_SIZE];
extern bool AUDIO_isFullTransferComplete;
extern bool AUDIO_isHalfTransferComplete;

#endif
