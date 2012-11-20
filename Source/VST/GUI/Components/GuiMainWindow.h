#pragma once

#include "GuiComponent.h"
#include "GuiPanelOsc.h"
#include "GuiKeyboard.h"

class GuiMainWindow : public GuiComponent
{
public:
	static GuiComponent *hotComponent, *dragComponent;
	static GPoint *dragPoint, *movePoint;
	int panelNumber;
	Patch* currentPatch;
	GuiPanelOsc* panelOsc;
	GuiKeyboard* keyboard;
	GuiComponent *panelFilter, *panelEg, *panelLfo, *panelMod, *panelMaster;
	GuiMainWindow(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiMainWindow(void);
	void draw();
	void PatchChanged(Patch* patch);
};

