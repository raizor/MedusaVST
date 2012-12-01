#include "ParamInt.h"


ParamInt::ParamInt(int value) : Param(kParamTypeInt, false, 0, 0)
{
	_value = new int();
	*(int*)_value = value;
}

ParamInt::~ParamInt(void)
{
}


int ParamInt::Value()
{
	return *(int*)_value;
}

void ParamInt::SetValue(int value)
{
	*(int*)_value = value;
}
