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

ParamList::ParamList(int size)
{
	Size = size;
	Count = 0;
	Params = (void**)zynth_mallocAlloc(sizeof(void*)*size);
	Types = (int*)zynth_mallocAlloc(sizeof(int)*size);
}

ParamList::~ParamList()
{
}
