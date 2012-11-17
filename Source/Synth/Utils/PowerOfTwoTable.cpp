#include "PowerOfTwoTable.h"
#include "ZynthTools.h"
#include <math.h>

const int TableSize = 4096;
PowerOfTwoTable* PowerOfTwoTable::instance = 0;

PowerOfTwoTable::PowerOfTwoTable()
{
	int i;
	// Phase accumulator.
	double accumulator = 0;
	
	// Calculate phase increment.
	float increment = 1.0f / TableSize;

	Table = new float[TableSize];

	// Initialize lookup table.
	for (i = 0; i < TableSize; i++)
	{
		float val = (float)pow((double)2.0f, (double)accumulator);
		Table[i] = val;
		accumulator += increment;
	}
}

float PowerOfTwoTable::GetPower(float exponent)
{
	float result;

	if (exponent >= 0)
	{
		// If exponent is positive.

		// Get whole part of exponent.
		int whole = (int)exponent;

		// Get fractional part of exponent.
		double fractional = exponent - whole;

		// Get index into lookup table. Some form of interpolation
		// would help here, but with a large enough lookup table, the
		// results seem acceptable.
		int index = (int)(TableSize * fractional);

		if (index<0)
		{
			int xx=0;
		}

		// Calculate final result. 
		result = Table[index] * (1 << whole);
	}
	else
	{
		// Else exponent is negative.

		// Get whole part of exponent.
		int whole = (int)-exponent;

		// Get fractional part of exponent.
		double fractional = -exponent - whole;

		// Get index into lookup table. Some form of interpolation
		// would help here, but with a large enough lookup table, the
		// results seem acceptable.
		int index = (int)(TableSize * fractional);

		if (index<0)
		{
			int xx=0;
		}

		// Calculate final result - divide 1 by result since exponent is negative. 
		result = 1.0f / (Table[index] * (1 << whole));
	}

	return result;
}
