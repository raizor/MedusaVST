#pragma once

#include "SampleBufferShort.h"

// dual channel buffer
class SampleBufferFloat 
{
public:
	StereoSample *Buffer;
	int Size;
	int SizeInBytes;
		
	SampleBufferFloat(long size);	
	void Clear();
	void ClearRange(int numSamples);
	void MixIn(SampleBufferFloat* bufferIn, SampleBufferFloat* ampBuffer, int numSamples);
	void AddClippedValue(int channel, int sampleNo, float val);
	void CopyToByteBuffer(SampleBufferShort* bufferTo);
};
