#include "VoicePool.h"
//#include "../Items/StackItems/Envelopes/EnvelopeAdsr.h"
#include "ZynthTools.h"

VoicePool* VoicePool::Pool = 0;

VoicePool::VoicePool()
{
	LastVoice = 0;
	Counter = 0;
		
	for (int i = 0; i < Constants_Polyphony; i++)
	{		
		Voices[i] = new Voice(i);
		voiceDelayAmounts[i] = 0;
	}

	for(int channel=0; channel<Constants_NumMidiChannels; channel++)
	{
		for(int note=0; note<Constants_NoteCount; note++)
		{
			NoteStates[channel][note] = new VoiceNoteState();
		}		
	}
	InitializeCriticalSection(&cs);

	// aux buffers
	BufferAuxA = new SampleBufferFloat(Constants_MixBufferSizeFloat);
	BufferAuxB = new SampleBufferFloat(Constants_MixBufferSizeFloat);

	// delay and reverb buffers
	BufferDelay = new SampleBufferFloat(Constants_MixBufferSizeFloat);
	BufferReverb = new SampleBufferFloat(Constants_MixBufferSizeFloat);

	// create channel buffer
	BufferChannels = new SampleBufferFloat(Constants_MixBufferSizeFloat);

	// init delay
	GlobalDelay = new ModDelay(32768);
	GlobalDelay->Set();

	// init reverb
	GlobalReverb = new Reverb();
	GlobalReverb->Set();
	
}

bool VoicePool::NotePlaying(int channel, int note)
{
	return Pool->NoteStates[channel][note]->NoteInfo == kNoteStateOn;
}

void VoicePool::Stop(int channel, int noteId)
{
	printf("NOTE OFF: chan %d, note %d\n", channel, noteId);
	if (noteId == 76)
	{
		DebugPrintLine("");
		DebugPrintLine("");
		DebugPrintLine("");
		DebugPrintLine("");

	}
	EnterCriticalSection(&Pool->cs);
	if (NoteStates[channel][noteId]->NoteInfo == kNoteStateOn)
	{
		if (NoteStates[channel][noteId]->VoiceInfo->CurrentPatch->polyphony < 2)
		{
			int lastNoteTime = -1;
			int lastNoteId = 0;
			Voice* lastVoice;
			// mono-phonic, change note to last keyed note with note-on
			for(int note=0; note<Constants_NoteCount; note++)
			{
				if (NoteStates[channel][note]->NoteInfo == kNoteStateOn)
				{
					if (Pool->NoteStates[channel][note]->NoteOnTimeId > lastNoteTime)
					{
						lastNoteTime = NoteStates[channel][note]->NoteOnTimeId;
						lastVoice = NoteStates[channel][note]->VoiceInfo;
						lastNoteId = note;
					}
				}
			}	
			if (lastNoteId > 0 && lastNoteId != noteId)
			{
				// bend the note back to last note
				NoteStates[channel][lastNoteId]->NoteOnTimeId = Pool->Counter++;
				lastVoice->PitchBend(lastNoteId);
			}else{
				goto VoiceOff;
			}
		}else{
			VoiceOff:
			NoteStates[channel][noteId]->NoteInfo = kNoteStateOff;			
			NoteStates[channel][noteId]->VoiceInfo->State =  kVoiceStateStopping;
			printf("Stopping voice %d\n", NoteStates[channel][noteId]->VoiceInfo->Number);
		}
	}
	LeaveCriticalSection(&Pool->cs);
}

void VoicePool::StopAllVoices()
{
	printf("NOTE OFF ALL\n");
	// stop voices
	for (int i = 0; i < Constants_Polyphony; i++)
	{
		Voice* voice = Pool->Voices[i];
		voice->State = kVoiceStateOff;
	}
	// set notestates for channels to off
	for(int channel=0; channel<Constants_NumMidiChannels; channel++)
	{
		for(int noteId=0; noteId<Constants_NoteCount; noteId++)
		{
			Pool->NoteStates[channel][noteId]->NoteInfo = kNoteStateOff;
		}
	}
}

