#include "FileIo.h"
#include "Synth.h"
#include "Constants.h"
#include "Writer.h"
#include <windows.h>
#include <stdarg.h>
#include "Utils/Patch.h"
#include "Items/Item.h"
#include "Utils/VoicePool.h"
#include "Utils/Params/Modulation/ModulationMatrix.h"
#include "Utils/Params/ParamFloat.h"
#include "Items/Processors/Osc.h";
#include "Items/Processors/Lfo.h";
#include "Items/Processors/Adsr.h";
#include "Items/Processors/Distort.h";
#include "Items/Processors/Boost.h";
#include "Items/Processors/ChorusFlange.h";
#include "Items/Processors/SimpleFilter.h";
#include "Items/Processors/Delay and Reverb/ModDelay.h";
#include "Items/Processors/Delay and Reverb/Reverb.h";
#include "Utils/WaveTableGen.h"

void ZynthIo::read(void* data, int size, int count, FILE *fp, Writer* writer, bool useFile)
{
	if (useFile)
	{
		fread(data, size, count, fp);
	}else{
		writer->Read(data, size, count);
	}
}

void ZynthIo::write(void* data, int size, int count, FILE *fp, Writer* writer, bool useFile)
{
	if (useFile)
	{
		fwrite(data, size, count, fp);
	}else{
		writer->Write(data, size, count);
	}
}

void ZynthIo::SaveParam(void* item, ParamType paramType, FILE *fp, Writer* writer, bool useFile)
{
	switch(paramType)
	{
	case (kParamTypeFloat):
		{
			ParamFloat* param =  (ParamFloat*)item;
			float val = param->ValueAsInt();
			write(&val, sizeof(int), 1, fp, writer, useFile);
			break;
		}
	case (kParamTypeInt):
		{
			ParamInt* param =  (ParamInt*)item;
			write(param->_value, sizeof(int), 1, fp, writer, useFile);
			break;
		}
	case (kParamTypeBool):
		{
			ParamBool* param =  (ParamBool*)item;
			write(param->_value, sizeof(bool), 1, fp, writer, useFile);
			break;
		}
	default:
		{
			int xxx =1;
		}
	}
}

// 
// Save stack item params to a file - used for patch/bank saving
//
void ZynthIo::SaveParams(Item* item, FILE *fp, Writer* writer, bool useFile)
{
	int is = sizeof(int);
	int bs = sizeof(bool);
	write(&item->enabled, sizeof(bool), 1, fp, writer, useFile);		
	write(&item->numParamsFloat, 1, sizeof(int), fp, writer, useFile);
	// param list count	
	for(int i=0; i<item->numParamsFloat; i++)
	{
		SaveParam(item->paramsFloat[i], item->paramsFloat[i]->type, fp, writer, useFile);
	}

	write(&item->numParamsInt, 1, sizeof(int), fp, writer, useFile);
	// param list count	
	for(int i=0; i<item->numParamsInt; i++)
	{
		SaveParam(item->paramsInt[i], item->paramsInt[i]->type, fp, writer, useFile);
	}

	write(&item->numParamsBool, 1, sizeof(int), fp, writer, useFile);
	// param list count	
	for(int i=0; i<item->numParamsBool; i++)
	{
		SaveParam(item->paramsBool[i], item->paramsBool[i]->type, fp, writer, useFile);
	}
}

void ZynthIo::LoadParam(void* item, ParamType paramType, FILE *fp, Writer* writer, bool useFile)
{
	switch(paramType)
	{
	case (kParamTypeFloat):
		{
			ParamFloat* param =  (ParamFloat*)item;
			float p = param->ValueAsInt();
			read(&p, sizeof(int), 1, fp, writer, useFile);
			param->SetValueWithInt(p);
			break;
		}
	case (kParamTypeInt):
		{
			ParamInt* param =  (ParamInt*)item;
			read(param->_value, sizeof(int), 1, fp, writer, useFile);
			break;
		}
	case (kParamTypeBool):
		{
			ParamBool* param =  (ParamBool*)item;
			read(param->_value, sizeof(bool), 1, fp, writer, useFile);
			break;
		}
	default:
		{
			DebugBreak;
		}
	}
}

