#pragma once
#include "Item.h"

// processor item - processes a buffer

#define PROC_PARAM_FLOAT_LEVEL         0

class Voice;

class ItemProcessor : public Item
{
public:
	ItemProcessor(StackItemType type, bool hasWaveTable = false);
	~ItemProcessor(void);
	virtual void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
};

