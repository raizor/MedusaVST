#include "PadSynth.h"
#include "../ZynthTools.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

REALTYPE PadSynth::_amplitude = 0;
REALTYPE PadSynth::_frequency = 0;
REALTYPE PadSynth::_metallicAmount= 0 ;
int PadSynth::_nPower = 0;
REALTYPE PadSynth::_fScaleFormants = 0;

REALTYPE* PadSynth::imgData = 0;
REALTYPE* PadSynth::realData = 0;
REALTYPE* PadSynth::freq_amp = 0;
sU32 PadSynth::_numSamples = 0;
REALTYPE PadSynth::A [NUM_HARMONICS];

// FFT/IFFT
void PadSynth::fft_double(REALTYPE* p_lpRealIn, REALTYPE* p_lpImagIn, REALTYPE* p_lpRealOut, REALTYPE* p_lpImagOut, bool p_bInverseTransform)
{
	if (p_lpRealIn == NULL) return;

	sU32 NumBits;
	sU32 i, j, k, n;
	sU32 BlockSize, BlockEnd;

	REALTYPE angle_numerator = 2.0f * PI;
	REALTYPE tr, ti;
#ifdef _DEBUG
	if (!isPowerOfTwo(_numSamples))
	{
		DebugBreak();
	}
#endif

	if (p_bInverseTransform) angle_numerator = -angle_numerator;

	NumBits = numberOfBitsNeeded(_numSamples);

	for (i = 0; i < _numSamples; i++)
	{
		j = ReverseBits(i, NumBits);
		p_lpRealOut[j] = p_lpRealIn[i];
		p_lpImagOut[j] = (p_lpImagIn == NULL) ? 0.0f : p_lpImagIn[i];
	}

	BlockEnd = 1;
	REALTYPE* ar = new REALTYPE[3];
	REALTYPE* ai = new REALTYPE[3];
	for (BlockSize = 2; BlockSize <= _numSamples; BlockSize <<= 1)
	{
		REALTYPE delta_angle = angle_numerator / (REALTYPE)BlockSize;
		REALTYPE sm2 = (REALTYPE)sin(-2 * delta_angle);
		REALTYPE sm1 = (REALTYPE)sin(-delta_angle);
		REALTYPE cm2 = (REALTYPE)cos(-2 * delta_angle);
		REALTYPE cm1 = (REALTYPE)cos(-delta_angle);
		REALTYPE w = 2 * cm1;

		for (i = 0; i < _numSamples; i += BlockSize)
		{
			ar[2] = cm2;
			ar[1] = cm1;

			ai[2] = sm2;
			ai[1] = sm1;

			for (j = i, n = 0; n < BlockEnd; j++, n++)
			{
				ar[0] = w * ar[1] - ar[2];
				ar[2] = ar[1];
				ar[1] = ar[0];

				ai[0] = w * ai[1] - ai[2];
				ai[2] = ai[1];
				ai[1] = ai[0];

				k = j + BlockEnd;
				tr = ar[0] * p_lpRealOut[k] - ai[0] * p_lpImagOut[k];
				ti = ar[0] * p_lpImagOut[k] + ai[0] * p_lpRealOut[k];

				p_lpRealOut[k] = p_lpRealOut[j] - tr;
				p_lpImagOut[k] = p_lpImagOut[j] - ti;

				p_lpRealOut[j] += tr;
				p_lpImagOut[j] += ti;
			}
		}

		BlockEnd = BlockSize;
	}

	if (p_bInverseTransform)
	{
		REALTYPE denom = (REALTYPE)_numSamples;

		for (i = 0; i < _numSamples; i++)
		{
			p_lpRealOut[i] /= denom;
			p_lpImagOut[i] /= denom;
		}
	}
}

// Simple normalization function. It normalizes the sound to 1/sqrt(2)
void PadSynth::normalize(REALTYPE *smp)
{
    REALTYPE max=0.0;
    for (sU32 i=0; i<_numSamples; i++) 
	{
		if (fabs(smp[i])>max)
		{
			max=fabs(smp[i]);
		}
	}
    if (max<1e-5f)
	{
		max=1e-5f;
	}
    for (sU32 i=0; i<_numSamples; i++) 
	{
		smp[i]/=max*1.4142f;
	}
};

