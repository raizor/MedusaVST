#include "GuiLabel.h"
#include "../Text/TextWriter.h"
#include "GuiMainWindow.h"
#include <pluginterfaces/vst2.x/aeffectx.h>

GuiLabel::GuiLabel(int width, int height, int offsetX, int offsetY, char* text, bool center, GuiLabelSize size, bool editable) :  GuiComponent(width, height, offsetX, offsetY, 0)
{
	this->isEditing = false;
	this->isEditable = editable;
	this->size = size;
	this->center = center;
	this->EditedHandler = 0;
	sprintf(this->text, "%s", text);
}


GuiLabel::~GuiLabel(void)
{
}

void GuiLabel::Clicked(GEvent* evt)
{

}

void GuiLabel::Edited(GEvent* evt)
{
	char* txt = new char[255];
	if (evt->key[1] == VKEY_DELETE)
	{
		int len = strlen(this->text);
		this->text[len-1] = 0;
		//sprintf(txt, "%s%c", lab->text, key.character);		
	}else{
		sprintf(txt, "%s%c", this->text, evt->key[0]);		
		this->SetText(txt);
	}
}

void GuiLabel::HandleEvent(GEvent* evt, bool recursing) 
{
	if (evt->type == kGEventKeyDown && GuiMainWindow::editingComponent == this && !evt->isHandled)
	{
		Edited(evt);

		if (EditedHandler != NULL)
		{
			(this->*EditedHandler)(this, evt);
			evt->isHandled = true;
		}
		return;
	}
	GuiComponent::HandleEvent(evt, false);
}

void GuiLabel::draw()
{
	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);
	if (enabled)
	{
		BMFont* font;

		switch (size)
		{
		case kGuiLabelSizeSmall:
			font = TextWriter::writer->Lucida;
			break;
		case kGuiLabelSizeLarge:
			font = TextWriter::writer->LucidaBig;
			break;
		case kGuiLabelSizeBold:
			font = TextWriter::writer->LucidaBold;
			break;
		case kGuiLabelSizeTiny:
			font = TextWriter::writer->LucidaTiny;
			break;
		default:
			break;
		}


		// shadow
		font->SetColor(0,0,0,255);
		font->SetScale(1.00f);
		//TextWriter::writer->Lucida->PrintCenter(240, "WAVE FORM");
		if (center)
		{
			font->PrintCenter(1, 1, width, text);
		}else{
			font->Print(1, 1, text);
		}
	
		if (GuiMainWindow::editingComponent == this)
		{
			font->SetColor(255,255,0,255);
		}else{
			font->SetColor(255,255,255,255);
		}
		
		font->SetScale(1.00f);
		//TextWriter::writer->Lucida->PrintCenter(240, "WAVE FORM");
		if (center)
		{
			font->PrintCenter(0, 0, width, text);
		}else{
			font->Print(0, 0, text);
		}
	}
	glPopMatrix();
}

void GuiLabel::SetText(char* txt)
{
	sprintf(text, txt);
}