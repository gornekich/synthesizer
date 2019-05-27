#ifndef _PERIPHERAL_H_
#define _PERIPHERAL_H_

#include "stm32f407xx.h"
#include "stm32f4xx_ll_i2c.h"
#include "stm32f4xx_ll_spi.h"
#include "stm32f4xx_ll_dma.h"

/*
 * Clock configuration parameters
 */
#define RCC_SYSTEM_CLK                  168000000U
#define RCC_AHB_CLK                     RCC_SYSTEM_CLK/1
#define RCC_APB1_CLK                    RCC_SYSTEM_CLK/4
#define RCC_APB2_CLK                    RCC_SYSTEM_CLK/2

/*
 * Audio dac I2C configuration
 */
#define AUDIO_I2C                       I2C1
#define AUDIO_I2C_MODE                  LL_I2C_MODE_I2C
#define AUDIO_I2C_CLK                   100000U
#define AUDIO_I2C_OWN_ADDRESS           0x33

/*
 * Audio dac I2S configuration
 */
#define AUDIO_I2S                       SPI3
#define AUDIO_I2S_DATA_FORMAT           LL_I2S_DATAFORMAT_16B
#define AUDIO_I2S_STANDART              LL_I2S_STANDARD_PHILIPS
#define AUDIO_I2S_PSC                   3U
#define AUDIO_I2S_PSC_PARITY            1U
#define AUDIO_I2S_POLARITY              LL_I2S_POLARITY_LOW
#define AUDIO_I2S_TRANSFER_MODE         LL_I2S_MODE_MASTER_TX

/*
 * Audio dac I2S DMA transmittion configuration
 */
#define AUDIO_DMA                       DMA1
#define AUDIO_DMA_CHANNEL               LL_DMA_CHANNEL_0
#define AUDIO_DMA_STREAM                LL_DMA_STREAM_7
#define AUDIO_DMA_STREAM_IRQN           DMA1_Stream7_IRQn
#define AUDIO_DMA_STREAM_IRQN_PRIORITY  (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY + 1)
#define AUDIO_DMA_DIRECTION             LL_DMA_DIRECTION_MEMORY_TO_PERIPH
#define AUDIO_DMA_BUFFER_SIZE           256U
#define AUDIO_DMA_MEM_INC_MODE          LL_DMA_MEMORY_INCREMENT
#define AUDIO_DMA_PERIPH_INC_MODE       LL_DMA_PERIPH_NOINCREMENT
#define AUDIO_DMA_MODE                  LL_DMA_MODE_NORMAL
#define AUDIO_DMA_DST_ADDR              (uint32_t)&(AUDIO_I2S->DR)

#endif //_PERIPHERAL_H_
