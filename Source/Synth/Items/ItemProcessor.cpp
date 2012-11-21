#include "ItemProcessor.h"
#include "../Utils/Voice.h"

ItemProcessor::ItemProcessor(StackItemType type, bool hasWaveTable) : Item(true, type, hasWaveTable)
{
}


ItemProcessor::~ItemProcessor(void)
{
}

void ItemProcessor::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{

}