
#include "ui.h"
#include "gpio.h"
#include "fir.h"
#include "impulse.h"
#include "amp.h"

uint8_t impulseIndex = 0;
uint8_t modeIndex = 0;

uint8_t encoderBtnCntr = 0;

volatile int16_t encoderRotations = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == ENC_INT_Pin)
  {
    if (GPIO_IsEncoderSenseHigh()) {
      encoderRotations--;
    } else {
      encoderRotations++;
    }
  }
}

void UI_Update(void)
{
  if (!FIR_impulseReady) 
  {
      FIR_ResumeLoad();
  }
  
  if (!GPIO_IsEncoderButtonHigh())
  {
    if (encoderBtnCntr == 0)
    {
      modeIndex = (modeIndex + 1) % UI_ModesNum;
      if (modeIndex == UI_MODE_AMP_VALUE)
        GPIO_StateLedOn();
      else
        GPIO_StateLedOff();
    }
    encoderBtnCntr = UINT8_MAX;
  }
  else if (GPIO_IsEncoderButtonHigh() && encoderBtnCntr)
  {
    encoderBtnCntr--;
  }
  
  if (encoderRotations)
  {
    if (modeIndex == UI_MODE_SELECT_PRESET && FIR_impulseReady)
    {
      if (encoderRotations > 0)
        impulseIndex = (impulseIndex == IMPULSES_NUM - 1) ? 0 : impulseIndex + 1;
      else
        impulseIndex = (impulseIndex == 0) ? IMPULSES_NUM - 1 : impulseIndex - 1;
      
      FIR_Load((const uint8_t *)IMPULSE_Impulses[impulseIndex], IMPULSE_SIZE);
    }
    else if (modeIndex == UI_MODE_AMP_VALUE)
    {
      if (encoderRotations > 0)
        AMP_IncrementValue();
      else
        AMP_DecrementValue();
    }
    
    encoderRotations = 0;
  }
}
