#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelCompression : public GuiComponent
{
public:
	GuiPanelCompression(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelCompression(void);
};

