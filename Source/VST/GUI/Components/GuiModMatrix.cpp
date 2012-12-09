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
		GuiLabel* lab = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*i), ""); 
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
		GuiLabel* lab = new GuiLabel(72, 12, textStartX+329, textStartY+(lineSpacing*i), "");
		lab->ClickedHandler = (FpClickedCallback)&GuiModMatrix::CallbackClicked;
		AddSubComponent(lab);
		lab->data = new int(i);
		butControl.push_back(lab);
	}

	// dest
	for(int i=0; i<8; i++)
	{
		GuiLabel* lab = new GuiLabel(72, 12, textStartX+442, textStartY+(lineSpacing*i), "");
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
			// SOURCE
			DebugPrintLine("SOURCE");
			menuSource = new GContextMenuEx();
			int id = 1000;
			Patch* p = PatchList::list->CurrentPatch;

			// oscs
			GContextMenuEx* subMenu = new GContextMenuEx(); 
			menuSource->AddMenu(subMenu, "Oscillators");
			
			for(int i=0; i<Constants_NumOscillators; i++)
			{
				subMenu->AddItem(i, StackItemTypeName(p->items[(NUMBER_START_OSC)+i]), p->items[(NUMBER_START_OSC)+i]);
			}	
			
			
			// filters
			subMenu = new GContextMenuEx();
			menuSource->AddMenu(subMenu, "Filters");
			
			for(int i=0; i<Constants_NumFilters; i++)
			{
				subMenu->AddItem(i, StackItemTypeName(p->items[(NUMBER_START_FILTER)+i]), p->items[(NUMBER_START_FILTER)+i]);
			}

			//// lfo av
			subMenu = new GContextMenuEx();
			menuSource->AddMenu(subMenu, "LFO AV");

			for(int i=0; i<Constants_NumFilters; i++)
			{
				subMenu->AddItem(i, StackItemTypeName(p->items[(NUMBER_START_LFO_AV)+i]), p->items[(NUMBER_START_LFO_AV)+i]);
			}


			//// lfo pv
			subMenu = new GContextMenuEx();
			menuSource->AddMenu(subMenu, "LFO PV");

			for(int i=0; i<Constants_NumFilters; i++)
			{
				subMenu->AddItem(i, StackItemTypeName(p->items[(NUMBER_START_LFO_PV)+i]), p->items[(NUMBER_START_LFO_PV)+i]);
			}

			///* TODO: moddable ADSR???
			//// adsr
			//menuItem = new GContextMenuEx(); 
			//menuSource->AddMenu(menuItem, "Amp Eg");
			//for(int i=0; i<Constants_NumEnvelopes; i++)
			//{
			//	GContextMenuEx* subMenu = new GContextMenuEx(); 
			//	AddParamMenus(subMenu, &id, p->items[NUMBER_START_EG]);
			//	char* msg = new char[100];
			//	sprintf(msg, "LFO %d", i+1);
			//	menuItem->AddMenu(subMenu, msg);
			//}*/

			GPoint gp;
			gp.x = 0;
			gp.y = 0;
			int it = menuSource->SelectAt(evt->pos);
			Item* pp = (Item*)it; 
			PatchList::list->CurrentPatch->ModMatrix->SetSource(i, (Item*)pp);
			GuiMainWindow::panelModMatrix->butSource.at(i)->SetText(SourceName(pp));
			/*
			opair* pp = (opair*)it; 
			PatchList::list->CurrentPatch->ModMatrix->SetSource(i, (Item*)pp->val1, (ParamFloat*)pp->val2);
			GuiMainWindow::panelModMatrix->butDest.at(i)->SetText(SourceName(pp));*/
			/*
			PatchList::list->CurrentPatch->ModMatrix->SetCurve(0, curve);
			char* txt = ModulationCurveName((ModulationCurve)curve);
			GuiMainWindow::panelModMatrix->butCurve.at(i)->SetText(txt);*/
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
				AddParamMenus(subMenu, &id, p->items[NUMBER_START_OSC+i]);
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
				AddParamMenus(subMenu, &id, p->items[NUMBER_START_FILTER+i]);
				char* msg = new char[100];
				sprintf(msg, "Filter %d", i+1);
				menuItem->AddMenu(subMenu, msg);
			}

			// lfo av
			menuItem = new GContextMenuEx(); 
			menuSource->AddMenu(menuItem, "LFO AV");
			for(int i=0; i<Constants_NumLfoAllVoices; i++)
			{
				GContextMenuEx* subMenu = new GContextMenuEx(); 
				AddParamMenus(subMenu, &id, p->items[NUMBER_START_LFO_AV+i]);
				char* msg = new char[100];
				sprintf(msg, "LFO %d", i+1);
				menuItem->AddMenu(subMenu, msg);
			}	

			// lfo pf
			menuItem = new GContextMenuEx(); 
			menuSource->AddMenu(menuItem, "LFO PV");
			for(int i=0; i<Constants_NumLfoPerVoice; i++)
			{
				GContextMenuEx* subMenu = new GContextMenuEx(); 
				AddParamMenus(subMenu, &id, p->items[NUMBER_START_LFO_PV+i]);
				char* msg = new char[100];
				sprintf(msg, "LFO %d", i+1);
				menuItem->AddMenu(subMenu, msg);
			}	

			/* TODO: moddable ADSR???
			// adsr
			menuItem = new GContextMenuEx(); 
			menuSource->AddMenu(menuItem, "Amp Eg");
			for(int i=0; i<Constants_NumEnvelopes; i++)
			{
				GContextMenuEx* subMenu = new GContextMenuEx(); 
				AddParamMenus(subMenu, &id, p->items[NUMBER_START_EG]);
				char* msg = new char[100];
				sprintf(msg, "LFO %d", i+1);
				menuItem->AddMenu(subMenu, msg);
			}*/

			GPoint gp;
			gp.x = 0;
			gp.y = 0;
			int it = menuSource->SelectAt(evt->pos);
			opair* pp = (opair*)it; 
			PatchList::list->CurrentPatch->ModMatrix->SetDest(i, (Item*)pp->val1, (ParamFloat*)pp->val2);
			GuiMainWindow::panelModMatrix->butDest.at(i)->SetText(DestName(pp));
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

