#pragma once

#include "../Constants.h"
#include "../Items/Item.h"
#include "Params/ParamFloat.h"

class Voice;
class Adsr;
class ModulationMatrix;

class Patch
{
public:
	Item** items;
	Adsr* egAmp;
	Adsr* egPitch;
	int numItems;
	int number;
	int polyphony;

	ModulationMatrix* ModMatrix;

	// global feed effects
	ParamFloat* DelayAmount;
	ParamFloat* ReverbAmount;
	ParamFloat* ChanVolAmount;

	Patch(int patchNum);
	~Patch(void);

	void Start(Voice* voice);
	void Generate(Voice* voice, int numSamples);
	void ResetForVoice(Voice* voice);
};

class PatchList
{
public:
	Patch** patches;
	Patch* CurrentPatch;
	int count;
	int currentPatchNumOnChannel[Constants_NumMidiChannels];
	static PatchList* list;


	PatchList();
	~PatchList();
};

extern Patch* CurrentPatch;
PatchList* PatchList_Create();
void PatchList_Changed();
