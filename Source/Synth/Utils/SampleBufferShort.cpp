#include "SampleBufferShort.h"
#include "../Utils/ZynthTools.h"

SampleBufferShort::SampleBufferShort(long size)
{
	Size = size;
	SizeInBytes = size*sizeof(short);
	Buffer = (short*)zynth_mallocAlloc(sizeof(short)*size);
}

void SampleBufferShort::Clear()
{
	for(int i=0; i<Constants_NumAudioChannels; i++)
	{
		zt_memset(Buffer , 0, SizeInBytes);
	}
}