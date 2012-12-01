#include "Item.h"
#include "../Utils/WaveTableGen.h"


Item::Item(bool hasBuffer, StackItemType type, bool hasWaveTable)
{
	itemType = type;
	this->hasBuffer = hasBuffer;
	this->hasWaveTable = hasWaveTable;
	buffer = new SampleBufferFloat(Constants_MixBufferSizeFloat);
	numParamsFloat = 0;
	numParamsBool = 0;
	numParamsInt = 0;
	enabled = false;
	paramsFloat = new ParamFloat*[100];
	paramsBool = new ParamBool*[100];
	paramsInt = new ParamInt*[100];

	if (hasWaveTable)
	{
		waveTableIdx = new WaveTableIndex(WaveTable::WaveTableSine);
		//item->WaveTableIdx = WaveTableIndex_Create(WaveTables_Tables->WaveTableSquare);
	}
}

Item::~Item(void)
{
}

void Item::AddFloatParam(ParamFloat* param)
{
	paramsFloat[numParamsFloat++] = param;
}

void Item::AddIntParam(ParamInt* param)
{
	paramsInt[numParamsInt++] = param;
}

void Item::AddBoolParam(ParamBool* param)
{
	paramsBool[numParamsBool++] = param;
}


void Item::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{
	// do nothing, virtual here
}

void Item::Reset()
{

}
