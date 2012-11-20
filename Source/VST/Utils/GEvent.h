#pragma once

#include "types.h"

extern const char* EMPTY_KEY;

enum GEventType
{
	kGEventNone = 0,
	kGEventMouseDown,
	kGEventMouseUp,
	kGEventMouseMoved,
	kGEventKeyDown,
	kGEventKeyUp,
	kGEventRedraw,
	kGEventTextEditFinished,
	kGEventResize,
	kGEventMouseWheel,
};

enum GEventMouseButton
{
	kGEventMouseButtonNone = 0,
	kGEventMouseButtonLeft = 1,
	kGEventMouseButtonRight = 2,
	kGEventMouseButtonMiddle = 3,
};

enum GEventModifier
{
	kGEventModifierControl= 1,
	kGEventModifierShift = 2,
	kGEventModifierAlt = 4,
};

class GEvent
{
public:
	// TODO: Put text in char[2] array?
	GEvent();

	GEventType type;
	GEventMouseButton button;
	GPoint pos;

	int clickCount;

	int modifiers;

	char key[2];

	bool isHandled;

	int width, height;

	bool HasModifier(int modifier);

	WPARAM wParam;
};