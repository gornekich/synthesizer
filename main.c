#include "stm32f4xx_ll_rcc.h"
#include "stm32f4xx_ll_system.h"
#include "stm32f4xx_ll_usart.h"

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "leds.h"
#include "audio_dac.h"

/**
  *   System Clock Configuration
  *   The system Clock is configured as follow :
  *   System Clock source        = PLL (HSE)
  *   SYSCLK(Hz)             = 168000000
  *   HCLK(Hz)               = 168000000
  *   AHB Prescaler          = 1
  *   APB1 Prescaler         = 4
  *   APB2 Prescaler         = 2
  *   HSE Frequency(Hz)          = 8000000
  *   PLL_M              = 8
  *   PLL_N              = 336
  *   PLL_P              = 2
  *   VDD(V)             = 3.3
  *   Main regulator output voltage  = Scale1 mode
  *   Flash Latency(WS)          = 5
  */
static void rcc_config()
{
    /* Enable HSE oscillator */
    LL_RCC_HSE_Enable();
    while (LL_RCC_HSE_IsReady() != 1);

    /* Set FLASH latency */
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_5);

    /* Main PLL configuration and activation */
    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_8,
                    336, LL_RCC_PLLP_DIV_2);
    LL_RCC_PLL_Enable();
    while (LL_RCC_PLL_IsReady() != 1);

    /* Sysclk activation on the main PLL */
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

    /* Set APB1 & APB2 prescaler */
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_2);

    /* Set systick to 1ms */
    SysTick_Config(168000000/1000);

    /* Update CMSIS variable (which can be updated also
     * through SystemCoreClockUpdate function) */
    SystemCoreClock = 168000000;
}

int main() {
    rcc_config();
    NVIC_SetPriorityGrouping(0);

    xTaskCreateStatic(leds_manager, "LEDS_MAN", LEDS_MAN_STACK_DEPTH,
                      NULL, 2, leds_manager_ts, &leds_manager_tb);
    xTaskCreateStatic(audio_dac_manager, "AUDIO_DAC_MAN", AUDIO_DAC_STACK_DEPTH,
                      NULL, 2, audio_dac_manager_ts, &audio_dac_manager_tb);

    vTaskStartScheduler();
    return 0;
}
