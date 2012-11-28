#include "GuiPanelEg.h"
#include "Items/Processors/Adsr.h"
#include "GuiMainWindow.h"


GuiPanelEg::GuiPanelEg(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobDelayTime = new GuiKnob(0, 0, 14, 148, IDB_KNOBS_UNI, 0, 127, true, "DELAY TIME");
	knobStartLevel = new GuiKnob(0, 0, 304, 148, IDB_KNOBS_UNI, 0, 127, false, "START LEVEL");
	knobAttackTime = new GuiKnob(0, 0, 72, 148, IDB_KNOBS_UNI, 0, 127, false, "ATTACK TIME");
	knobAttackLevel = new GuiKnob(0, 0, 188, 148, IDB_KNOBS_UNI, 0, 127, false, "ATTACK LEVEL");
	knobDecayTime = new GuiKnob(0, 0, 130, 148, IDB_KNOBS_UNI, 0, 127, false, "DECAY TIME");
	knobDecayLevel = new GuiKnob(0, 0, 188, 148, IDB_KNOBS_UNI, 0, 127, false, "DECAY LEVEL");
	knobSustainTime = new GuiKnob(0, 0, 246, 148, IDB_KNOBS_UNI, 0, 127, false, "SUSTAIN TIME");
	knobSustainLevel = new GuiKnob(0, 0, 304, 148, IDB_KNOBS_UNI, 0, 127, false, "SUSTAIN LEVEL");
	knobReleaseTime = new GuiKnob(0, 0, 362, 148, IDB_KNOBS_UNI, 0, 127, false, "RELEASE TIME");
	knobReleaseLevel = new GuiKnob(0, 0, 363, 148, IDB_KNOBS_UNI, 0, 127, false, "RELEASE LEVEL");

	// overlay panel
	panelOverlay = new GuiComponent(406, 66, 6, 142, IDB_BUTTONSTRIP, kSpritesButtons_Overlay_adsr_other, false, 0);
	panelOverlay->enabled = false;
	AddSubComponent(panelOverlay);	
	
	AddSubComponent(knobDelayTime);
	AddSubComponent(knobStartLevel);
	AddSubComponent(knobAttackTime);
	AddSubComponent(knobAttackLevel);
	AddSubComponent(knobDecayTime);
	AddSubComponent(knobDecayLevel);
	AddSubComponent(knobSustainTime);
	AddSubComponent(knobSustainLevel);
	AddSubComponent(knobReleaseTime);
	AddSubComponent(knobReleaseLevel);

	// amount slider
	sliderAmount = new GuiSlider(30, 130, 419, 54, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider);
	AddSubComponent(sliderAmount);
	
	int amt = 192;

	// amp eg
	GuiButton* butEg;
	butEg = new GuiButton(34, 27, 56+amt, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_amp_off, kSpritesButtons_But_amp_on, kSpritesButtons_But_amp_off_lit, kSpritesButtons_But_amp_on_lit);
	butEg->itemNumber = NUMBER_EG_AMP;
	butEgs.push_back(butEg);
	LinkedSynthItem* si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->egAmp;
	si->param = &si->item->enabled;	
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	butEg->fp = &GuiPanelEg::ftest;
	//butEg->HandlerClicked = (void*)&EgChanged;
	AddSubComponent(butEg);

	// pitch eg
	butEg = new GuiButton(34, 27, 87+amt, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_pitch_off, kSpritesButtons_But_pitch_on, kSpritesButtons_But_pitch_off_lit, kSpritesButtons_But_pitch_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = NUMBER_EG_PITCH;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->egPitch;
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);
	
	// eg 1
	butEg = new GuiButton(26, 27, 118+amt, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_1_off, kSpritesButtons_But_1_on, kSpritesButtons_But_1_off_lit, kSpritesButtons_But_1_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 0;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+0];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	// eg 2
	butEg = new GuiButton(26, 27, 141+amt, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_2_off, kSpritesButtons_But_2_on, kSpritesButtons_But_2_off_lit, kSpritesButtons_But_2_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 1;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+1];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	// eg 3
	butEg = new GuiButton(26, 27, 164+amt, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_3_off, kSpritesButtons_But_3_on, kSpritesButtons_But_3_off_lit, kSpritesButtons_But_3_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 2;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+2];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	// eg 4
	butEg = new GuiButton(26, 27, 187+amt, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_4_off, kSpritesButtons_But_4_on, kSpritesButtons_But_4_off_lit, kSpritesButtons_But_4_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 3;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+3];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	// eg 5
	butEg = new GuiButton(26, 27, 210+amt, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_5_off, kSpritesButtons_But_5_on, kSpritesButtons_But_5_off_lit, kSpritesButtons_But_5_on_lit);
	butEgs.push_back(butEg);
	butEg->itemNumber = 4;
	si = new LinkedSynthItem();
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+4];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	// eg 6
	butEg = new GuiButton(26, 27, 233+amt, 8, IDB_BUTTONSTRIP, kSpritesButtons_But_6_off, kSpritesButtons_But_6_on, kSpritesButtons_But_6_off_lit, kSpritesButtons_But_6_on_lit);
	butEgs.push_back(butEg);
	si = new LinkedSynthItem();
	butEg->itemNumber = 5;
	butEg->buttonType = kButtonTypeEgNumber;
	si->item = PatchList::list->patches[0]->items[NUMBER_START_EG+5];
	si->param = &si->item->enabled;
	si->paramType = kParamTypeDefault;
	butEg->synthItem = si;
	AddSubComponent(butEg);

	SetStackItem((Adsr*)PatchList::list->CurrentPatch->egAmp);
}


