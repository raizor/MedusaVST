#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "../Sprites/buttons.h"

class GuiKeyboardKey : public GuiComponent
{
public: 
	int midiNumber;
	bool keyDown;
	GuiKeyboardKey(int width, int height, int offsetX, int offsetY, int imageId, int spriteId);
	~GuiKeyboardKey(void);
	virtual void HandleEvent(GEvent* evt, bool recursing = false);
	virtual void draw();
};

class GuiKeyboard : public GuiComponent
{
public:
	bool keyDown[100];
	GuiKeyboard(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiKeyboard(void);
	virtual void draw();
	void HandleEvent(GEvent* evt, bool recursing = false);
};


