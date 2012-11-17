#pragma once

#include "../Constants.h"

// single channel buffer
class SampleBufferShort 
{
public:
	short *Buffer;
	int Size;
	int SizeInBytes;
	
	SampleBufferShort(long size);
	void Clear();
};





