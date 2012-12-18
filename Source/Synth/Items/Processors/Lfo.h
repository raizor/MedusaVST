#pragma once

#include "../ItemProcessor.h"

// float params
#define LFO_PARAM_FLOAT_RATE          1
#define LFO_PARAM_FLOAT_DELAY         2

// int params
#define LFO_PARAM_INT_WAVEFORM      0
#define LFO_PARAM_INT_POLARITY      1
#define LFO_PARAM_INT_SYNC          2

enum NoteType 
{ 
	kNoteTypeRegular = 0, 
	kNoteTypeTriplet, 
	kNoteTypeDotted, 
	kNoteTypeItemCount
}; 

enum NoteDivision 
{ 
	kNoteDivisioneWhole = 0, 
	kNoteDivisioneHalf, 
	kNoteDivisionQuarter, 
	kNoteDivisionEighth, 
	kNoteDivisionSixteenth, 
	kNoteDivisionThirtysecond, 
	kNoteDivisionSixtyfourth, 
	kNoteDivisionItemCount
}; 

enum LfoSync
{
	kLfoSyncNone = 0,
	kLfoSync16,
	kLfoSync8,
	kLfoSync4,
	kLfoSync2,
	kLfoSync1,
	kLfoSync1_2, // 1/2
	kLfoSync1_4, // 1/4
	kLfoSync1_8, // 1/8
	kLfoSyncItemCount,

};

class Voice;
class Lfo : public ItemProcessor
{
public:
	Lfo(StackItemType lfoType);
	~Lfo(void);
	virtual void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
	void Lfo::WaveChanged();
};

