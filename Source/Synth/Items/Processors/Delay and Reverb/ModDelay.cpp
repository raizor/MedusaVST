#include "ModDelay.h"


ModDelay::ModDelay(int bufferLength) : ItemProcessor(kStackItemTypeModDelay, true)
{
	itemType = kStackItemTypeModDelay;

	AddFloatParam(new ParamFloat(0, true, 1.0f, 0.5f, kParamValueTypeZeroToOneBi, true)); // feedback 
	AddFloatParam(new ParamFloat(127, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni, true)); // delay left
	AddFloatParam(new ParamFloat(127, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni, true)); // delay right
	AddFloatParam(new ParamFloat(0, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni, true)); // rate
	AddFloatParam(new ParamFloat(0, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni, true)); // depth
	AddFloatParam(new ParamFloat(0, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni, true)); // phase

	db[0] = new float[bufferLength];
	db[1] = new float[bufferLength];
	//DelayBuffer = SampleBufferFloat_CreateInit(Constants_MixBufferSizeFloat);
	//dbufmask = DelayBuffer->Size-1;
	dbufmask = bufferLength-1;

	Reset();
}

void ModDelay::Reset()
{
	dbptr = 0;
	mcnt = 0;
	//SampleBufferFloat_Clear(DelayBuffer);

	/*
	zt_memset(db[0], 0, (dbufmask + 1) * sizeof(sF32));
	zt_memset(db[1], 0, (dbufmask + 1) * sizeof(sF32));
	*/
}

void ModDelay::Set()
{
	wetout = (paramsFloat[PROC_PARAM_FLOAT_LEVEL]->ValueAsInt() - 64.0f) / 64.0f;
	dryout = 1.0f - fabsf(wetout);
	fbval = (paramsFloat[MODDELAY_PARAM_FLOAT_FEEDBACK]->ValueAsInt() - 64.0f) / 64.0f;

	sF32 lenscale = ((sF32)dbufmask - 1023.0f) / 128.0f;
	dboffs[0] = FloatToInt(paramsFloat[MODDELAY_PARAM_FLOAT_DELAY_LENGTH_LEFT]->ValueAsInt() * lenscale);
	dboffs[1] = FloatToInt(paramsFloat[MODDELAY_PARAM_FLOAT_DELAY_LENGTH_RIGHT]->ValueAsInt() * lenscale);

	mfreq = FloatToInt(SRfclinfreq * fcmdlfomul * calcfreq(paramsFloat[MODDELAY_PARAM_FLOAT_MOD_RATE]->ValueAsInt() / 128.0f));
	mmaxoffs = FloatToInt(paramsFloat[MODDELAY_PARAM_FLOAT_MOD_DEPTH]->ValueAsInt() * 1023.0f / 128.0f);
	mphase = ftou32((paramsFloat[MODDELAY_PARAM_FLOAT_MOD_PHASE]->ValueAsInt() - 64.0f) / 128.0f);
}


void ModDelay::RenderBuffer(SampleBufferFloat* bufferIn, sInt nsamples)
{
	if (!wetout)
		return;

	sF32 dry = dryout;

	for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+nsamples; i++)
	{
		int idx = i%Constants_MixBufferSizeFloat;
		StereoSample samp;
		ProcessSample(&samp, bufferIn->Buffer[idx].l + fcdcoffset, bufferIn->Buffer[idx].r + fcdcoffset, dry);
		//processSample(&chanbuf[i], chanbuf[i].l + fcdcoffset, chanbuf[i].r + fcdcoffset, dry);
		bufferIn->Buffer[idx].l = samp.l;
		bufferIn->Buffer[idx].r = samp.r;
	}

	/*
	for (sInt i=0; i < nsamples; i++)
	{
		processSample(&chanbuf[i], chanbuf[i].l + fcdcoffset, chanbuf[i].r + fcdcoffset, dry);
	}*/
}

void ModDelay::RenderChan(StereoSample *chanbuf, sInt nsamples)
{
	if (!wetout)
		return;

	//COVER("MODDEL chan");

	sF32 dry = dryout;
	for (sInt i=0; i < nsamples; i++)
	{
		ProcessSample(&chanbuf[i], chanbuf[i].l + fcdcoffset, chanbuf[i].r + fcdcoffset, dry);
	}
}

inline sF32 ModDelay::ProcessChanSample(sF32 in, sInt ch, sF32 dry)
{
	// modulation is a triangle wave
	sU32 counter = mcnt + (ch ? mphase : 0);
	counter = (counter < 0x80000000u) ? counter*2 : 0xffffffffu - counter*2;

	// determine effective offset
	sU64 offs32_32 = (sU64)counter * mmaxoffs; // 32.32 fixed point
	sU32 offs_int = sU32(offs32_32 >> 32) + dboffs[ch];
	sU32 index = dbptr - offs_int;

	// linear interpolation using low-order bits of offs32_32.
	sF32 *delaybuf = db[ch];
	sF32 x = utof23((sU32)(offs32_32 & 0xffffffffu));
	sF32 delayed = lerp(delaybuf[(index - 0) & dbufmask], delaybuf[(index - 1) & dbufmask], x);

	// mix and output
	delaybuf[dbptr] = in + delayed*fbval;
	return delayed;
	//return in*dry + delayed*wetout;
}

inline void ModDelay::ProcessSample(StereoSample *out, sF32 l, sF32 r, sF32 dry)
{
	out->l = ProcessChanSample(l, 0, dry);
	out->r = ProcessChanSample(r, 1, dry);

	// tick
	mcnt += mfreq;
	dbptr = (dbptr + 1) & dbufmask;
}

ModDelay::~ModDelay(void)
{
}
