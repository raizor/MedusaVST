#pragma once
#include "../../Constants.h"

#define REALTYPE double // data format (use double, float is a bugged atm)
#define DUMP_TABLES // dump the wavetables to disk?
#define NUM_HARMONICS 64 // number of harmonics per wavetable
//#define memset zt_memset // memset func pointer
#define sampleRate Constants_SamplesPerSec // samples per sec, 44100 usually
#define PI Constants_Pi // PI 

class PadSynth
{
private:
	static REALTYPE _amplitude;
	static REALTYPE _frequency;
	static REALTYPE _metallicAmount;
	static int _nPower;
	static REALTYPE _fScaleFormants;

	static REALTYPE* imgData;
	static REALTYPE* realData;
	static REALTYPE* freq_amp;
	static REALTYPE A [NUM_HARMONICS]; //note that A[0] is unused
	static sU32 _numSamples;

	static void PadSynth::fft_double(REALTYPE* p_lpRealIn, REALTYPE* p_lpImagIn, REALTYPE* p_lpRealOut, REALTYPE* p_lpImagOut, bool p_bInverseTransform);
	static void PadSynth::normalize(REALTYPE *smp);
	static void PadSynth::RawFrequencyToSamples(REALTYPE* samples, REALTYPE* freqReal, REALTYPE* freqImag);
	static REALTYPE PadSynth::getHarmonicFrequency(PadSynthType synthType, int nHarmonic);
	static REALTYPE PadSynth::getBandwidthInHertz(PadSynthType synthType, int nHarmonic);
	static REALTYPE* PadSynth::GetHarmonicWeights(PadSynthType synthType);
	static REALTYPE PadSynth::profile(REALTYPE fi, REALTYPE bandwidth);
	static REALTYPE* PadSynth::BuildArrayInFrequency(PadSynthType synthType);

public:
	static REALTYPE* PadSynthBuildWaveTable(PadSynthType synthType, REALTYPE frequency, REALTYPE amplitude, int npower, REALTYPE fScaleFormants, int numSamples, bool dump);


};


