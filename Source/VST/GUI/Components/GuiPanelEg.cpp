#include "GuiPanelEg.h"
#include "Items/Processors/Adsr.h"
#include "GuiMainWindow.h"


GuiPanelEg::GuiPanelEg(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	itemAdsr = 0;
	knobDelayTime = new GuiKnob(0, 0, 14, 148, IDB_KNOBS_BI, true);
	knobAttackTime = new GuiKnob(0, 0, 72, 148, IDB_KNOBS_UNI, false);
	knobDecayTime = new GuiKnob(0, 0, 130, 148, IDB_KNOBS_UNI, false);
	knobDecayLevel = new GuiKnob(0, 0, 188, 148, IDB_KNOBS_UNI, false);
	knobSustainTime = new GuiKnob(0, 0, 246, 148, IDB_KNOBS_UNI, false);
	knobSustainLevel = new GuiKnob(0, 0, 304, 148, IDB_KNOBS_UNI, false);
	knobReleaseTime = new GuiKnob(0, 0, 362, 148, IDB_KNOBS_UNI, false);
	knobReleaseLevel = new GuiKnob(0, 0, 363, 148, IDB_KNOBS_UNI, false);
	
	AddSubComponent(knobDelayTime);
	AddSubComponent(knobAttackTime);
	AddSubComponent(knobDecayTime);
	AddSubComponent(knobDecayLevel);
	AddSubComponent(knobSustainTime);
	AddSubComponent(knobSustainLevel);
	AddSubComponent(knobReleaseTime);

	sliderAmount = new GuiSlider(30, 130, 419, 54, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider);
	AddSubComponent(sliderAmount);

	GuiButton* butEg;
	butEg = new GuiButton(34, 27, 56, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_amp_off, kSpritesButtons_But_amp_on, kSpritesButtons_But_amp_off_lit, kSpritesButtons_But_amp_on_lit);
	butEg->itemNumber = NUMBER_EG_AMP;
	butEgs.push_back(butEg);
	LinkedSynthItem* si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->egAmp;
	si->param = &si->item->enabled;	
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	butEg = new GuiButton(34, 27, 87, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_pitch_off, kSpritesButtons_But_pitch_on, kSpritesButtons_But_pitch_off_lit, kSpritesButtons_But_pitch_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = NUMBER_EG_PITCH;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->egPitch;
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 118, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_But_1_off_lit, kSpritesButtons_But_1_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 0;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+0];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 141, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_But_2_off_lit, kSpritesButtons_But_2_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 1;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+1];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 164, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_3_off, kSpritesButtons_But_3_on, kSpritesButtons_But_3_off_lit, kSpritesButtons_But_3_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 2;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+2];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 187, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_4_off, kSpritesButtons_But_4_on, kSpritesButtons_But_4_off_lit, kSpritesButtons_But_4_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 3;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+3];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 210, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_5_off, kSpritesButtons_But_5_on, kSpritesButtons_But_5_off_lit, kSpritesButtons_But_5_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 4;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+4];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 233, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_6_off, kSpritesButtons_But_6_on, kSpritesButtons_But_6_off_lit, kSpritesButtons_But_6_on_lit);
	butEgs.push_back(butEg);
	si = new LinkedSynthItem();
	butEg->itemNumber = 5;
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+5];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	//AddSubComponent(knobReleaseLevel);
}


GuiPanelEg::~GuiPanelEg(void)
{
}

void GuiPanelEg::SetEg(Adsr* adsr)
{
	itemAdsr = adsr;
}
