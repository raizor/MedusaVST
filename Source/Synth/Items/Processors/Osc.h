#pragma once

#include "../ItemProcessor.h"

// float params
#define OSC_PARAM_FLOAT_DETUNE_OCT    1
#define OSC_PARAM_FLOAT_DETUNE_SEMI   2
#define OSC_PARAM_FLOAT_DETUNE_FINE   3
#define OSC_PARAM_FLOAT_PHASE         4
#define OSC_PARAM_FLOAT_COLOR         5
#define OSC_PARAM_FLOAT_PITCH_MOD     6

// bool params
#define OSC_PARAM_BOOL_RINGMOD       0
#define OSC_PARAM_BOOL_IS_SLAVE      1
#define OSC_PARAM_BOOL_PORTAMENTO    2

// int params
#define OSC_PARAM_INT_WAVEFORM      0
#define OSC_PARAM_INT_POLARITY      1
#define OSC_PARAM_INT_MODE          2
#define OSC_PARAM_INT_MOD_MODE      3


class Voice;
class Osc : public ItemProcessor
{
public:
	Osc* OscPrevious; // ref to next osc in chain
	Osc* OscNext; // ref to previous
	int* SyncPositions[Constants_Polyphony];
	int SyncPositionsCount[Constants_Polyphony];

	float GetFrequency(Voice* voice, int bufferIndex, bool haveFreqMod);
	void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
	void WaveChanged();
	
	Osc(void);
	~Osc(void);
};

