#include "ItemProcessor.h"
#include "../Utils/Voice.h"

ItemProcessor::ItemProcessor(bool hasWaveTable) : Item(true, hasWaveTable)
{
}


ItemProcessor::~ItemProcessor(void)
{
}

void ItemProcessor::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{

}