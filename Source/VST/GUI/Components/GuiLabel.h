#pragma once

#include "GuiComponent.h"

enum GuiLabelSize
{
	kGuiLabelSizeSmall = 0,
	kGuiLabelSizeLarge,
	kGuiLabelSizeBold,
	kGuiLabelSizeTiny,

};

class GuiLabel : public GuiComponent
{
public:
	bool isEditable;
	bool isEditing;
	char text[255];
	bool center;
	GuiLabelSize size;
	GuiLabel(int width, int height, int offsetX, int offsetY, char* text, bool center = false, GuiLabelSize size = kGuiLabelSizeSmall, bool editable = false);
	~GuiLabel(void);
	virtual void draw();
	virtual void HandleEvent(GEvent* evt, bool recursing);
	void Clicked(GEvent* evt);
	void Edited(GEvent* evt);
	virtual void SetText(char* txt);

};

