#pragma once

#include "Constants.h"
#include "Utils/PitchUtils.h"
#include "Utils/Patch.h"
#include "Utils/SampleBufferFloat.h"
//

class Synth
{
public:
	bool rendering;
	
	Synth(void);
	SampleBufferFloat* MixBuffer;
	SampleBufferFloat* TestBuffer;
	SampleBufferFloat* AmpBuffer;
	void Synth_Init();
	void MixTest(SampleBufferFloat* bufferOut, int numSamples);
	void Render(short *buffer, int numSamples);
	~Synth(void);
};

