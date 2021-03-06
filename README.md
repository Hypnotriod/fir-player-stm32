# fir-player-stm32
`STM32F407ZGT` based project to test [FPGA's fir filter design](https://github.com/Hypnotriod/fir-filter-16bit-8x8-m9k)  
Configured with `STM32CubeMX` initialization code generator

## Hardware
* HY-STM32F4xxCore144 Core/Dev Board
* Cirrus Logic CS4270 ADC / DAC chip

## Pinout
* I2S_LRCLK -> **PB12**
* I2S_SCK -> **PB13**
* I2S_SDIN -> **PB14**
* I2S_SDOUT -> **PB15**
* I2S_MCK -> **PC6**
* I2S_EN -> **PD2**
* SPI_SCK -> **PC10**
* SPI_MISO -> **PC11**
* SPI_MOSI -> **PC12**
* SPI_CS -> **PG12**
* FIR_DO -> **PA7**
* FIR_SCK -> **PA5**
* FIR_LOAD -> **PA4**
* ENC_INT -> **PA0**
* ENC_SENSE -> **PA1**
* ENC_BTN -> **PA2**
* FPGA_READY -> **PA6**
* STATE_LED -> **PF6**
