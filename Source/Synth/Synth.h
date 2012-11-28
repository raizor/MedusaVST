#pragma once

#include "Globals.h"
#include "Constants.h"
#include "Utils/PitchUtils.h"
#include "Utils/Patch.h"
#include "Utils/midi.h"
#include "Utils/console.h"
#include "Utils/SampleBufferFloat.h"
//

#define NUMBER_START_OSC 0
#define NUMBER_START_EG Constants_NumOscillators
#define NUMBER_START_LFO NUMBER_START_EG + Constants_NumEnvelopes + 2 // extra 2 for amp and pitch eg 

class Synth
{
public:
	bool rendering;
#if ENABLE_CONSOLE
	static ZDebugConsole* console;
#endif
	static double renderTime;
	static MidiEventQueue* midiQueue;
	Synth(void);
	SampleBufferFloat* MixBuffer;
	SampleBufferFloat* TestBuffer;
	SampleBufferFloat* AmpBuffer;
	void Synth_Init();
	void MixTest(SampleBufferFloat* bufferOut, int numSamples);
	void Render(short *buffer, int numSamples);
	void RenderFloat(float* bufferLeft, float* bufferRight, int numSamples);
	~Synth(void);
};

