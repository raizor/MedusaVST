#pragma once

#include "../../Constants.h"
#include "../ZynthTools.h"

enum ParamType
{
	kParamTypeDefault = 1,
	kParamTypeFloat,
	kParamTypeInt,
	kParamTypeBool,
	kParamTypeEnabled,
};

class Param
{
public:
	int number;
	ParamType type;
	bool Modifiable;
	float DefaultModValue;
	float ModValueInc;

	Param();
	Param(ParamType type, bool modifiable, float defaultModValue, float modIncVal);
	~Param(void);

protected:	
	void* _value;	
#ifndef REPLAYER
	friend class ZynthIo;
#endif
};
