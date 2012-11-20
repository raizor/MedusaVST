#pragma once

#include "GuiComponent.h"

class GuiKeyboard : public GuiComponent
{
public:
	bool keyDown[100];
	GuiKeyboard(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiKeyboard(void);
	void draw();
	void HandleEvent(GEvent* evt, bool recursing = false);
};


