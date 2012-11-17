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

void ModulationMatrix::SetSource(int row, int itemType, int itemNumber, int paramNumber)
{
	ModulationMatrixItem* matrixItem = &Rows[row].ItemSource;
	matrixItem->itemNumber = itemNumber;
	matrixItem->ItemType = (StackItemType)itemType;
	matrixItem->ParamNumber = -1;
	matrixItem->ParentRow = &Rows[row];
	matrixItem->ParentRow->SourceSet = true;

	/* TODO
	switch((StackItemType)itemType)
	{
	case (kStackItemTypeWfOsc):
		{
			matrixItem->Item = patch->Oscs[itemNumber]._item;
			break;
		}

	case (kStackItemTypeLfoAllVoices):
		{
			matrixItem->Item = patch->LfosAv[itemNumber]._item;
			break;
		}

	case (kStackItemTypeLfoPerVoice):
		{
			matrixItem->Item = patch->LfosPv[itemNumber]._item;
			break;
		}

	case (kStackItemTypeEnvAdsr):
		{
			matrixItem->Item = patch->EnvAdsr[itemNumber]._item;
			break;
		}

	case (kStackItemTypeAmpEg):
		{
			matrixItem->Item = patch->EnvAmp->_item;
			break;
		}

	case (kStackItemTypePitchEg):
		{
			matrixItem->Item = patch->EnvPitch->_item;
			break;
		}
	}*/

	Changed = true;
}

void ModulationMatrix::SetDest(int row, int itemType, int itemNumber, int paramNumber)
{

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
