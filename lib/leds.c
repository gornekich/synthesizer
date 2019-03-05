#include "leds.h"

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"

static void leds_hw_config(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
    LL_GPIO_SetPinMode(GPIOD, LL_GPIO_PIN_13, LL_GPIO_MODE_OUTPUT);
    return;
}

void leds_manager(void *args)
{
    (void) args;

    leds_hw_config();

    while (1) {
        LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_13);
        vTaskDelay(1000);
        LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_13);
        vTaskDelay(1000);
    }
}