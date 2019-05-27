#include "ModularSynth.h"
#include "VCO.h"

extern "C" {
	#include "arm_math.h"
}

extern "C" int16_t sinTable_q15[];

VCO vco1;

extern "C" int16_t modular_step();

uint16_t kk = 0;

int16_t modular_step()
{
	// vco1.step();

	// vco1.vout.value = arm_sin_q15(kk);
	// kk += 0.01;

	int f = 0;
	for (f = 0; f < 20; f++){};

	kk += 1;
	return sinTable_q15[kk%512];
	return arm_sin_q15(kk);

	// return vco1.vout.value;
}