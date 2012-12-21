#include "GuiPanelOsc.h"
#include "Items/Processors/Osc.h"
#include "Utils/WaveTableGen.h"
#include "../../GUI/Components/GuiMainWindow.h"
#include "../../Utils/ContextMenus.h"
#include "windows.h"

GuiPanelOsc::GuiPanelOsc(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobFinetune = new GuiKnob(0, 0, 8, 120, IDB_KNOBS_BI, 0, 100, true, kKnobTypeCents, "FINETUNE");
	knobPhase = new GuiKnob(0, 0, 52, 155, IDB_KNOBS_UNI, 0, 127, false, kKnobTypeDecimalTwoPlaces, "PHASE");
	knobLevel = new GuiKnob(0, 0, 96, 120, IDB_KNOBS_UNI, 0, 127, false, kKnobTypeDecimalTwoPlaces, "LEVEL");

	butStripOscs = new GuiButtonStrip(0, 0, 8, 287);

	LinkedSynthItem* si;

	AddSubComponent(knobFinetune);
	AddSubComponent(knobPhase);
	AddSubComponent(knobLevel);

	sliderFilter = new GuiSlider(30, 128, 419, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "LEVEL");
	AddSubComponent(sliderFilter);

	butEnabled = new GuiButton(26, 26, 62, 118, IDB_BUTTONSTRIP, kSpritesButtons_But_osc_power_off, kSpritesButtons_But_osc_power_on, kSpritesButtons_None);
	butEnabled->buttonType = kButtonTypeEnabledSwitch;
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butEnabled->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	butEnabled->synthItem = si;
	AddSubComponent(butEnabled);
	
	// osc numbers

	GuiButton* butOsc;
	butOsc = new GuiButton(26, 27, 102+206, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_But_1_off_lit, kSpritesButtons_But_1_on_lit);
	butOsc->itemNumber = 0;
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC];
	si->param = &si->item->enabled;	
	butOsc->synthItem = si;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOscs.push_back(butOsc);
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 125+206, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_But_2_off_lit, kSpritesButtons_But_2_on_lit);
	butOsc->itemNumber = 1;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+1];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 148+206, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_3_off, kSpritesButtons_But_3_on, kSpritesButtons_But_3_off_lit, kSpritesButtons_But_3_on_lit);
	butOsc->itemNumber = 2;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+2];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 171+206, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_4_off, kSpritesButtons_But_4_on, kSpritesButtons_But_4_off_lit, kSpritesButtons_But_4_on_lit);
	butOsc->itemNumber = 3;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+3];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 194+206, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_5_off, kSpritesButtons_But_5_on, kSpritesButtons_But_5_off_lit, kSpritesButtons_But_5_on_lit);
	butOsc->itemNumber = 4;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+4];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 217+206, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_6_off, kSpritesButtons_But_6_on, kSpritesButtons_But_6_off_lit, kSpritesButtons_But_6_on_lit);
	butOsc->itemNumber = 5;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+5];
	si->param = &si->item->enabled;
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	int lineSpacing = 13;
	int textStartY = 43;
	int textStartX = 68;

	butLabWaveType = new GuiButton(50, 12, 13, 47, IDB_BUTTONSTRIP, kSpritesButtons_None, kSpritesButtons_None, kSpritesButtons_None); 
	butLabWaveType->buttonType = kButtonTypeOscParam;
	butLabWaveType->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(butLabWaveType);

	butLabTranspose = new GuiButton(50, 12, 13, 59, IDB_BUTTONSTRIP, kSpritesButtons_None, kSpritesButtons_None, kSpritesButtons_None); 
	butLabTranspose->buttonType = kButtonTypeOscParam;
	butLabTranspose->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(butLabTranspose);

	butLabOctave = new GuiButton(50, 12, 13, 72, IDB_BUTTONSTRIP, kSpritesButtons_None, kSpritesButtons_None, kSpritesButtons_None); 
	butLabOctave->buttonType = kButtonTypeOscParam;
	butLabOctave->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(butLabOctave);

	butLabMode = new GuiButton(50, 12, 13, 85, IDB_BUTTONSTRIP, kSpritesButtons_None, kSpritesButtons_None, kSpritesButtons_None); 
	butLabMode->buttonType = kButtonTypeOscParam;
	butLabMode->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(butLabMode);

	butLabModMode = new GuiButton(50, 12, 13, 99, IDB_BUTTONSTRIP, kSpritesButtons_None, kSpritesButtons_None, kSpritesButtons_None); 
	butLabModMode->buttonType = kButtonTypeOscParam;
	butLabModMode->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(butLabModMode);

	// labels
	labWaveType = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*0), "Sine");
	labWaveType->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(labWaveType);

	labTranspose = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*1), "0");
	labTranspose->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(labTranspose);

	labOctave = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*2), "0");
	labOctave->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(labOctave);

	labMode = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*3), "Sync");
	labMode->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(labMode);

	labModMode = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*4), "Add");
	labModMode->ClickedHandler = (FpClickedCallback)&GuiPanelOsc::CallbackClicked;
	AddSubComponent(labModMode);

	// knob labels
	labKnob1 = new GuiLabel(40, 12, 12, 166, "FINE", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob1);
	labKnob2 = new GuiLabel(40, 12, 100, 166, "LEVEL", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob2);
	labKnob3 = new GuiLabel(40, 12, 55, 200, "PHASE", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob3);
	
	displayWave = new GuiDisplayWave(159, 159, 147, 47, 0);
	AddSubComponent(displayWave);
}


