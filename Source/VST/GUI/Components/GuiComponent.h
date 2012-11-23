#pragma once

#include "../../includes.h"
#include "GuiImageManager.h"

using namespace std;

enum GuiComponentType
{
	kGuiComponentTypeGeneric = 0,
	kGuiComponentTypeKnob,
	kGuiComponentTypeSlider
};

class GuiComponent
{
private:
	vector<GuiComponent*> subComponents;

public:
	int width, height;
	int offsetX, offsetY;
	Item* synthItem;
	GuiComponentType type;
	GuiComponent* parent;
	bool dirty;
	bool hottable;
	bool enabled;
	bool scrollable;
	bool scrolloffset;
	bool hasImage;
	GuiImage* image;	
	GuiComponent(int width, int height, int offsetX, int offsetY, int imageId = 0, bool scrollable = false);
	bool SetImage(int imageId);
	~GuiComponent(void);

	virtual void AddSubComponent(GuiComponent* component);
	virtual int SubComponentCount();
	virtual GuiComponent* GetComponent(int index);
	virtual void draw();
	virtual void HandleEvent(GEvent* evt, bool recursing = false);
	virtual void Clicked();
	virtual int GetOffsetX();
	virtual int GetOffsetY();
};

