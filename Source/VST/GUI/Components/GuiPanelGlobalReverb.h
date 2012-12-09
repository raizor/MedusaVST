#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelGlobalReverb : public GuiComponent
{
public:
	GuiPanelGlobalReverb(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelGlobalReverb(void);
};

