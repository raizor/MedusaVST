#include "Voice.h"
#include "VoicePool.h"
#include "Patch.h"

Voice::Voice(int number)
{
	StopPos = Constants_MixBufferSizeFloat;
	State = kVoiceStateOff;
	FrequencyPrevious = -1;
	Frequency = 0;
	NoteIdPrevious = 0;
	NoteId = 0;
	CurrentPatch = 0;
	ChannelId = 0;
	PatchNumberPrevious = -1;
	PatchNumber = 0;
	Time = 0;
	PitchBendAmount = 0;
	//OffTime = 0;
	ApproxVolume = 0;
	Number = number;
	PitchBending = false;
	Buffer = new SampleBufferFloat(Constants_MixBufferSizeFloat);
	BufferTemp = new SampleBufferFloat(Constants_MixBufferSizeFloat);
	PitchBendBuffer = new SampleBufferFloat(Constants_MixBufferSizeFloat);
}

void Voice::Start(int noteId, int channel, Patch* patch, long onTime)
{
	StopPos = Constants_MixBufferSizeFloat;
	NoteIdPrevious = 0; // clear previous note id, we won't need to pitch bend back to it
	PatchNumberPrevious = PatchNumber;
	FrequencyPrevious = 0; // clear previous frequency, we won't need to pitch bend back to it
	PatchNumber = patch->number;
	CurrentPatch = patch;
	ChannelId = channel;
	NoteId = noteId;
	Frequency = PitchUtils::instance->MidiNoteToFrequency(noteId);
	TargetFrequency = Frequency;
	Time = 0;
	//OffTime = 0;
	State = kVoiceStateOn;
	CurrentPatch->Start(this);
}

void Voice::PitchBend(int noteId)
{	
	TargetFrequency = PitchUtils::instance->MidiNoteToFrequency(noteId);
	NoteId = noteId;
	//voice->PitchBendAmount = 0;
	//voice->PitchBending = true;
}

void Voice::Generate(long numSamples)
{
	// TODO TODO: Note off is turning off previous voice?!?!
	Buffer->ClearRange(numSamples); // clear voice buffer
	float freq = Frequency;
	PitchBendBuffer->ClearRange(numSamples);
	float amt = 1.00001f;	
	
	for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
	{
		int idx = i % Constants_MixBufferSizeFloat;

		if (TargetFrequency != freq)
		{
			if (freq < TargetFrequency)
			{		
				if (freq*amt <= TargetFrequency)
				{
					freq*=amt;
				}else{
					freq = TargetFrequency;
					Frequency = TargetFrequency;
				}		
			}else{
				if (freq/amt >= TargetFrequency)
				{
					freq/=amt;
				}else{
					freq = TargetFrequency;
					Frequency = TargetFrequency;
				}	
			}
		}
		PitchBendBuffer->Buffer[idx].ch[0] = freq;
	}

	Frequency = freq;
	
	CurrentPatch->Generate(this, numSamples);
	//ApproxVolume = Buffer->Buffer[0][Buffer->Size/2];
	//Time += Constants.TimeIncrement*Buffer.Size;
	for(int i=0; i<numSamples; i++)
	{
		Time += Constants_TimeIncrement;
	}
}

// stop the voice dead and reset the patch
void Voice::Stop()
{
	printf("* STOP VOICE %d", Number);
	State = kVoiceStateOff;
	//voice->CurrentPatch->
}

void Voice::StopDead()
{
	printf("* STOP DEAD VOICE %d", Number);
	// set state
	State = kVoiceStateOff;
	StopPos = 0;
	
	// clear any associated wavetable indexes
	CurrentPatch->ResetForVoice(this);	
}



