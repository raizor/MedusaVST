#include "GuiPanelPatchGlobal.h"


GuiPanelPatchGlobal::GuiPanelPatchGlobal(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobDelay = new GuiKnob(0, 0, 9, 145, IDB_KNOBS_UNI, 0, 127, false, kKnobTypePercentage, "DELAY");
	knobReverb = new GuiKnob(0, 0, 68, 145, IDB_KNOBS_UNI, 0, 127, false, kKnobTypePercentage, "REVERB");
	knobBoost = new GuiKnob(0, 0, 126, 145, IDB_KNOBS_UNI, 0, 127, false, kKnobTypePercentage, "BOOST");
	knobChanVol = new GuiKnob(127, 0, 184, 145, IDB_KNOBS_UNI, 0, 127, false, kKnobTypePercentage, "CHAN. VOL");

	AddSubComponent(knobDelay);
	AddSubComponent(knobReverb);
	AddSubComponent(knobBoost);
	AddSubComponent(knobChanVol);

	SetPatch(PatchList::list->CurrentPatch);
}

void GuiPanelPatchGlobal::SetPatch(Patch* patch)
{
	// root
	this->synthItem = new LinkedSynthItem();
	this->synthItem->item = 0;

	// controls
	LinkedSynthItem* si;

	// delay
	si = new LinkedSynthItem();
	si->item = 0;
	si->itemType = kStackItemTypePatchSettings;
	si->param = patch->DelayAmount;
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobDelay->synthItem = si;

	// reverb
	si = new LinkedSynthItem();
	si->item = 0;
	si->itemType = kStackItemTypePatchSettings;
	si->param = patch->ReverbAmount;
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobReverb->synthItem = si;

	// boost
	si = new LinkedSynthItem();
	si->item = 0;
	si->itemType = kStackItemTypePatchSettings;
	si->param = patch->BoostAmount;
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobBoost->synthItem = si;

	// chan. vol
	si = new LinkedSynthItem();
	si->item = 0;
	si->itemType = kStackItemTypePatchSettings;
	si->param = patch->ChanVolAmount;
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobChanVol->synthItem = si;
}


GuiPanelPatchGlobal::~GuiPanelPatchGlobal(void)
{
}
