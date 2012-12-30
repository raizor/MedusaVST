#include "WaveTableGen.h"
#include "WaveFormGen.h"
#include "PadSynth/PadSynth.h" 
#include "PitchUtils.h"

#ifndef REPLAYER
	#include <stdio.h>
#endif

// WAVE TABLE

// WAVE TABLE INDEX

WaveTable* WaveTable::WaveTableOff = 0;
WaveTable* WaveTable::WaveTableSine = 0;
WaveTable* WaveTable::WaveTableSaw = 0;
WaveTable* WaveTable::WaveTableTri = 0;
WaveTable* WaveTable::WaveTableSquare = 0;
WaveTable* WaveTable::WaveTableNoise = 0;
WaveTable** WaveTable::Wavetables = 0;

int WaveTable::NumWaveTables = 0;
	
WaveTableIndex::WaveTableIndex(WaveTable* waveTable)
{
	voicePhaseAccumulator = new double[Constants_Polyphony];
	zt_memset(&voicePhaseAccumulator[0], 0, sizeof(double) * Constants_Polyphony );
	Table = waveTable;
	Phase = 0;
	PhaseOffset = 0;
}

void WaveTableIndex::SetWaveTable(WaveTable* waveTable)
{
	Table = waveTable;
}

void WaveTableIndex::CalcPhaseOffset()
{
	PhaseOffset = Phase*(Table->Tables[0].FloatBuffer->Size-2);
}

float WaveTableIndex::Sample(Voice* voice, float frequency, bool* syncHit)
{
	if (frequency < 0) frequency = -frequency;
	WaveTableSubTable* targetTablePrev; 
	WaveTableSubTable* targetTable; 
	float val;

	if (Table->TablesPerOctave)
	{
		// find closest table
		for(int i=0; i<8*Table->TablesPerOctave; i++)
		{
			if (frequency < Table->Tables[i].Frequency || i == (8*Table->TablesPerOctave)-1) // don't go off the bloody end!
			{
				if (i > 0)
				{
					targetTablePrev = &Table->Tables[i-1];

				}
				targetTable = &Table->Tables[i];
				break;
			}
		}
		if (targetTable == 0)
		{
			//DebugBreak();
		}
		
		// get the value from the wavetable buffer
		// we do a little interpolation here to cope with the voicePhaseAccumulator value being between 2 positions
		// replayer may or may not interpolate - probably a define...
		long whole = (long)voicePhaseAccumulator[voice->Number];
		double fract = voicePhaseAccumulator[voice->Number] - whole;
		long idx = (long)(voicePhaseAccumulator[voice->Number]) % (targetTable->FloatBuffer->Size - 1);

		// slow
		// TODO: idx = -254648 here?!?! wtf
		float idxVal = targetTable->FloatBuffer->Buffer[idx].ch[0];
		float idxValNext = targetTable->FloatBuffer->Buffer[idx+1].ch[0];
		val = (float)(idxVal + ((idxValNext - idxVal) * fract));
		/*
		if (targetTablePrev != 0)
		{
			float idxVal = targetTablePrev->FloatBuffer->Buffer[0][idx];
			float idxValNext = targetTablePrev->FloatBuffer->Buffer[0][idx+1];
			float val2 = (float)(idxVal + ((idxValNext - idxVal) * fract));
			float amtPrev = targetTablePrev->Frequency/frequency;
			float amtNext = frequency/targetTable->Frequency;
			val = (val2 * (1.0f - amtPrev)) + (val * amtPrev);
		}*/

		// increment the phase accumulator for this voice for next sampling
		double phaseAccumulation = frequency/targetTable->Frequency;
		//double amt = waveTableIndex->voicePhaseAccumulator[voice->Number] + phaseAccumulation;
		double amt = voicePhaseAccumulator[voice->Number] + phaseAccumulation;
		if (amt >= Table->Tables[0].FloatBuffer->Size - 2)
		{
			//*syncHit = true; // hit end of period
			voicePhaseAccumulator[voice->Number] = fmod(amt, (targetTable->FloatBuffer->Size - 2));
			//waveTableIndex->voicePhaseAccumulator[voice->Number] += waveTableIndex->PhaseOffset;
		}
		else
		{
			voicePhaseAccumulator[voice->Number] += phaseAccumulation;
		}

		return val;
	}else{
		targetTable = &Table->Tables[0];
		// get the value from the wavetable buffer
		// we do a little interpolation here to cope with the voicePhaseAccumulator value being between 2 positions
		// replayer may or may not interpolate - probably a define...
		double whole = voicePhaseAccumulator[voice->Number];
		double fract = voicePhaseAccumulator[voice->Number] - whole;
		long idx = (long)(voicePhaseAccumulator[voice->Number]) % (targetTable->FloatBuffer->Size - 2);

		// slow
		// TODO: idx = -254648 here?!?! wtf
		float idxVal = targetTable->FloatBuffer->Buffer[idx].ch[0];
		float idxValNext = targetTable->FloatBuffer->Buffer[idx+1].ch[0];
		float val = (float)(idxVal + ((idxValNext - idxVal) * fract));

		// increment the phase accumulator for this voice for next sampling
		//double phaseAccumulation = (frequency / Constants_SamplesPerSec) * (targetTable->FloatBuffer->Size -2) * targetTable->Frequency;
		double phaseAccumulation = frequency / targetTable->Frequency;
		if (phaseAccumulation < 0.0)
		{
			//DebugBreak();
		}
		//double amt = waveTableIndex->voicePhaseAccumulator[voice->Number] + phaseAccumulation;
		double amt = voicePhaseAccumulator[voice->Number] + phaseAccumulation;
		if (amt >= targetTable->FloatBuffer->Size - 2)
		{
			*syncHit = true; // hit end of period
			voicePhaseAccumulator[voice->Number] = fmod(amt, (targetTable->FloatBuffer->Size - 2));
			//waveTableIndex->voicePhaseAccumulator[voice->Number] += waveTableIndex->PhaseOffset;
		}
		else
		{
			voicePhaseAccumulator[voice->Number] += phaseAccumulation;
		}

		return val;
	}

}

