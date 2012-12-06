#include "GuiModMatrix.h"
#include "GuiMainWindow.h"
#include "Items/ItemProcessor.h"
#include "Items/Processors/SimpleFilter.h"
#include "Items/Processors/Lfo.h"
#include "Items/Processors/Osc.h"
#include "Utils/Patch.h"
#include "Utils/Params/Modulation/ModulationMatrix.h"

opair::opair(void* v1, void* v2)
{
	val1 = v1;
	val2 = v2;
}

GuiModMatrix::GuiModMatrix(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	int lineSpacing = 18;
	int textStartY = 55;
	int textStartX = 35;

	// source
	for(int i=0; i<8; i++)
	{
		GuiLabel* lab = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*i), "Source"); 
		lab->ClickedHandler = (FpClickedCallback)&GuiModMatrix::CallbackClicked;
		AddSubComponent(lab);
		lab->data = new int(i);
		butSource.push_back(lab);
	}

	// curve
	for(int i=0; i<8; i++)
	{
		GuiLabel* lab = new GuiLabel(72, 12, textStartX+218, textStartY+(lineSpacing*i), "");
		lab->ClickedHandler = (FpClickedCallback)&GuiModMatrix::CallbackClicked;
		AddSubComponent(lab);
		lab->data = new int(i);
		butCurve.push_back(lab);
	}

	// control
	for(int i=0; i<8; i++)
	{
		GuiLabel* lab = new GuiLabel(72, 12, textStartX+329, textStartY+(lineSpacing*i), "Control");
		lab->ClickedHandler = (FpClickedCallback)&GuiModMatrix::CallbackClicked;
		AddSubComponent(lab);
		lab->data = new int(i);
		butControl.push_back(lab);
	}

	// dest
	for(int i=0; i<8; i++)
	{
		GuiLabel* lab = new GuiLabel(72, 12, textStartX+442, textStartY+(lineSpacing*i), "Destination");
		lab->ClickedHandler = (FpClickedCallback)&GuiModMatrix::CallbackClicked;
		AddSubComponent(lab);
		lab->data = new int(i);
		butDest.push_back(lab);
	}
}


GuiModMatrix::~GuiModMatrix(void)
{
}

void GuiModMatrix::CallbackClicked(void* data, GEvent* evt)
{
	for(int i=0; i<8; i++)
	{
		if (GuiMainWindow::panelModMatrix->butSource.at(i) == data)
		{
			DebugPrintLine("SOURCE");
			menuSource = new GContextMenuEx();
			int id = 1000;
			Patch* p = PatchList::list->CurrentPatch;
			for(int i=0; i<p->numItems; i++)
			{
				StackItemType type = p->items[i]->itemType;
				char* txt = StackItemTypeName(type);
				menuSource->AddItem(id++, txt);
			}			
			GPoint gp;
			gp.x = 0;
			gp.y = 0;
			menuSource->SelectAt(evt->pos);
			return;
		}

		if (GuiMainWindow::panelModMatrix->butCurve.at(i) == data)
		{
			DebugPrintLine("Curve");
			menuSource = new GContextMenuEx();
			int id = 1000;
			for(int i=0; i<kModulationCurveItemCount; i++)
			{
				menuSource->AddItem(i, ModulationCurveName((ModulationCurve)i));
			}
			GPoint gp;
			gp.x = 0;
			gp.y = 0;
			int curve = menuSource->SelectAt(evt->pos);
			PatchList::list->CurrentPatch->ModMatrix->SetCurve(i, curve);
			char* txt = ModulationCurveName((ModulationCurve)curve);
			GuiMainWindow::panelModMatrix->butCurve.at(i)->SetText(txt);
			return;
		}

		if (GuiMainWindow::panelModMatrix->butDest.at(i) == data)
		{
			DebugPrintLine("DEST");
			menuSource = new GContextMenuEx();
			int id = 1000;
			Patch* p = PatchList::list->CurrentPatch;

			// oscs
			GContextMenuEx* menuItem = new GContextMenuEx(); 
			menuSource->AddMenu(menuItem, "Oscillators");
			for(int i=0; i<Constants_NumOscillators; i++)
			{
				GContextMenuEx* subMenu = new GContextMenuEx(); 
				AddParamMenus(subMenu, &id, p->items[i]);
				char* msg = new char[100];
				sprintf(msg, "OSC %d", i+1);
				menuItem->AddMenu(subMenu, msg);
			}	
			
			// filters
			menuItem = new GContextMenuEx(); 
			menuSource->AddMenu(menuItem, "Filters");
			for(int i=0; i<Constants_NumFilters; i++)
			{
				GContextMenuEx* subMenu = new GContextMenuEx(); 
				AddParamMenus(subMenu, &id, p->items[i]);
				char* msg = new char[100];
				sprintf(msg, "Filter %d", i+1);
				menuItem->AddMenu(subMenu, msg);
			}

			// lfo
			menuItem = new GContextMenuEx(); 
			menuSource->AddMenu(menuItem, "LFO");
			for(int i=0; i<Constants_NumFilters; i++)
			{
				GContextMenuEx* subMenu = new GContextMenuEx(); 
				AddParamMenus(subMenu, &id, p->items[i]);
				char* msg = new char[100];
				sprintf(msg, "LFO %d", i+1);
				menuItem->AddMenu(subMenu, msg);
			}	

			// adsr
			menuItem = new GContextMenuEx(); 
			menuSource->AddMenu(menuItem, "Amp Eg");
			for(int i=0; i<Constants_NumFilters; i++)
			{
				GContextMenuEx* subMenu = new GContextMenuEx(); 
				AddParamMenus(subMenu, &id, p->items[i]);
				char* msg = new char[100];
				sprintf(msg, "LFO %d", i+1);
				menuItem->AddMenu(subMenu, msg);
			}

			GPoint gp;
			gp.x = 0;
			gp.y = 0;
			int it = menuSource->SelectAt(evt->pos);
			opair* pp = (opair*)it; 
			PatchList::list->CurrentPatch->ModMatrix->SetDest(i, (Item*)pp->val1, (ParamFloat*)pp->val2);
			/*
			PatchList::list->CurrentPatch->ModMatrix->SetCurve(0, curve);
			char* txt = ModulationCurveName((ModulationCurve)curve);
			GuiMainWindow::panelModMatrix->butCurve.at(i)->SetText(txt);*/

			return;
		}
	}
}

