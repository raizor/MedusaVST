#include "GuiPanelLfo.h"
#include "Items/Processors/Lfo.h"
#include "Utils/WaveTableGen.h"
#include "../../GUI/Components/GuiMainWindow.h"

GuiPanelLfo::GuiPanelLfo(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobOffset = new GuiKnob(0, 0, 10, 117, IDB_KNOBS_BI, 0, 127, true);
	knobDelay = new GuiKnob(0, 0, 48, 147, IDB_KNOBS_UNI, 0, 127, false);
	knobFadeIn = new GuiKnob(0, 0, 87, 117, IDB_KNOBS_UNI, 0, 127, false);
	AddSubComponent(knobOffset);
	AddSubComponent(knobDelay);
	AddSubComponent(knobFadeIn);

	sliderMorph = new GuiSlider(30, 128, 320, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, "MORPH");
	AddSubComponent(sliderMorph);

	sliderSpeed = new GuiSlider(30, 128, 364, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, "SPEED");
	AddSubComponent(sliderSpeed);

	sliderAmount = new GuiSlider(30, 128, 416, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, "AMOUNT");
	AddSubComponent(sliderAmount);

	int amtx = 205;
	int amty  = 8;

	// av
	GuiButton* butOsc;
	butOsc = new GuiButton(26, 27, 53+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_None);
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 76+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_None);
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 99+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_3_off, kSpritesButtons_But_3_on, kSpritesButtons_None);
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 122+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_4_off, kSpritesButtons_But_4_on, kSpritesButtons_None);
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	// pv
	butOsc = new GuiButton(26, 27, 171+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_None);
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 194+amtx, amty, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_None);
	butsAv.push_back(butOsc);
	AddSubComponent(butOsc);

	SetStackItem((Lfo*)PatchList::list->CurrentPatch->items[NUMBER_START_LFO]);
}


GuiPanelLfo::~GuiPanelLfo(void)
{
}

void GuiPanelLfo::SetStackItem(Lfo* item)
{
	// root
	this->synthItem = new LinkedSynthItem();
	this->synthItem->item = item;

	// controls
	LinkedSynthItem* si;

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