void WaveTableIndex::Reset(Voice* voice)
{
	voicePhaseAccumulator[voice->Number] = PhaseOffset;
}

// WAVE TABLE

 WaveTable::WaveTable(long size, int tablesPerOctave)
{
	int numSubTables = tablesPerOctave ? (tablesPerOctave*8) : 1;
	TablesPerOctave = tablesPerOctave;
	Tables = new WaveTableSubTable[numSubTables];
	for(int i=0; i<numSubTables; i++)
	{
		Tables[i].FloatBuffer = new SampleBufferFloat(size+1);	// last pos in buffer is same as first
		//size/=2;
	}	
}

float WaveTable::Sample(long index)
{
	float val = Tables[0].FloatBuffer->Buffer[index].ch[0];
	return val;
}

// WAVE TABLE GENERATOR

void WaveTableGen::GenerateTables()
{
	WaveTable::NumWaveTables = 0;
	WaveTable::WaveTableOff = WaveTableGen::GenerateWaveTable(kWaveFormOff, "Off"); // 0 
	WaveTable::WaveTableSine = WaveTableGen::GenerateWaveTable(kWaveFormSin, "Sin"); // 1 
	WaveTable::WaveTableSaw = WaveTableGen::GenerateWaveTable(kWaveFormSaw, "Saw");	 // 2 
	WaveTable::WaveTableTri = WaveTableGen::GenerateWaveTable(kWaveFormTriangle, "Tri"); // 3 
	WaveTable::WaveTableSquare = WaveTableGen::GenerateWaveTable(kWaveFormSquare, "Square"); // 4
	WaveTable::WaveTableNoise = WaveTableGen::GenerateWaveTable(kWaveFormNoise, "Noise"); // 5
	//WaveTables_Tables->WaveTableNoise = WaveTableGen_GeneratePadWaveTable(WaveFormPadSynthExtended, "xx", 1.0, 2, 1.0, 20.0, 0.5, 8);

	WaveTable::Wavetables = new WaveTable*[100]; // up to 100 wavetables atm

	WaveTable::Wavetables[WaveTable::NumWaveTables++] = WaveTable::WaveTableOff;
	WaveTable::Wavetables[WaveTable::NumWaveTables++] = WaveTable::WaveTableSine;
	WaveTable::Wavetables[WaveTable::NumWaveTables++] = WaveTable::WaveTableSaw;	
	WaveTable::Wavetables[WaveTable::NumWaveTables++] = WaveTable::WaveTableTri;
	WaveTable::Wavetables[WaveTable::NumWaveTables++] = WaveTable::WaveTableSquare;
	WaveTable::Wavetables[WaveTable::NumWaveTables++] = WaveTable::WaveTableNoise;


	//WaveTables_Tables->WaveTablePadSynthChoir = WaveTableGen_GenerateWaveTable(WaveFormPadSynthChoir);
	//WaveTables_Tables->WaveTablePadSynthEnsemble = WaveTableGen_GenerateWaveTable(WaveFormPadSynthEnsemble);
	//WaveTables_Tables->WaveTablePadSynthEnsemble = WaveTableGen_GenerateWaveTable(WaveFormPadSynthExtended);
}


