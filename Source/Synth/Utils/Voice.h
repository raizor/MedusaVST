#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "../Constants.h"
#include "../Utils/ZynthTools.h"
#include "../Utils/PitchUtils.h"
#include "SampleBufferFloat.h"

class Patch;

class Voice
{
public:
	enum VoiceState State;
	Patch* CurrentPatch;
	float FrequencyPrevious;
	float Frequency;
	int NoteIdPrevious;
	int NoteId;
	int ChannelId;
	int PatchNumberPrevious;
	int PatchNumber;
	double Time;
	//double OffTime;
	double ApproxVolume;
	int Number;
	int StopPos;
	
	bool PitchBending;
	float TargetFrequency;
	float PitchBendAmount;
	
	SampleBufferFloat* Buffer;
	SampleBufferFloat* BufferTemp;
	SampleBufferFloat* PitchBendBuffer;

	Voice(int number);
	void Voice::Generate(long numSamples);
	void Voice::Start(int noteId, int channel, Patch* patch, long onTime);
	void Voice::Stop();
	void Voice::PitchBend(int noteId);
	void Voice::StopDead();

};


#ifdef __cplusplus
}
#endif
