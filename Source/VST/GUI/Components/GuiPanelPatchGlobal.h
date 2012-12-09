#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelPatchGlobal : public GuiComponent
{
public:
	GuiPanelPatchGlobal(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelPatchGlobal(void);
};

