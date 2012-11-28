#include "TextWriter.h"

TextWriter* TextWriter::writer = 0;

TextWriter::TextWriter(void)
{
	Lucida = new BMFont();
	if (!Lucida->LoadFont(IDR_FONT_ENVY_DATA, IDB_FONT_ENVY_PNG))
	{
		DebugBreak();
	}

	LucidaBig = new BMFont();
	if (!LucidaBig->LoadFont(IDR_FONT_ENVYBIG_DATA, IDB_FONT_ENVYBIG_PNG))
	{
		DebugBreak();
	}
}


TextWriter::~TextWriter(void)
{
}
