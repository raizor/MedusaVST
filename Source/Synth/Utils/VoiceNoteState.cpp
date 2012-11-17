#include "VoiceNoteState.h"

VoiceNoteState::VoiceNoteState(Voice* voice)
{
	VoiceInfo = voice;
	NoteInfo = kNoteStateOff;	
	NoteOnTimeId = 0;
}
