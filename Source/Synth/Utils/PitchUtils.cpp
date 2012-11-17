#include "PitchUtils.h"
#include "ZynthTools.h"

//float PitchUtils_NoteToFrequencyTable[128];

PitchUtils* PitchUtils::instance = 0;

PitchUtils::PitchUtils()
{
	//PitchUtils_NoteToFrequencyTable = (float*)zynth_mallocAlloc(sizeof(float)*(PitchUtils_NoteIDMaxValue + 1));

	// The number of notes per octave.
	int notesPerOctave = 12;            

	// Reference frequency used for calculations.
	float referenceFrequency = 440;

	// The note ID of the reference frequency.
	int referenceNoteID = 69;

	float exponent;

	float notes1[128];
	float notes2[128];

	// Fill table with the frequencies of all MIDI notes.
	for(int i = 0; i < PitchUtils_NoteIDMaxValue + 1; i++)
	{
		exponent = (float)(i - referenceNoteID) / notesPerOctave;
		notes1[i] = exponent;

		//float powa = pow(2, exponent);
		float powa = PowerOfTwoTable::instance->GetPower(exponent);
		float v = (float)(PowerOfTwoTable::instance->GetPower(exponent) * referenceFrequency);
		NoteToFrequencyTable[i] = v;
		float vv = PowerOfTwoTable::instance->GetPower(exponent);
		notes2[i] = PowerOfTwoTable::instance->GetPower(exponent) * referenceFrequency;		
	}
}

float PitchUtils::MidiNoteToFrequency(int noteID)
{
	if (noteID < PitchUtils_NoteIDMinValue || noteID > PitchUtils_NoteIDMaxValue)
	{
		//throw new ArgumentOutOfRangeException("Note ID out of range.");
		int xx =1;
	}

	float f = NoteToFrequencyTable[noteID];

	return f;
}

int PitchUtils::FrequencyToMidiNote(float frequency)
{
	return 0;
}

float PitchUtils::FrequencyNoteDifference(int note1, int note2)
{
	return 0;
}