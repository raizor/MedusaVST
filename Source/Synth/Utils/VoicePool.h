#pragma once

#include "VoiceNoteState.h"
#include "../Constants.h"
#include "../Items/Item.h"
#include "Patch.h"
/*
#include "../Patches/StackItems/Delay/ModDelay.h"
#include "../Patches/StackItems/Reverb/Reverb.h"
#include "../Patches/StackItems/Boost/Boost.h"
#include "../Patches/StackItems/Distort/Distortion.h"
*/
#include <dsound.h>

//struct V2ModDel;

class VoicePool  
{
public:
	Item* GlobalDelay;
	Item* GlobalReverb;
	Voice *Voices[Constants_Polyphony]; 
	Voice *LastVoice;
	long Counter;
	float voiceDelayAmounts[Constants_Polyphony];

	static VoicePool* Pool;

	VoiceNoteState* NoteStates[Constants_NumMidiChannels][Constants_NoteCount]; 
	CRITICAL_SECTION cs;

	SampleBufferFloat* BufferChannels; // all channels are mixed here one by one
	SampleBufferFloat* BufferDelay; // delay, reverb routed here for processing
	SampleBufferFloat* BufferReverb; // delay, reverb routed here for processing
	SampleBufferFloat* BufferAuxA; 
	SampleBufferFloat* BufferAuxB;
		
	VoicePool();
	~VoicePool();
	void Init();
	void Stop(int channel, int noteId);
	void StopAllVoices();
	bool NotePlaying(int channel, int note);
	void MixVoicesToBuffer(SampleBufferFloat* bufferOut, int numSamples);
	Voice* GetVoiceAndPlayNote(int channel, int noteId, Patch* patch);
};	
