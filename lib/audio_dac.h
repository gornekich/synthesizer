#ifndef _AUDIO_CODEC_H_
#define _AUDIO_CODEC_H_

#include "FreeRTOS.h"
#include "task.h"

#define AUDIO_DAC_STACK_DEPTH    256

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