// Perform IFFT
void PadSynth::RawFrequencyToSamples(REALTYPE* samples, REALTYPE* freqReal, REALTYPE* freqImag)
{
	REALTYPE* tmpImage = new REALTYPE[_numSamples];
	fft_double(freqReal, freqImag, samples, tmpImage, true);
	// normalize
	normalize(samples);
	delete(tmpImage);
}

// Get the frequency of the nth harmonic. Can be overridden to create metallic effects.
REALTYPE PadSynth::getHarmonicFrequency(PadSynthType synthType, int nHarmonic)
{
	switch (synthType)
	{
		case (kPadSynthTypeExtended):
			{
				return _frequency * nHarmonic * (nHarmonic * _metallicAmount + 1.0f); 
			}
		default: // choir or ensemble
			{
				return nHarmonic * _frequency;
			}
	}	
}

// Get the bandwidth of the nth harmonic (the width of the distribution).
REALTYPE PadSynth::getBandwidthInHertz(PadSynthType synthType, int nHarmonic)
{
	switch (synthType)
	{
		case (kPadSynthTypeEnsemble):
			{
				const REALTYPE baseBandwidth =40.0f;
				return (REALTYPE)(zt_pow((REALTYPE)2.0f, baseBandwidth / 1200.0f) - 1.0f) * getHarmonicFrequency(synthType, nHarmonic);
			}

		case (kPadSynthTypeChoir):
			{
				const REALTYPE baseBandwidth = 60.0f;
				return (REALTYPE)(zt_pow((REALTYPE)2.0f, baseBandwidth / 1200.0f) - 1.0f) * getHarmonicFrequency(synthType, nHarmonic);
			}

		case (kPadSynthTypeExtended):
			{
				const REALTYPE baseBandwidth = 20.0f;
				const REALTYPE bandwidthScale = 0.5f;
				return (REALTYPE)_frequency * (zt_pow((REALTYPE)2.0f, baseBandwidth / 1200.0f) - 1.0f) * zt_pow(getHarmonicFrequency(synthType, nHarmonic) / _frequency, bandwidthScale);
			}
	}
	return 0;
}

// Get harmonic weights for synthesis type
REALTYPE* PadSynth::GetHarmonicWeights(PadSynthType synthType)
{
	REALTYPE f1 = _frequency * _fScaleFormants; // 1/16 ~ strings
	REALTYPE formantParameters[5][3] = { 
		// freq, width, height
		{ 600.0f, 1.0f/150.0f, 1.0f},
		{ 900.0f, 1.0f/250.0f, 1.0f}, 
		{ 2200.0f, 1.0f/200.0f, 1.0f}, 
		{ 2600.0f, 1.0f/250.0f, 1.0f},
		{ 0, 1.0f/3000.0, 0.1f }
	};

	switch (synthType)
	{
	case (kPadSynthTypeChoir):
		{
			for (int i = 1; i < NUM_HARMONICS; i++)
			{
				REALTYPE weight = 0.0;

				for (int j = 0; j < 5; j++)
				{
					weight += exp(-zt_pow((i * f1 - formantParameters[j][0]) * formantParameters[j][1], (REALTYPE)2.0f)) * formantParameters[j][2];
				}

				A[i] = (1.0f / (REALTYPE)i) * weight;
			}
			break;
		}
	case(kPadSynthTypeEnsemble):
		{
			for (int i = 1; i < NUM_HARMONICS; i++)
			{
				A[i] = 1.0f / ((REALTYPE)i * i);
				if (i % 2 == 0) 
				{
					A[i] *= 2;
				}
			}
			break;
		}
	case(kPadSynthTypeExtended):
		{
			for (int i = 1; i < NUM_HARMONICS; i++)
			{
				// A[i] = 1.0 / ((double)i);
				A[i] = 1.0f / zt_pow((REALTYPE)i, (REALTYPE)_nPower);
			}
			break;
		}
	}
	return A;
}

