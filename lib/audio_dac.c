#include "audio_dac.h"
#include "gpio_map.h"
#include "peripheral.h"

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_rcc.h"

#include "arm_math.h"

extern uint16_t AUDIO_SAMPLE[];
extern float32_t sinTable_f32[];
/*
 * Private control variable
 */
static audio_ctrl_t *audio_ctrl;

/*
 * Private functions
 */

/*
 * Audio dac GPIO configuration
 */
static void audio_gpio_config(void)
{
    /*
     * Setup RESET pin
     */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
    LL_GPIO_SetPinMode(AUDIO_RESET_PORT, AUDIO_RESET_PIN, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(AUDIO_RESET_PORT, AUDIO_RESET_PIN,
                             AUDIO_RESET_OUTPUT_TYPE);
    LL_GPIO_SetPinPull(AUDIO_RESET_PORT, AUDIO_RESET_PIN, LL_GPIO_PULL_NO);

    /*
     * Setup I2C pins
     * SCL pin
     */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOB);
    LL_GPIO_SetPinMode(AUDIO_I2C_PORT, AUDIO_I2C_SCL_PIN,
                       LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinOutputType(AUDIO_I2C_PORT, AUDIO_I2C_SCL_PIN,
                             AUDIO_I2C_OUTPUT_TYPE);
    LL_GPIO_SetAFPin_0_7(AUDIO_I2C_PORT, AUDIO_I2C_SCL_PIN, AUDIO_I2C_AF);
    LL_GPIO_SetPinSpeed(AUDIO_I2C_PORT, AUDIO_I2C_SCL_PIN,
                        LL_GPIO_SPEED_FREQ_HIGH);
    /*
     * SDA pin
     */
    LL_GPIO_SetPinMode(AUDIO_I2C_PORT, AUDIO_I2C_SDA_PIN,
                       LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinOutputType(AUDIO_I2C_PORT, AUDIO_I2C_SDA_PIN,
                             AUDIO_I2C_OUTPUT_TYPE);
    LL_GPIO_SetAFPin_8_15(AUDIO_I2C_PORT, AUDIO_I2C_SDA_PIN, AUDIO_I2C_AF);
    LL_GPIO_SetPinSpeed(AUDIO_I2C_PORT, AUDIO_I2C_SDA_PIN,
                        LL_GPIO_SPEED_FREQ_HIGH);

    /*
     * Setup I2S pins
     * SCL pin
     */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
    LL_GPIO_SetPinMode(AUDIO_I2S_SCK_PORT, AUDIO_I2S_SCK_PIN,
                       LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinOutputType(AUDIO_I2S_SCK_PORT, AUDIO_I2S_SCK_PIN,
                             AUDIO_I2S_OUTPUT_TYPE);
    LL_GPIO_SetAFPin_8_15(AUDIO_I2S_SCK_PORT, AUDIO_I2S_SCK_PIN, AUDIO_I2S_AF);
    LL_GPIO_SetPinSpeed(AUDIO_I2S_SCK_PORT, AUDIO_I2S_SCK_PIN,
                        LL_GPIO_SPEED_FREQ_HIGH);
    /*
     * SD pin
     */
    LL_GPIO_SetPinMode(AUDIO_I2S_SD_PORT, AUDIO_I2S_SD_PIN,
                       LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinOutputType(AUDIO_I2S_SD_PORT, AUDIO_I2S_SD_PIN,
                             AUDIO_I2S_OUTPUT_TYPE);
    LL_GPIO_SetAFPin_8_15(AUDIO_I2S_SD_PORT, AUDIO_I2S_SD_PIN, AUDIO_I2S_AF);
    LL_GPIO_SetPinSpeed(AUDIO_I2S_SD_PORT, AUDIO_I2S_SD_PIN,
                        LL_GPIO_SPEED_FREQ_HIGH);
    /*
     * MCK pin
     */
    LL_GPIO_SetPinMode(AUDIO_I2S_MCK_PORT, AUDIO_I2S_MCK_PIN,
                       LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinOutputType(AUDIO_I2S_MCK_PORT, AUDIO_I2S_MCK_PIN,
                             AUDIO_I2S_OUTPUT_TYPE);
    LL_GPIO_SetAFPin_0_7(AUDIO_I2S_MCK_PORT, AUDIO_I2S_MCK_PIN, AUDIO_I2S_AF);
    LL_GPIO_SetPinSpeed(AUDIO_I2S_MCK_PORT, AUDIO_I2S_MCK_PIN,
                        LL_GPIO_SPEED_FREQ_HIGH);
    /*
     * WC pin
     */
    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_GPIO_SetPinMode(AUDIO_I2S_WC_PORT, AUDIO_I2S_WC_PIN,
                       LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinOutputType(AUDIO_I2S_WC_PORT, AUDIO_I2S_WC_PIN,
                             AUDIO_I2S_OUTPUT_TYPE);
    LL_GPIO_SetAFPin_0_7(AUDIO_I2S_WC_PORT, AUDIO_I2S_WC_PIN, AUDIO_I2S_AF);
    LL_GPIO_SetPinSpeed(AUDIO_I2S_WC_PORT, AUDIO_I2S_WC_PIN,
                        LL_GPIO_SPEED_FREQ_HIGH);
    return;
}

/*
 * Peripheral I2C and I2S configuration
 */
static void audio_periph_config(void)
{
    /*
     * Audio I2C configuration
     */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);
    LL_I2C_ConfigSpeed(AUDIO_I2C, RCC_APB1_CLK, AUDIO_I2C_CLK,
                       LL_I2C_DUTYCYCLE_2);
    LL_I2C_SetMode(AUDIO_I2C, AUDIO_I2C_MODE);
    LL_I2C_Enable(AUDIO_I2C);
    /*
     * Audio I2S configuration
     */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
    LL_I2S_SetDataFormat(AUDIO_I2S, AUDIO_I2S_DATA_FORMAT);
    LL_I2S_SetStandard(AUDIO_I2S, AUDIO_I2S_STANDART);
    LL_I2S_SetTransferMode(AUDIO_I2S, AUDIO_I2S_TRANSFER_MODE);
    LL_I2S_SetClockPolarity(AUDIO_I2S, AUDIO_I2S_POLARITY);
    LL_I2S_SetPrescalerLinear(AUDIO_I2S, AUDIO_I2S_PSC);
    LL_I2S_SetPrescalerParity(AUDIO_I2S, AUDIO_I2S_PSC_PARITY);
    LL_I2S_EnableMasterClock(AUDIO_I2S);
    // LL_I2S_EnableDMAReq_TX(AUDIO_I2S);
    LL_I2S_Enable(AUDIO_I2S);
    /*
     * Audio I2S DMA transmition configuration
     */
    // LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);
    // LL_DMA_SetChannelSelection(AUDIO_DMA, AUDIO_DMA_STREAM, AUDIO_DMA_CHANNEL);
    // LL_DMA_ConfigAddresses(AUDIO_DMA, AUDIO_DMA_STREAM,
    //                        (uint32_t)(&AUDIO_SAMPLE[58]),
    //                        AUDIO_DMA_DST_ADDR, AUDIO_DMA_DIRECTION);
    // LL_DMA_SetDataLength(AUDIO_DMA, AUDIO_DMA_STREAM, 500000);
    // LL_DMA_SetPeriphSize(AUDIO_DMA, AUDIO_DMA_STREAM,
    //                      LL_DMA_PDATAALIGN_HALFWORD);
    // LL_DMA_SetMemorySize(AUDIO_DMA, AUDIO_DMA_STREAM,
    //                      LL_DMA_MDATAALIGN_HALFWORD);
    // LL_DMA_SetMode(AUDIO_DMA, AUDIO_DMA_STREAM, AUDIO_DMA_MODE);
    // LL_DMA_SetMemoryIncMode(AUDIO_DMA, AUDIO_DMA_STREAM,
    //                         AUDIO_DMA_MEM_INC_MODE);
    // LL_DMA_SetPeriphIncMode(AUDIO_DMA, AUDIO_DMA_STREAM,
    //                         AUDIO_DMA_PERIPH_INC_MODE);
    // LL_DMA_SetStreamPriorityLevel(AUDIO_DMA, AUDIO_DMA_STREAM,
    //                               LL_DMA_PRIORITY_VERYHIGH);
    // LL_DMA_EnableIT_TC(AUDIO_DMA, AUDIO_DMA_STREAM);
    // NVIC_SetPriority(AUDIO_DMA_STREAM_IRQN, AUDIO_DMA_STREAM_IRQN_PRIORITY);
    NVIC_EnableIRQ(AUDIO_DMA_STREAM_IRQN);
    return;
}

static void play_wav(void)
{
    uint32_t i = 0;

    for (i = 58; i < 500000; i++)
    {
        LL_I2S_TransmitData16(AUDIO_I2S, AUDIO_SAMPLE[i]);
        while (!LL_I2S_IsActiveFlag_TXE(AUDIO_I2S));
        LL_I2S_TransmitData16(AUDIO_I2S, AUDIO_SAMPLE[i]);
        while (!LL_I2S_IsActiveFlag_TXE(AUDIO_I2S));
    }
}

static void transmit_i2s(void)
{
    int i = 0;
    float freq = 440;
    int samples = AUDIO_FREQUENCY; // samples for 1 sec
    float time_step = 1 / (float) samples;
    float time = 0.0;
    float rad = 0.0;
    float sample_f = 0.0;
    uint16_t sample = 0;

    for (i = 0; i < samples * freq; i++) {
        // rad =  2.0 * 3.1415 * freq * time;
        // sample_f = 0.5 * (arm_sin_f32(rad) + 1.0); // data from [0, 1]
        // sample = (uint16_t) (sample_f * 20000.0);
        sample = (uint16_t) (0.5 * (sinTable_f32[i%512] + 1) * 32657.0);

        LL_I2S_TransmitData16(AUDIO_I2S, sample);
        while (!LL_I2S_IsActiveFlag_TXE(AUDIO_I2S));
        LL_I2S_TransmitData16(AUDIO_I2S, sample);
        while (!LL_I2S_IsActiveFlag_TXE(AUDIO_I2S));
        time += time_step;
    }
}

static uint8_t audio_i2c_set_reg(uint8_t reg_addr, uint8_t reg_val)
{
    int timeout = 100000;

    /*
     * Check if i2c is buisy
     */
    while (LL_I2C_IsActiveFlag_BUSY(AUDIO_I2C) && (timeout-- > 0));
    if (timeout <= 0)
        return 1;
    /*
     * Generate start condition
     */
    LL_I2C_GenerateStartCondition(AUDIO_I2C);
    /*
     * Wait for start condition generation
     */
    while (!LL_I2C_IsActiveFlag_SB(AUDIO_I2C) && (timeout-- > 0));
    if (timeout <= 0)
        return 1;
    /*
     * Transmit addres, AD0 pin and write request
     */
    LL_I2C_TransmitData8(AUDIO_I2C, AUDIO_DAC_ADDRESS);
    /*
     * Wait for master transmitting mode selection
     */
    while (!LL_I2C_IsActiveFlag_ADDR(AUDIO_I2C) && (timeout-- > 0));
    if (timeout <= 0)
        return 1;
    LL_I2C_ClearFlag_ADDR(AUDIO_I2C);
    /*
     * Transmit target register address
     */
    LL_I2C_TransmitData8(AUDIO_I2C, reg_addr);
    /*
     * Wait for transmittion complete
     */
    while (!LL_I2C_IsActiveFlag_BTF(AUDIO_I2C) && (timeout-- > 0));
    if (timeout <= 0)
        return 1;
    /*
     * Transmit target register value
     */
    LL_I2C_TransmitData8(AUDIO_I2C, reg_val);
    /*
     * Wait for transmittion complete
     */
    while (!LL_I2C_IsActiveFlag_BTF(AUDIO_I2C) && (timeout-- > 0));
    if (timeout <= 0)
        return 1;
    /*
     * Generate stop condition
     */
    LL_I2C_GenerateStopCondition(AUDIO_I2C);
    return 0;

}

static void audio_set_volume(uint8_t volume)
{
    if (volume > 0xe6) {
        audio_i2c_set_reg(0x20, volume - 0xe7);
        audio_i2c_set_reg(0x21, volume - 0xe7);
    }
    else {
        audio_i2c_set_reg(0x20, volume + 0x19);
        audio_i2c_set_reg(0x21, volume + 0x19);
    }
    return;
}

static void audio_play()
{
    LL_DMA_EnableStream(AUDIO_DMA, AUDIO_DMA_STREAM);
}

static void audio_reset()
{
    LL_GPIO_ResetOutputPin(AUDIO_RESET_PORT, AUDIO_RESET_PIN);
    vTaskDelay(30);
    LL_GPIO_SetOutputPin(AUDIO_RESET_PORT, AUDIO_RESET_PIN);
}

/*
 * Hardware initialization
 */
static void codec_hw_config(void)
{
    /*
     * GPIO and peripheral configuration
     */
    audio_gpio_config();
    audio_periph_config();
    /*
     * Audio dac setup
     */
    /* Reset dac */
    audio_reset();
    /* Switch off the codec */
    audio_i2c_set_reg(0x02, 0x01);
    /* SPK off and HP on */
    audio_i2c_set_reg(0x04, 0xaf);
    /* Clock configuration - auto detection */
    audio_i2c_set_reg(0x05, 0x81);
    /* Set slave mode anf audio standart */
    audio_i2c_set_reg(0x06, AUDIO_DAC_STANDART);
    /* Set default volume */
    audio_set_volume(AUDIO_DEFAULT_VOLUME);
    /* Switch on the codec */
    audio_i2c_set_reg(0x02, 0x9e);
    /* Supplementary setup */
    audio_i2c_set_reg(0x0a, 0x00);
    audio_i2c_set_reg(0x0e, 0x04);
    audio_i2c_set_reg(0x27, 0x00);
    audio_i2c_set_reg(0x1f, 0x0f);
    audio_i2c_set_reg(0x1a, 0x0a);
    audio_i2c_set_reg(0x1b, 0x0a);
    /* Whait until all settings done */
    vTaskDelay(30);
    return;
}

/*
 * Public functions
 */

/*
 * Audio manager task
 */
void audio_dac_manager(void *args)
{
    (void) args;

    codec_hw_config();
    // audio_play();

    while (1) {
        // transmit_i2s();
        play_wav();
        //vTaskDelay(30);
    }
}

/*
 * Hardware interrupts
 */

/*
 * Audio I2S DMA interrupt
 */
void DMA1_Stream7_IRQHandler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

        if (LL_DMA_IsActiveFlag_TC7(AUDIO_DMA)) {
                LL_DMA_DisableStream(AUDIO_DMA, AUDIO_DMA_STREAM);
                LL_DMA_ClearFlag_TC7(AUDIO_DMA);
                LL_DMA_EnableStream(AUDIO_DMA, AUDIO_DMA_STREAM);
        }
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
