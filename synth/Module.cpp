#include "Module.h"

#define NULL 0

Parameter::Parameter()
{

}
	
Parameter::Parameter(char * name_)
{
	unsigned char i;
	for (i = 0; i < PARAM_NAME_LENGTH; i++) name[i] = name_[i];
	mapping = NULL;
	value = 0;
}

void Parameter::map(int16_t * param)
{
	mapping = param;
}

void Parameter::unmap()
{
	mapping = NULL;
}

void Parameter::set(int16_t value_)
{
	value = value_;
	range_guard();
}

void Parameter::setdelta(int16_t delta)
{
	value += delta;
	range_guard();
}

int16_t Parameter::get()
{
	return value;
}

bool Parameter::ismapped()
{
	return (mapping != 0);
}

void Parameter::range_guard()
{

}


ParameterMinMax::ParameterMinMax(char * name_, float min_, float max_)
	: Parameter(name_)
{
	min = min_;
	max = max_;
}

void ParameterMinMax::range_guard()
{
	if (value > max) value = max;
	if (value < min) value = min;
}

ParameterPeriodic::ParameterPeriodic(char * name_, float min_, float max_)
	: ParameterMinMax(name_, min_, max_)
{

}

void ParameterPeriodic::range_guard()
{
	// if (value > max) value = fmod(value - min, max - min) + min;
	// if (value < min) value = fmod(value - max, max - min) + max;
}


Module::Module()
{

}

Module::Module(char * name_)
{
	unsigned char i;
	for (i = 0; i < PARAM_NAME_LENGTH; i++) name[i] = name_[i];
}

void Module::step()
{

}