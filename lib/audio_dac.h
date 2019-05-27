#ifndef _AUDIO_CODEC_H_
#define _AUDIO_CODEC_H_

#include "FreeRTOS.h"
#include "task.h"

#define AUDIO_DAC_ADDRESS        0x94
#define AUDIO_DAC_STANDART       0x04
#define AUDIO_DEFAULT_VOLUME     200
#define AUDIO_FREQUENCY          48000

#define BUFF_SIZE                4096

#define AUDIO_DAC_STACK_DEPTH    256

// extern uint16_t *AUDIO_SAMPLE;

typedef struct {
        uint16_t buff1[BUFF_SIZE];
        uint16_t buff2[BUFF_SIZE];
        uint16_t *cur_source;
        uint8_t start_processing;
        uint8_t cur_state;
        uint32_t audio_size;
} audio_ctrl_t;

/*
 * Memory for audio codec task
 */
StackType_t audio_dac_manager_ts[AUDIO_DAC_STACK_DEPTH];
StaticTask_t audio_dac_manager_tb;

/*
 * Leds manager task
 */
void audio_dac_manager(void *args);

#endif //_AUDIO_CODEC_H_
