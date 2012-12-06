#include "ModulationMatrix.h"
#include "../ParamFloat.h"
#include "../../../Items/Item.h"
#include "../../../Utils/Patch.h"

ModulationMatrix::ModulationMatrix(Patch* patch)
{
	this->patch = patch;
	for(int i=0; i<ModulationMatrixNumRows; i++)
	{
		// TODO: change according to modulator type: eg = mult, lfo = plus etc
		Rows[i].RowNum = i;
		Rows[i].SourceSet = false;		
		Rows[i].Curve = kModulationCurveMultUnipolarPlus;
		Rows[i].DestSet = false;
	}
	Changed = false;
	for(int i=0; i<ModulationMatrixNumRows; i++)
	{
		Rows[i].ItemDest;
	}	
	
}

ModulationMatrix::~ModulationMatrix()
{
}

void ModulationMatrix::SetSource(int row, Item* item)
{
	ModulationMatrixItem* matrixItem = &Rows[row].ItemSource;
	matrixItem->Item = item;
	matrixItem->ParentRow = &Rows[row];
	matrixItem->ParentRow->SourceSet = true;
	
	Changed = true;
}

void ModulationMatrix::SetDest(int row, Item* item, ParamFloat* param)
{
	ModulationMatrixItem* matrixItem = &Rows[row].ItemSource;
	matrixItem->Item = item;
	matrixItem->Param = param;
	matrixItem->ParentRow = &Rows[row];
	matrixItem->ParentRow->SourceSet = true;

	Changed = true;
}

void ModulationMatrix::SetCurve(int row, int curve)
{

}

void ModulationMatrix::HandleChanges()
{

}

void ModulationMatrix::HandleDestItemChanges(Item* item)
{

}
