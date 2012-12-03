#include "Osc.h"
#include "../../Utils/Voice.h"
#include "../../Utils/WaveTableGen.h"

Osc::Osc(void) : ItemProcessor(kStackItemTypeWfOsc, true)
{
	AddIntParam(new ParamInt(kWaveFormSin)); // waveform type	
	AddFloatParam(new ParamFloat(0.0f, true, 1, 0.5f, kParamValueTypeIntBi)); // detune octaves
	AddFloatParam(new ParamFloat(0, true, 1, 0.5f, kParamValueTypeIntBi)); // detune semitones
	AddFloatParam(new ParamFloat(50, true, 1, 0.5f, kParamValueTypeCents)); // detune finetune
	AddFloatParam(new ParamFloat(0, true, 1, 0.5f, kParamValueTypeZeroToOneUni)); // phase
	AddFloatParam(new ParamFloat(0, true, 1, 0.5f, kParamValueTypeZeroToOneUni)); // color
	AddFloatParam(new ParamFloat(0, true, 1, 0.5f, kParamValueTypeZeroToOneUni)); // pitch modifier

	AddBoolParam(new ParamBool(false)); // ring mod
	AddBoolParam(new ParamBool(false)); // is slave
	AddBoolParam(new ParamBool(false)); // portamento

	AddIntParam(new ParamInt(kPolarityPositive)); // polarity type
	AddIntParam(new ParamInt(kOscModeNormalSync)); // mode
	AddIntParam(new ParamInt(kOscModModeAdd)); // modulation mode

	for(int i=0; i<Constants_Polyphony; i++)
	{
		SyncPositions[i] = new int[100];
		zt_memset(SyncPositions[i], 0, sizeof(int)*100);
		SyncPositionsCount[i] = 0;
	}
	
#ifndef REPLAYER
	paramsFloat[PROC_PARAM_FLOAT_LEVEL]->SetValueWithInt(64);
#endif
}

Osc::~Osc(void)
{
}

float Osc::GetFrequency(Voice* voice, int bufferIndex, bool haveFreqMod)
{
	//float freq = voice->Frequency;
	float freq = voice->PitchBending ? voice->PitchBendBuffer->Buffer[bufferIndex].ch[0] : voice->Frequency;
	float dtOct = paramsFloat[OSC_PARAM_FLOAT_DETUNE_OCT]->Value();

	//dtOct-=4;

	float dtSemi = paramsFloat[OSC_PARAM_FLOAT_DETUNE_SEMI]->Value();
	float dtFine = paramsFloat[OSC_PARAM_FLOAT_DETUNE_FINE]->Value();

	float v  = PowerOfTwoTable::instance->GetPower(2.0f);
	//int xx = 1;


	paramsFloat[OSC_PARAM_FLOAT_PITCH_MOD]->Value();

	// float mv = FloatStackItemParam_ModValue(osc->PitchModifier, voice, bufferIndex);
	float mv = 0;//FloatStackItemParam_ModValue(osc->PitchModifier, voice, bufferIndex);

	if (haveFreqMod)
	{
		//dtSemi += mv * 100.0f;	
	}	

	// detune freq
	// octaves
	if (dtOct != 0)
	{
		float amt = PowerOfTwoTable::instance->GetPower(fabsf(dtOct));
		if (dtOct < 0)
		{
			// octave down
			freq /= amt;
		}
		else
		{
			// octave up
			freq *= amt;
		}
	}
		
	// semitones
	if (dtSemi != 0)
	{
		float val = fabsf(dtSemi) / 12.0f;
		float amt = PowerOfTwoTable::instance->GetPower(val);
		if (dtSemi < 0)
		{
			// semitone up
			freq /= amt;
		}
		else
		{
			// semitone down
			freq *= amt;
		}
	}

	// cents- todo: bug here when going to/from 0
	if (dtFine != 0)
	{
		float val = 1.0f / (12.0f * (dtFine * 10.0f));
		//if (!float.IsInfinity(val))
		//{
			float amt = PowerOfTwoTable::instance->GetPower(val);
			if (dtFine < 0)
			{
				// semitone up
				freq /= amt;
			}
			else
			{
				// semitone down
				freq *= amt;
			}
		//}
			if (freq < 50 || freq > 1000)
			{
				float amt = PowerOfTwoTable::instance->GetPower(val);
				int xx =1;
			}
	}
	float moddedFreq = freq;

	///float moddedFreq = freq + (freq * modVal);
		
	//osc->inc += 0.1f;

	float nq = (float)Constants_Nyquist;

	//moddedFreq = moddedFreq * mv;

	// handle freq mod
	//osc->PitchModifier->ModulatedValue(&moddedFreq, bufferIndex);

	// get eg mods
	/*
	for(int i=0; i<osc->PitchModifier->ModList->Count; i++)
	{
		Modulator* mod = &osc->PitchModifier->ModList->Modulators[i];
		if (mod->Curve == ModulationCurveMultUnipolarPlus)
		{
			//eg?
			float modder = osc->PitchModifier->ModList->Modulators[i].ModBuffer->Buffer[0][bufferIndex];
			moddedFreq = moddedFreq * modder;
		}
	}*/

	if (moddedFreq > nq*0.75f)
	{
		moddedFreq = nq*0.75f;
	}
			
	return moddedFreq;
}

