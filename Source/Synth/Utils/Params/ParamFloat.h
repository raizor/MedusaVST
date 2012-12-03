#pragma once

#include "../../Constants.h"
#include "Param.h"
#include "../SampleBufferFloat.h"

class ModulatorList;
class Modulator;
class Voice;

// float param - fully modulatable
class ParamFloat : public Param
{
public:
	bool exponential;
	float exponentialIncrement;
	float TargetValue;
	float DefaultValue;		
	ParamValueTypeFloat ValueType;

	ParamFloat(float value, bool modifiable, float defaultModValue, float modIncVal, ParamValueTypeFloat valueType, bool exponential = false, float exponentialInc = 0.0f);
	~ParamFloat(void);
	float ConvertValueFromInt(float value);
	void SetValueWithInt(float value);
	void SetValue(int value);
	float Value();
	float ValueAsInt();

	float GetModValue(Voice* voice, int bufferIndex);
	float GetModdedValue(Voice* voice, int bufferIndex);
	float GetModulatedValue(float *value, int bufferIndex);

	static float ModValue(float* value, float modValue, ModulationCurve* curve);

	ModulatorList* ModList;

private: 	
	float _intValue;
	float _source;
	float _diff;
	float _fade;
	float _maxValue;
};

// todo: remove??
class ModulationStackItemParam  
{				
	Param* _param;
};

class Modulator
{
public:
	StackItemType Type;
	SampleBufferFloat *ModBuffer;
	ModulationCurve Curve;
	
	Modulator();
	~Modulator();
};

// as only float params are modulatable, we store the modulators here.
// this list gets updated each time the mod matrix is changed.
// the update is done before rendering the next audio block after a matrix change.
class ModulatorList
{
public:
	Modulator Modulators[Constants_MaxModulations];
	int Size;
	int Count;

	ModulatorList();
	~ModulatorList();
};

