#include "Midi.h"

MidiEvent::MidiEvent()
{
	handled = false;
	deltaTime = 0;
	
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

MidiEvent* MidiEventQueue::GetEvent()
{
	return events[readOffset < size ? readOffset++ : 0];
}

void MidiEventQueue::Clear()
{
	readOffset = 0;
	writeOffset = 0;

}
