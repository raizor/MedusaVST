#pragma once

#include "GuiComponent.h"
#include "GuiPanelOsc.h"
#include "GuiPanelEg.h"
#include "GuiPanelLfo.h"
#include "GuiPanelFilter.h"
#include "GuiPanelMaster.h"
#include "GuiPanelModeller.h"
#include "GuiKeyboard.h"
#include "GuiModMatrix.h"
#include "GuiPanelMain.h"
#include "GuiPanelHeader.h"
#include "GuiOverlayPadsynth.h"
#include "GuiTxtEdit.h"


#include "GuiPanelPatchGlobal.h"
#include "GuiPanelDistortion.h"
#include "GuiPanelCompression.h"
#include "GuiPanelGlobalDelay.h"
#include "GuiPanelGlobalReverb.h"
#include "GuiPanelGlobalModulation.h"
#include "GuiPanelGlobalEq.h"
#include "GuiPanelFxRouting.h"

#define NUMBER_EG_AMP 6
#define NUMBER_EG_PITCH 7

class GuiPanelMaster;

class GuiMainWindow : public GuiComponent
{
public:
	static void* hWindow;
	static char labelText[100];
	static GuiComponent *hotComponent, *dragComponent, *editingComponent;
	static GPoint *dragPoint, *movePoint;	
	Patch* currentPatch;
	static GuiPanelOsc* panelOsc;
	//GSurface* surface;
	static GuiPanelEg* panelEg;
	static GuiPanelFilter* panelFilter;
	static GuiPanelLfo* panelLfo;
	static GuiPanelModeller* panelModeller;
	static GuiModMatrix* panelModMatrix;
	//static GuiPanelModulations* panelModulations;
	static GuiKeyboard* keyboard;
	static GuiPanelMaster *panelMaster;
	static GuiPanelHeader* panelHeader;
	static GuiOverlayPadsynth* padsynthOverlay;
	static GuiTxtEdit *txtEdit;

	// patch fx
	GuiPanelPatchGlobal* panelPatchGlobal;
	GuiPanelDistortion* panelDistortion;
	GuiPanelCompression* panelCompression;
	GuiPanelFxRouting* panelFxRoutingPatch;
	GuiPanelFxRouting* panelFxRoutingGlobal;

	// global fx
	GuiPanelGlobalDelay* panelGlobalDelay;
	GuiPanelGlobalReverb* panelGlobalReverb;
	GuiPanelGlobalEq* panelGlobalEq;
	GuiPanelGlobalModulation* panelGlobalModulation;

	static GuiPanelMain *panelMain;

	static int currentOscNumber;
	static int currentEgNumber;
	static int currentLfoAvNumber;
	static int currentLfoPvNumber;

	GuiMainWindow(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiMainWindow(void);
	//void draw();
	void PatchChanged(Patch* patch);
};

