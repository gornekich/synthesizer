#include "leds.h"
#include "gpio_map.h"

#include "stm32f4xx_ll_bus.h"

/*
 * Private functions
 */

/*
 * Hardware configuration
 */
static void leds_hw_config(void)
{
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
    LL_GPIO_SetPinMode(LED_PORT, LED_GREEN_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(LED_PORT, LED_ORANGE_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(LED_PORT, LED_RED_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(LED_PORT, LED_BLUE_PIN, LL_GPIO_MODE_OUTPUT);
    return;
}

/*
 * Public functions
 */
void leds_manager(void *args)
{
    (void) args;

    leds_hw_config();

    while (1) {
        LL_GPIO_SetOutputPin(LED_PORT, LED_GREEN_PIN);
        LL_GPIO_SetOutputPin(LED_PORT, LED_ORANGE_PIN);
        LL_GPIO_ResetOutputPin(LED_PORT, LED_RED_PIN);
        LL_GPIO_ResetOutputPin(LED_PORT, LED_BLUE_PIN);
        vTaskDelay(200);
        LL_GPIO_ResetOutputPin(LED_PORT, LED_GREEN_PIN);
        LL_GPIO_SetOutputPin(LED_PORT, LED_ORANGE_PIN);
        LL_GPIO_SetOutputPin(LED_PORT, LED_RED_PIN);
        LL_GPIO_ResetOutputPin(LED_PORT, LED_BLUE_PIN);
        vTaskDelay(200);
        LL_GPIO_ResetOutputPin(LED_PORT, LED_GREEN_PIN);
        LL_GPIO_ResetOutputPin(LED_PORT, LED_ORANGE_PIN);
        LL_GPIO_SetOutputPin(LED_PORT, LED_RED_PIN);
        LL_GPIO_SetOutputPin(LED_PORT, LED_BLUE_PIN);
        vTaskDelay(200);
        LL_GPIO_SetOutputPin(LED_PORT, LED_GREEN_PIN);
        LL_GPIO_ResetOutputPin(LED_PORT, LED_ORANGE_PIN);
        LL_GPIO_ResetOutputPin(LED_PORT, LED_RED_PIN);
        LL_GPIO_SetOutputPin(LED_PORT, LED_BLUE_PIN);
        vTaskDelay(200);
    }
}