/*

TODO: allow user to set processing order of FX per patch
this is needed as delay/reverb reduce output of channel buffer
depending on delay/reverb amount. The lower channel buffer volume
after processing affects the strength of the following delay/reverb effect.

TODO: OPT: do not process channels that are not in use!

*/

void VoicePool::MixVoicesToBuffer(SampleBufferFloat* bufferOut, int numSamples)
{
	bool delayBeforeReverb = true;

	// clear aux buffers	
	BufferAuxA->ClearRange(numSamples);
	BufferAuxB->ClearRange(numSamples);
	BufferDelay->ClearRange(numSamples);
	BufferReverb->ClearRange(numSamples);

	for(int chan=0; chan<Constants_NumMidiChannels; chan++)
	{
		// TODO
		Patch* patch = PatchList::list->patches[PatchList::list->currentPatchNumOnChannel[chan]];

		// clear channel buffer
		BufferChannels->ClearRange(numSamples);
		// loop through voices looking for ones on current channel
		for(int voiceNum=0; voiceNum<Constants_Polyphony; voiceNum++)
		{
			Voice* voice = Voices[voiceNum];		
			if (voice->State != kVoiceStateOff && voice->ChannelId == chan)
			{
				// voice is on this channel, mix in to channel buffer
				// TODO
				//SampleBufferFloat* ampBuffer = patch->EnvAmp->TempBuffer;
				VoicePool::Pool->BufferChannels->MixIn(voice->Buffer, 0, numSamples);
				//VoicePool_Pool->BufferChannels->MixIn(voice->Buffer, ampBuffer, numSamples);
			}
		}

		// process boost for this channel
		//Boost_Process(patch->Boost, VoicePool_Pool->BufferChannels, VoicePool_Pool->BufferChannels, numSamples);

		// pre process delay and reverb for this channel		
		for(int fx = 0; fx < 2; fx++)
		{
			// todo: fx order
			bool processDelay = fx == 0;
			SampleBufferFloat* fxBuffer = processDelay ? BufferDelay : BufferReverb;
			// TODO
			float delayAmount = 0;//FloatStackItemParam_Value(patch->DelayAmount) * FloatStackItemParam_Value(VoicePool_Pool->GlobalDelay->Amount);
			float reverbAmount = 0;//FloatStackItemParam_Value(patch->ReverbAmount) * FloatStackItemParam_Value(VoicePool_Pool->GlobalReverb->Amount);

			// get current patch for this channel to determine delay/reverb amounts
			// we do a wet/dry mix thing here. the dry amount is copied to the channel buffer
			// the wet amount is copied to the FX buffer where global fx will be added (delay/reverb)
			for(int i=0; i<Constants_NumAudioChannels; i++)
			{
				// delay
				float amt = processDelay ? delayAmount : reverbAmount;
				float dry = 1.0f - (amt);
				float wet = amt;
				for (int j = Constants::instance->BufferOffset; j < Constants::instance->BufferOffset+numSamples; j++)
				{			
					int idx = j%Constants_MixBufferSizeFloat;
					//float val = VoicePool_Pool->BufferChannels->Buffer[idx].ch[i] * FloatStackItemParam_Value(patch->ChanVolAmount);
					// TODO
					float level = 1;//FloatStackItemParam_Value(patch->ChanVolAmount);

					//buffer->Buffer[i][idx] += val * Constants_MasterVolume * amp;		
					float chanVal = BufferChannels->Buffer[idx].ch[i];
					// copy dry back to channel buffer
					Pool->BufferChannels->Buffer[idx].ch[i] = chanVal * dry * level;
					// copy/add wet to fx buffer
					fxBuffer->Buffer[idx].ch[i] += chanVal * wet * level;
				}
			}
		}

		// mix channel buffer into main mix buffer
		bufferOut->MixIn(BufferChannels, 0, numSamples);
	}

	// TODO

	// handle global delay by processing contents of FX buffer
	// delay
	//VoicePool_Pool->GlobalDelay->renderBuffer(VoicePool_Pool->BufferDelay, numSamples);		
	//bufferOut->MixIn(VoicePool_Pool->BufferDelay, 0, numSamples);

	// reverb
	//VoicePool_Pool->GlobalReverb->renderBuffer(VoicePool_Pool->BufferReverb, numSamples);		
	//bufferOut->MixIn(VoicePool_Pool->BufferReverb, 0, numSamples);


}

