#include "Module.h"
#include "VCO.h"

extern "C" {
	#include "arm_math.h"
}

VCO::VCO()
	:Module()
{
	param[VIN] = new Parameter("VIN");
	param[PHASE] = new Parameter("PHASE");// ParameterPeriodic("PHASE", -PI, PI);
	param[AMP] = new ParameterMinMax("AMP", 0.0, 1.0);
	param[MODE] = new Parameter();

	param[VIN]->set(100);
	param[AMP]->set(40000);
	param[PHASE]->set(0);
}

void VCO::step()
{
	float vin = param[VIN]->get();
	float phase = param[PHASE]->get();
	float amp = param[AMP]->get();

	vout.set(arm_sin_f32(phase) * amp);

	// if (!param[PHASE]->ismapped()) 
	param[PHASE]->setdelta(vin * 2.0);
}