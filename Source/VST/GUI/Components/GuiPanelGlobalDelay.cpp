#include "GuiPanelGlobalDelay.h"
#include "Utils/VoicePool.h"


GuiPanelGlobalDelay::GuiPanelGlobalDelay(int width, int height, int offsetX, int offsetY, int imageId) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	knobTimeLeft = new GuiKnob(0, 0, 11, 137, IDB_KNOBS_UNI, 0, 127, true, kKnobTypePercentage, "DELAY LEFT");
	knobTimeRight = new GuiKnob(0, 0, 76, 137, IDB_KNOBS_UNI, 0, 127, true, kKnobTypePercentage, "DELAY RIGHT");
	knobFeedback = new GuiKnob(0, 0, 143, 137, IDB_KNOBS_BI, 0, 127, true, kKnobTypePercentage, "FEEDBACK");

	AddSubComponent(knobTimeLeft);
	AddSubComponent(knobTimeRight);
	AddSubComponent(knobFeedback);

	sliderDepth = new GuiSlider(30, 128, 211, 53, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "Depth");
	sliderPhase = new GuiSlider(30, 128, 254, 53, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "Phase");
	sliderRate = new GuiSlider(30, 128, 300, 53, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "Rate");
	sliderLevel = new GuiSlider(30, 128, 352, 53, IDB_BUTTONSTRIP, kSpritesButtons_Slider_focus, kSpritesButtons_Slider, kSliderTypeGeneric, "Level");
	
	AddSubComponent(sliderDepth);
	AddSubComponent(sliderPhase);
	AddSubComponent(sliderRate);
	AddSubComponent(sliderLevel);


}

void GuiPanelGlobalDelay::SetStackItem()
{
	ModDelay* item = VoicePool::Pool->GlobalDelay;

	// left time
	LinkedSynthItem* si = new LinkedSynthItem();
	si->item = (Item*)VoicePool::Pool->GlobalDelay;
	si->itemType = kStackItemTypeModDelay;
	si->param = item->paramsFloat[MODDELAY_PARAM_FLOAT_DELAY_LENGTH_LEFT];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobTimeLeft->synthItem = si;

	// right time
	si = new LinkedSynthItem();
	si->item = (Item*)VoicePool::Pool->GlobalDelay;
	si->itemType = kStackItemTypeModDelay;
	si->param = item->paramsFloat[MODDELAY_PARAM_FLOAT_DELAY_LENGTH_RIGHT];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	knobTimeRight->synthItem = si;

	// feedback
	si = new LinkedSynthItem();
	si->item = (Item*)VoicePool::Pool->GlobalDelay;
	si->itemType = kStackItemTypeModDelay;
	si->param = item->paramsFloat[MODDELAY_PARAM_FLOAT_FEEDBACK];
	si->valueType = kParamValueTypeZeroToOneBi;
	si->paramType = kParamTypeFloat;
	knobFeedback->synthItem = si;

	// depth slider
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->type;
	si->param = item->paramsFloat[MODDELAY_PARAM_FLOAT_MOD_DEPTH];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderDepth->synthItem = si;
	sliderDepth->knob->synthItem = si;

	// phase slider
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->type;
	si->param = item->paramsFloat[MODDELAY_PARAM_FLOAT_MOD_PHASE];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderPhase->synthItem = si;
	sliderPhase->knob->synthItem = si;

	// rate slider
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->type;
	si->param = item->paramsFloat[MODDELAY_PARAM_FLOAT_MOD_RATE];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderRate->synthItem = si;
	sliderRate->knob->synthItem = si;

	// level slider
	si = new LinkedSynthItem();
	si->item = item;
	si->itemType = item->type;
	si->param = item->paramsFloat[PROC_PARAM_FLOAT_LEVEL];
	si->valueType = kParamValueTypeZeroToOneUni;
	si->paramType = kParamTypeFloat;
	sliderLevel->synthItem = si;
	sliderLevel->knob->synthItem = si;
}


GuiPanelGlobalDelay::~GuiPanelGlobalDelay(void)
{
}