Voice* VoicePool::GetVoiceAndPlayNote(int channel, int noteId, Patch* patch)
{
	printf("\n\nNOTE ON: chan %d, note %d, patch %d\n", channel, noteId, patch->number);
	// TODO
	int patchMaxPoly = patch->polyphony;

	EnterCriticalSection(&cs);
	//PluginEditorView.Instance.AddText("START channel: " + channel + " note: " + noteId);
    //MessageBox.Show("START channel: " + channel + " note: " + noteId);

	// stop voice if already playing this note on this chan
	// TODO: WHAT??
	if (NotePlaying(channel, noteId))
	{
		// stop dead
		Stop(channel, noteId);
	}

    Voice* voiceToRealloc = 0;
    /*
        find a voice which is keyed off and playing the same note (on the same channel) as we want to play, and reallocate it
    else: find all voices which are keyed off and reallocate the one with the lowest volume
    else: find a voice which is playing the same note (on the same channel) as we want to play, and reallocate it
    else: reallocate the voice with the lowest volume
        */
	
	if (patchMaxPoly < 2)
	{
		// mono-phonic, find number of playing voice with this patch on this channel and bend note
		for(int i=0; i<Constants_Polyphony; i++)
		{
			Voice* voice = Voices[i];
			if (voice != 0 && voice->State == kVoiceStateOn && voice->ChannelId == channel)
			{
				// toggle old note id
				//NoteStates[voice->ChannelId][voice->NoteId]->NoteInfo = kNoteStateOff;
				//NoteStates[voice->ChannelId][noteId]->NoteInfo = kNoteStateOn;
				// bend the note
				NoteStates[voice->ChannelId][noteId]->NoteOnTimeId = Counter++;
				voice->PitchBend(noteId);
				return voice;
			}
		}
	}

	if (voiceToRealloc == 0)
	{
		// find a free voice
		for(int i=0; i<Constants_Polyphony; i++)
		{
			Voice* voice = Voices[i];
			if (voice != 0 && voice->State == kVoiceStateOff)
			{
				voiceToRealloc = voice;
				break;
			}
		}
	}
	
    if (voiceToRealloc == 0)
    {
        // find stopping voice with lowest volume
		for(int i=0; i<Constants_Polyphony; i++)
		{
			Voice* voice = Voices[i];
            if (voice != 0 && voice->State == kVoiceStateStopping)
            {
                if (voiceToRealloc == 0 || voice->ApproxVolume < voiceToRealloc->ApproxVolume)
                {
                    voiceToRealloc = voice;
                }
            }
        }
    }
	
    // find lowest voice playing same note
    if (voiceToRealloc == 0)
    {
		for(int i=0; i<Constants_Polyphony; i++)
		{
			Voice* voice = Voices[i];
            if (voice != 0 && voice->NoteId == noteId)
            {
                voiceToRealloc = voice;
            }
        }
    }
	
    // find voice with lowest volume
	if (voiceToRealloc == 0)
	{
		for(int i=0; i<Constants_Polyphony; i++)
		{
			Voice* voice = Voices[i];
            if (voiceToRealloc == 0 || voice->ApproxVolume < voiceToRealloc->ApproxVolume)
            {
                voiceToRealloc = voice;
            }
        }
    }
	if (voiceToRealloc!=0)
	{
		NoteStates[channel][noteId]->VoiceInfo = voiceToRealloc;
		NoteStates[channel][noteId]->NoteInfo = kNoteStateOn;
		printf("Starting voice %d\n", NoteStates[channel][noteId]->VoiceInfo->Number);
		voiceToRealloc->Start(noteId, channel, patch, Counter++);
	}
	LeaveCriticalSection(&cs);
    return voiceToRealloc;            
}