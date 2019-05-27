#ifndef _MODULE_H_
#define _MODULE_H_

extern "C" {
	#include "arm_math.h"
}

/**    
 * Parameter base class
 */

#define PARAM_NAME_LENGTH 10

class Parameter
{
public:

	int16_t value;
	int16_t * mapping;
	char name[PARAM_NAME_LENGTH + 1];

	Parameter();
	Parameter(char * name_);
	void map(int16_t * param);
	void unmap();
	void set(int16_t value_);
	void setdelta(int16_t delta);
	int16_t get();
	bool ismapped();
	void range_guard();
};


class ParameterMinMax : public Parameter
{
public:
	float min, max;	
	
	ParameterMinMax(char * name_, float min_, float max_);
	void range_guard();
};

class ParameterPeriodic : public ParameterMinMax
{
public:

	ParameterPeriodic(char * name_, float min_, float max_);
	void range_guard();
};

/**    
 * Module base class
 */

#define MODULE_NAME_LENGTH 10

class Module
{

public:

	char name[MODULE_NAME_LENGTH + 1];

	Parameter *param[10]; // should be dynamic list
	Parameter vout;

	Module();
	Module(char * name_);
	void step();
};



#endif // _MODULE_H_