#include "Midi.h"

// event

MidiEvent::MidiEvent()
{
	handled = false;
	deltaTime = 0;
	
}

// queue

MidiEvent* MidiEventQueue::CurrentEvent()
{
	return readOffset < writeOffset ? events[readOffset] : 0;
}


MidiEventQueue::MidiEventQueue(int queueSize)
{
	size = queueSize;
	currentTime = 0;
	readOffset = writeOffset = 0;
	events = new MidiEvent*[size];
}


MidiEventQueue::~MidiEventQueue(void)
{
}

void MidiEventQueue::AddEvent(MidiEvent* evt)
{
	events[writeOffset < size ? writeOffset++ : 0] = evt;
}

bool MidiEventQueue::NextEvent()
{
	if (readOffset < writeOffset)
	{
		readOffset++;
		return true;
	}else{
		return false;
	}
}

void MidiEventQueue::Clear()
{
	readOffset = 0;
	writeOffset = 0;

}
