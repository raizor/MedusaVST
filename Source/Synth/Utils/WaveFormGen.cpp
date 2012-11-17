#include "WaveFormGen.h"
#include "../Constants.h"
#include "ZynthTools.h"
#include <math.h>

static int seed = 0;

float WaveFormGen::Sine(float frequency, double* time, float speed)
{
	double fv = (frequency * 2 * Constants_Pi);
	double ss = (fv / 44100);
	double val = *time += (ss * speed);
	//double sv = sin(val);
	double sv = (double)msys_sinf((float)val);
	float fvv = (float)sv;
	return fvv;
}

float WaveFormGen::Square(float frequency, double* time, float speed)
{
    return WaveFormGen::Sine(frequency, time, speed) >= 0 ? 1.0f : -1.0f;
}

float WaveFormGen::Sawtooth(float frequency, double* time, float speed)
{
    float val = (float)(2 * (*time * frequency - msys_ifloorf((float)(*time * frequency + 0.5f))));
    *time += Constants_TimeIncrement;
    return val;
}

float WaveFormGen::Triangle(float frequency, double* time, float speed)
{
    return fabs(WaveFormGen::Sawtooth(frequency, time, 1.0)) * 2.0f - 1.0f;
}


float WaveFormGen::Noise(float frequency, double* time, float speed)
{
	float val = -1.0f + (msys_frand(&seed)*2.0f);
	*time += Constants_TimeIncrement;
	return val;
}


