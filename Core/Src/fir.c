
#include "fir.h"
#include "spi.h"

#define INPUT_AMPLIFY_FACTOR 12

volatile bool FIR_isFullTransferComplete = false;

int32_t FIR_buffer[AUDIO_CIRCULAR_BUFFER_QUARTER_SIZE] = {0};

#define FIR_CSHigh()  {SPI_CS_GPIO_Port->ODR |= SPI_CS_Pin;}
#define FIR_CSLow()   {SPI_CS_GPIO_Port->ODR &= ~SPI_CS_Pin;}

void FIR_Init(void)
{
  FIR_CSHigh();
}

void FIR_Transfer(int16_t * pBuff)
{
  size_t i;
  int16_t sample;
  
  for (i = 0; i < AUDIO_CIRCULAR_BUFFER_HALF_SIZE; i += 4) {
    sample = *pBuff * INPUT_AMPLIFY_FACTOR;
    pBuff += 2;
    ((uint16_t *) FIR_buffer)[i]   = AUDIO_Swap16(sample);
    sample = *pBuff * INPUT_AMPLIFY_FACTOR;
    pBuff += 2;
    ((uint16_t *) FIR_buffer)[i+1] = AUDIO_Swap16(sample);
    ((int16_t *) FIR_buffer)[i+2] = 0;
    ((int16_t *) FIR_buffer)[i+3] = 0;
  }
  
  FIR_CSLow();
  HAL_SPI_TransmitReceive_DMA(&hspi3, (uint8_t *)FIR_buffer, (uint8_t *)FIR_buffer, sizeof(FIR_buffer));
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if(hspi == &hspi3)
  {
    FIR_isFullTransferComplete = true;
    FIR_CSHigh();
  }
}
