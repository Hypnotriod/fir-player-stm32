
#include "fir.h"
#include "spi.h"

volatile bool FIR_dataReady = false;

static int32_t _buffer[AUDIO_CIRCULAR_BUFFER_QUARTER_SIZE] = {0};

#define FIR_CSHigh()  {SPI_CS_GPIO_Port->ODR |= SPI_CS_Pin;}
#define FIR_CSLow()   {SPI_CS_GPIO_Port->ODR &= ~SPI_CS_Pin;}

void FIR_Init(void)
{
  FIR_CSHigh();
}

void FIR_Transfer(int16_t * pBuff)
{
  size_t i;
  
  for (i = 0; i < AUDIO_CIRCULAR_BUFFER_HALF_SIZE; i += FIR_PACKET_SAMPLES_NUM * sizeof(uint16_t)) {
    ((uint16_t *) _buffer)[i]   = AUDIO_Swap16(pBuff[0]);
    ((uint16_t *) _buffer)[i+1] = AUDIO_Swap16(pBuff[2]);
    ((uint16_t *) _buffer)[i+2] = AUDIO_Swap16(pBuff[4]);
    ((uint16_t *) _buffer)[i+3] = AUDIO_Swap16(pBuff[6]);
    ((uint16_t *) _buffer)[i+4] = AUDIO_Swap16(pBuff[8]);
    ((uint16_t *) _buffer)[i+5] = AUDIO_Swap16(pBuff[10]);
    ((uint16_t *) _buffer)[i+6] = AUDIO_Swap16(pBuff[12]);
    ((uint16_t *) _buffer)[i+7] = AUDIO_Swap16(pBuff[14]);
    ((int16_t *) _buffer)[i+8] = 0;
    ((int16_t *) _buffer)[i+9] = 0;
    ((int16_t *) _buffer)[i+10] = 0;
    ((int16_t *) _buffer)[i+11] = 0;
    ((int16_t *) _buffer)[i+12] = 0;
    ((int16_t *) _buffer)[i+13] = 0;
    ((int16_t *) _buffer)[i+14] = 0;
    ((int16_t *) _buffer)[i+15] = 0;
    pBuff += 16;
  }
  
  FIR_CSLow();
  HAL_SPI_TransmitReceive_DMA(&hspi3, (uint8_t *)_buffer, (uint8_t *)_buffer, sizeof(_buffer));
}

void FIR_Fill(int16_t * pBuff)
{
  size_t i;
  int16_t sample;
  
  for (i = 0 ; i < AUDIO_CIRCULAR_BUFFER_QUARTER_SIZE; i++) {
    sample = _buffer[i];
    pBuff[i * 2] = AUDIO_Swap16(sample);
    pBuff[i * 2 + 1] = pBuff[i * 2];
  }
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if(hspi == &hspi3)
  {
    FIR_dataReady = true;
    FIR_CSHigh();
  }
}
