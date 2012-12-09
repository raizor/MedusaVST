#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelGlobalEq : public GuiComponent
{
public:
	GuiPanelGlobalEq(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelGlobalEq(void);
};

