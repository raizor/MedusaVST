#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelKeyboard  : public GuiComponent
{
public:
	GuiPanelKeyboard(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelKeyboard(void);
};

