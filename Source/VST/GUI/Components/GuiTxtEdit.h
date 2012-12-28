#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "Displays/GuiDisplayWave.h"

class GuiTxtEdit : public GuiComponent
{
public:
	GuiComponent* bgImage;
	GuiTxtEdit(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiTxtEdit(void);
};

