#pragma once

#include "GuiComponent.h"
#include "GuiPanelOsc.h"
#include "GuiPanelEg.h"
#include "GuiPanelLfo.h"
#include "GuiPanelModulations.h"
#include "GuiPanelFilter.h"
#include "GuiPanelMaster.h"
#include "GuiKeyboard.h"

#define NUMBER_EG_AMP 6
#define NUMBER_EG_PITCH 7

class GuiPanelMaster;

class GuiMainWindow : public GuiComponent
{
public:
	static char labelText[100];
	static GuiComponent *hotComponent, *dragComponent;
	static GPoint *dragPoint, *movePoint;
	int panelNumber;
	Patch* currentPatch;
	static GuiPanelOsc* panelOsc;
	//GSurface* surface;
	static GuiPanelEg* panelEg;
	static GuiPanelFilter* panelFilter;
	static GuiPanelLfo* panelLfo;
	static GuiPanelModulations* panelModulations;
	static GuiKeyboard* keyboard;
	static GuiPanelMaster *panelMaster;

	static int currentOscNumber;
	static int currentEgNumber;
	static int currentLfoNumber;

	GuiMainWindow(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiMainWindow(void);
	void draw();
	void PatchChanged(Patch* patch);
};

