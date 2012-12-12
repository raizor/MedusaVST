
#include "../../../Utils/Patch.h"
#include "ModulationMatrix.h"

// ROW

ModulationMatrixRow::ModulationMatrixRow()
{
}

// ITEM

ModulationMatrixItem::ModulationMatrixItem()
{
	Item = 0;
	Param = 0;
	ParentRow = 0;
}

// MATRIX

ModulationMatrix::ModulationMatrix(Patch* patch)
{
	this->patch = patch;
	Rows = new ModulationMatrixRow*[ModulationMatrixNumRows];
	//this->v = new void*[ModulationMatrixNumRows];

	for(int i=0; i<ModulationMatrixNumRows; i++)
	{
		Rows[i] = new ModulationMatrixRow();
		Rows[i]->ItemSource = new ModulationMatrixItem();
		Rows[i]->ItemDest = new ModulationMatrixItem();
		// TODO: change according to modulator type: eg = mult, lfo = plus etc
		Rows[i]->RowNum = i;
		Rows[i]->SourceSet = false;		
		Rows[i]->Curve = kModulationCurveNone;
		Rows[i]->DestSet = false;
	}
	Changed = false;
}

ModulationMatrix::~ModulationMatrix()
{
}

void ModulationMatrix::SetSource(int row, Item* item)
{
	ModulationMatrixItem* matrixItem = Rows[row]->ItemSource;
	matrixItem->Item = item;
	matrixItem->ParentRow = Rows[row];
	matrixItem->ParentRow->SourceSet = true;
	
	Changed = true;
}

void ModulationMatrix::SetDest(int row, Item* item, ParamFloat* param)
{
	ModulationMatrixItem* matrixItem = Rows[row]->ItemDest;
	matrixItem->Item = item;
	matrixItem->Param = param;
	matrixItem->ParentRow = Rows[row];
	matrixItem->ParentRow->DestSet = true;

	Changed = true;
}

void ModulationMatrix::SetCurve(int row, int curve)
{
	Rows[0]->Curve = (ModulationCurve)curve;
}

void ModulationMatrix::HandleItem(Item* item)
{
	for(int i=0; i<item->numParamsFloat; i++)
	{
		ParamFloat* param = item->paramsFloat[i];
		// clear count
		param->ModList->Count = 0;

		// check each matrix row
		for(int j=0; j<Constants_MaxModulations; j++)
		{
			ModulationMatrixRow* row = Rows[j];
			// row has a valid source and dest?
			if (row->SourceSet && row->DestSet)
			{
				Item* siItem = row->ItemDest->Item;
				if (siItem == item && row->ItemDest->Param == param)
				{
					// store ref to tempbuffer of modulator stack item (source item)
					Item* sourceItem = row->ItemSource->Item;
					if (sourceItem->enabled)
					{
						Modulator* mod = &param->ModList->Modulators[param->ModList->Count];
						mod->Type = sourceItem->type;
						mod->Curve = row->Curve;
						mod->ModBuffer = sourceItem->buffer;			
						param->ModList->Count++;
					}						
				}
			}
		}
	}
}

void ModulationMatrix::HandleChanges()
{
	Changed = false; // set flag to indicate handled

	// update linked params	

	// oscs
	for(int i=NUMBER_START_OSC; i<NUMBER_START_OSC+Constants_NumOscillators; i++)
	{
		HandleItem(patch->items[i]);
	}

	// egs
	HandleItem((Item*)patch->egAmp);
	HandleItem((Item*)patch->egPitch);

	for(int i=NUMBER_START_EG; i<NUMBER_START_EG+Constants_NumEnvelopes; i++)
	{
		HandleItem(patch->items[i]);
	}

	// lfos
	for(int i=NUMBER_START_LFO_AV; i<NUMBER_START_LFO_AV+Constants_NumLfoAllVoices; i++)
	{
		HandleItem(patch->items[i]);
	}

	for(int i=NUMBER_START_LFO_PV; i<NUMBER_START_LFO_PV+Constants_NumLfoPerVoice; i++)
	{
		HandleItem(patch->items[i]);
	}

	// filters
	for(int i=NUMBER_START_FILTER; i<NUMBER_START_FILTER+Constants_NumFilters; i++)
	{
		HandleItem(patch->items[i]);
	}
}

