#pragma once

class WaveFormGen
{
public:
	static float Sine(float frequency, double* time, float speed);
	static float Square(float frequency, double* time, float speed);
	static float Sawtooth(float frequency, double* time, float speed);
	static float Triangle(float frequency, double* time, float speed);
	static float Noise(float frequency, double* time, float speed);
};



