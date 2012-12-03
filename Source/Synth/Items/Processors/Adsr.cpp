#include "Adsr.h"
#include "../../Utils/Voice.h"

Adsr::Adsr(EgType type) : ItemProcessor(kStackItemTypeAmpEg, true)
{
	this->type = type;
	stage = (int*)zynth_mallocAlloc(sizeof(int)*Constants_Polyphony);
	value = (float*)zynth_mallocAlloc(sizeof(float)*Constants_Polyphony);
	stageAmount = (float*)zynth_mallocAlloc(sizeof(float)*Constants_Polyphony);

	for(int i=0; i<Constants_Polyphony; i++)
	{
		stage[i] = kStageNone;
		stageAmount[i] = 0;
		value[i] = 0;
	}
	

	// TODO: optimize
	if (this->type == kEgTypePitch)
	{
		AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // delay time
		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneBi)); // start level

		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // attack time
		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneBi)); // attack level

		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // decay time
		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // decay level

		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // sustain time
		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // sustain level
		
		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // release time
		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneBi)); // release level
	}else{
		AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // delay time
		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // start level

		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // attack time
		AddFloatParam(new ParamFloat(127.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // attack level

		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // decay time
		AddFloatParam(new ParamFloat(127.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // decay level

		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // sustain time
		AddFloatParam(new ParamFloat(127.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // sustain level

		AddFloatParam(new ParamFloat(64.0f, true, 1.0f, 0.5f, kParamValueTypeTime)); // release time
		AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni)); // release level
	}

	enabled = this->type == kEgTypeAmp;
}


Adsr::~Adsr(void)
{
}

void Adsr::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{
	bool isAmpEg = type == kEgTypeAmp;

	for (int i = Constants::instance->BufferOffset; i < Constants::instance->BufferOffset+numSamples; i++)
	{
		int idx = i%Constants_MixBufferSizeFloat;
		if (voice->State == kVoiceStateOn)
		{			
			switch (stage[voice->Number])
			{
				case (kStageNone):
					{
						if (voice->Time > 0)
						{
							// envelope has finished for this voice and note
							break;
						}
						// prepare for delay
						stage[voice->Number] = kStageDelay;							
						goto DelayCase;
						break;
					}
				case (kStageDelay):
					{
DelayCase:
						//envelopeAdsr->Value[voice->Number] = 0;
						value[voice->Number] = paramsFloat[ADSR_PARAM_FLOAT_START_LEVEL]->TargetValue;
						if (voice->Time >= paramsFloat[ADSR_PARAM_FLOAT_DELAY_TIME]->TargetValue)
						{
							if (paramsFloat[ADSR_PARAM_FLOAT_ATTACK_TIME]->TargetValue > 0)
							{
								// prepare for attack
								value[voice->Number] = 0.0f;
								stage[voice->Number] = kStageAttack;								
								//envelopeAdsr->StageAmount[voice->Number] = 1.0f / envelopeAdsr->Attack->TargetValue / Constants_SamplesPerSec;
								stageAmount[voice->Number] = (1.0f - paramsFloat[ADSR_PARAM_FLOAT_START_LEVEL]->TargetValue) / paramsFloat[ADSR_PARAM_FLOAT_ATTACK_TIME]->TargetValue / Constants_SamplesPerSec;
								//envelopeAdsr->StageAmount[voice->Number] = (1.0f - envelopeAdsr->StartLevel->TargetValue) / (envelopeAdsr->Attack->TargetValue / Constants_SamplesPerSec);
							}else{
								goto prepareDecay;
							}

						}
						break;
					}
				case (kStageAttack):
					{
						value[voice->Number] += stageAmount[voice->Number];
						if (value[voice->Number] >= 1.0f)
						{
							// prepare for decay
prepareDecay:
							if (paramsFloat[ADSR_PARAM_FLOAT_DECAY_TIME]->TargetValue > 0)
							{
								value[voice->Number] = 1.0f;
								stage[voice->Number] = kStageDecay;								
								stageAmount[voice->Number] = (1.0f - paramsFloat[ADSR_PARAM_FLOAT_DECAY_LEVEL]->TargetValue) / paramsFloat[ADSR_PARAM_FLOAT_DECAY_TIME]->TargetValue / Constants_SamplesPerSec;
							}else{
								goto prepareSustain;
							}

						}
						break;
					}

				case (kStageDecay):
					{
						value[voice->Number] -= stageAmount[voice->Number];

						if (value[voice->Number] <= paramsFloat[ADSR_PARAM_FLOAT_DECAY_LEVEL]->TargetValue)
						{
prepareSustain:
							// prepare for sustain
							//envelopeAdsr->Value[voice->Number] = FloatStackItemParam_Value(envelopeAdsr->Sustain);
							if (paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_TIME]->TargetValue > 0)
							{
								stage[voice->Number] = kStageSustain;
								if (value[voice->Number] > paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_LEVEL]->TargetValue)
								{
									stageAmount[voice->Number] = (value[voice->Number] - paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_LEVEL]->TargetValue) / paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_TIME]->TargetValue / Constants_SamplesPerSec;
								}else{
									stageAmount[voice->Number] = (paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_LEVEL]->TargetValue - value[voice->Number]) / paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_TIME]->TargetValue / Constants_SamplesPerSec;
								}
								//float v = envelopeAdsr->StageAmount[voice->Number];
							}else{
								// no sustain time
								if (isAmpEg)
								{
									voice->State = kVoiceStateStopping;
								}									
								goto prepareRelease;
							}

						}
						break;
					}

				case (kStageSustain):
					{
						if (value[voice->Number] > paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_LEVEL]->TargetValue)
						{
							value[voice->Number] -= stageAmount[voice->Number];
						}else if (value[voice->Number] < paramsFloat[ADSR_PARAM_FLOAT_SUSTAIN_LEVEL]->TargetValue)
						{
							value[voice->Number] += stageAmount[voice->Number];
						}

						break;
					}

				default:
					{
						int xx = 1;
						goto RELEASE;
					}	
			}

		}else if(voice->State == kVoiceStateStopping)
		{
			switch (stage[voice->Number])
			{
			case (kStageRelease):
				{
RELEASE:
					value[voice->Number] -= stageAmount[voice->Number];
					if (value[voice->Number] <= 0.0f || stageAmount[voice->Number] == 0)
					{
						// prepare for stop
						stage[voice->Number] = kStageNone;
						value[voice->Number] = 0;								
						stageAmount[voice->Number] = 0;
						if (isAmpEg)
						{
							// this is an amp env, turn off the voice 
							voice->StopDead();
							stage[voice->Number] = kStageNone;
							value[voice->Number] = 0;
							//Reset(); // reset this eg
							//voice->StopPos = idx;
						}else{
							//StackItem_Reset(envelopeAdsr->_item, voice);
						}			
					}
					break;
				}

			default:
				{
					// switch to release state set amount per sample for release
					// TODO: need to only fade to release level!
prepareRelease:
					stageAmount[voice->Number] = value[voice->Number] / paramsFloat[ADSR_PARAM_FLOAT_RELEASE_TIME]->TargetValue / Constants_SamplesPerSec;
					stage[voice->Number] = kStageRelease;
					break;
				}
			}
		}

		float amt = paramsFloat[PROC_PARAM_FLOAT_LEVEL]->Value();
		amt *= value[voice->Number];

		for (int j = 0; j < Constants_NumAudioChannels; j++)
		{
			if (isAmpEg)
			{
				bufferOut->Buffer[idx].ch[j] *= amt;					
			}
			//
			buffer->Buffer[idx].ch[j] = amt;
			if (!isAmpEg)
			{
				int xx = 1;
				//envelopeAdsr->TempBuffer->Buffer[j][idx] = WaveFormGen_Noise(0, 0, 0);
			}
		}
	}
}

void Adsr::Reset()
{
	for(int i=0; i<Constants_Polyphony; i++)
	{
		stage[i] = kStageNone;
		value[i] = stageAmount[i] = 0;
	}
}
