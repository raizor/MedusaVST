#include "GuiPanelOsc.h"
#include "Items/Processors/Osc.h"


GuiPanelOsc::GuiPanelOsc(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobFinetune = new GuiKnob(0, 0, 8, 118, IDB_KNOBS_BI, 0, 100, true, "FINETUNE");
	knobPhase = new GuiKnob(0, 0, 52, 152, IDB_KNOBS_UNI, 0, 127, false, "PHASE");
	knobLevel = new GuiKnob(0, 0, 96, 118, IDB_KNOBS_UNI, 0, 127, false, "LEVEL");

	butStripOscs = new GuiButtonStrip(0, 0, 8, 287);

	LinkedSynthItem* si;

	AddSubComponent(knobFinetune);
	AddSubComponent(knobPhase);
	AddSubComponent(knobLevel);

	sliderFilter = new GuiSlider(30, 128, 419, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider);
	AddSubComponent(sliderFilter);

	butEnabled = new GuiButton(26, 26, 62, 118, IDB_BUTTONSTRIP, kSpritesButtons_But_osc_power_off, kSpritesButtons_But_osc_power_on, kSpritesButtons_None);
	butEnabled->buttonType = kButtonTypeEnabledSwitch;
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
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
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 125+206, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_But_2_off_lit, kSpritesButtons_But_2_on_lit);
	butOsc->itemNumber = 1;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+1];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
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
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 194+206, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_5_off, kSpritesButtons_But_5_on, kSpritesButtons_But_5_off_lit, kSpritesButtons_But_5_on_lit);
	butOsc->itemNumber = 4;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+4];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 217+206, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_6_off, kSpritesButtons_But_6_on, kSpritesButtons_But_6_off_lit, kSpritesButtons_But_6_on_lit);
	butOsc->itemNumber = 5;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+5];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	int lineSpacing = 13;
	int textStartY = 43;
	int textStartX = 68;

	// labels
	labWaveType = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*0), "Sine");
	AddSubComponent(labWaveType);

	labTranspose = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*1), "0");
	AddSubComponent(labTranspose);

	labOctave = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*2), "0");
	AddSubComponent(labOctave);

	labMode = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*3), "Sync");
	AddSubComponent(labMode);

	labModMode = new GuiLabel(72, 12, textStartX, textStartY+(lineSpacing*4), "Add");
	AddSubComponent(labModMode);

	SetStackItem((Osc*)PatchList::list->CurrentPatch->items[NUMBER_START_OSC]);
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
	si->item = (Item*)item;
	si->itemType = kStackItemTypeWfOsc;
	si->param = item->paramsFloat[OSC_PARAM_DETUNE_FINE];
	si->valueType = kParamValueTypeIntBi;
	si->paramType = kParamTypeFloat;
	knobFinetune->synthItem = si;

	// phase
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeWfOsc;
	si->param = item->paramsFloat[OSC_PARAM_PHASE];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobFinetune->synthItem = si;

	// level
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeWfOsc;
	si->param = item->paramsFloat[OSC_PARAM_VOLUME];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobFinetune->synthItem = si;
}