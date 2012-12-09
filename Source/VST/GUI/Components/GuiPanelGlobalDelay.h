#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelGlobalDelay : public GuiComponent
{
public:

	GuiKnob* knobTimeLeft;
	GuiKnob* knobTimeRight;
	GuiKnob* knobFeedback;

	GuiSlider* sliderDepth;
	GuiSlider* sliderPhase;
	GuiSlider* sliderRate;
	GuiSlider* sliderLevel;

	GuiPanelGlobalDelay(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelGlobalDelay(void);
};

