#pragma once

#include "PowerOfTwoTable.h"
	
#define PitchUtils_NoteIDMinValue 0
#define PitchUtils_NoteIDMaxValue 127
	
class PitchUtils
{
public:
	static PitchUtils* instance;
	PitchUtils();	
	~PitchUtils();	
	float NoteToFrequencyTable[128];	
	float MidiNoteToFrequency(int noteID);
	int FrequencyToMidiNote(float frequency);
	float FrequencyNoteDifference(int note1, int note2);
};