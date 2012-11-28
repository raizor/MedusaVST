#pragma once

#include "GuiComponent.h"

enum GuiLabelSize
{
	kGuiLabelSizeSmall = 0,
	kGuiLabelSizeLarge,

};

class GuiLabel : public GuiComponent
{
public:
	char text[255];
	bool center;
	GuiLabelSize size;
	GuiLabel(int width, int height, int offsetX, int offsetY, char* text, bool center = false, GuiLabelSize size = kGuiLabelSizeSmall);
	~GuiLabel(void);
	virtual void draw();

};

