#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "../Sprites/buttons.h"


class GuiSlider : public GuiComponent
{
private:
	void HandleDrag(GEvent* evt);
public:
	SpritesButton sliderOn, sliderOff;
	int value;

	GuiSlider(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton sliderOn, SpritesButton sliderOff);
	~GuiSlider(void);
	virtual void draw();
	void HandleEvent(GEvent* evt, bool recursing = false);
};

