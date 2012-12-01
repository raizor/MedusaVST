#include "Lfo.h"
#include "../../Utils/Voice.h"
#include "../../Utils/WaveTableGen.h"

Lfo::Lfo(StackItemType lfoType) : ItemProcessor(lfoType, true)
{
	// TODO: INIT
	AddIntParam(new ParamInt(kWaveFormSin)); // waveform type
	AddIntParam(new ParamInt(kPolarityPositive)); // polarity

	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // rate 
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // delay time
}


Lfo::~Lfo(void)
{
}

void Lfo::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{
	for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
	{
		//float frequency = FloatStackutItemParam_ModdedValue(lfo->Frequency, voice, i);
		float depth = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->Value();
		float rate = paramsFloat[LFO_PARAM_FLOAT_RATE]->Value();		

		// todo
		bool syncHit = false;
		int idx = i%Constants_MixBufferSizeFloat;
		float level = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->GetModdedValue(voice, i);
		float v = waveTableIdx->Sample(voice, rate, &syncHit);		

		float depthMod = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->GetModdedValue(voice, i);
		float rateMod = paramsFloat[LFO_PARAM_FLOAT_RATE]->GetModdedValue(voice, i);

		for (int j = 0; j < Constants_NumAudioChannels; j++)
		{
			bufferOut->Buffer[idx].ch[j] = v*depth*level;				
		}
	}
}
