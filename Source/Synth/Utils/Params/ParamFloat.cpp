#include "ParamFloat.h"
#include "../Voice.h"

ParamFloat::ParamFloat(float value, bool modifiable, float defaultModValue, float modIncVal, ParamValueTypeFloat valueType) : Param(kParamTypeFloat, modifiable, defaultModValue, modIncVal)
{
	float* f = (float*)zynth_mallocAlloc(sizeof(float));
	_value = f;
	ValueType = valueType;
	
	SetValueWithInt(value);

	ModList = new ModulatorList();
}

ParamFloat::~ParamFloat(void)
{
}

float ParamFloat::ConvertValueFromInt(float value)
{
	switch(ValueType)
	{
	case (kParamValueTypeTime):
		{
			float val = value == 0 ? 0 : (float)(zt_pow(2.0, ((double)_intValue / 127.0f) * 10) * 0.0127);
			
			return val;
		}
	case(kParamValueTypeIntBi):
		{
			return (float)value;
		}
	case(kParamValueTypeCents):
		{
			return (float)value-50;
		}
	case(kParamValueTypeZeroToOneBi):
		{
			//targetValue =  -1.0f + (((float)knob.Value / knob.Maximum)*2);
			return -1.0f + ((float)value/127.0f)*2.0f;
		}
	default:
		{
			return ((float)value)/127.0f;
		}
	}	
}

float ParamFloat::Value()
{
	if (_fade < 1.0f)
	{
		if (_fade + ModValueInc > 1.0f)
		{
			_fade = 1.0f;
		}
		else
		{
			_fade += ModValueInc;
		}
	}
	float *val = (float*)_value;
	*val = _source + (_diff * _fade);
	return *val;
}


float ParamFloat::ModValue(float* value, float modValue, ModulationCurve* curve)
{
	float val = 0;

	switch(*curve)
	{
		case(kModulationCurveAddBipolarPlus):
			{
				float v = -1.0f + ((modValue* 2.0f) * *value);
				*value += v;
				break;
			}	

		case(kModulationCurveAddBipolarMinus):
			{
				*value -= -1.0f + ((modValue* 2.0f) * *value);
				break;
			}	

		case(kkModulationCurveAddUnipolarPlus):
			{
				*value += modValue * *value;
				break;
			}	

		case(kModulationCurveAddUnipolarMinus):
			{
				*value -= modValue * *value;
				break;
			}	

		case(kModulationCurveMultBipolarPlus):
			{
				*value *= -1.0f+(modValue*2.0f);
				break;
			}	

		case(kModulationCurveMultBipolarMinus):
			{
				*value /= -1.0f+(modValue*2.0f);
				break;
			}

		case(kModulationCurveMultUnipolarPlus):
			{
				*value *= modValue;
				break;
			}	

		case(kModulationCurveMultUnipolarMinus):
			{
				*value /= modValue;
				break;
			}
	}
	return *value;
}

float ParamFloat::GetModValue(Voice* voice, int bufferIndex)
{
	if (ModList->Count > 0)
	{	
		float modValue = 0;
		for(int i=0; i<ModList->Count; i++)
		{
			Modulator* mod = &ModList->Modulators[i];
			ModValue(&modValue, ModList->Modulators[i].ModBuffer->Buffer[bufferIndex].ch[0], &mod->Curve);
		}
		return modValue;	
	}else{
		return 0.0f;
	}
}

float ParamFloat::GetModdedValue(Voice* voice, int bufferIndex)
{
	return Value() * GetModValue(voice, bufferIndex);
}

float ParamFloat::GetModulatedValue(float* value, int bufferIndex)
{
	for (int i=0; i<ModList->Count; i++)
	{
		Modulator* mod = &ModList->Modulators[i];
		float modder = ModList->Modulators[i].ModBuffer->Buffer[bufferIndex].ch[0];
		ModValue(value, modder, &mod->Curve);
	}
	return 0;
}


void ParamFloat::SetValue(int value)
{
	_intValue = (float)value;
	float val  = ConvertValueFromInt(_intValue);
	_source = Value();
	_diff = val - _source;
	_fade = 0;
	TargetValue = val;
}

void ParamFloat::SetValueWithInt(float value)
{
	_intValue = value;
	float val = ConvertValueFromInt(value);
	float*f = (float*)_value;
	*f = val;
	DefaultValue = *f;
	TargetValue = *f;	
	_diff = 0;
	_fade = 1.0f;
	_maxValue  =1.0f;
	_source = DefaultValue;
}

ModulatorList::ModulatorList()
{
}

ModulatorList::~ModulatorList()
{
}

Modulator::Modulator()
{
}

Modulator::~Modulator()
{
}