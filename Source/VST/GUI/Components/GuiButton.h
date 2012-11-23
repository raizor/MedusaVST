#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "../Sprites/buttons.h"

enum ButtonState
{
	kButtonStateOff = 0,
	kButtonStateOn,
	kButtonStateHot,
};

class GuiButton;

class GuiButtonStrip : public GuiComponent
{
public:
	int numItems;
	GuiButtonStrip(int width, int height, int offsetX, int offsetY);
	~GuiButtonStrip(void);	
};


class GuiButton : public GuiComponent
{
public:
	ButtonState state;
	SpritesButton buttonOff;
	SpritesButton buttonOn;
	SpritesButton buttonOnHot;
	SpritesButton buttonOffHot;
	GuiButton(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton buttonOff, SpritesButton buttonOn, SpritesButton buttonHotOn = kSpritesButtons_None, SpritesButton buttonHotOff = kSpritesButtons_None);
	~GuiButton(void);
	virtual void HandleEvent(GEvent* evt, bool recursing);
	void Clicked();
	virtual void draw();
};

