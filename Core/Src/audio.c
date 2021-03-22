
#include "audio.h"

//************ public variables ************ //
int16_t AUDIO_circularBuffer[AUDIO_CIRCULAR_BUFFER_SIZE] = {0};
volatile bool AUDIO_isFullTransferComplete = false;
volatile bool AUDIO_isHalfTransferComplete = false;

//************ private functions prototypes ************ //
void AUDIO_FullTransferCompleteCallback(struct __DMA_HandleTypeDef * hdma);
void AUDIO_HalfTransferCompleteCallback(struct __DMA_HandleTypeDef * hdma);

#define AUDIO_CodecEnable()   {I2S_EN_GPIO_Port->ODR |= I2S_EN_Pin;}
#define AUDIO_CodecDisable()  {I2S_EN_GPIO_Port->ODR &= ~I2S_EN_Pin;}

void AUDIO_Init(void)
{
  AUDIO_CodecEnable();
}

void AUDIO_Start(void)
{
  HAL_Delay(100);
  
  HAL_I2SEx_TransmitReceive_DMA(&hi2s2, (uint16_t*)AUDIO_circularBuffer, (uint16_t*)AUDIO_circularBuffer, AUDIO_CIRCULAR_BUFFER_SIZE);
  
  hi2s2.hdmatx->XferCpltCallback     = NULL;
  hi2s2.hdmatx->XferHalfCpltCallback = NULL;
  
  hi2s2.hdmarx->XferCpltCallback     = AUDIO_FullTransferCompleteCallback;
  hi2s2.hdmarx->XferHalfCpltCallback = AUDIO_HalfTransferCompleteCallback;
}

void AUDIO_FullTransferCompleteCallback(struct __DMA_HandleTypeDef * hdma)
{
  AUDIO_isFullTransferComplete = true;
}

void AUDIO_HalfTransferCompleteCallback(struct __DMA_HandleTypeDef * hdma)
{
  AUDIO_isHalfTransferComplete = true;
}
