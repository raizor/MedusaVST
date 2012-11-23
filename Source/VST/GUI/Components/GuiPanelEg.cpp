#include "GuiPanelEg.h"
#include "Items/Processors/Adsr.h"


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

	GuiButton* butEg;
	butEg = new GuiButton(34, 27, 56, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_amp_off, kSpritesButtons_But_amp_on, kSpritesButtons_None);
	butEgs.push_back(butEg);
	AddSubComponent(butEg);

	butEg = new GuiButton(34, 27, 87, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_pitch_off, kSpritesButtons_But_pitch_on, kSpritesButtons_None);
	butEgs.push_back(butEg);
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 118, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_None);
	butEgs.push_back(butEg);
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 141, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_None);
	butEgs.push_back(butEg);
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 164, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_3_off, kSpritesButtons_But_3_on, kSpritesButtons_None);
	butEgs.push_back(butEg);
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 187, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_4_off, kSpritesButtons_But_4_on, kSpritesButtons_None);
	butEgs.push_back(butEg);
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 210, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_5_off, kSpritesButtons_But_5_on, kSpritesButtons_None);
	butEgs.push_back(butEg);
	AddSubComponent(butEg);

	butEg = new GuiButton(26, 27, 233, 5, IDB_BUTTONSTRIP, kSpritesButtons_But_6_off, kSpritesButtons_But_6_on, kSpritesButtons_None);
	butEgs.push_back(butEg);
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
