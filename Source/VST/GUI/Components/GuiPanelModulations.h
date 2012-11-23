#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "../Sprites/buttons.h"

class GuiPanelModulations : public GuiComponent
{
public:
	GuiButton* butNums;

	GuiPanelModulations(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelModulations(void);
};

