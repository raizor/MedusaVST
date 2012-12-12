#include "ChorusFlange.h"

ChorusFlange::ChorusFlange(void): ItemProcessor(kStackItemTypeChorusFlange, true)
{
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeTime, true, 20.0f)); // delay time
}

ChorusFlange::~ChorusFlange(void)
{
}

void ChorusFlange::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{
}

