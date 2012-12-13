#include "SimpleFilter.h"
#include "../../Utils/Voice.h"
#include "../../Utils/WaveTableGen.h"

SimpleFilter::SimpleFilter(void) : ItemProcessor(kStackItemTypeSimpleFilter)
{
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // cutoff 
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // res 
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypePan)); // panning 
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneBi)); // separation 
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // // cutoff mod 

	AddIntParam(new ParamInt(kFilterTypeOff)); // filter type
	AddIntParam(new ParamInt(0)); // limiter

	AddBoolParam(new ParamBool(false)); // res boost

	moog.init();
	for(int i=0; i<Constants_Polyphony; i++)
	{
		for(int chan=0; chan<2; chan++)
		{
			lrc[i][chan].init();
		}

	}
}


SimpleFilter::~SimpleFilter(void)
{
}

void SimpleFilter::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{
	FilterType filterType = (FilterType)paramsInt[PROC_PARAM_FLOAT_LEVEL]->Value(); 
	V2LRC flt_left, flt_right;
	//V2Moog m;

	//sF32 ff = calcfreq(fr) * 44100.0f;

	switch(filterType)
	{
		case(kFilterTypeLowPass):
		{
			flt_left = lrc[voice->Number][0];
			flt_right = lrc[voice->Number][1];
			for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
			{
				//float wet = FloatStackItemParam_Value(filter->Level);
				float wet = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->Value();
				float dry = 1.0f - wet;

				int idx = i%Constants_MixBufferSizeFloat;
				//float fv = FloatStackItemParam_Value(filter->Cutoff);
				float fv = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->Value();
				float mod = fv;
				//FloatStackItemParam_ModulateValue(filter->Cutoff, &mod, idx);
				mod = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->GetModulatedValue(voice, &mod, idx);
				fv = fv+(fv*mod);
				float fr = calcfreq(fv);
				float f = fr < 1.0f ? fr : 0.999f;
				float resv = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->Value();//FloatStackItemParam_Value(filter->Resonance);
				mod = resv;
				//FloatStackItemParam_ModulateValue(filter->Resonance, &mod, idx);
				mod = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->GetModulatedValue(voice, &mod, idx);
				resv = resv+(resv*mod);
				float res = 1.0f - resv;
				
				float inLeft = bufferIn->Buffer[idx].ch[0];
				float inRight = bufferIn->Buffer[idx].ch[1];
				flt_left.step_2x(inLeft, f, res);
				flt_right.step_2x(inRight, f, res);
				bufferOut->Buffer[idx].ch[0]= (flt_left.l * wet) + (inLeft * dry);
				bufferOut->Buffer[idx].ch[1] =(flt_right.l * wet) + (inRight * dry);

			}				
			lrc[voice->Number][0] = flt_left;
			lrc[voice->Number][1] = flt_right;
			break;
		}

		case(kFilterTypeHighPass):
			{
				flt_left = lrc[voice->Number][0];
				flt_right = lrc[voice->Number][1];
				for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
				{
					float wet = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->Value();
					float dry = 1.0f - wet;

					int idx = i%Constants_MixBufferSizeFloat;
					float fv = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->Value();
					float mod = fv;
					//FloatStackItemParam_ModulateValue(filter->Cutoff, &mod, idx);
					mod = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->GetModulatedValue(voice, &mod, idx);
					fv = fv+(fv*mod);
					float fr = calcfreq(fv);
					float f = fr < 1.0f ? fr : 0.999f;
					float resv = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->Value();
					mod = resv;
					//FloatStackItemParam_ModulateValue(filter->Resonance, &mod, idx);
					mod = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->GetModulatedValue(voice, &mod, idx);
					resv = resv+(resv*mod);
					float res = 1.0f - resv;

					float inLeft = bufferIn->Buffer[idx].ch[0];
					float inRight = bufferIn->Buffer[idx].ch[1];
					float h_left = flt_left.step_2x(inLeft, f, res);
					float h_right = flt_right.step_2x(inRight, f, res);
					bufferOut->Buffer[idx].ch[0] = (h_left * wet) + (inLeft * dry); 
					bufferOut->Buffer[idx].ch[1] = (h_right * wet) + (inRight * dry);
				}				
				lrc[voice->Number][0] = flt_left;
				lrc[voice->Number][1] = flt_right;
				break;
			}
		case(kFilterTypeBandPass):
			{
				flt_left = lrc[voice->Number][0];
				flt_right = lrc[voice->Number][1];
				for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
				{
					float wet = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->Value();
					float dry = 1.0f - wet;

					int idx = i%Constants_MixBufferSizeFloat;
					//float fv = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->Value();
					float fv = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->Value();
					float mod = fv;
					//FloatStackItemParam_ModulateValue(filter->Cutoff, &mod, idx);
					fv = fv+(fv*mod);
					float fr = calcfreq(fv);
					float f = fr < 1.0f ? fr : 0.999f;
					float resv = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->Value();
					mod = resv;
					//FloatStackItemParam_ModulateValue(filter->Resonance, &mod, idx);
					mod = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->GetModulatedValue(voice, &mod, idx);
					resv = resv+(resv*mod);
					float res = 1.0f - resv;

					float inLeft = bufferIn->Buffer[idx].ch[0];
					float inRight = bufferIn->Buffer[idx].ch[1];
					flt_left.step_2x(inLeft, f, res);
					flt_right.step_2x(inRight, f, res);
					bufferOut->Buffer[idx].ch[0] = (flt_left.b * wet) + (inLeft * dry);
					bufferOut->Buffer[idx].ch[1] = (flt_right.b * wet) + (inRight * dry);
				}				
				lrc[voice->Number][0] = flt_left;
				lrc[voice->Number][1] = flt_right;
				break;
			}
		case(kFilterTypeNotch):
			{				
				flt_left = lrc[voice->Number][0];
				flt_right = lrc[voice->Number][1];
				for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
				{
					float wet = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->Value();
					float dry = 1.0f - wet;

					int idx = i%Constants_MixBufferSizeFloat;
					float fv = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->Value();
					float mod = fv;
					mod = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->GetModulatedValue(voice, &mod, idx);
					//FloatStackItemParam_ModulateValue(filter->Cutoff, &mod, idx);
					fv = fv+(fv*mod);
					float fr = calcfreq(fv);
					float f = fr < 1.0f ? fr : 0.999f;
					float resv = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->Value();
					mod = resv;
					//FloatStackItemParam_ModulateValue(filter->Resonance, &mod, idx);
					mod = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->GetModulatedValue(voice, &mod, idx);
					resv = resv+(resv*mod);
					float res = 1.0f - resv;

					float inLeft = bufferIn->Buffer[idx].ch[0];
					float inRight = bufferIn->Buffer[idx].ch[1];
					float h_left = flt_left.step_2x(inLeft, f, res);
					float h_right = flt_right.step_2x(inRight, f, res);
					bufferOut->Buffer[idx].ch[0] = ((flt_left.l + h_left) * wet) + (inLeft * dry);
					bufferOut->Buffer[idx].ch[1] = ((flt_right.l + h_right) * wet) + (inRight * dry);
				}				
				lrc[voice->Number][0] = flt_left;
				lrc[voice->Number][1] = flt_right;
				break;
			}
		case(kFilterTypeAll):
			{				
				flt_left = lrc[voice->Number][0];
				flt_right = lrc[voice->Number][1];
				for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
				{
					float wet = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->Value();
					float dry = 1.0f - wet;

					int idx = i%Constants_MixBufferSizeFloat;
					float fv = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->Value();
					float mod = fv;
					//FloatStackItemParam_ModulateValue(filter->Cutoff, &mod, idx);
					mod = paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]->GetModulatedValue(voice, &mod, idx);
					fv = fv+(fv*mod);
					float fr = calcfreq(fv);
					float f = fr < 1.0f ? fr : 0.999f;
					float resv = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->Value();
					mod = resv;
					//FloatStackItemParam_ModulateValue(filter->Resonance, &mod, idx);
					mod = paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]->GetModulatedValue(voice, &mod, idx);
					resv = resv+(resv*mod);
					float res = 1.0f - resv;

					float inLeft = bufferIn->Buffer[idx].ch[0];
					float inRight = bufferIn->Buffer[idx].ch[1];
					float h_left = flt_left.step_2x(inLeft, f, res);
					float h_right = flt_right.step_2x(inRight, f, res);
					bufferOut->Buffer[idx].ch[0] = ((flt_left.l + flt_left.b + h_left) * wet) + (inLeft * dry);
					bufferOut->Buffer[idx].ch[1] = ((flt_right.l + flt_right.b + h_right) * wet) + (inRight * dry);
				}				
				lrc[voice->Number][0] = flt_left;
				lrc[voice->Number][1] = flt_right;
				break;
			}
		case(kFilterTypeMoogLow):
			{
				/*
				// Moog filters are 2x oversampled, so run filter twice.
				m = filter->moog;
				for (int i = Constants_BufferOffset; i < Constants_BufferOffset+numSamples; i++)
				{

					float fr = FloatStackItemParam_Value(filter->Cutoff);
					float resv = FloatStackItemParam_Value(filter->Resonance);
					float f = fr < 1.0f ? fr : 0.999f;
					float res = resv > 0.01f ? resv : 0.01f;
					int idx = i%Constants_MixBufferSizeFloat;	

					float in = bufferIn->Buffer[0][idx];
					m.step(in, filter->moogf, filter->moogp, filter->moogq);			
					
					
					bufferOut->Buffer[0][idx] = flt.l + flt.b + h;
					bufferOut->Buffer[1][idx] = flt.l + flt.b + h;
				}				
				filter->lrc = flt;
				break;*/
			}
	}		
}