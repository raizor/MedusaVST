#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelFxRouting : public GuiComponent
{
public:
	GuiPanelFxRouting(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelFxRouting(void);
};

