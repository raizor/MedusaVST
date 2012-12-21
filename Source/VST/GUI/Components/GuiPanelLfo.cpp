#include "GuiPanelLfo.h"
#include "Items/Processors/Lfo.h"
#include "Utils/WaveTableGen.h"
#include "GuiPanelOsc.h"
#include "../../GUI/Components/GuiMainWindow.h"
#include "../../Utils/ContextMenus.h"

GuiPanelLfo::GuiPanelLfo(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobOffset = new GuiKnob(0, 0, 10, 117, IDB_KNOBS_BI, 0, 127, true, kKnobTypeDecimalTwoPlaces, "Offset");
	knobDelay = new GuiKnob(0, 0, 48, 147, IDB_KNOBS_UNI, 0, 127, false, kKnobTypeDecimalTwoPlaces, "Delay");
	knobFadeIn = new GuiKnob(0, 0, 87, 117, IDB_KNOBS_UNI, 0, 127, false, kKnobTypeDecimalTwoPlaces, "Fade In");
	AddSubComponent(knobOffset);
	AddSubComponent(knobDelay);
	AddSubComponent(knobFadeIn);

	sliderMorph = new GuiSlider(30, 128, 320, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "MORPH");
	AddSubComponent(sliderMorph);

	sliderSpeed = new GuiSlider(30, 128, 364, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric,  "SPEED");
	AddSubComponent(sliderSpeed);

	sliderAmount = new GuiSlider(30, 128, 416, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeLfoLevel, "AMOUNT");
	AddSubComponent(sliderAmount);

	int amtx = 205;
	int amty  = 8;

	// av
	GuiButton* butOsc;
	butOsc = new GuiButton(26, 27, 53+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_But_1_off_lit, kSpritesButtons_But_1_on_lit);
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelLfo::CallbackClicked;
	butOsc->itemNumber = 0;
	LinkedSynthItem* si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_LFO_AV];
	si->param = &si->item->enabled;	
	butOsc->synthItem = si;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeLfoAvNumber;
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 76+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_But_2_off_lit, kSpritesButtons_But_2_on_lit);
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelLfo::CallbackClicked;
	butOsc->itemNumber = 1;
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_LFO_AV+1];
	si->param = &si->item->enabled;	
	butOsc->synthItem = si;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeLfoAvNumber;
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 99+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_3_off, kSpritesButtons_But_3_on, kSpritesButtons_But_3_off_lit, kSpritesButtons_But_3_on_lit);
	butOsc->itemNumber = 2;
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelLfo::CallbackClicked;
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_LFO_AV+2];
	si->param = &si->item->enabled;	
	butOsc->synthItem = si;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeLfoAvNumber;
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 122+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_4_off, kSpritesButtons_But_4_on, kSpritesButtons_But_4_off_lit, kSpritesButtons_But_4_on_lit);
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelLfo::CallbackClicked;
	butOsc->itemNumber = 3;
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_LFO_AV+3];
	si->param = &si->item->enabled;	
	butOsc->synthItem = si;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeLfoAvNumber;
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	// pv
	butOsc = new GuiButton(26, 27, 171+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_But_1_off_lit, kSpritesButtons_But_1_on_lit);
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelLfo::CallbackClicked;
	si = new LinkedSynthItem();
	butOsc->itemNumber = 0;
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_LFO_PV];
	si->param = &si->item->enabled;	
	butOsc->synthItem = si;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeLfoPvNumber;
	butPv.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 194+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_But_2_off_lit, kSpritesButtons_But_2_on_lit);
	butOsc->ClickedHandler = (FpClickedCallback)&GuiPanelLfo::CallbackClicked;
	si = new LinkedSynthItem();
	butOsc->itemNumber = 1;
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_LFO_PV+1];
	si->param = &si->item->enabled;	
	butOsc->synthItem = si;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeLfoPvNumber;
	butPv.push_back(butOsc);
	AddSubComponent(butOsc);

	displayWave = new GuiDisplayWave(155, 155, 144, 44, 0);
	AddSubComponent(displayWave);

	// wave type 1

	labWaveType1 = new GuiLabel(72, 12, 63, 44, "Sine");
	labWaveType1->ClickedHandler = (FpClickedCallback)&GuiPanelLfo::CallbackClicked;
	AddSubComponent(labWaveType1);

	butLabWaveType1 = new GuiButton(52, 14, 9, 42, IDB_BUTTONSTRIP, kSpritesButtons_None, kSpritesButtons_None, kSpritesButtons_None); 
	butLabWaveType1->buttonType = kButtonTypeOscParam;
	butLabWaveType1->ClickedHandler = (FpClickedCallback)&GuiPanelFilter::CallbackClicked;
	AddSubComponent(butLabWaveType1);
	
	// wave type 2

	labWaveType2 = new GuiLabel(72, 12, 63, 56, "Sine");
	labWaveType2->ClickedHandler = (FpClickedCallback)&GuiPanelLfo::CallbackClicked;
	AddSubComponent(labWaveType2);

	butLabWaveType2 = new GuiButton(52, 14, 9, 57, IDB_BUTTONSTRIP, kSpritesButtons_None, kSpritesButtons_None, kSpritesButtons_None); 
	butLabWaveType2->buttonType = kButtonTypeOscParam;
	butLabWaveType2->ClickedHandler = (FpClickedCallback)&GuiPanelFilter::CallbackClicked;
	AddSubComponent(butLabWaveType2);


	// knob labels
	labKnob1 = new GuiLabel(40, 12, 10, 166, "OFFSET", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob1);
	labKnob2 = new GuiLabel(40, 12, 50, 193, "DELAY", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob2);
	labKnob3 = new GuiLabel(40, 12, 95, 166, "FADE IN", true, kGuiLabelSizeBold);
	AddSubComponent(labKnob3);

	labSlider1 = new GuiLabel(40, 12, 315, 190, "MORPH", true, kGuiLabelSizeTiny);
	AddSubComponent(labSlider1);
	labSlider2 = new GuiLabel(40, 12, 360, 190, "SPEED", true, kGuiLabelSizeTiny);
	AddSubComponent(labSlider2);
	labSlider3 = new GuiLabel(40, 12, 410, 190, "AMOUNT", true, kGuiLabelSizeTiny);
	AddSubComponent(labSlider3);
}


