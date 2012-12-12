#include "Distort.h"


Distort::Distort(void): ItemProcessor(kStackItemTypeDistortion, true)
{
}

void Distort::Process(SampleBufferFloat* bufferIn, SampleBufferFloat* bufferOut, Voice* voice, int numSamples)
{
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni, true)); // gain 
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni, true)); // amount1 
	AddFloatParam(new ParamFloat(0.0f, true, 1.0f, 0.5f, kParamValueTypeZeroToOneUni, true)); // amount2 
}


Distort::~Distort(void)
{
}

// Fast arctangent
sF32 Distort::fastatan(sF32 x)
{
	// extract sign
	sF32 sign = 1.0f;
	if (x < 0.0f)
	{
		sign = -1.0f;
		x = -x;
	}

	// we have two rational approximations: one for |x| < 1.0 and one for
	// |x| >= 1.0, both of the general form
	//   r(x) = (cx1*x + cx3*x^3) / (cxm0 + cxm2*x^2 + cxm4*x^4) + bias
	// original V2 code uses doubles here but frankly the coefficients
	// just aren't accurate enough to warrant it :)
	static const sF32 coeffs[2][6] = {
		//          cx1          cx3         cxm0         cxm2         cxm4         bias
		{          1.0f, 0.43157974f,        1.0f, 0.05831938f, 0.76443945f,        0.0f },
		{ -0.431597974f,       -1.0f, 0.05831938f,        1.0f, 0.76443945f, 1.57079633f },
	};
	const sF32 *c = coeffs[x >= 1.0f]; // interestingly enough, V2 code does this test wrong (cmovge instead of cmovae)
	sF32 x2 = x*x;
	sF32 r = (c[1]*x2 + c[0])*x / ((c[4]*x2 + c[3])*x2 + c[2]) + c[5];
	return r * sign;
}
