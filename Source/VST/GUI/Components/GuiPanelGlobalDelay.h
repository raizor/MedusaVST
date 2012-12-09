#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelGlobalDelay : public GuiComponent
{
public:
	GuiPanelGlobalDelay(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelGlobalDelay(void);
};

