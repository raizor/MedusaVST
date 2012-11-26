#pragma once

#include "GuiComponent.h"

class GuiKnob : public GuiComponent
{
private:
	void HandleDrag(GEvent* evt);
public:
	bool biDirectional;
	bool lit;
	int value;
	GuiKnob(int width, int height, int offsetX, int offsetY, int imageId, bool biDirectional);
	~GuiKnob(void);
	void draw();
	virtual void HandleEvent(GEvent* evt, bool recursing = false);
};

