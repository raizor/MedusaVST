#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "Displays/GuiDisplayWave.h"

class GuiPanelModeller: public GuiComponent
{
public:
	GuiPanelModeller(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelModeller(void);
};

