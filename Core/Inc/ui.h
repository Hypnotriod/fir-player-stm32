
#ifndef __UI_H__
#define __UI_H__

#include "stm32f4xx_hal.h"
#include <stdbool.h>

void UI_Update(void);

#define UI_ModesNum 2

typedef enum
{
  UI_MODE_SELECT_PRESET = 0,
  UI_MODE_AMP_VALUE = 1
} UI_Mode_t;

#endif
