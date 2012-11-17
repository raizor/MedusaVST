#pragma once
#include "Item.h"

// processor item - processes a buffer

class Voice;

class ItemProcessor : public Item
{
public:
	ItemProcessor(bool hasWaveTable = false);
	~ItemProcessor(void);
	void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
};

