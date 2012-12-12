#include "Reverb.h"


Reverb::Reverb(void) : ItemProcessor(kStackItemTypeGlobalReverb, true)
{
	// init filters
	combd[0][0].Init(bcombl0, REVERB_bcombl0_LEN);
	combd[0][1].Init(bcombl1, REVERB_bcombl1_LEN);
	combd[0][2].Init(bcombl2, REVERB_bcombl2_LEN);
	combd[0][3].Init(bcombl3, REVERB_bcombl3_LEN);
	alld[0][0].Init(balll0, REVERB_balll0_LEN);
	alld[0][1].Init(balll1, REVERB_balll1_LEN);
	combd[1][0].Init(bcombr0, REVERB_bcombr0_LEN);
	combd[1][1].Init(bcombr1, REVERB_bcombr1_LEN);
	combd[1][2].Init(bcombr2, REVERB_bcombr2_LEN);
	combd[1][3].Init(bcombr3, REVERB_bcombr3_LEN);
	alld[1][0].Init(ballr0, REVERB_ballr0_LEN);
	alld[1][1].Init(ballr1, REVERB_ballr1_LEN);

	AddFloatParam(new ParamFloat(100, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // time
	AddFloatParam(new ParamFloat(112, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // low cut
	AddFloatParam(new ParamFloat(32, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // hi cut

	// reset
	Reset();
}


Reverb::~Reverb(void)
{
}

void Reverb::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{

}

void Reverb::Set()
{
	static const sF32 gaincdef[4] = {
		0.966384599f, 0.958186359f, 0.953783929f, 0.950933178f
	};
	static const sF32 gainadef[2] = {
		0.994260075f, 0.998044717f
	};

	// todo - should be 127 not 128?

	sF32 e = SRfclinfreq * sqr(64.0f / (paramsFloat[REVERB_PARAM_FLOAT_TIME]->ValueAsInt() + 1.0f));
	for (sInt i=0; i < 4; i++)
		gainc[i] = zt_powf(gaincdef[i], e);

	for (sInt i=0; i < 2; i++)
		gaina[i] = zt_powf(gainadef[i], e);

	damp = SRfclinfreq * ((float)paramsFloat[REVERB_PARAM_FLOAT_HI_CUT]->ValueAsInt() / 128.0f);
	gainin = (float)paramsFloat[PROC_PARAM_FLOAT_LEVEL]->ValueAsInt() / 128.0f;
	lowcutVal = SRfclinfreq * sqr(sqr(paramsFloat[REVERB_PARAM_FLOAT_LOW_CUT]->ValueAsInt() / 128.0f));
}

void Reverb::Reset()
{
	for (sInt ch=0; ch < 2; ch++)
	{
		// comb
		for (sInt i=0; i < 4; i++)
		{
			combd[ch][i].Reset();
			combl[ch][i] = 0.0f;
		}

		// allpass
		for (sInt i=0; i < 2; i++)
			alld[ch][i].Reset();

		// low cut
		hpf[ch] = 0.0f;
	}
}