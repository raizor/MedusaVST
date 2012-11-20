#pragma once

#include "../../includes.h"
#include "GuiImageManager.h"

enum GuiComponentType
{
	kGuiComponentTypeGeneric = 0,
	kGuiComponentTypeKnob
};

class GuiComponent
{
public:
	int width, height;
	int offsetX, offsetY;
	GuiComponentType type;
	bool dirty;
	bool hottable;
	bool enabled;
	bool scrollable;
	bool scrolloffset;
	bool hasImage;
	GuiImage* image;
	objectStack* subComponents;
	GuiComponent(int width, int height, int offsetX, int offsetY, int imageId = 0, bool scrollable = false);
	bool SetImage(int imageId);
	~GuiComponent(void);

	virtual void draw();
	virtual void HandleEvent(GEvent* evt, bool recursing = false);
	virtual void AddComponent(GuiComponent* component);
};

