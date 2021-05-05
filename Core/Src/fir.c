
#include "fir.h"
#include "spi.h"

volatile bool FIR_dataReady = false;
volatile bool FIR_impulseReady = true;

static int32_t buffer[AUDIO_CIRCULAR_BUFFER_QUARTER_SIZE] = {0};
static volatile uint32_t impulseBytesLeft = 0;
static volatile uint8_t * impulse;

#define FIR_CSHigh()  {SPI_CS_GPIO_Port->ODR |= SPI_CS_Pin;}
#define FIR_CSLow()   {SPI_CS_GPIO_Port->ODR &= ~SPI_CS_Pin;}

#define FIR_LoadHigh()  {FIR_LOAD_GPIO_Port->ODR |= FIR_LOAD_Pin;}
#define FIR_LoadLow()   {FIR_LOAD_GPIO_Port->ODR &= ~FIR_LOAD_Pin;}

void FIR_Init(void)
{
  FIR_CSHigh();
  FIR_LoadLow();
}

void FIR_Load(const uint8_t * pBuff, uint32_t size)
{
  uint16_t bytesToTransmit;

  if (!FIR_impulseReady) return;
  
  bytesToTransmit = size < FIR_IMPULSE_PORTION_SIZE ? size : FIR_IMPULSE_PORTION_SIZE;
  FIR_impulseReady = false;
  FIR_LoadHigh();
  impulseBytesLeft = size - bytesToTransmit;
  HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)pBuff, bytesToTransmit);
  impulse = (uint8_t * )pBuff + bytesToTransmit;
}

void FIR_ResumeLoad(void)
{
  uint16_t bytesToTransmit;
  
  if (hspi1.State != HAL_SPI_STATE_READY || FIR_impulseReady) return;
  
  bytesToTransmit = impulseBytesLeft < FIR_IMPULSE_PORTION_SIZE ? impulseBytesLeft : FIR_IMPULSE_PORTION_SIZE;
  impulseBytesLeft -= bytesToTransmit;
  HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)impulse, bytesToTransmit);
  impulse += bytesToTransmit;
}

void FIR_Transfer(const int16_t * pBuff)
{
  size_t i;
  
  for (i = 0; i < AUDIO_CIRCULAR_BUFFER_HALF_SIZE; i += FIR_PACKET_SAMPLES_NUM * sizeof(uint16_t)) {
    ((uint16_t *) buffer)[i]   = AUDIO_Swap16(pBuff[0]);
    ((uint16_t *) buffer)[i+1] = AUDIO_Swap16(pBuff[2]);
    ((uint16_t *) buffer)[i+2] = AUDIO_Swap16(pBuff[4]);
    ((uint16_t *) buffer)[i+3] = AUDIO_Swap16(pBuff[6]);
    ((uint16_t *) buffer)[i+4] = AUDIO_Swap16(pBuff[8]);
    ((uint16_t *) buffer)[i+5] = AUDIO_Swap16(pBuff[10]);
    ((uint16_t *) buffer)[i+6] = AUDIO_Swap16(pBuff[12]);
    ((uint16_t *) buffer)[i+7] = AUDIO_Swap16(pBuff[14]);
    ((int16_t *) buffer)[i+8] = 0;
    ((int16_t *) buffer)[i+9] = 0;
    ((int16_t *) buffer)[i+10] = 0;
    ((int16_t *) buffer)[i+11] = 0;
    ((int16_t *) buffer)[i+12] = 0;
    ((int16_t *) buffer)[i+13] = 0;
    ((int16_t *) buffer)[i+14] = 0;
    ((int16_t *) buffer)[i+15] = 0;
    pBuff += 16;
  }
  
  FIR_CSLow();
  HAL_SPI_TransmitReceive_DMA(&hspi3, (uint8_t *)buffer, (uint8_t *)buffer, sizeof(buffer));
}

void FIR_Fill(int16_t * pBuff)
{
  size_t i;
  int16_t sample;
  
  for (i = 0 ; i < AUDIO_CIRCULAR_BUFFER_QUARTER_SIZE; i++) {
    sample = buffer[i];
    pBuff[i * 2] = AUDIO_Swap16(sample);
    pBuff[i * 2 + 1] = pBuff[i * 2];
  }
}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if(hspi == &hspi1)
  {
    if (impulseBytesLeft == 0) {
      FIR_LoadLow();
      FIR_impulseReady = true;
    }
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
