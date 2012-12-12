#include "Boost.h"


Boost::Boost(void) : ItemProcessor(kStackItemTypeBoost, true)
{
}

void Boost::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{
	for (int ch = 0; ch < Constants_NumAudioChannels; ch++)
	{
		sF32 xm1 = x1[ch];
		sF32 xm2 = x2[ch];
		sF32 ym1 = y1[ch];
		sF32 ym2 = y2[ch];

		for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
		{		
			int idx = i%Constants_MixBufferSizeFloat;
			sF32 x = bufferIn->Buffer[idx].ch[ch] + fcdcoffset;

			// Second-order IIR filter
			sF32 y = b0*x + b1*xm1 + b2*xm2 - a1*ym1 - a2*ym2;
			ym2 = ym1; 
			ym1 = y;
			xm2 = xm1; 
			xm1 = x;

			bufferOut->Buffer[idx].ch[ch] = y;
			//bufferOut->Buffer[idx].ch[ch] = v;		
		}
		x1[ch] = xm1; 
		x2[ch] = xm2;
		y1[ch] = ym1; 
		y2[ch] = ym2;
	}
}

Boost::~Boost(void)
{
}
