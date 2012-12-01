#pragma once

#include "../Constants.h"
#include "Voice.h"
#include "SampleBufferFloat.h"
#include "WaveFormGen.h"
#include "WaveTableGen.h"


class WaveTables;

class WaveTableSubTable
{
public:
	float Frequency;
	int MidiNoteNumber;
	SampleBufferFloat* FloatBuffer;
};

// *** wave table
class WaveTable 
{	
public:
	// standard wavetables
	static WaveTable* WaveTableOff;
	static WaveTable* WaveTableSine;
	static WaveTable* WaveTableSaw;
	static WaveTable* WaveTableTri;
	static WaveTable* WaveTableSquare;
	static WaveTable* WaveTableNoise; 
	// custom wavetables
	static WaveTable** Wavetables;
	static int NumWaveTables;

	WaveTableSubTable* Tables;
	int TablesPerOctave;
#ifndef REPLAYER
	char TableName[100];
#endif
	WaveForm Form;
	
	// stuff to re-gen
	float amplitude;
	int npower;
	float formantScale;
	float bandWidth;
	float bandWidthScale;

	WaveTable(long size, int tablesPerOctave);
	float Sample(long index);
};

// *** wave table index

class WaveTableIndex 
{
public:
	WaveTable *Table;
	float Phase;
	float PhaseOffset;
	double *voicePhaseAccumulator; // new double[Constants.Polyphony];		

	WaveTableIndex(WaveTable* waveTable);
	void SetWaveTable(WaveTable* waveTable);
	float Sample(Voice* voice, float frequency, bool* syncHit);
	void CalcPhaseOffset();
	void Reset(Voice* voice);
};

class WaveTableGen
{
public:
	static void GenerateTables();
	static WaveTable* GenerateWaveTable(WaveForm waveForm, char* name);
	static WaveTable* GeneratePadWaveTable(WaveForm waveForm, char* name, float amplitude, int npower, float formantScale, float bandWidth, float bandWidthScale, int numOctaves);
};
