#pragma once

#include "GuiComponent.h"

class GuiVizualizer : public GuiComponent
{
public:
	GuiVizualizer(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiVizualizer(void);
};

