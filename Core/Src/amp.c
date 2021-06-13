
#include "amp.h"
#include "audio.h"

float AMP_value = 0.f;

void AMP_IncrementValue(void)
{
  AMP_value += AMP_VALUE_INCREMENT;
  if (AMP_value > 1.f) AMP_value = 1.0f;
}

void AMP_DecrementValue(void)
{
  AMP_value -= AMP_VALUE_INCREMENT;
  if (AMP_value < 0.f) AMP_value = 0.f;
}

void AMP_Process(int16_t * pBuff)
{
  size_t i;
  float origSample;
  float sample;
  
  for (i = 0; i < AUDIO_CIRCULAR_BUFFER_HALF_SIZE; i += 2) {
    origSample = (float) pBuff[i] / (float) INT16_MAX;
    sample = (origSample > 0) ? origSample : -origSample;
    sample = (sample - sample * sample * 0.5f) * 2.f;
    
    if (origSample < 0) sample = -sample;
    pBuff[i] = (origSample * (1.f - AMP_value) + sample * AMP_value) * (float) INT16_MAX;
  }
}
