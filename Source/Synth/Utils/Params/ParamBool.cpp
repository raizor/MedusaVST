#include "ParamBool.h"


ParamBool::ParamBool(bool value) : Param(kParamTypeBool, false, 0, 0)
{
	_value = new bool();
	*(bool*)_value = value;
}

ParamBool::~ParamBool(void)
{
}

bool ParamBool::Value()
{
	return *(bool*)_value;
}
