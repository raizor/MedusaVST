#pragma once

#include "GuiComponent.h"

enum KnobType
{
	kKnobTypePercentage = 0, // x.xx%
	kKnobTypeInteger, // x
	kKnobTypeDecimalTwoPlaces, // x.xx
	kKnobTypeDecimalOnePlace, // x.x
	kKnobTypeDualDecimalOnePlace, // x.x : x.x
	kKnobTypeSeconds, // x.xx secs
	kKnobTypeCents,
	kKnobTypePan
};

class GuiKnob : public GuiComponent
{
private:
	void HandleDrag(GEvent* evt);
public:
	bool biDirectional;
	bool lit;
	int value;
	KnobType knobType;
	int min, max;
	GuiKnob(int width, int height, int offsetX, int offsetY, int imageId, int min, int max, bool biDirectional, KnobType knobType, char* name = NULL);
	~GuiKnob(void);
	void draw();
	virtual void HandleEvent(GEvent* evt, bool recursing = false);
};

