#include "Patch.h"
#include "Voice.h"
#include "../Items/Processors/Osc.h"
#include "../Items/Processors/Adsr.h"
#include "../Items/Processors/SimpleFilter.h"
#include "../Items/Processors/Lfo.h"
#include "../Items/Processors/Distort.h"
#include "../Items/Processors/Boost.h"
#include "../Items/Processors/ChorusFlange.h"
#include "Params/Modulation/ModulationMatrix.h"

#ifndef REPLAYER
	#include <stdio.h>
#endif

PatchList* PatchList::list = 0;

Patch::Patch(int number)
{
	this->number = number;
	numItems = 0;
	polyphony = 1;
	items = new Item*[100]; // 100 items per patch atm - probably waaaaay too many

	ModMatrix = new ModulationMatrix(this);

	DelayAmount = new ParamFloat(0, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni);
	ReverbAmount = new ParamFloat(0, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni);		
	BoostAmount = new ParamFloat(0, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni);
	ChanVolAmount = new ParamFloat(127.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni);
	FilterProcMode = new ParamInt(kFilterModeParallel);

#ifndef REPLAYER
	name = new char[100];
	sprintf(name, "UNNAMED");
#endif 

	polyphony = 4;

	// OSCS
	for(int i=0; i<Constants_NumOscillators; i++)
	{
		Osc* osc = new Osc();
		osc->enabled = i == 0;

		/*
		Osc* prev = i > 0 ? &patch->Oscs[i-1] : &patch->Oscs[Constants_NumOscillators-1];
		Osc* next = i < Constants_NumOscillators - 1 ? &patch->Oscs[i+1] : &patch->Oscs[0];
		patch->Oscs[i].OscPrevious = prev; 
		patch->Oscs[i].OscNext = next;*/

		items[numItems++] = osc;
	}

	// EGs
	egAmp = new Adsr(kStackItemTypeAmpEg);
	egAmp->enabled  = true; // no needed
	egAmp->paramsFloat[PROC_PARAM_FLOAT_LEVEL]->SetValueWithInt(127);

	egPitch = new Adsr(kStackItemTypePitchEg);
	egPitch->enabled  = false; // no needed

	for(int i=0; i<Constants_NumEnvelopes; i++)
	{
		Adsr* adsr = new Adsr(kStackItemTypeEnvAdsr);
		adsr->enabled = false;
		items[numItems++] = adsr;
	}

	// amp and pitch follow other egs
	//items[numItems++] = egAmp;
	//items[numItems++] = egPitch;

	// filters
	//Filters = (Filter*)zynth_mallocAlloc(sizeof(V2Filter)*Constants_NumFilters);
	for(int i=0; i<Constants_NumFilters; i++)
	{
		SimpleFilter* filter = new SimpleFilter();
		items[numItems++] = filter;
		filter->number = i;
		//patch->Filters[i]._item = StackItem_Create(FILTER_NUM_PARAMS);
		//FILTER_INIT(&patch->Filters[i], i, patch);
	}	

	for(int i=0; i<Constants_NumLfoAllVoices; i++)
	{
		Lfo* lfo = new Lfo(kStackItemTypeLfoAllVoices);
		items[numItems++] = lfo;
		lfo->number = i;
		//patch->Filters[i]._item = StackItem_Create(FILTER_NUM_PARAMS);
		//FILTER_INIT(&patch->Filters[i], i, patch);
	}	

	for(int i=0; i<Constants_NumLfoPerVoice; i++)
	{
		Lfo* lfo = new Lfo(kStackItemTypeLfoPerVoice);
		items[numItems++] = lfo;
		lfo->number = i;
		//patch->Filters[i]._item = StackItem_Create(FILTER_NUM_PARAMS);
		//FILTER_INIT(&patch->Filters[i], i, patch);
	}	

	// distortion
	distort = new Distort();
	boost = new Boost();
	chorus = new ChorusFlange();
}

Patch::~Patch(void)
{
}

void Patch::Generate(Voice* voice, int numSamples)
{
	if (voice->State == kVoiceStateOff) return;

	if (ModMatrix->Changed)
	{
		// modulation matrix has changed, updated linked matrix params
		ModMatrix->HandleChanges();
	}

	for(int i=0; i<numItems; i++)
	{
		Item* item = items[i];
		if (item->enabled)
		{
			item->Process(voice->Buffer, voice->Buffer, voice, numSamples);	
		}
	}

	if (egAmp->enabled)
	{
		// EGs output to voice temp buffer
		egAmp->Process(voice->Buffer, voice->Buffer, voice, numSamples);
	}

}

void Patch::Start( Voice* voice)
{
}


void Patch::ResetForVoice(Voice* voice)
{
	/*
	for(int i=0; i<Constants_NumLfoAllVoices; i++)
	{
		if (&patch->LfosAv[i] != 0)
		{
			StackItem_Reset(patch->LfosAv[i]._item, voice);
		}	
	}
	*/
	//TODO
	/*
	// per voice
	for(int i=0; i<Constants_NumLfoPerVoice; i++)
	{
		if (&patch->LfosPv[i] != 0 && &patch->LfosPv[i]._item->Enabled)
		{
			StackItem_Reset(patch->LfosPv[i]._item, voice);
		}	
	}

	for(int i=0; i<Constants_NumOscillators; i++)
	{
		if (&patch->Oscs[i] != 0)
		{
			OscMode mode = (OscMode)IntStackItemParam_Value(patch->Oscs[i].Mode);
			if (mode == OscModeFixedSync || mode == OscModeNormalSync || mode == OscModInvertedSync)
			{
				// reset wavetable index if oscillator mode is sync, otherwise it's free running
				// monophonic items should never have a sync mode (in theory)
				if (patch->Oscs[i]._item->HasWaveTable)
				{
					StackItem_Reset(patch->Oscs[i]._item, voice);
				}				
			}			
		}	
	}

	for(int i=0; i<Constants_NumFilters; i++)
	{
		//patch->Filters[i].
	}	

	StackItem_Reset(patch->EnvAmp->_item, voice);
	StackItem_Reset(patch->EnvPitch->_item, voice);
	*/
	for(int i=0; i<Constants_NumEnvelopes; i++)
	{
		//patch->EnvAdsr[i]._item = StackItem_Create(ENV_ADSR_NUM_PARAMS);
	}
	/*
	patch->EnvPitch->Stage[voice->Number] = StageNone;
	patch->EnvPitch->Value[voice->Number] = 0;
	patch->EnvPitch->StageAmount[voice->Number] = 0;*/

}


PatchList::PatchList()
{
	patches = new Patch*[Constants_MaxPatches];
	zt_memset(&currentPatchNumOnChannel[0], 0, Constants_NumMidiChannels * sizeof(int));
	for(int i=0; i<Constants_MaxPatches; i++)
	{
		patches[i] = new Patch(i);
	}
}

PatchList::~PatchList()
{
}