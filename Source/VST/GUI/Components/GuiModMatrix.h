#pragma once

#include "GuiComponent.h"
#include "GuiKnob.h"
#include "GuiSlider.h"
#include "GuiButton.h"
#include "GuiLabel.h"
#include "../../Utils/ContextMenus.h"
#include "../Sprites/buttons.h"

class opair
{
public:
	void* val1;
	void* val2;
	opair(void* v1, void* v2);
};

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
	static char* StackItemTypeName(Item* item);
	static char* GuiModMatrix::ModulationCurveName(ModulationCurve type);
	void AddParamMenus(GContextMenuEx* menu, int* itemId, Item* item);
	char* GuiModMatrix::ParamName(Item* item, Param* param);
	char* GuiModMatrix::DestName(opair* pair);
	char* GuiModMatrix::SourceName(Item* item);
	void GuiModMatrix::UpdateGrid();
};

