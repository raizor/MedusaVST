#pragma once

#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

enum GuiMainPanel
{
	kPanelPatch = 0,
	kPanelPatchFx, 
	KPanelGlobalFx
};

class GuiPanelMain: public GuiComponent
{
public:
	int panelNumber;
	GuiComponent* panelPatch;
	GuiComponent* panelPatchFx;
	GuiComponent* panelGlobalFx;

	GuiPanelMain(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelMain(void);
	void draw();
};

