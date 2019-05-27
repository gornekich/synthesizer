#ifndef _VCO_H_
#define _VCO_H_

#include "Module.h"

enum VCOPARAM {VIN, PHASE, AMP, MODE};

class VCO: public Module
{

public:
	VCO();
	void step();
};



#endif // _LEDS_H_