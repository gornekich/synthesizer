#ifndef _LEDS_H_
#define _LEDS_H_

#include "FreeRTOS.h"
#include "task.h"

#define LEDS_MAN_STACK_DEPTH    256

/*
 * Memory for terminal task
 */
StackType_t leds_manager_ts[LEDS_MAN_STACK_DEPTH];
StaticTask_t leds_manager_tb;

/*
 * Leds manager task
 */
void leds_manager(void *args);

#endif // _LEDS_H_