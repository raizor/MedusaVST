#pragma once

#include "../ItemProcessor.h"

// float params
#define ADSR_PARAM_FLOAT_DELAY_TIME    1

#define ADSR_PARAM_FLOAT_START_LEVEL   2

#define ADSR_PARAM_FLOAT_ATTACK_TIME   3
#define ADSR_PARAM_FLOAT_ATTACK_LEVEL  4

#define ADSR_PARAM_FLOAT_DECAY_TIME    5
#define ADSR_PARAM_FLOAT_DECAY_LEVEL   6

#define ADSR_PARAM_FLOAT_SUSTAIN_TIME  7
#define ADSR_PARAM_FLOAT_SUSTAIN_LEVEL 8

#define ADSR_PARAM_FLOAT_RELEASE_TIME  9
#define ADSR_PARAM_FLOAT_RELEASE_LEVEL 10

class Adsr : public ItemProcessor
{
public:
	EgType type;
	int* stage;
	float* value;
	float* stageAmount;

	Adsr(EgType egType);
	~Adsr(void);

	void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
	void Reset();
};