void Osc::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{
	bool haveFreqMod = paramsFloat[OSC_PARAM_FLOAT_PITCH_MOD]->ModList->Count > 0;
	bool haveAmpMod = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->ModList->Count > 0;

	//float freq = voice.Frequency;


	//localTime = voice.Time;

	// Max amplitude for 16-bit audio
	//int amplitude = (int)(Constants.ClipLimit * _volume.Value);
		
	// todo
	//float vol = paramsFloat[OSC_PARAM_VOLUME]->GetModdedValue(voice, );
	//float vol = Constants::instance->MasterVolume * ParamFloat[OSC_PARAM_VOLUME].Value();

	//float v1[50];
	//float v2[50];
	int ix = 0;
	float moddedFreq = 0;
	// Fill the data array with sample data

	int syncCheckIndex = 0;

	/* TODO
	OscMode prevOscMode = (OscMode)OscPrevious->paramsInt[OSC_PARAM_MODE]->Value();
	OscModMode prevOscModMode = (OscModMode)OscPrevious->paramsInt[OSC_PARAM_MOD_MODE]->Value();
	bool ringMod = prevOscModMode == kOscModModeRing;
	bool invert = prevOscMode == kOscModeInvertedFree  || prevOscMode == kOscModInvertedSync; 
	bool fm = prevOscModMode == kOscModModeFM;
	*/

	bool ringMod = false;
	bool invert = false;
	bool fm = false;

	SyncPositionsCount[voice->Number] = 0;
	
	for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
	{
		int idx = i%Constants_MixBufferSizeFloat;
		// todo
		float volume = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->GetModdedValue(voice, i);
		float f = GetFrequency(voice, idx, haveFreqMod);
		bool syncHit = false;

		/* // TODO
		// check sync point hit if prev osc mode is sync
		if (prevOscMode ==  kOscModeNormalSync && syncCheckIndex < OscPrevious->SyncPositionsCount[voice->Number] && i>=OscPrevious->SyncPositions[voice->Number][syncCheckIndex])
		{
			// hit sync point of previous osc, reset wavetable idx
			WaveTableIdx->Reset(voice);
 			syncCheckIndex++;
		}
		*/

		if (fm)
		{
			f = f + (OscPrevious->buffer->Buffer[idx].ch[0] * 10000);
		}
		
		float v = waveTableIdx->Sample(voice, f, &syncHit);

		if (invert)
		{
			v = -v;
		}

		if (syncHit)
		{
			SyncPositions[voice->Number][SyncPositionsCount[voice->Number]++] = i;
		}

		if (haveAmpMod)
		{
			volume *= paramsFloat[PROC_PARAM_FLOAT_LEVEL]->GetModValue(voice, idx);
		}	

		//if (ix < 50)
		//{
		//	v1[ix] = v;
		//}
		for (int j = 0; j < Constants_NumAudioChannels; j++)
		{
			//if (BoolStackItemParam_Value(osc->RingMod))
			//{
			//	float vo = bufferOut->Buffer[j][idx];
			//	float vn = vo*v;
			//	bufferOut->Buffer[j][idx] *= vn/2;
			//}else
			//{

			float val = v;

			// write val to temp buffer
			buffer->Buffer[idx].ch[j] = val;
			// write val to output buffer
			if (ringMod)
			{
				bufferOut->Buffer[idx].ch[j] *= val * volume;
			}else{
				bufferOut->Buffer[idx].ch[j] += val * volume;
			}
			
			
			//}
		}
		//if (ix < 50)
		//{
		//	v2[ix++] = bufferOut->Buffer[0][idx];
		//}		
	}
	//Oscillator_PostProcess(osc, bufferOut, bufferOut, voice, numSamples);
}

void Osc::WaveChanged()
{
	WaveTable* table;
	int wf = paramsInt[OSC_PARAM_INT_WAVEFORM]->Value();
	table = WaveTable::Wavetables[wf];
	waveTableIdx->SetWaveTable(table);
}
