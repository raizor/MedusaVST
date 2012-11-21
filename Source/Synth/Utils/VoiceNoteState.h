#pragma once
#include "Voice.h"

class VoiceNoteState 
{
public: 
	Voice* VoiceInfo;
	enum NoteState NoteInfo;
	long NoteOnTimeId;
	
	VoiceNoteState();
};