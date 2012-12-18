#include "GuiPanelGlobalReverb.h"


GuiPanelGlobalReverb::GuiPanelGlobalReverb(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	sliderTime = new GuiSlider(30, 128, 23, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "SIZE");
	sliderHiCut = new GuiSlider(30, 128, 142, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "HI CUT");
	sliderLowCut = new GuiSlider(30, 128, 194, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "LO CUT");
	sliderAmount = new GuiSlider(30, 128, 250, 56, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "LEVEL");
	AddSubComponent(sliderTime);
	AddSubComponent(sliderHiCut);
	AddSubComponent(sliderLowCut);
	AddSubComponent(sliderAmount);
}


GuiPanelGlobalReverb::~GuiPanelGlobalReverb(void)
{
}

void GuiPanelGlobalReverb::SetStackItem(Reverb* item)
{
	// root
	this->synthItem = new LinkedSynthItem();
	this->synthItem->item = item;

	// controls
	LinkedSynthItem* si;

	// amount slider
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeGlobalReverb;
	si->param = item->paramsFloat[PROC_PARAM_FLOAT_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderAmount->synthItem = si;
	sliderAmount->knob->synthItem = si;

	// hi slider
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeGlobalReverb;
	si->param = item->paramsFloat[REVERB_PARAM_FLOAT_HI_CUT];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderHiCut->synthItem = si;
	sliderHiCut->knob->synthItem = si;

	// low slider
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeGlobalReverb;
	si->param = item->paramsFloat[REVERB_PARAM_FLOAT_LOW_CUT];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderLowCut->synthItem = si;
	sliderLowCut->knob->synthItem = si;

	// time slider
	si = new LinkedSynthItem();
	si->item = (Item*)item;
	si->itemType = kStackItemTypeGlobalReverb;
	si->param = item->paramsFloat[REVERB_PARAM_FLOAT_TIME];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderTime->synthItem = si;
	sliderTime->knob->synthItem = si;
}
