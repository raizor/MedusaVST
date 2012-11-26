#include "GuiPanelOsc.h"


GuiPanelOsc::GuiPanelOsc(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobFinetune = new GuiKnob(0, 0, 8, 118, IDB_KNOBS_BI, true);
	knobPhase = new GuiKnob(0, 0, 52, 152, IDB_KNOBS_UNI, false);
	knobLevel = new GuiKnob(0, 0, 96, 118, IDB_KNOBS_UNI, false);

	butStripOscs = new GuiButtonStrip(0, 0, 8, 287);

	AddSubComponent(knobFinetune);
	AddSubComponent(knobPhase);
	AddSubComponent(knobLevel);

	sliderFilter = new GuiSlider(30, 128, 419, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider);
	AddSubComponent(sliderFilter);

	butEnabled = new GuiButton(26, 26, 62, 118, IDB_BUTTONSTRIP, kSpritesButtons_But_osc_power_off, kSpritesButtons_But_osc_power_on, kSpritesButtons_None);
	butEnabled->buttonType = kButtonTypeEnabledSwitch;
	LinkedSynthItem* si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butEnabled->synthItem = si;
	AddSubComponent(butEnabled);
	
	// osc numbers

	GuiButton* butOsc;
	butOsc = new GuiButton(26, 27, 102, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_But_1_off_lit, kSpritesButtons_But_1_on_lit);
	butOsc->itemNumber = 0;
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC];
	si->param = &si->item->enabled;	
	butOsc->synthItem = si;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOscs.push_back(butOsc);
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 125, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_But_2_off_lit, kSpritesButtons_But_2_on_lit);
	butOsc->itemNumber = 1;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+1];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 148, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_3_off, kSpritesButtons_But_3_on, kSpritesButtons_But_3_off_lit, kSpritesButtons_But_3_on_lit);
	butOsc->itemNumber = 2;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+2];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 171, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_4_off, kSpritesButtons_But_4_on, kSpritesButtons_But_4_off_lit, kSpritesButtons_But_4_on_lit);
	butOsc->itemNumber = 3;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+3];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 194, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_5_off, kSpritesButtons_But_5_on, kSpritesButtons_But_5_off_lit, kSpritesButtons_But_5_on_lit);
	butOsc->itemNumber = 4;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+4];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

	butOsc = new GuiButton(26, 27, 217, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_6_off, kSpritesButtons_But_6_on, kSpritesButtons_But_6_off_lit, kSpritesButtons_But_6_on_lit);
	butOsc->itemNumber = 5;
	butOscs.push_back(butOsc);
	si = new LinkedSynthItem();
	si->item = PatchList::list->CurrentPatch->items[NUMBER_START_OSC+5];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeEnabled;
	butOsc->buttonType = kButtonTypeOscNumber;
	butOsc->synthItem = si;
	AddSubComponent(butOsc);

}


GuiPanelOsc::~GuiPanelOsc(void)
{
}
