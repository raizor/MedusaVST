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
	int Number;
	ParamType type;
	bool Modifiable;
	float DefaultModValue;
	float ModValueInc;

	Param();
	Param(ParamType type, bool modifiable, float defaultModValue, float modIncVal);
	~Param(void);

protected:	
	void* _value;	
};

class ParamList
{
public:
	int* Types;
	void** Params;
	int Size;
	int Count;

	ParamList(int size);
	~ParamList();
};

