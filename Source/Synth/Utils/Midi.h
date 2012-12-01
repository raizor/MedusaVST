#pragma once

#include "../Constants.h"

class Midi
{
public:
	Midi(void);
	~Midi(void);
};

class MidiEvent
{
public:
	int deltaTime;
	bool handled;
	int note;
	PlayerEventType type;
	MidiEvent(void);
	~MidiEvent(void);
};

class MidiEventQueue
{
public:
	MidiEvent** events;
	int size;
	long currentTime;
	int readOffset;
	int writeOffset;
	MidiEventQueue(int queueSize);
	~MidiEventQueue(void);
	void AddEvent(MidiEvent* evt);
	MidiEvent* CurrentEvent();
	bool NextEvent();
	void Clear();
};


