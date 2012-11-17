#pragma once

#include "../Constants.h"
#include "../Items/Item.h"
#include "Params/ParamFloat.h"

class Voice;
class ModulationMatrix;

class Patch
{
public:
	Item** items;
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
	static PatchList* list;

	PatchList();
	~PatchList();
};

extern Patch* CurrentPatch;
PatchList* PatchList_Create();
void PatchList_Changed();
