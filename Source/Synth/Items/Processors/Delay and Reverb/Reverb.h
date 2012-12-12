#pragma once

#include "../../ItemProcessor.h"
#include "FixedDelay.h"

#define REVERB_bcombl0_LEN 1309
#define REVERB_bcombl1_LEN 1635
#define REVERB_bcombl2_LEN 1811
#define REVERB_bcombl3_LEN 1926
#define REVERB_balll0_LEN 220
#define REVERB_balll1_LEN 74
#define REVERB_bcombr0_LEN 1327
#define REVERB_bcombr1_LEN 1631
#define REVERB_bcombr2_LEN 1833
#define REVERB_bcombr3_LEN 1901
#define REVERB_ballr0_LEN 205
#define REVERB_ballr1_LEN 77

// float params
#define REVERB_PARAM_FLOAT_TIME    1
#define REVERB_PARAM_FLOAT_LOW_CUT 2
#define REVERB_PARAM_FLOAT_HI_CUT  3

class Reverb : public ItemProcessor
{
public:
	Reverb(void);
	~Reverb(void);

	void Set();
	void Reset();
	void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);

private:
	sF32 gainc[4];  // feedback gain for comb filter delays 0-3
	sF32 gaina[2];  // feedback gain for allpas delays 0-1
	sF32 gainin;    // input gain
	sF32 damp;      // high cut (1-val^2)
	sF32 lowcutVal;


	FixedDelay combd[2][4];  // left/right comb filter delay lines
	sF32 combl[2][4];     // left/right comb delay filter buffers
	FixedDelay alld[2][2];   // left/right allpass filters
	sF32 hpf[2];          // memory for low cut filters

	// delay line buffers
	sF32 bcombl0[REVERB_bcombl0_LEN];
	sF32 bcombl1[REVERB_bcombl1_LEN];
	sF32 bcombl2[REVERB_bcombl2_LEN];
	sF32 bcombl3[REVERB_bcombl3_LEN];
	sF32 balll0[REVERB_balll0_LEN];
	sF32 balll1[REVERB_balll1_LEN];
	sF32 bcombr0[REVERB_bcombr0_LEN];
	sF32 bcombr1[REVERB_bcombr1_LEN];
	sF32 bcombr2[REVERB_bcombr2_LEN];
	sF32 bcombr3[REVERB_bcombr3_LEN];
	sF32 ballr0[REVERB_ballr0_LEN];
	sF32 ballr1[REVERB_ballr1_LEN];

};

