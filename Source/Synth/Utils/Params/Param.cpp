#include "Param.h"

Param::Param()
{
}

Param::Param(ParamType type, bool modifiable, float defaultModValue, float modIncVal)
{	
	this->type = type;
	Modifiable = modifiable;
	DefaultModValue = defaultModValue;
	ModValueInc = modIncVal;	
}


Param::~Param(void)
{
}