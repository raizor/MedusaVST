#pragma once

#include "../../includes.h"
#include "../../Utils/LinkedSynthItem.h"
#include "GuiImageManager.h"

using namespace std;

#define xDRAW_OVERLAYS

enum GuiComponentType
{
	kGuiComponentTypeGeneric = 0,
	kGuiComponentTypeKnob,
	kGuiComponentTypeSlider,
	kGuiComponentTypeSliderKnob,
	kGuiComponentTypeKeyboard
};

class GuiComponent;

typedef void (GuiComponent::*FpClickedCallback)(void* component, GEvent* evt);

class GuiComponent
{
private:
	vector<GuiComponent*> subComponents;

public:
	bool drawOverlay;
	char name[100];
	bool hasName;
	int width, height;
	int offsetX, offsetY;
	LinkedSynthItem* synthItem;
	GuiComponentType type;
	GuiComponent* parent;
	FpClickedCallback ClickedHandler;
	FpClickedCallback EditedHandler;
	bool dirty;
	bool hottable;
	bool enabled;
	bool scrollable;
	bool scrolloffset;
	bool hasImage;
	int spriteId;
	void* data;
	GuiImage* image;	
	GuiComponent(int width, int height, int offsetX, int offsetY, int imageId = 0, int spriteId = 0, bool scrollable = false, char* name = NULL);
	bool SetImage(int imageId);
	virtual ~GuiComponent();

	virtual void AddSubComponent(GuiComponent* component);
	virtual int SubComponentCount();
	virtual GuiComponent* GetComponent(int index);
	virtual void draw();
	virtual void HandleEvent(GEvent* evt, bool recursing = false);
	virtual void Clicked(GEvent* evt);
	virtual void Edited(GEvent* evt);
	virtual int GetOffsetX();
	virtual int GetOffsetY();
	virtual bool IsHot(GPoint pos, bool onlyCheckY = false);
	virtual void SetStackItem(Item* item);
	virtual void SetOffset(int x, int y);
	

	virtual void CallbackVoid();
};

