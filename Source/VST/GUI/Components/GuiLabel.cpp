#include "GuiLabel.h"
#include "../Text/TextWriter.h"
#include "GuiMainWindow.h"

GuiLabel::GuiLabel(int width, int height, int offsetX, int offsetY, char* text, bool center, GuiLabelSize size) :  GuiComponent(width, height, offsetX, offsetY, 0)
{
	this->size = size;
	this->center = center;
	sprintf(this->text, "%s", text);
}


GuiLabel::~GuiLabel(void)
{
}

void GuiLabel::draw()
{
	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);

	BMFont* font;

	switch (size)
	{
	case kGuiLabelSizeSmall:
		font = TextWriter::writer->Lucida;
		break;
	case kGuiLabelSizeLarge:
		font = TextWriter::writer->LucidaBig;
		break;
	default:
		break;
	}
	font->SetColor(255,255,255,254);
	font->SetScale(1.00f);
	//TextWriter::writer->Lucida->PrintCenter(240, "WAVE FORM");
	if (center)
	{
		font->PrintCenter(0, 0, width, text);
	}else{
		font->Print(0, 0, text);
	}
	
	glPopMatrix();
}

void GuiLabel::SetText(char* txt)
{
	sprintf(text, txt);
}