// This is the profile of one harmonic. In this case is a Gaussian distribution, e^(-x^2) 
REALTYPE PadSynth::profile(REALTYPE fi, REALTYPE bandwidth)
{
	REALTYPE x = fi / bandwidth; // The amplitude is divided by the bandwidth to ensure that the harmonic keeps the same amplitude regardless of the bandwidth
	x *= x;
	return (x > 14.7128f) ? 0.0f : exp(-x) / bandwidth; //avoid computing e^(-x^2) where results are very close to zero
}

// Create array in frequency. We smooth out peaks with Gaussian dist.
REALTYPE* PadSynth::BuildArrayInFrequency(PadSynthType synthType)
{
	GetHarmonicWeights(synthType);

	//NOTE: only the first half of this is filled, because the second half is negative frequencies that are only important for a complex signal

	//for each harmonic, add to the array.
	for (sU32 i = 0; i < _numSamples; i++)
	{
		freq_amp[i]=0;
	}
	for (sU32 nHarmonic = 1; nHarmonic < NUM_HARMONICS; nHarmonic++)
	{
		//bandwidth of the current harmonic measured in Hz
		//note that this is wider for each harmonic
		REALTYPE bw_Hz = getBandwidthInHertz(synthType, nHarmonic);

		REALTYPE bwi = bw_Hz / (2.0f * sampleRate);
		REALTYPE fi = getHarmonicFrequency(synthType, nHarmonic) / (REALTYPE)sampleRate;
		for (sU32 i = 0; i < _numSamples / 2; i++)
		{
			REALTYPE hprofile = profile((i / (REALTYPE)_numSamples) - fi, bwi);
			freq_amp[i] += hprofile * A[nHarmonic];
		}
	}
	return freq_amp;
}

REALTYPE* PadSynth::PadSynthBuildWaveTable(PadSynthType synthType, REALTYPE frequency, REALTYPE amplitude, int npower, REALTYPE fScaleFormants, int numSamples, bool dump)
{
	_amplitude = amplitude;
	_frequency = frequency;
	_numSamples = numSamples;
	_nPower = npower;
	_fScaleFormants = fScaleFormants;
	REALTYPE* outSamples = new REALTYPE[_numSamples];
	imgData = new REALTYPE[_numSamples];
	realData = new REALTYPE[_numSamples];
	freq_amp = new REALTYPE[_numSamples];
	memset(outSamples, 0, sizeof(REALTYPE) * _numSamples);
	memset(imgData, 0, sizeof(REALTYPE) * _numSamples);
	memset(realData, 0, sizeof(REALTYPE) * _numSamples);
	memset(freq_amp, 0, sizeof(REALTYPE) * _numSamples);
	
	// this array contains amplitudes, indices correspond to frequencies
	REALTYPE* arrayInFrequency = BuildArrayInFrequency(synthType);

	// calculate magic amp boost as amplitude drops off as numSamples increases
	REALTYPE ampBoost = _amplitude * (REALTYPE)(zt_pow((REALTYPE)2.0f, (REALTYPE)20.0f) / _numSamples);
	srand(0);
	// create real and img. parts, using random phases
	for (sU32 i = 0; i < _numSamples; i++)
	{
		REALTYPE phase = RND_0_1() * 2.0f * (REALTYPE)PI;
		realData[i] = arrayInFrequency[i] * (REALTYPE)cos(phase) * ampBoost;
		imgData[i] = arrayInFrequency[i] * (REALTYPE)sin(phase) * ampBoost;
	}

	// perform IFFT, mono samples written to [outSamples]
	RawFrequencyToSamples(outSamples, realData, imgData);

	delete(imgData);
	delete(realData);
	delete(freq_amp);

#ifdef _DEBUG
	/*
	// save wavetable
	if (dump)
	{
		char fname[100];
		sprintf(fname, "g:/temp/_wt%.1f_%d_c.raw", frequency, numSamples);
		FILE *fp = fopen( fname, "wb+" );
		fwrite(outSamples, numSamples, sizeof(double), fp);
		if( !fp )
		{
			DebugBreak();
		}
		fclose(fp);
	}*/
	
#endif

	return outSamples;
}