// 
// Load stack item params from a file - used for patch/bank loading
// 
void ZynthIo::LoadParams(Item* item, FILE *fp, Writer* writer, bool useFile)
{
	bool itemEnabled = false;
	read(&itemEnabled, sizeof(bool), 1, fp, writer, useFile);
	item->enabled = itemEnabled;


	// param list size
	int count;
	// floats
	read(&count, sizeof(int), 1, fp, writer, useFile);
	for(int i=0; i<count; i++)
	{
		LoadParam(item->paramsFloat[i], kParamTypeFloat, fp, writer, useFile);
	}
	// ints
	read(&count, sizeof(int), 1, fp, writer, useFile);
	for(int i=0; i<count; i++)
	{
		LoadParam(item->paramsInt[i], kParamTypeInt, fp, writer, useFile);
	}

	// bools
	read(&count, sizeof(int), 1, fp, writer, useFile);
	for(int i=0; i<count; i++)
	{
		LoadParam(item->paramsBool[i], kParamTypeBool, fp, writer, useFile);
	}
}

void ZynthIo::WriteBool(bool val, FILE *fp, Writer* writer, bool useFile)
{
	write(&val, sizeof(bool),1, fp, writer, useFile);
}

void ZynthIo::WriteInt(int val, FILE *fp, Writer* writer, bool useFile)
{
	write(&val, sizeof(int),1, fp, writer, useFile);
}

bool ZynthIo::ReadBool(FILE *fp, Writer* writer, bool useFile)
{
	bool b;
	read(&b, sizeof(bool), 1, fp, writer, useFile);
	return b;
}

int ZynthIo::ReadInt(FILE *fp, Writer* writer, bool useFile)
{
	int b;
	read(&b, sizeof(int), 1, fp, writer, useFile);
	return b;
}

float ZynthIo::ReadFloat(FILE *fp, Writer* writer, bool useFile)
{
	float b;
	read(&b, sizeof(float), 1, fp, writer, useFile);
	return b;
}

void ZynthIo::LoadBankFromFile(char* loadPath)
{
	FILE *fp;
	fp = fopen( loadPath, "r" );
	if( !fp )
	{
		DebugBreak();
	}

	LoadBank(fp, 0, true);

	fclose( fp );
}

void ZynthIo::LoadBankFromMem(unsigned char* mem)
{
	Writer *writer = new Writer(mem);
	LoadBank(0, writer, false);
}

