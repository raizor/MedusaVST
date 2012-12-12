#pragma once
#include "../ItemProcessor.h"

class ChorusFlange: public ItemProcessor
{
public:
	ChorusFlange(void);
	~ChorusFlange(void);
	virtual void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
};

