#pragma once

#include "../ItemProcessor.h"

// float params
#define LFO_PARAM_FLOAT_RATE          1
#define LFO_PARAM_FLOAT_DELAY         2

// int params
#define LFO_PARAM_INT_WAVEFORM      0
#define LFO_PARAM_INT_POLARITY      1

class Voice;
class Lfo : public ItemProcessor
{
public:
	Lfo(StackItemType lfoType);
	~Lfo(void);
	virtual void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
};

