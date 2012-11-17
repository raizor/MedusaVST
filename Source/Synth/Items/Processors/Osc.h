#pragma once

#include "../ItemProcessor.h"

// float params
#define OSC_PARAM_VOLUME        0
#define OSC_PARAM_DETUNE_OCT    1
#define OSC_PARAM_DETUNE_SEMI   2
#define OSC_PARAM_DETUNE_FINE   3
#define OSC_PARAM_PHASE         4
#define OSC_PARAM_COLOR         5
#define OSC_PARAM_PITCH_MOD     6

// bool params
#define OSC_PARAM_RINGMOD       0
#define OSC_PARAM_IS_SLAVE      1
#define OSC_PARAM_PORTAMENTO    2

// int params
#define OSC_PARAM_POLARITY      0
#define OSC_PARAM_MODE          1
#define OSC_PARAM_MOD_MODE      2


class Voice;
class Osc : public ItemProcessor
{
public:
	Osc* OscPrevious; // ref to next osc in chain
	Osc* OscNext; // ref to previous
	int* SyncPositions[Constants_Polyphony];
	int SyncPositionsCount[Constants_Polyphony];

	float Osc::GetFrequency(Voice* voice, int bufferIndex, bool haveFreqMod);
	void Osc::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
	void Osc::WaveChanged();
	
	Osc(void);
	~Osc(void);
};

