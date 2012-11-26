#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "../Sprites/buttons.h"


class GuiSliderKnob : public GuiComponent
{
private:
	void HandleDrag(GEvent* evt);
public:
	int value;
	GuiSliderKnob(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton sliderOn, SpritesButton sliderOff);
	~GuiSliderKnob(void);
	SpritesButton spriteOn, spriteOff;
	virtual void draw();
	virtual bool IsHot(GPoint pos, bool onlyCheckY = false);
	void HandleEvent(GEvent* evt, bool recursing = false);
};

class GuiSlider : public GuiComponent
{
public:
	GuiSliderKnob* knob;
	
	GuiSlider(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton sliderOn, SpritesButton sliderOff);
	~GuiSlider(void);
	virtual void draw();
	
};