char* GuiModMatrix::SourceName(Item* item)
{
	StackItemType t = item->itemType;
	char* nn = StackItemTypeName(item);
	char* xx = new char[50];
	sprintf(xx, "%s", nn);
	return xx;
}

char* GuiModMatrix::DestName(opair* op)
{
	Item* it = (Item*)op->val1;
	Param* pp = (Param*)op->val2;
	StackItemType t = it->itemType;
	char* item = StackItemTypeName(it);
	char* param = ParamName(it, pp);
	char* xx = new char[50];
	sprintf(xx, "%s : %s", item, param);
	return xx;
}

char* GuiModMatrix::StackItemTypeName(Item* item)
{
	char *name = new char[25];
	Patch* p = PatchList::list->CurrentPatch;
	switch (item->itemType)
	{
	case(kStackItemTypeWfOsc):
		for(int i = NUMBER_START_OSC; i<NUMBER_START_OSC + Constants_NumOscillators; i++)
		{
			if (item == p->items[i])
			{
				sprintf(name, "Osc %d", i-(NUMBER_START_OSC)+1);
				return name;
			}
		}
		break;
	case(kStackItemTypeSimpleFilter):
		for(int i = NUMBER_START_FILTER; i<NUMBER_START_FILTER + Constants_NumFilters; i++)
		{
			int xx = NUMBER_START_FILTER;
			if (item == p->items[i])
			{
				sprintf(name, "Filter %d", i-(NUMBER_START_FILTER)+1);
				return name;
			}
		}
		break;
	case(kStackItemTypeAmpEg):
		return "EG Amp";
		break;
	case(kStackItemTypeEnvAdsr):
		for(int i = NUMBER_START_EG; i<NUMBER_START_EG+ Constants_NumEnvelopes; i++)
		{
			if (item == p->items[i])
			{
				sprintf(name, "EG %d", i-(NUMBER_START_EG)+1);
				return name;
			}
		}
		break;
	case(kStackItemTypePitchEg):
		return "EG Pitch";
		break;
	case(kStackItemTypeLfoAllVoices):
		for(int i = NUMBER_START_LFO_AV; i<NUMBER_START_LFO_AV + Constants_NumLfoAllVoices; i++)
		{
			if (item == p->items[i])
			{
				sprintf(name, "LFO AV %d", i-(NUMBER_START_LFO_AV)+1);
				return name;
			}
		}
		break;
	case(kStackItemTypeLfoPerVoice):
		for(int i = NUMBER_START_LFO_PV; i<NUMBER_START_LFO_PV + Constants_NumLfoPerVoice; i++)
		{
			if (item == p->items[i])
			{
				sprintf(name, "LFO PV %d", i-(NUMBER_START_LFO_PV)+1);
				return name;
			}
		}
		break;
	default:
		return "???";
		break;
	}	
}


char* GuiModMatrix::ParamName(Item* item, Param* param)
{
	if (item->itemType == kStackItemTypeWfOsc)
	{
		if (item->paramsFloat[PROC_PARAM_FLOAT_LEVEL] == param)
			return "Level";

		if (item->paramsFloat[OSC_PARAM_FLOAT_PITCH_MOD] == param)
			return "Pitch";
	}

	if (item->itemType == kStackItemTypeLfoAllVoices || item->itemType == kStackItemTypeLfoPerVoice)
	{
		if (item->paramsFloat[PROC_PARAM_FLOAT_LEVEL] == param)
			return "Level";

		if (item->paramsFloat[LFO_PARAM_FLOAT_RATE] == param)
			return "Speed";

	}

	if (item->itemType == kStackItemTypeSimpleFilter)
	{
		if (item->paramsFloat[PROC_PARAM_FLOAT_LEVEL] == param)
			return "Level";

		if (item->paramsFloat[FILTER_PARAM_FLOAT_CUTOFF] == param)
			return "Cutoff";

		if (item->paramsFloat[FILTER_PARAM_FLOAT_PANNING] == param)
			return "Panning";

		if (item->paramsFloat[FILTER_PARAM_FLOAT_RESONANCE] == param)
			return "Resonance";
	}

	return "???";
}