GuiPanelEg::~GuiPanelEg(void)
{
}

void GuiPanelEg::SetStackItem(Adsr* item)
{
	panelOverlay->enabled = item->type == kEgTypePitch;

	bool isPitch = item->type == kEgTypePitch;

	// root
	this->synthItem = new LinkedSynthItem();
	this->synthItem->item = item;

	// controls
	LinkedSynthItem* si;

	// delay time
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_DELAY_TIME];
	si->valueType = kParamValueTypeTime;
	si->paramType = kParamTypeFloat;
	knobDelayTime->synthItem = si;

	// start level
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_START_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobStartLevel->synthItem = si;

	// attack time
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_ATTACK_TIME];
	si->valueType = kParamValueTypeTime;
	si->paramType = kParamTypeFloat;
	knobAttackTime->synthItem = si;

	// attack level
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_ATTACK_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobAttackLevel->synthItem = si;

	// decay time
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_DECAY_TIME];
	si->valueType = kParamValueTypeTime;
	si->paramType = kParamTypeFloat;
	knobDecayTime->synthItem = si;

	// decay level
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_DECAY_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobDecayLevel->synthItem = si;

	// sustain time
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_SUSTAIN_TIME];
	si->valueType = kParamValueTypeTime;
	si->paramType = kParamTypeFloat;
	knobSustainTime->synthItem = si;

	// sustain level
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_SUSTAIN_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobSustainLevel->synthItem = si;

	// release time
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_RELEASE_TIME];
	si->valueType = kParamValueTypeTime;
	si->paramType = kParamTypeFloat;
	knobReleaseTime->synthItem = si;

	// release level
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeEnvAdsr;
	si->param = item->paramsFloat[ADSR_PARAM_RELEASE_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobReleaseLevel->synthItem = si;

	/*

	AMP:
		DELAY TIME
		ATTACK TIME
		DECAY TIME
		DECAY LEVEL
		SUSTAIN TIME
		SUSTAIN LEVEL
		RELEASE TIME

	PITCH:
		DELAY TIME
		START LEVEL
		ATTACK TIME
		ATTACK LEVEL
		DECAY TIME
		RELEASE TIME
		RELEASE LEVEL


	*/

	if (isPitch)
	{
		// pitch eg

		/*
		knobStartLevel->enabled = true;		
		knobAttackLevel->enabled = true;
		knobReleaseLevel->enabled = true;
		knobDecayLevel->enabled = false;
		knobSustainTime->enabled = false;		
		knobSustainLevel->enabled = false;
		*/

		knobAttackTime->enabled = true;	
		knobAttackTime->SetOffset(130, 148);

		knobDecayTime->enabled = true;
		knobDecayTime->SetOffset(246, 148);
		
		knobReleaseTime->enabled = true;
		knobReleaseTime->SetOffset(304, 148);

		knobStartLevel->enabled = true;		
		knobStartLevel->SetOffset(72, 148);

		knobAttackLevel->enabled = true;
		knobAttackLevel->SetOffset(188, 148);

		knobReleaseLevel->enabled = true;
		knobReleaseLevel->SetOffset(362, 148);

		knobDecayLevel->enabled = false;
		knobSustainTime->enabled = false;		
		knobSustainLevel->enabled = false;
		
	}else{
		// other eg

		/*
		knobStartLevel->enabled = false;		
		knobAttackLevel->enabled = false;
		knobReleaseLevel->enabled = false;
		knobDecayLevel->enabled = true;
		knobSustainTime->enabled = true;		
		knobSustainLevel->enabled = true;
		*/

		knobAttackTime->enabled = true;	
		knobAttackTime->SetOffset(72, 148);

		knobDecayTime->enabled = true;
		knobDecayTime->SetOffset(130, 148);

		knobReleaseTime->enabled = true;
		knobReleaseTime->SetOffset(362, 148);

		knobDecayLevel->enabled = true;
		knobDecayLevel->SetOffset(188, 148);

		knobSustainTime->enabled = true;		
		knobSustainTime->SetOffset(246, 148);

		knobSustainLevel->enabled = true;
		knobSustainLevel->SetOffset(304, 148);

		knobStartLevel->enabled = false;		
		knobAttackLevel->enabled = false;
		knobReleaseLevel->enabled = false;
		
		
		
	}
}