// 
// load bank
// 
void ZynthIo::LoadBank(FILE* fp, Writer *writer, bool useFile)
{
	char header[7];
	read(header, 7, 1, fp, writer, useFile);
	if (strcmp("medusa", header) != 0)
	{
		DebugBreak();
	}
	byte ver;
	read(&ver, sizeof(byte),1, fp, writer, useFile);

	int numPatches = 0;

	if (ver > 0)
	{		
		// num patches
		read(&numPatches, sizeof(int), 1, fp, writer, useFile);
	}

	// global delay
	LoadParams(VoicePool::Pool->GlobalDelay, fp, writer, useFile);

	// global reverb
	LoadParams(VoicePool::Pool->GlobalReverb, fp, writer, useFile);

	for(int i=0; i<numPatches; i++)
	{
		Patch* patch = PatchList::list->patches[i];

		// load patch name
		read(patch->name, sizeof(char)*100, 1, fp, writer, useFile);

		// filter mode
		int filtMode = ReadInt(fp, writer, useFile);
		patch->FilterProcMode->SetValue(filtMode);

		// load oscillators	
		int num = Constants_NumOscillators;
		read(&num, sizeof(int), 1, fp, writer, useFile);
		for(int j=0; j<Constants_NumOscillators; j++)
		{
			Osc* oobj = (Osc*)patch->items[NUMBER_START_OSC+j];
			LoadParams(oobj, fp, writer, useFile);
		}

		// load lfo av	
		num = Constants_NumLfoAllVoices;
		read(&num, sizeof(int), 1, fp, writer, useFile);
		for(int j=0; j<Constants_NumLfoAllVoices; j++)
		{
			Lfo* laobj = (Lfo*)patch->items[NUMBER_START_LFO_AV+j];
			LoadParams(laobj, fp, writer, useFile);
		}

		// load lfo pv	
		num = Constants_NumLfoPerVoice;
		read(&num, sizeof(int), 1, fp, writer, useFile);
		for(int j=0; j<Constants_NumLfoPerVoice; j++)
		{
			Lfo* pvobj = (Lfo*)patch->items[NUMBER_START_LFO_PV+j];
			LoadParams(pvobj, fp, writer, useFile);
		}

		// amp eg
		Adsr* a1obj = patch->egAmp;
		LoadParams(a1obj, fp, writer, useFile);

		// pitch eg
		Adsr* a2obj = patch->egPitch;
		LoadParams(a2obj, fp, writer, useFile);

		// egs	
		num = Constants_NumEnvelopes;
		read(&num, sizeof(int), 1, fp, writer, useFile);
		for(int j=0; j<Constants_NumEnvelopes; j++)
		{
			Adsr* a3obj = (Adsr*)patch->items[NUMBER_START_EG+j];
			LoadParams(a3obj, fp, writer, useFile);
		}

		// simple filters
		num = Constants_NumFilters;
		read(&num, sizeof(int), 1, fp, writer, useFile);
		for(int j=0; j<Constants_NumFilters; j++)
		{
			SimpleFilter* a3obj = (SimpleFilter*)patch->items[NUMBER_START_FILTER+j];
			LoadParams(a3obj, fp, writer, useFile);
		}

		// distortion
		LoadParams(patch->distort, fp, writer, useFile);

		// chorus
		LoadParams(patch->chorus, fp, writer, useFile);

		// boost
		LoadParams(patch->boost, fp, writer, useFile);

		int numMatrixRows = ReadInt(fp, writer, useFile);

		for(int j=0; j<numMatrixRows; j++)
		{
			ModulationMatrixRow* row = patch->ModMatrix->Rows[j];			
			row->RowNum = ReadInt(fp, writer, useFile);
			row->SourceSet = ReadBool(fp, writer, useFile);
			row->DestSet = ReadBool(fp, writer, useFile);
			row->Curve = (ModulationCurve)ReadInt(fp, writer, useFile);
			// source
			if (row->SourceSet)
			{
				int itemNumber = ReadInt(fp, writer, useFile);
				StackItemType itemType = (StackItemType)ReadInt(fp, writer, useFile);
				patch->ModMatrix->SetSource(row->RowNum, patch->items[itemNumber]);
			}			

			if (row->DestSet)
			{
				// dest
				int itemNumber = ReadInt(fp, writer, useFile);
				StackItemType itemType = (StackItemType)ReadInt(fp, writer, useFile);
				int paramNumber = ReadInt(fp, writer, useFile);
				patch->ModMatrix->SetDest(row->RowNum, patch->items[itemNumber], patch->items[itemNumber]->paramsFloat[paramNumber]);
			}
		}

		// changes
		// set patch & changed flag
		patch->ModMatrix->patch = patch;
		patch->ModMatrix->Changed = true;
		patch->ModMatrix->HandleChanges();

		/*
		// mod matrix
		num = ModulationMatrixNumRows;
		fwrite(&num, 1, sizeof(int), fp);
		for(int j=0; j<ModulationMatrixNumRows; j++)
		{
			ModulationMatrixRow* row = &patch->ModMatrix->Rows[j];
			num = row->RowNum;
			fwrite(&num, 1, sizeof(int), fp);
			fwrite(&row->SourceSet, 1, sizeof(bool), fp);
			fwrite(&row->DestSet, 1, sizeof(bool), fp);
			fwrite(&row->ItemSource.itemNumber, 1, sizeof(int), fp);
			fwrite(&row->ItemSource.ItemType, 1, sizeof(int), fp);
			fwrite(&row->ItemSource.ParamNumber, 1, sizeof(int), fp);
		}*/
	}


	int numWaveTables = ReadInt(fp, writer, useFile);

	for(int i=0; i<numWaveTables; i++)
	{
		char tableName[100];

		read(tableName, sizeof(char)*100, 1, fp, writer, useFile);
		WaveForm form = (WaveForm)ReadInt(fp, writer, useFile);
		float amplitude = ReadFloat(fp, writer, useFile);
		float npower = ReadInt(fp, writer, useFile);
		float formantScale = ReadFloat(fp, writer, useFile);
		float bandWidth = ReadFloat(fp, writer, useFile);
		float bandWidthScale = ReadFloat(fp, writer, useFile);
		int tablesPerOctave = ReadInt(fp, writer, useFile);

		// re-create the wavetables - assume all are padsynth atm

		WaveTable* table;

		if (i>5)
		{
			if (form == kWaveFormPadSynthChoir || form == kWaveFormPadSynthEnsemble || form == kWaveFormPadSynthExtended)
			{
				table = WaveTableGen::GeneratePadWaveTable(form, tableName, amplitude, npower, formantScale, bandWidth, bandWidthScale, tablesPerOctave);
			}else{
				DebugBreak();
			}

			WaveTable::Wavetables[WaveTable::NumWaveTables++] = table;
		}

	}

}

