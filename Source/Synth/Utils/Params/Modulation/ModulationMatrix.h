#pragma once

#include "../../../Constants.h"
#include "../../ZynthTools.h"

#define ModulationMatrixNumRows 16

class ParamFloat;
class Item;
class Patch;
class Voice;
class ModulationMatrixRow;
class FloatStackItemParam;

class ModulationRange
{
public:
	float start;
	float end;
};

class ModulationMatrixItem
{
public:
	Item* Item;
	int itemNumber;
	int ParamNumber;
	StackItemType ItemType;
	ParamFloat* Param;
	ModulationMatrixRow* ParentRow;
};

class ModulationMatrixRow
{
public:
	int RowNum;
	ModulationRange Range;
	ModulationMatrixItem ItemSource;
	ModulationMatrixItem ItemDest;
	ModulationCurve Curve;
	bool SourceSet;
	bool DestSet;
};

class ModulationMatrix 
{
public:
	Patch* patch;
	ModulationMatrixRow Rows[ModulationMatrixNumRows];		
	int RowCount;
	bool Changed;

	ModulationMatrix(Patch* patch);
	~ModulationMatrix();

	void SetSource(int row, int itemType, int itemNumber, int paramNumber);
	void SetDest(int row, int itemType, int itemNumber, int paramNumber);
	void SetCurve(int row, int curve);
	void HandleChanges();
	void HandleDestItemChanges(Item* item);
};