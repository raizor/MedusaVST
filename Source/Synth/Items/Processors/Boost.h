#pragma once

#include "../ItemProcessor.h"

class Boost : public ItemProcessor
{
public:
	Boost(void);
	~Boost(void);
	virtual void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);

private:		
	sF32 a1, a2;      // normalized filter coeffs
	sF32 b0, b1, b2;
	sF32 x1[2];       // state variables
	sF32 x2[2];
	sF32 y1[2];
	sF32 y2[2];
};

