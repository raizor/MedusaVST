#include "Synth.h"
#include "Utils/ZynthTools.h"
#include "Utils/WaveTableGen.h"
#include "Utils/VoicePool.h"
#include "Utils/Voice.h"
#include "Utils/PadSynth/PadSynth.h"
#include "Utils/Patch.h"
#include "Items/Processors/Osc.h"
#include "Items/Processors/Adsr.h"

MidiEventQueue* Synth::midiQueue = 0;
ZDebugConsole* Synth::console = 0;

double Synth::renderTime = 0;

Synth::Synth(void)
{
	Synth_Init();
}

void Synth::Synth_Init()
{
	rendering = false;
	renderTime = 0;
	console = new ZDebugConsole();
	DebugPrintLine("INIT");
	midiQueue = new MidiEventQueue(10000);
	Constants::instance = new Constants();
	PowerOfTwoTable::instance = new PowerOfTwoTable();
	PitchUtils::instance = new PitchUtils();
	VoicePool::Pool = new VoicePool();
	PatchList::list = new PatchList();
	WaveTableGen::GenerateTables();
	MixBuffer = new SampleBufferFloat(Constants_MixBufferSizeFloat);
	TestBuffer = new SampleBufferFloat(Constants_MixBufferSizeFloat);
	AmpBuffer = new SampleBufferFloat(Constants_MixBufferSizeFloat);
	for(int i=0; i<AmpBuffer->Size; i++)
	{
		AmpBuffer->Buffer[i].l = 1.0f;
		AmpBuffer->Buffer[i].r = 1.0f;
	}

	//double* d = PadSynth::PadSynthBuildWaveTable(kPadSynthTypeChoir, 10.0, 10.0, 10, 10, 5000, false);

	// setup test patch
	Osc* osc = new Osc();
	osc->enabled = true;
	
	Adsr* eg = new Adsr(kEgTypeAmp);
	eg->enabled  = true; // no needed
	
	Patch* p = PatchList::list->CurrentPatch = PatchList::list->patches[0];
	PatchList::list->patches[0]->polyphony = 4;
	
	
	p->items[p->numItems++] = osc;

	p->egAmp = eg;



	//VoicePool::Pool->GetVoiceAndPlayNote(0, 69, patch);
}

void Synth::MixTest(SampleBufferFloat* bufferOut, int numSamples)
{
	int seed = 0;
	float v = msys_frand(&seed);
	for(int i=0; i<TestBuffer->Size; i++)
	{
		TestBuffer->Buffer[i].l = v;
		TestBuffer->Buffer[i].r = v;
	}
	bufferOut->MixIn(TestBuffer, AmpBuffer, numSamples);
}
	
void Synth::Render(short *buffer, int numSamples)
{
	if (rendering)
	{
		DebugBreak();
	}
	rendering = true;
	// clear output buffer
	zt_memset(buffer, 0, numSamples);

	for(int i=0; i<Constants_Polyphony; i++)
	{
		Voice* voice = VoicePool::Pool->Voices[i];
		if (voice != 0 && voice->State != kVoiceStateOff)
		{
			voice->Generate(numSamples/2);
		}
	}

	MixBuffer->ClearRange(numSamples/2);
	VoicePool::Pool->MixVoicesToBuffer(MixBuffer, numSamples/2);
	//MixTest(MixBuffer, numSamples/2);
	
	int r = 0;

	int ix = 0;
	for(int i=0; i<numSamples/2; i++)
	{
		int idx = (Constants::instance->BufferOffset+i) % Constants_MixBufferSizeFloat;
		float fv = zt_clampfMixMax(MixBuffer->Buffer[idx].ch[0] * Constants::instance->MasterVolume, -1.0f, 1.0f); // clamp
		float fv2 = zt_clampfMixMax(MixBuffer->Buffer[idx].ch[1] * Constants::instance->MasterVolume, -1.0f, 1.0f); // clamp
		short sval = (short)(fv * Constants_ClipLimitMax);
		short sval2 = (short)(fv2 * Constants_ClipLimitMax);
		buffer[ix++] = sval;
		buffer[ix++] = sval2;
	}

	/*
	int outIdx = 0;
	for(int i=0; i<numSamples; i++)
	{
		int idx = (Constants_BufferOffset+i) % Constants_MixBufferSizeFloat;
		float fv = zt_clampfMixMax(SynthInstance->MixBuffer->Buffer[idx].ch[0], -1.0f, 1.0f); // clamp
		short sval = (short)(fv * Constants_ClipLimitMax);
		buffer[outIdx++] = sval;
		buffer[outIdx++] = sval;
	}*/
	int bo = Constants::instance->BufferOffset;
	Constants::instance->BufferOffset = (bo + (numSamples/2)) % Constants_MixBufferSizeFloat;
	rendering = false;
}

static  int xx = 0;
static float vol = 1.0f;
static bool volUp = false;
static float volInc = 0.00001f;

void Synth::RenderFloat(float* bufferLeft, float* bufferRight, int numSamples)
{
	if (rendering)
	{
		DebugBreak();
	}
	rendering = true;

	zt_memset(bufferLeft, 0, numSamples * sizeof(float));
	zt_memset(bufferRight, 0, numSamples * sizeof(float));
	
	for(int i=0; i<Constants_Polyphony; i++)
	{
		Voice* voice = VoicePool::Pool->Voices[i];
		if (voice != 0 && voice->State != kVoiceStateOff)
		{
			voice->Generate(numSamples);
		}
	}

	MixBuffer->ClearRange(numSamples);
	VoicePool::Pool->MixVoicesToBuffer(MixBuffer, numSamples);

	int ix = 0;
	for(int i=0; i<numSamples; i++)
	{
		int idx = (Constants::instance->BufferOffset+i) % Constants_MixBufferSizeFloat;
		float fv = zt_clampfMixMax(MixBuffer->Buffer[idx].ch[0] * Constants::instance->MasterVolume, -1.0f, 1.0f); // clamp
		float fv2 = zt_clampfMixMax(MixBuffer->Buffer[idx].ch[1] * Constants::instance->MasterVolume, -1.0f, 1.0f); // clamp
		short sval = (short)(fv * Constants_ClipLimitMax);
		short sval2 = (short)(fv2 * Constants_ClipLimitMax);
		bufferLeft[i] = fv;
		bufferRight[i] = fv;
	}
	
	int bo = Constants::instance->BufferOffset;
	Constants::instance->BufferOffset = (bo + (numSamples)) % Constants_MixBufferSizeFloat;

	for(int i=0; i<numSamples; i++)
	{
		//bufferLeft[i] = msys_frand(&xx);
		//bufferRight[i] = msys_frand(&xx);
	}
	rendering = false;
}


Synth::~Synth(void)
{
}