GuiPanelOsc::~GuiPanelOsc(void)
{
}

void GuiPanelOsc::SetStackItem(Osc* item)
{
	// root
	this->synthItem = new LinkedSynthItem();
	this->synthItem->item = item;
	
	// controls
	LinkedSynthItem* si;

	// fine tune
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->type;
	si->param = item->paramsFloat[OSC_PARAM_FLOAT_DETUNE_FINE];
	si->valueType = kParamValueTypeIntBi;
	si->paramType = kParamTypeFloat;
	knobFinetune->synthItem = si;

	// phase
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->type;
	si->param = item->paramsFloat[OSC_PARAM_FLOAT_PHASE];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobPhase->synthItem = si;

	// level
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->type;
	si->param = item->paramsFloat[PROC_PARAM_FLOAT_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobLevel->synthItem = si;

	Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
	char txt [100];

	// osc mode
	ParamInt *iparam = osc->paramsInt[OSC_PARAM_INT_MODE];	
	GuiMainWindow::panelOsc->labMode->SetText(OscModeToString(iparam->Value()));

	// osc mod mode
	iparam = osc->paramsInt[OSC_PARAM_INT_MOD_MODE];	
	GuiMainWindow::panelOsc->labModMode->SetText(OscModModeToString(iparam->Value()));

	// transpose
	ParamFloat *fparam = osc->paramsFloat[OSC_PARAM_FLOAT_DETUNE_SEMI];
	sprintf(txt, "%d", fparam->ValueAsInt());
	GuiMainWindow::panelOsc->labTranspose->SetText(&txt[0]);

	// octave
	fparam = osc->paramsFloat[OSC_PARAM_FLOAT_DETUNE_OCT];
	sprintf(txt, "%d", fparam->ValueAsInt());
	GuiMainWindow::panelOsc->labOctave->SetText(&txt[0]);

	// set wave viz osc
	displayWave->SetOsc(item);
	SetWaveformName(item);
}

void GuiPanelOsc::SetWaveformName(Osc* osc)
{
	char* c = GuiMainWindow::panelOsc->labWaveType->text;
	sprintf(c, osc->waveTableIdx->Table->TableName);
}

void GuiPanelOsc::CallbackClicked(void* data, GEvent* evt)
{
	char msg[100];
	for (int i=0; i<GuiMainWindow::panelOsc->butOscs.size(); i++)
	{
		if (data == GuiMainWindow::panelOsc->butOscs[i])
		{
			sprintf(&msg[0], "osc %d", i);
			DebugPrintLine(msg);
			Osc* osc = (Osc*)PatchList::list->CurrentPatch->items[NUMBER_START_OSC+i];
			GuiMainWindow::panelOsc->SetStackItem(osc);
			return;
		}

		if (data == GuiMainWindow::panelOsc->butEnabled)
		{
			DebugPrintLine("EN");
			return;
		}		
	}

	// wave type
	if (data == GuiMainWindow::panelOsc->butLabWaveType)
	{
		DebugPrintLine("WT");
		Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;			
		int numWaveTables = WaveTable::NumWaveTables;
		ParamInt *param = osc->paramsInt[OSC_PARAM_INT_WAVEFORM];
		int currentIndex = param->Value();
		if (currentIndex < numWaveTables-1)
		{
			currentIndex++;
		}else{
			currentIndex = 0;
		}
		param->SetValue(currentIndex);
		osc->WaveChanged();
		SetWaveformName(osc);
		return;
	}

	if (data == GuiMainWindow::panelOsc->labWaveType && evt->button == kGEventMouseButtonRight)
	{
		GuiMainWindow::panelOsc->menuMenu = new GContextMenuEx();
		int numWaveTables = WaveTable::NumWaveTables;
		for(int i=0; i<numWaveTables-1; i++)
		{
			char* c = new char[100];
			sprintf(c, WaveTable::Wavetables[i]->TableName);
			GuiMainWindow::panelOsc->menuMenu->AddItem(i+1, c, 0);
		}
		int it = GuiMainWindow::panelOsc->menuMenu->SelectAt(evt->pos);
		if (it)
		{
			Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
			ParamInt *param = osc->paramsInt[OSC_PARAM_INT_WAVEFORM];
			param->SetValue(it-1);
			osc->WaveChanged();
			SetWaveformName(osc);
		}
	}

	// transpose
	if (data == GuiMainWindow::panelOsc->butLabTranspose)
	{
		DebugPrintLine("TR");
		Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
		ParamFloat *param = osc->paramsFloat[OSC_PARAM_FLOAT_DETUNE_SEMI];
		int currentIndex = param->ValueAsInt();
		if (evt->button == kGEventMouseButtonLeft)
		{
			if (currentIndex < 12) // +/- 12 semitones (1 octave)
			{
				currentIndex++;
			}else{
				currentIndex = -12;
			}
		}else if (evt->button == kGEventMouseButtonRight){
			if (currentIndex >-12) // +/- 12 semitones (1 octave)
			{
				currentIndex--;
			}else{
				currentIndex = 12;
			}
		}

		param->SetValueWithInt(currentIndex);
		char txt [100];
		sprintf(txt, "%d", currentIndex);
		GuiMainWindow::panelOsc->labTranspose->SetText(&txt[0]);
	}

	if (data == GuiMainWindow::panelOsc->labTranspose && evt->button == kGEventMouseButtonRight)
	{
		GuiMainWindow::panelOsc->menuMenu = new GContextMenuEx();
		for(int i=0; i<25; i++)
		{
			char* txt = new char[5];
			sprintf(txt, "%d", i-12);
			GuiMainWindow::panelOsc->menuMenu->AddItem(i+1, txt, 0);
			delete(txt);
		}
		int it = GuiMainWindow::panelOsc->menuMenu->SelectAt(evt->pos);
		if (it)
		{
			char* txt = new char[5];
			sprintf(txt, "%d", it-13);
			Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
			ParamFloat *param = osc->paramsFloat[OSC_PARAM_FLOAT_DETUNE_SEMI];
			param->SetValue(it-13);
			GuiMainWindow::panelOsc->labTranspose->SetText(txt);
			delete(txt);
		}
	}

	// octave detune
	if (data == GuiMainWindow::panelOsc->butLabOctave)
	{
		DebugPrintLine("OCT");
		Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
		ParamFloat *param = osc->paramsFloat[OSC_PARAM_FLOAT_DETUNE_OCT];
		int currentIndex = param->ValueAsInt();
		if (evt->button == kGEventMouseButtonLeft)
		{
			if (currentIndex < 5) // +/- 5 octaves
			{
				currentIndex++;
			}else{
				currentIndex = -5;
			}
		}else if (evt->button == kGEventMouseButtonRight)
		{
			if (currentIndex >-5) // +/- 5 octaves
			{
				currentIndex--;
			}else{
				currentIndex = 5;
			}
		}
		
		param->SetValueWithInt(currentIndex);
		char txt [100];
		sprintf(txt, "%d", currentIndex);
		GuiMainWindow::panelOsc->labOctave->SetText(&txt[0]);
		delete(txt);
	}


	if (data == GuiMainWindow::panelOsc->labOctave && evt->button == kGEventMouseButtonRight)
	{
		GuiMainWindow::panelOsc->menuMenu = new GContextMenuEx();
		for(int i=0; i<11; i++)
		{
			char* txt = new char[5];
			sprintf(txt, "%d", i-5);
			GuiMainWindow::panelOsc->menuMenu->AddItem(i+1, txt, 0);
			delete(txt);
		}
		int it = GuiMainWindow::panelOsc->menuMenu->SelectAt(evt->pos);
		if (it)
		{
			char* txt = new char[5];
			sprintf(txt, "%d", it-6);
			Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
			ParamFloat *param = osc->paramsFloat[OSC_PARAM_FLOAT_DETUNE_OCT];
			param->SetValue(it-6);
			GuiMainWindow::panelOsc->labOctave->SetText(txt);
			delete(txt);
		}
	}

	// mode
	if (data == GuiMainWindow::panelOsc->labMode && evt->button == kGEventMouseButtonRight)
	{
		GuiMainWindow::panelOsc->menuMenu = new GContextMenuEx();
		for(int i=0; i<kOscModeItemCount-1; i++)
		{
			GuiMainWindow::panelOsc->menuMenu->AddItem(i+1, OscModeToString(i), 0);
		}
		int it = GuiMainWindow::panelOsc->menuMenu->SelectAt(evt->pos);
		if (it)
		{
			Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
			ParamInt *param = osc->paramsInt[OSC_PARAM_INT_MODE];
			param->SetValue(it-1);
			GuiMainWindow::panelOsc->labMode->SetText(OscModeToString(it-1));
		}
		// oscs
		//GContextMenuEx* subMenu = new GContextMenuEx(); 
		//menuSource->AddMenu(subMenu, "Oscillators");
	}

	if (data == GuiMainWindow::panelOsc->butLabMode)
	{
		DebugPrintLine("mode");
		Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
		ParamInt *param = osc->paramsInt[OSC_PARAM_INT_MODE];
		int currentIndex = param->Value();
		if (currentIndex < kOscModeItemCount-1) // +/- 5 octaves
		{
			currentIndex++;
		}else{
			currentIndex = 0;
		}
		param->SetValue(currentIndex);
		char txt [100];
		sprintf(txt, "%d", currentIndex);
		GuiMainWindow::panelOsc->labMode->SetText(OscModeToString(currentIndex));
		delete(txt);
	}

	// mod mode

	if (data == GuiMainWindow::panelOsc->labModMode)
	{
		GuiMainWindow::panelOsc->menuMenu = new GContextMenuEx();
		for(int i=0; i<kOscModModeItemCount-1; i++)
		{
			GuiMainWindow::panelOsc->menuMenu->AddItem(i+1, OscModModeToString(i), 0);
		}
		int it = GuiMainWindow::panelOsc->menuMenu->SelectAt(evt->pos);
		if (it)
		{
			Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
			ParamInt *param = osc->paramsInt[OSC_PARAM_INT_MOD_MODE];
			param->SetValue(it-1);
			GuiMainWindow::panelOsc->labModMode->SetText(OscModModeToString(it-1));
		}
	}

	if (data == GuiMainWindow::panelOsc->butLabModMode)
	{
		DebugPrintLine("mode");
		Osc* osc = (Osc*)GuiMainWindow::panelOsc->synthItem->item;		
		ParamInt *param = osc->paramsInt[OSC_PARAM_INT_MOD_MODE];
		int currentIndex = param->Value();
		if (currentIndex < kOscModModeItemCount-1) // +/- 5 octaves
		{
			currentIndex++;
		}else{
			currentIndex = 0;
		}
		param->SetValue(currentIndex);
		char txt [100];
		sprintf(txt, "%d", currentIndex);
		GuiMainWindow::panelOsc->labModMode->SetText(OscModModeToString(currentIndex));
		delete(txt);
	}
}

char* GuiPanelOsc::OscModModeToString(int val) 
{ 
	if (val == kOscModModeAdd) return "Add"; 
	if (val == kOscModModeFM) return "Freq. Mod"; 
	if (val == kOscModModeRing) return "Ring Mod."; 
	if (val == kOscModModeSync) return "Sync."; 
	if (val == kOscModModePM) return "PM"; 
	return "???";
}

char* GuiPanelOsc::OscModeToString(int val) 
{ 
	if (val == kOscModeNormalSync) return "Sync"; 
	if (val == kOscModInvertedSync) return "Inv. Sync"; 
	if (val == kOscModeFixedFree) return "Fixed Free"; 
	if (val == kOscModeFixedSync) return "Fixed Sync"; 
	if (val == kOscModeInvertedFree) return "Inv. Free"; 
	if (val == kOscModeNormalFree) return "Free"; 
	
	return "???";
}