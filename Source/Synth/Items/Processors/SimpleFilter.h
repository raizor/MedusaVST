#pragma once

#include "../ItemProcessor.h"

// float params
#define FILTER_PARAM_FLOAT_CUTOFF          1
#define FILTER_PARAM_FLOAT_RESONANCE       2
#define FILTER_PARAM_FLOAT_PANNING         3
#define FILTER_PARAM_FLOAT_SEPARATION      4
#define FILTER_PARAM_FLOAT_CUTOFF_MOD      5

// int params
#define FILTER_PARAM_INT_TYPE              0
#define FILTER_PARAM_INT_LIMITER           1

// bool
#define FILTER_PARAM_BOOL_RESONANCE_BOOST  0

// LRC filter.
// The state variables are 'l' and 'b'. The time series for l and b
// correspond to a resonant low-pass and band-pass respectively, hence
// the name. 'step' returns 'h', which is just the "missing" resonant
// high-pass.
//
// Note that 'freq' here isn't actually a frequency at all, it's actually
// 2*(1 - cos(2pi*freq/SR)), but V2 calls this "frequency" anyway :)
struct V2LRC
{
	sF32 l, b;

	void init()
	{
		l = b = 0.0f;
	}

	sF32 step(sF32 in, sF32 freq, sF32 reso)
	{
		l += freq * b;
		sF32 h = in - b*reso - l;
		b += freq * h;
		return h;
	}

	// 2x oversampled step (the good stuff)
	sF32 step_2x(sF32 in, sF32 freq, sF32 reso)
	{
		// the filters get slightly biased inputs to avoid the state variables
		// getting too close to 0 for prolonged periods of time (which would
		// cause denormals to appear)
		in += fcdcoffset;

		// step 1
		l += freq * b - fcdcoffset; // undo bias here (1 sample delay)
		b += freq * (in - b*reso - l);

		// step 2
		l += freq * b;
		sF32 h = in - b*reso - l;
		b += freq * h;

		return h;
	}
};

// Moog filter state
struct V2Moog
{
	sF32 b[5]; // filter state

	void init()
	{
		b[0] = b[1] = b[2] = b[3] = b[4] = 0.0f;
	}

	sF32 step(sF32 realin, sF32 f, sF32 p, sF32 q)
	{
		sF32 in = realin + fcdcoffset; // again, biased in
		sF32 t1, t2, t3, b4;

		in -= q * b[4]; // feedback
		t1 = b[1]; b[1] = (in + b[0]) * p - b[1] * f;
		t2 = b[2]; b[2] = (t1 + b[1]) * p - b[2] * f;
		t3 = b[3]; b[3] = (t2 + b[2]) * p - b[3] * f;
		b4   = (t3 + b[3]) * p - b[4] * f; 

		b4 -= b4*b4*b4 * (1.0f/6.0f); // clipping
		b4 -= fcdcoffset; // un-bias
		b[4] = b4 - fcdcoffset;
		b[0] = realin;

		return b4;
	}
};

class SimpleFilter : public ItemProcessor
{
public:

	float Cache[Constants_Polyphony][2][2]; 

	// Setup parameters
	float Damp;
	float Freq;

	// PrevSample
	float PrevSample;

	// Outputs
	float Low;
	float High;
	float Band;
	float Notch;

	V2Moog moog;
	V2LRC lrc[Constants_Polyphony][Constants_NumAudioChannels];

	float moogf, moogp, moogq; // moog filter coeffs

	SimpleFilter(void);
	~SimpleFilter(void);
	virtual void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
};

