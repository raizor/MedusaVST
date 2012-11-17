#pragma once

#include "../../Constants.h"
#include "Param.h"
#include "../SampleBufferFloat.h"

class ParamBool  : public Param
{
public:
	ParamBool(bool value);
	~ParamBool(void);
	bool Value();
};

