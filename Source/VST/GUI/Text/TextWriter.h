#pragma once
#include "../../includes.h"
#include "../../Utils/Types.h"
#include "bmfont.h"


class TextWriter
{
public:
	static TextWriter* writer;
	BMFont* Lucida;
	BMFont* LucidaBig;
	TextWriter(void);
	~TextWriter(void);
};