void GuiModMatrix::AddParamMenus(GContextMenuEx* menu, int* itemId, Item* item)
{
	switch(item->itemType)
	{
	case (kStackItemTypeWfOsc):
		{
			menu->AddItem((*itemId)++, "Level", new opair(item, item->paramsFloat[PROC_PARAM_FLOAT_LEVEL]));
			menu->AddItem((*itemId)++, "Pitch", new opair(item, item->paramsFloat[OSC_PARAM_FLOAT_PITCH_MOD]));			
			break;
		}
	case (kStackItemTypeSimpleFilter):
		{
			menu->AddItem((*itemId)++, "Level", new opair(item, item->paramsFloat[PROC_PARAM_FLOAT_LEVEL]));
			menu->AddItem((*itemId)++, "Cutoff", new opair(item, item->paramsFloat[FILTER_PARAM_FLOAT_CUTOFF]));
			menu->AddItem((*itemId)++, "Resonance", new opair(item, item->paramsFloat[FILTER_PARAM_FLOAT_RESONANCE]));
			menu->AddItem((*itemId)++, "Panning", new opair(item, item->paramsFloat[FILTER_PARAM_FLOAT_PANNING]));			
			break;
		}
	case (kStackItemTypeLfoAllVoices):
		{
			menu->AddItem((*itemId)++, "Level", new opair(item, item->paramsFloat[PROC_PARAM_FLOAT_LEVEL]));
			menu->AddItem((*itemId)++, "Speed", new opair(item, item->paramsFloat[LFO_PARAM_FLOAT_RATE]));			
			break;
		}
	case (kStackItemTypeLfoPerVoice):
		{
			menu->AddItem((*itemId)++, "Level", new opair(item, item->paramsFloat[PROC_PARAM_FLOAT_LEVEL]));
			menu->AddItem((*itemId)++, "Speed",new opair(item,  item->paramsFloat[LFO_PARAM_FLOAT_RATE]));			
			break;
		}
	default:
		break;

	}
}

char* GuiModMatrix::ModulationCurveName(ModulationCurve type)
{
	switch (type)
	{
	case(kModulationCurveAddBipolarPlus):
		return "Add Bipolar +";
		break;
	case(kModulationCurveAddBipolarMinus):
		return "Add Biploar -";
		break;
	case(kkModulationCurveAddUnipolarPlus):
		return "Add Unipolar +";
		break;
	case(kModulationCurveAddUnipolarMinus):
		return "Add Unipolar -";
		break;
	case(kModulationCurveMultBipolarPlus):
		return "Mult. Bipolar +";
		break;
	case(kModulationCurveMultBipolarMinus):
		return "Mult. Bipolar -";
		break;
	case(kModulationCurveMultUnipolarPlus):
		return "Mult. Unipolar +";
		break;
	case(kModulationCurveMultUnipolarMinus):
		return "Mult. Unipolar -";
		break;
	default:
		return "???";
		break;
	}	
}

char* GuiModMatrix::StackItemTypeName(StackItemType type)
{
	switch (type)
	{
	case(kStackItemTypeWfOsc):
		return "Osc";
		break;
	case(kStackItemTypeSimpleFilter):
		return "Filter";
		break;
	case(kStackItemTypeAmpEg):
		return "Amg EG";
		break;
	case(kStackItemTypeEnvAdsr):
		return "EG";
		break;
	case(kStackItemTypePitchEg):
		return "Pitch EG";
		break;
	case(kStackItemTypeLfoAllVoices):
		return "LFO All Voices";
		break;
	case(kStackItemTypeLfoPerVoice):
		return "LFO Per Voice";
		break;
	default:
		return "???";
		break;
	}	
}


char* GuiModMatrix::ParamName(Param* param)
{
	switch (param->type)
	{
	case(kStackItemTypeWfOsc):
		return "Osc";
		break;
	case(kStackItemTypeSimpleFilter):
		return "Filter";
		break;
	case(kStackItemTypeAmpEg):
		return "Amg EG";
		break;
	case(kStackItemTypeEnvAdsr):
		return "EG";
		break;
	case(kStackItemTypePitchEg):
		return "Pitch EG";
		break;
	case(kStackItemTypeLfoAllVoices):
		return "LFO All Voices";
		break;
	case(kStackItemTypeLfoPerVoice):
		return "LFO Per Voice";
		break;
	default:
		return "???";
		break;
	}	
}