int ZynthIo::SaveBankToMem(unsigned char* mem)
{
	Writer* writer = new Writer(mem);
	return SaveBank(0, writer, false);
}

//
// Save bank
// 
void ZynthIo::SaveBankToFile(char* savePath)
{
	// format
	// num patchs : int
	// version : byte
	// patches
	//	- oscillators
	//  - 

	FILE *fp;
	fp = fopen( savePath, "wb+" );
	if( !fp )
	{
		DebugBreak();
	}

	SaveBank(fp, 0, true);

	//fprintf( fp, "debug file\n" );
	//fprintf( fp, "-------------------------\n" );


	fflush( fp );
	fclose( fp );
}

int ZynthIo::SaveBank(FILE* fp, Writer *writer, bool useFile)
{
	int numPatches = Constants_MaxPatches;
	
	// header
	char* header = "medusa\0";
	write(header, 1, strlen(header)+1, fp, writer, useFile);

	// version
	byte ver = 0x01;	
	write(&ver, 1, sizeof(byte), fp, writer, useFile);

	// num patches
	write(&numPatches, 1, sizeof(int), fp, writer, useFile);
	
	/*
	for(int i=0; i<numPatches; i++)
	{
		Patch* patch = &GlobalPatchList->Patches[i];
		fwrite(patch, 1, sizeof(Patch), fp);
	}*/

	// global delay
	ModDelay* md2 = VoicePool::Pool->GlobalDelay;
	SaveParams(md2, fp, writer, useFile);

	// global reverb
	Reverb* gr = VoicePool::Pool->GlobalReverb;
	SaveParams(gr, fp, writer, useFile);
		
	for(int i=0; i<numPatches; i++)
	{
		Patch* patch = PatchList::list->patches[i];

		// save patch name
		write(patch->name, 1, sizeof(char)*100, fp, writer, useFile);
		
		// filter mode
		WriteInt(patch->FilterProcMode->Value(), fp, writer, useFile);

		// save oscillators	
		WriteInt(Constants_NumOscillators, fp, writer, useFile);
		for(int j=0; j<Constants_NumOscillators; j++)
		{
			Osc* oobj = (Osc*)patch->items[NUMBER_START_OSC+j];
			SaveParams(oobj, fp, writer, useFile);
		}

		// save lfo av	
		WriteInt(Constants_NumLfoAllVoices, fp, writer, useFile);
		for(int j=0; j<Constants_NumLfoAllVoices; j++)
		{
			Lfo* laobj = (Lfo*)patch->items[NUMBER_START_LFO_AV+j];
			SaveParams(laobj, fp, writer, useFile);
		}

		// save lfo pv	
		WriteInt(Constants_NumLfoPerVoice, fp, writer, useFile);
		for(int j=0; j<Constants_NumLfoPerVoice; j++)
		{
			Lfo* pvobj = (Lfo*)patch->items[NUMBER_START_LFO_PV+j];
			SaveParams(pvobj, fp, writer, useFile);
		}

		// amp eg
		Adsr* a1obj = patch->egAmp;
		SaveParams(a1obj, fp, writer, useFile);

		// pitch eg
		Adsr* a2obj = patch->egPitch;
		SaveParams(a2obj, fp, writer, useFile);

		// egs	
		WriteInt(Constants_NumEnvelopes, fp, writer, useFile);
		for(int j=0; j<Constants_NumEnvelopes; j++)
		{
			Adsr* a3obj = (Adsr*)patch->items[NUMBER_START_EG+j];
			SaveParams(a3obj, fp, writer, useFile);
		}

		// filters
		WriteInt(Constants_NumFilters, fp, writer, useFile);
		for(int j=0; j<Constants_NumFilters; j++)
		{
			SimpleFilter* ss = (SimpleFilter*)patch->items[NUMBER_START_FILTER+j];
			SaveParams(ss, fp, writer, useFile);
		}

		// distortion
		Distort* dd = patch->distort;
		SaveParams(dd, fp, writer, useFile);

		// chorus
		ChorusFlange* md = patch->chorus;
		SaveParams(md, fp, writer, useFile);;

		// boost
		Boost* bb = patch->boost;
		SaveParams(bb, fp, writer, useFile);

		// mod matrix
		WriteInt(ModulationMatrixNumRows, fp, writer, useFile);

		for(int j=0; j<ModulationMatrixNumRows; j++)
		{
			ModulationMatrixRow* row = patch->ModMatrix->Rows[j];
			WriteInt(row->RowNum, fp, writer, useFile);
			WriteBool(row->SourceSet, fp, writer, useFile);
			WriteBool(row->DestSet, fp, writer, useFile);
			WriteInt(row->Curve, fp, writer, useFile);
			if (row->SourceSet)
			{
				WriteInt(row->ItemSource->Item->number, fp, writer, useFile);
				WriteInt(row->ItemSource->Item->type, fp, writer, useFile);
			}
			if (row->DestSet)
			{
				WriteInt(row->ItemDest->Item->number, fp, writer, useFile);
				WriteInt(row->ItemDest->Item->type, fp, writer, useFile);
				WriteInt(row->ItemDest->Param->number, fp, writer, useFile);
			}
		}
	}

	// save wavetables
	write(&WaveTable::NumWaveTables, 1, sizeof(int), fp, writer, useFile);

	for(int i=0; i<WaveTable::NumWaveTables; i++)
	{
		WaveTable* wt = WaveTable::Wavetables[i];

		// save patch name
		write(&wt->TableName, 1, sizeof(char)*100, fp, writer, useFile);

		write(&wt->Form, 1, sizeof(int), fp, writer, useFile);
		write(&wt->amplitude, 1, sizeof(float), fp, writer, useFile);
		write(&wt->npower, 1, sizeof(int), fp, writer, useFile);
		write(&wt->formantScale, 1, sizeof(float), fp, writer, useFile);
		write(&wt->bandWidth, 1, sizeof(float), fp, writer, useFile);
		write(&wt->bandWidthScale, 1, sizeof(float), fp, writer, useFile);
		write(&wt->TablesPerOctave, 1, sizeof(int), fp, writer, useFile);
	}

	// return amount of mem used
	return useFile ? 0 : writer->memBufferOffset;
}