#pragma once

class PowerOfTwoTable
{
public:
	static PowerOfTwoTable* instance; 
	float* Table;
	PowerOfTwoTable();
	~PowerOfTwoTable();
	float GetPower(float exponent);
};



