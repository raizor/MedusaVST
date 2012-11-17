#include "GuiComponent.h"

#pragma once
class GuiStackItem : public GuiComponent
{
public:
	GuiStackItem(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiStackItem(void);
};

