#pragma once

#include "../../Constants.h"
#include "Param.h"
#include "../SampleBufferFloat.h"

class ParamInt  : public Param
{
public:
	ParamInt(int value);
	~ParamInt(void);
	int Value();
	void SetValue(int value);
};

