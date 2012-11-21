#include "Midi.h"

MidiEvent::MidiEvent()
{
}

MidiEventQueue::MidiEventQueue(int queueSize)
{
	size = queueSize;
	currentTime = 0;
	events = new MidiEvent*[size];
}


MidiEventQueue::~MidiEventQueue(void)
{
}

void MidiEventQueue::AddEvent(MidiEvent* evt)
{
	events[readOffset < size ? readOffset++ : 0] = evt;
}

MidiEvent* MidiEventQueue::GetEvent()
{
	return events[writeOffset < size ? writeOffset++ : 0];
}
