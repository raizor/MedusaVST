#pragma once

#include "Constants.h"

Constants* Constants::instance = 0;

Constants::Constants()
{
	BufferOffset = 0; // offset into float buffers for current dsound mix pos, offset is in floats
	MasterVolume = 1;
	CurrentPatchNumber[Constants_NumMidiChannels];
	CurrentPatchNumberEditor = 0;
	long RenderTime = 0;

	MasterVolume = 1.0f;
	RenderTime = 0;
	
	for(int i=0; i<Constants_NumMidiChannels; i++)
	{
		// default to one patch per channel atm
		CurrentPatchNumber[i] = i;
	}

	//Constants_CurrentPatchNumber = 0;
	
	//PowerOfTwoTable::instance
	//Pow2Table= new PowerOfTwoTable();
	//Constants::TimeIncrement = 1.0f / (float)Constants::SamplesPerSec;
	//
	Constants::CalcNewSampleRate(Constants_SamplesPerSec);
}

//int Constants_CurrentPatchNumber;

// Stuff that depends on the sample rate
sF32 SRfcsamplesperms;
sF32 SRfcobasefrq;
sF32 SRfclinfreq;
sF32 SRfcBoostCos, SRfcBoostSin;
sF32 SRfcdcfilter;

sInt SRcFrameSize;
sF32 SRfciframe;

void Constants::CalcNewSampleRate(sInt samplerate)
{
	sF32 sr = (sF32)samplerate;

	SRfcsamplesperms = sr / 1000.0f;
	SRfcobasefrq = (fcoscbase * fc32bit) / sr;
	SRfclinfreq = fcsrbase / sr;
	SRfcdcfilter = 1.0f - fcdcflt / sr;

	// frame size
	SRcFrameSize = (sInt)(fcframebase * sr / fcsrbase + 0.5f);
	SRfciframe = 1.0f / (sF32)SRcFrameSize;

	// low shelving EQ
	sF32 boost = (fcboostfreq * fc2pi) / sr;
	SRfcBoostCos = cos(boost);
	SRfcBoostSin = sin(boost);
}

int Constants::GetExponentialValue(float value, int max, float mult)
{
	for (int i = 0; i <= max; i++)
	{
		float val = (float)pow(mult, ((float)i / max) * 10) * 0.0127f;
		if (val >= value)
		{
			return i;
		}
	}
	return 0;
}
