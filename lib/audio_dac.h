#ifndef _AUDIO_CODEC_H_
#define _AUDIO_CODEC_H_

#include "FreeRTOS.h"
#include "task.h"

#define AUDIO_DAC_ADDRESS        0x94
#define AUDIO_DAC_STANDART       0x04
#define AUDIO_DEFAULT_VOLUME     200
#define AUDIO_FREQUENCY          48000

#define AUDIO_DAC_STACK_DEPTH    256

// extern uint16_t *AUDIO_SAMPLE;

typedef struct {
        uint16_t *audio_src;
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
