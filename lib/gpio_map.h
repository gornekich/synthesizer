#ifndef _GPIO_MAP_H
#define _GPIO_MAP_H

#include "stm32f407xx.h"
#include "stm32f4xx_ll_gpio.h"

/*
 * Debug LED pinout
 */
#define LED_PORT                        GPIOD
#define LED_GREEN_PIN                   LL_GPIO_PIN_12
#define LED_ORANGE_PIN                  LL_GPIO_PIN_13
#define LED_RED_PIN                     LL_GPIO_PIN_14
#define LED_BLUE_PIN                    LL_GPIO_PIN_15

/*
 * Audio dac pinout :
 * RESET pin
 */
#define AUDIO_RESET_PORT                GPIOD
#define AUDIO_RESET_PIN                 LL_GPIO_PIN_4
#define AUDIO_RESET_OUTPUT_TYPE         LL_GPIO_OUTPUT_PUSHPULL

/*
 * I2C pinout
 */
#define AUDIO_I2C_PORT                  GPIOB
#define AUDIO_I2C_SCL_PIN               LL_GPIO_PIN_6
#define AUDIO_I2C_SDA_PIN               LL_GPIO_PIN_9
#define AUDIO_I2C_OUTPUT_TYPE           LL_GPIO_OUTPUT_OPENDRAIN
#define AUDIO_I2C_AF                    LL_GPIO_AF_4

/*
 * I2S pinout
 */
#define AUDIO_I2S_SCK_PORT              GPIOC
#define AUDIO_I2S_SCK_PIN               LL_GPIO_PIN_10
#define AUDIO_I2S_SD_PORT               GPIOC
#define AUDIO_I2S_SD_PIN                LL_GPIO_PIN_12
#define AUDIO_I2S_MCK_PORT              GPIOC
#define AUDIO_I2S_MCK_PIN               LL_GPIO_PIN_7
#define AUDIO_I2S_WC_PORT               GPIOA
#define AUDIO_I2S_WC_PIN                LL_GPIO_PIN_4
#define AUDIO_I2S_OUTPUT_TYPE           LL_GPIO_OUTPUT_PUSHPULL
#define AUDIO_I2S_AF                    LL_GPIO_AF_6





#endif //_GPIO_MAP_H
