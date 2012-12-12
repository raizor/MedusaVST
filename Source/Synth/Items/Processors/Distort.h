#pragma once

#include "../ItemProcessor.h"

// float params
#define DISTORT_PARAM_FLOAT_Gain          1
#define DISTORT_PARAM_FLOAT_Amount1       2
#define DISTORT_PARAM_FLOAT_Amount2       3

class Distort : public ItemProcessor
{
public:
	Distort(void);
	~Distort(void);
	virtual void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
	static sF32 Distort::fastatan(sF32 x);
};

