#include "Lfo.h"
#include "../../Utils/Voice.h"
#include "../../Utils/WaveTableGen.h"

Lfo::Lfo(StackItemType lfoType) : ItemProcessor(lfoType, true)
{
	// TODO: INIT
	AddIntParam(new ParamInt(kWaveFormSin)); // waveform type
	AddIntParam(new ParamInt(kPolarityPositive)); // polarity
	AddIntParam(new ParamInt(kLfoSyncNone)); // sync

	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni, true, 20.0f)); // rate 
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeTime, true, 20.0f)); // delay time

#ifndef REPLAYER
	paramsFloat[PROC_PARAM_FLOAT_LEVEL]->SetValueWithInt(0);
#endif
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
			buffer[voice->Number]->Buffer[idx].ch[j] = v*depth*level;				
		}
	}
}

void Lfo::WaveChanged()
{
	WaveTable* table;
	int wf = paramsInt[LFO_PARAM_INT_WAVEFORM]->Value();
	table = WaveTable::Wavetables[wf];
	waveTableIdx->SetWaveTable(table);
}
