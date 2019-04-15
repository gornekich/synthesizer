#include "audio_dac.h"

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_i2c.h"
#include "stm32f4xx_ll_spi.h"

static void codec_hw_config(void)
{
    
}

void audio_dac_manager(void *args)
{
    (void) args;

    codec_hw_config();

    while (1) {

    }
}