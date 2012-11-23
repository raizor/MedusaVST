#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelMaster : public GuiComponent
{
public:
	GuiPanelMaster(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelMaster(void);
};