GuiPanelLfo::~GuiPanelLfo(void)
{
}

void GuiPanelLfo::SetWaveformName(Lfo* osc)
{
	char* c = GuiMainWindow::panelLfo->labWaveType1->text;
	sprintf(c, osc->waveTableIdx->Table->TableName);
}

void GuiPanelLfo::SetStackItem(Lfo* item)
{
	// root
	this->synthItem = new LinkedSynthItem();
	this->synthItem->item = item;

	// controls
	LinkedSynthItem* si;
	
	// speed slider
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->type;
	si->param = item->paramsFloat[LFO_PARAM_FLOAT_RATE];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderSpeed->synthItem = si;
	sliderSpeed->knob->synthItem = si;

	// amount slider
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->type;
	si->param = item->paramsFloat[PROC_PARAM_FLOAT_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderAmount->synthItem = si;
	sliderAmount->knob->synthItem = si;

	// set wave viz osc
	displayWave->SetOsc(item);
	SetWaveformName(item);

	/*
	// morph slider
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->itemType;
	si->param = item->paramsFloat[PROC_PARAM_FLOAT_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderMorph->synthItem = si;
	sliderMorph->knob->synthItem = si;
	*/

	/*
	// fine tune
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = item->itemType;
	si->param = item->paramsFloat[LFO_PARAM_DELAY];
	si->valueType = kParamValueTypeIntBi;
	si->paramType = kParamTypeFloat;
	knobFinetune->synthItem = si;

	// phase
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = item->itemType;
	si->param = item->paramsFloat[OSC_PARAM_PHASE];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobPhase->synthItem = si;

	// level
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = item->itemType;
	si->param = item->paramsFloat[PROC_PARAM_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobLevel->synthItem = si;
	*/


}


void GuiPanelLfo::CallbackClicked(void* data, GEvent* evt)
{
	char msg[100];
	for (int i=0; i<GuiMainWindow::panelLfo->butsAv.size(); i++)
	{
		if (data == GuiMainWindow::panelLfo->butsAv[i])
		{
			DebugPrintLine("XX");
			sprintf(&msg[0], "lfo av %d", i);
			DebugPrintLine(msg);
			Lfo* lfo = (Lfo*)PatchList::list->CurrentPatch->items[NUMBER_START_LFO_AV+i];
			GuiMainWindow::panelLfo->SetStackItem(lfo);
		}
	}

	for (int i=0; i<GuiMainWindow::panelLfo->butPv.size(); i++)
	{

		if (data == GuiMainWindow::panelLfo->butPv[i])
		{
			DebugPrintLine("XX");
			sprintf(&msg[0], "lfo pv %d", i);
			DebugPrintLine(msg);
			Lfo* lfo = (Lfo*)PatchList::list->CurrentPatch->items[NUMBER_START_LFO_PV+i];
			GuiMainWindow::panelLfo->SetStackItem(lfo);
		}
	}

	if (data == GuiMainWindow::panelLfo->labWaveType1)
	{
		Lfo* osc = (Lfo*)GuiMainWindow::panelLfo->synthItem->item;		
		ParamInt *param = osc->paramsInt[LFO_PARAM_INT_WAVEFORM];
		int currentIndex = param->Value();
		int numWaveTables = WaveTable::NumWaveTables;
		if (currentIndex < numWaveTables-1)
		{
			currentIndex++;
		}else{
			currentIndex = 0;
		}
		param->SetValue(currentIndex);
		osc->WaveChanged();
		char* c = GuiMainWindow::panelLfo->labWaveType1->text;
		sprintf(c, osc->waveTableIdx->Table->TableName);
		GuiMainWindow::panelLfo->labWaveType1->SetText(c);
		
	}
}