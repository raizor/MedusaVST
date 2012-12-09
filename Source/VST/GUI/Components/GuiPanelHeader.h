#pragma once
#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"

class GuiPanelHeader  : public GuiComponent
{
public:
	static GuiButton* butPatch;
	static GuiButton* butPatchFx;
	static GuiButton* butGlobalFx;

	GuiPanelHeader(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiPanelHeader(void);

	void CallbackClicked(void* data, GEvent* evt);
};

