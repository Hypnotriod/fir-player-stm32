
#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "stm32f4xx_hal.h"
#include "i2s.h"
#include <stdbool.h>

#define AUDIO_CIRCULAR_BUFFER_SIZE          32
#define AUDIO_CIRCULAR_BUFFER_HALF_SIZE     (AUDIO_CIRCULAR_BUFFER_SIZE / 2)
#define AUDIO_CIRCULAR_BUFFER_QUARTER_SIZE  (AUDIO_CIRCULAR_BUFFER_SIZE / 4)
#define AUDIO_SAMPLE_RATE                   44100

#define AUDIO_Swap16(_sample_) ((((uint16_t) _sample_) << 8) | (((uint16_t) _sample_) >> 8))

void AUDIO_Init(void);
void AUDIO_Start(void);
void AUDIO_ClearBuffer(void);
void AUDIO_ClearBufferFirstHalf(void);
void AUDIO_ClearBufferSecondHalf(void);

void DMA1_Stream5_IRQHandler(void);

#define AUDIO_OnFirstBufferHalfProcessed() AUDIO_firstBufferHalfReady = false
#define AUDIO_OnSecondBufferHalfProcessed() AUDIO_secondBufferHalfReady = false

extern int16_t AUDIO_circularBuffer[AUDIO_CIRCULAR_BUFFER_SIZE];
extern volatile bool AUDIO_secondBufferHalfReady;
extern volatile bool AUDIO_firstBufferHalfReady;

#endif
