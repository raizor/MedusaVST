#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelHeader  : public GuiComponent
{
public:
	GuiPanelHeader(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelHeader(void);
};

