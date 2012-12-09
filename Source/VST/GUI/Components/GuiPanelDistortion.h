#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelDistortion : public GuiComponent
{
public:
	GuiPanelDistortion(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelDistortion(void);
};