WaveTable* WaveTableGen::GenerateWaveTable(WaveForm waveForm, char* name)
{
	WaveTable *wt;

	// standard wavetable
	float fr = 0.1f;
	int phaseLen = (int)FloatToInt((Constants_SamplesPerSec) / fr);
	double time = 0;

	wt = new WaveTable(phaseLen + 1, 0);
	wt->Tables[0].Frequency = fr;
	wt->Form = waveForm;
#ifndef REPLAYER
	sprintf(wt->TableName, name);
#endif
	for (int i = 0; i < wt->Tables[0].FloatBuffer->Size - 2; i++)
	{
		float v = 0;
		switch(waveForm)
		{
		case(kWaveFormSin):
			{
				v = WaveFormGen::Sine(fr, &time, 1.0f);
				break;
			}

		case (kWaveFormSquare):
			{
				v = WaveFormGen::Square(fr, &time, 1.0f);
				break;
			}

		case (kWaveFormTriangle):
			{
				v = WaveFormGen::Triangle(fr, &time, 1.0f);
				break;
			}
		case (kWaveFormSaw):
			{
				v = WaveFormGen::Sawtooth(fr, &time, 1.0f);
				break;
			}
		case (kWaveFormNoise):
			{
				v = WaveFormGen::Noise(fr, &time, 1.0f);
				break;
			}
		}

		wt->Tables[0].FloatBuffer->Buffer[i].ch[0] = v;
		wt->Tables[0].FloatBuffer->Buffer[i].ch[1] = v;
	}
	

	wt->Tables[0].FloatBuffer->Buffer[ wt->Tables[0].FloatBuffer->Size - 1].ch[0] = wt->Tables[0].FloatBuffer->Buffer[0].ch[0];
	wt->Tables[0].FloatBuffer->Buffer[ wt->Tables[0].FloatBuffer->Size - 1].ch[1] = wt->Tables[0].FloatBuffer->Buffer[0].ch[1];
	return wt;
}


WaveTable* WaveTableGen::GeneratePadWaveTable(WaveForm waveForm, char* name, float amplitude, int npower, float formantScale, float bandWidth, float bandWidthScale, int tablesPerOctave)
{
	WaveTable *wt = 0;	

	if (waveForm == kWaveFormPadSynthChoir || waveForm == kWaveFormPadSynthEnsemble || waveForm == kWaveFormPadSynthExtended)
	{
		/*
		int tableSize = (int)pow(2.0,16.0); // 512kb
		double* vals = PadSynthBuildWaveTable(PadSynthTypeChoir, 1760, 1.0f, 1.0f, tableSize, true);
		DebugBreak();*/
		// padsynth choir wavetable
		
		int tableSize = (int)FloatToInt(pow(2.0f,16.0f)); // 512kb
		//int tableSize = (int)pow(2.0,22.0); // 512kb
		//wt = WaveTable_Create(tableSize + 1, false);
		wt = new WaveTable(tableSize + 1, tablesPerOctave);
		sprintf(wt->TableName, name);
		wt->Form = waveForm;

		wt->amplitude = amplitude;
		wt->npower = npower;		
		wt->formantScale = formantScale;
		wt->bandWidth = bandWidth;
		wt->bandWidthScale = bandWidthScale;
		wt->TablesPerOctave = tablesPerOctave;


		float freq = 27.5f; // A0		
		int midiNoteNum = 21; // A0
		for(int tab =0; tab<tablesPerOctave*8; tab++) // 8 octaves
		//for(int tab =0; tab<1; tab++) // 8 octaves
		{			
			//break;
			wt->Tables[tab].Frequency = freq;
			wt->Tables[tab].MidiNoteNumber = midiNoteNum;
			midiNoteNum+=(12/tablesPerOctave); // 12 semitones = 1 octave
			// NOTE: sample length for padsynth affects amplitude, smaller = higher amp!! need to cater for this
			PadSynthType padType;
			if (waveForm == kWaveFormPadSynthChoir)
			{
				padType = kPadSynthTypeChoir;
			}else if (waveForm == kWaveFormPadSynthEnsemble)
			{	
				padType = kPadSynthTypeEnsemble;
			}else if (waveForm == kWaveFormPadSynthExtended)
			{
				padType = kPadSynthTypeExtended;
			}
			REALTYPE* vals = PadSynth::PadSynthBuildWaveTable(padType, freq, amplitude, npower, formantScale, tableSize, true);
			for (int i = 0; i < wt->Tables[tab].FloatBuffer->Size - 1; i++)
			{
				float v = (float)vals[i];
				wt->Tables[tab].FloatBuffer->Buffer[i].ch[0] = v;
				wt->Tables[tab].FloatBuffer->Buffer[i].ch[0] = v;
			}
			freq=PitchUtils::instance->MidiNoteToFrequency(midiNoteNum); // double frequency (+1 octave)
			delete(vals);
		}		
	}

	wt->Tables[0].FloatBuffer->Buffer[ wt->Tables[0].FloatBuffer->Size - 1].ch[0] = wt->Tables[0].FloatBuffer->Buffer[0].ch[0];
	wt->Tables[0].FloatBuffer->Buffer[ wt->Tables[0].FloatBuffer->Size - 1].ch[1] = wt->Tables[0].FloatBuffer->Buffer[0].ch[1];
	return wt;
}
	
//const WaveTable* WaveTable::WaveTableSine = WaveTableGen::GenerateWaveTable(WaveFormSin);
//WaveTable::WaveTableSine = WaveTableGen::GenerateWaveTable(WaveFormSin);
