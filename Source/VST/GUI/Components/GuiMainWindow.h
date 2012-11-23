#pragma once

#include "GuiComponent.h"
#include "GuiPanelOsc.h"
#include "GuiPanelEg.h"
#include "GuiPanelLfo.h"
#include "GuiPanelModulations.h"
#include "GuiPanelFilter.h"
#include "GuiKeyboard.h"

class GuiMainWindow : public GuiComponent
{
public:
	static GuiComponent *hotComponent, *dragComponent;
	static GPoint *dragPoint, *movePoint;
	int panelNumber;
	Patch* currentPatch;
	GuiPanelOsc* panelOsc;
	GuiPanelEg* panelEg;
	GuiPanelFilter* panelFilter;
	GuiPanelLfo* panelLfo;
	GuiPanelModulations* panelModulations;
	GuiKeyboard* keyboard;
	GuiComponent *panelMaster;
	GuiMainWindow(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiMainWindow(void);
	void draw();
	void PatchChanged(Patch* patch);
};

