#pragma once

#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glext.h"
#include "Types.h"
#include "Synth.h"

class LinkedSynthItem
{
public:
	Item* item;
	StackItemType itemType;
	ParamType paramType;
	ParamValueTypeFloat valueType;
	void* param;
	LinkedSynthItem(void);
	~LinkedSynthItem(void);
};

