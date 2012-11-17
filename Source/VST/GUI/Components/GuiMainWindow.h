#pragma once

#include "GuiComponent.h"
#include "Synth.h"

class GuiMainWindow : public GuiComponent
{
public:
	Patch* currentPatch;
	GuiMainWindow(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiMainWindow(void);
	void PatchChanged(Patch* patch);
};

