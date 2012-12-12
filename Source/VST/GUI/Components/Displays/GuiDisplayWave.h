#pragma once
#include "../GuiComponent.h"
#include "../GuiKnob.h"
#include "../GuiSlider.h"
#include "../GuiButton.h"
#include "../GuiLabel.h"

class GuiDisplayWave : public GuiComponent
{
public:
	Item* osc;
	GuiDisplayWave(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiDisplayWave(void);
	virtual void draw();
	void SetOsc(Item* osc);
};

