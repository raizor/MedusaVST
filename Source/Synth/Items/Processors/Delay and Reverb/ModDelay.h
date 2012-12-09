#pragma once

#include "../../ItemProcessor.h"

// float params
#define MODDELAY_PARAM_FLOAT_FEEDBACK            1
#define MODDELAY_PARAM_FLOAT_DELAY_LENGTH_LEFT   2
#define MODDELAY_PARAM_FLOAT_DELAY_LENGTH_RIGHT  3
#define MODDELAY_PARAM_FLOAT_MOD_RATE           4
#define MODDELAY_PARAM_FLOAT_MOD_DEPTH          5
#define MODDELAY_PARAM_FLOAT_MOD_PHASE          6

class ModDelay : public ItemProcessor
{
private:
	sF32 *db[2];    // left/right delay buffer
	sU32 dbufmask;  // delay buffer mask (size-1, must be pow2)

	sU32 dbptr;     // buffer write pos
	sU32 dboffs[2]; // buffer read offset

	sU32 mcnt;      // mod counter
	sInt mfreq;     // mod freq
	sU32 mphase;    // mod phase
	sU32 mmaxoffs;  // mod max offs (2048samples*depth)

	sF32 fbval;     // feedback val
	sF32 dryout;
	sF32 wetout;

public:
	ModDelay(int bufferLength);
	void Reset();
	void Set();
	inline void ProcessSample(StereoSample *out, sF32 l, sF32 r, sF32 dry);
	sF32 ProcessChanSample(sF32 in, sInt ch, sF32 dry);
	void RenderBuffer(SampleBufferFloat* bufferIn, sInt nsamples);
	void RenderChan(StereoSample *chanbuf, sInt nsamples);
	~ModDelay(void);
};

