#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "Items/Processors/Delay and Reverb/Reverb.h"

class GuiPanelGlobalReverb : public GuiComponent
{
public:
	GuiSlider* sliderHiCut;
	GuiSlider* sliderLowCut;
	GuiSlider* sliderTime;
	GuiSlider* sliderAmount;

	GuiPanelGlobalReverb(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelGlobalReverb(void);
	virtual void SetStackItem(Reverb* item);
};

