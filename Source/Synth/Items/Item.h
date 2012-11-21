#pragma once

#include "../Utils/SampleBufferFloat.h"
#include "../Utils/Params/ParamFloat.h"
#include "../Utils/Params/ParamInt.h"
#include "../Utils/Params/ParamBool.h"

// core item which all synth items inherit from

class WaveTableIndex;

class Item
{
public:
	bool hasBuffer;
	bool hasWaveTable;
	bool enabled;
	StackItemType itemType;
	SampleBufferFloat* buffer;
	ParamFloat** paramsFloat;
	ParamInt** paramsInt;
	ParamBool** paramsBool;
	int numParamsFloat;
	int numParamsBool;
	int numParamsInt;
	WaveTableIndex* WaveTableIdx;

	Item(bool hasBuffer, StackItemType type, bool hasWaveTable = false);
	~Item(void);

	virtual void AddFloatParam(ParamFloat* param);
	virtual void AddIntParam(ParamInt* param);
	virtual void AddBoolParam(ParamBool* param);
	virtual void Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples);
	virtual void Reset();
};

