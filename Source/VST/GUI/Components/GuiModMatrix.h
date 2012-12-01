#pragma once

#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "../../Utils/ContextMenus.h"
#include "../Sprites/buttons.h"

class GuiModMatrix : public GuiComponent
{
public:
	std::vector<GuiLabel*> butSource;
	std::vector<GuiLabel*> butCurve;
	std::vector<GuiLabel*> butControl;
	std::vector<GuiLabel*> butDest;

	GContextMenuEx* menuSource;

	GuiModMatrix(int width, int height, int offsetX, int offsetY, int imageId);
	~GuiModMatrix(void);
	void CallbackClicked(void* data, GEvent* evt);
};

