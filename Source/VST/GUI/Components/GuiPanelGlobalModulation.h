#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelGlobalModulation : public GuiComponent
{
public:
	GuiPanelGlobalModulation(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelGlobalModulation(void);
};

