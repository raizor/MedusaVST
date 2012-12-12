#pragma once

#include "../Constants.h"
#include "../Items/Item.h"
#include "Params/ParamFloat.h"
#include "Params/ParamInt.h"

class Voice;
class Adsr;
class SimpleFilter;
class ModulationMatrix;
class Patch;
class Osc;
class Distort;
class ChorusFlange;
class Boost;

class Patch
{
public:
	Item** items;
	Adsr* egAmp;
	Adsr* egPitch;
	Distort* distort;
	ChorusFlange* chorus;
	Boost* boost;
	int numItems;
	int number;
	int polyphony;
#ifndef REPLAYER
	char* name;
#endif

	ModulationMatrix* ModMatrix;

	ParamInt* FilterProcMode;

	// global feed effects
	ParamFloat* DelayAmount;
	ParamFloat* ReverbAmount;
	ParamFloat* BoostAmount;
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
