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
	ParamType paramType;
	void* param;
	LinkedSynthItem(void);
	~LinkedSynthItem(void);
};

