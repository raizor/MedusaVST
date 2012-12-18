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

	LucidaBold = new BMFont();
	if (!LucidaBold->LoadFont(IDR_FONT_ENVYBOLD_DATA, IDB_FONT_ENVYBOLD_PNG))
	{
		DebugBreak();
	}

	LucidaTiny = new BMFont();
	if (!LucidaTiny->LoadFont(IDR_FONT_ENVYTINY_DATA, IDB_FONT_ENVYTINY_PNG))
	{
		DebugBreak();
	}
}


TextWriter::~TextWriter(void)
{
}
