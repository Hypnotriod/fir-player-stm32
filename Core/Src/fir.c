
#include "fir.h"
#include "spi.h"

bool FIR_isFullTransferComplete = false;

int32_t FIR_buffer[AUDIO_CIRCULAR_BUFFER_HALF_SIZE] = {0};

void FIR_FullTransferCompleteCallback(struct __DMA_HandleTypeDef * hdma);

#define FIR_CSHigh()  {SPI_CS_GPIO_Port->ODR |= SPI_CS_Pin;}
#define FIR_CSLow()   {SPI_CS_GPIO_Port->ODR &= ~SPI_CS_Pin;}

void FIR_Init(void)
{
  FIR_CSHigh();
}

void FIR_Transfer(int16_t * pBuff)
{
  size_t i;
  
  for (i = 0; i < AUDIO_CIRCULAR_BUFFER_HALF_SIZE; i += FIR_PACKET_SAMPLES_NUM * 2) {
    ((int16_t *) FIR_buffer)[i]   = *pBuff++;
    ((int16_t *) FIR_buffer)[i+1] = *pBuff++;
    ((int16_t *) FIR_buffer)[i+2] = 0;
    ((int16_t *) FIR_buffer)[i+3] = 0;
  }
  
  FIR_CSLow();
  HAL_SPI_TransmitReceive_DMA(&hspi3, (uint8_t *)FIR_buffer, (uint8_t *)FIR_buffer, sizeof(FIR_buffer));
  hspi3.hdmarx->XferHalfCpltCallback = NULL;
  hspi3.hdmarx->XferCpltCallback     = FIR_FullTransferCompleteCallback;
}

void FIR_FullTransferCompleteCallback(struct __DMA_HandleTypeDef * hdma)
{
  FIR_isFullTransferComplete = true;
  FIR_CSHigh();
}
