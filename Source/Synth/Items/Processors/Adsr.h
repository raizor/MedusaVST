#pragma once

#include "../ItemProcessor.h"

// float params
#define ADSR_PARAM_AMOUNT_LEVEL  0

#define ADSR_PARAM_DELAY_TIME    1

#define ADSR_PARAM_START_LEVEL   2

#define ADSR_PARAM_ATTACK_TIME   3
#define ADSR_PARAM_ATTACK_LEVEL  4

#define ADSR_PARAM_DECAY_TIME    5
#define ADSR_PARAM_DECAY_LEVEL   6

#define ADSR_PARAM_SUSTAIN_TIME  7
#define ADSR_PARAM_SUSTAIN_LEVEL 8

#define ADSR_PARAM_RELEASE_TIME  9
#define ADSR_PARAM_RELEASE_LEVEL 10

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

