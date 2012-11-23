#include "GuiKnob.h"
#include "GuiMainWindow.h"

GuiKnob::GuiKnob(int width, int height, int offsetX, int offsetY, int imageId, bool biDirectional) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	this->width = 46;
	this->height = 46;
	value = 0;
	lit = false;
	this->biDirectional = biDirectional;
	hottable = true;
	type = kGuiComponentTypeKnob;
}


GuiKnob::~GuiKnob(void)
{
}


void GuiKnob::draw()
{
	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);

	if (hasImage)
	{
		//if (!dirty) return; // doesn't need drawing

		image->bind();
		//glColor4f(1,1,1,1);
		
		glBegin(GL_QUADS);
		
		float knobVal = value;

		// todo: precalc knob rotation positions

		lit = GuiMainWindow::hotComponent == this || GuiMainWindow::dragComponent == this;

		if (lit)
		{
			knobVal += 128;
		}

		float pixelSizeX = 1.0f / image->height;
		float pixelSizeY = 1.0f / image->width;
		int itemsPerRow = 22;
		int ioffsetY = knobVal / itemsPerRow;
		int ioffsetX = ((int)knobVal-(ioffsetY*itemsPerRow)); // BUG
		float px = ioffsetX * 46.0f;
		float py = ioffsetY * 46.0f;
		float x = px * pixelSizeX;
		float y = py * pixelSizeY;
		float knobSizeX = pixelSizeX * 46;
		float knobSizeY = pixelSizeY * 46;
				
		
		glTexCoord2f(x, y);
		glVertex2i(0, 0);

		glTexCoord2f(x, y+knobSizeY);
		glVertex2i(0, 0+46);

		glTexCoord2f(x+knobSizeX, y+knobSizeY);
		glVertex2i(0+46, 0+46);

		glTexCoord2f(x+knobSizeX, y);
		glVertex2i(0+46, 0);
		
		glEnd();
	}

	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<this->SubComponentCount(); i++)
	{
		GuiComponent* gc = GetComponent(i);
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}

	dirty = false;
	glPopMatrix();
}

void GuiKnob::HandleDrag(GEvent* evt)
{
	float distance = (evt->pos.y  -GuiMainWindow::dragPoint->y) * 0.75f;
	char msg[255];
	sprintf(&msg[0], "drag y: %d", (int)distance);
	DebugPrintLine(msg);

	// set value
	float newVal = value - distance;
	if (newVal < 0) newVal = 0;
	if (newVal > 127) newVal = 127;

	value = newVal;

	GuiMainWindow::dragPoint->y = evt->pos.y;

}

void GuiKnob::HandleEvent(GEvent* evt, bool recursing) 
{
	switch(evt->type)
	{
	case(kGEventMouseMoved):
		{
			if (!recursing)
			{
				char msg[255];
				sprintf(&msg[0], "x: %d, y: %d", (int)evt->pos.x, (int)evt->pos.y);
				//DebugPrintLine(msg);
			}

			if (GuiMainWindow::dragComponent == this)
			{
				//DebugPrintLine("DRAGGING KNOB");
				HandleDrag(evt);
				evt->isHandled = true;
			}

			// check children first
			for(int i=0; i<this->SubComponentCount(); i++)
			{
				GuiComponent* gc = GetComponent(i);
				gc->HandleEvent(evt, true);		
			}

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && hottable && width > 0 && height > 0 && (evt->pos.x >= GetOffsetX() &&  evt->pos.x <= GetOffsetX() + width) && (evt->pos.y >= GetOffsetY() &&  evt->pos.y <= GetOffsetY() + height))
			{
				if (GuiMainWindow::hotComponent  != this)
				{
					//DebugPrintLine("HOT KNOB");

				}
				GuiMainWindow::hotComponent = this;
				evt->isHandled = true;
				return;
			}
			break;
		}
	case(kGEventMouseDown):
		{
			if (!recursing)
			{
				char msg[255];
				sprintf(&msg[0], "x: %d, y: %d", (int)evt->pos.x, (int)evt->pos.y);
				//DebugPrintLine(msg);
			}

			// check children first
			for(int i=0; i<this->SubComponentCount(); i++)
			{
				GuiComponent* gc = GetComponent(i);
				gc->HandleEvent(evt, true);
				break;				
			}

			if (!evt->isHandled && hottable && width > 0 && height > 0 && (evt->pos.x >= GetOffsetX() &&  evt->pos.x <= GetOffsetX() + width) && (evt->pos.y >= GetOffsetY() &&  evt->pos.y <= GetOffsetY() + height))
			{
				//DebugPrintLine("START DRAG KNOB");
				GuiMainWindow::dragComponent = this;
				GuiMainWindow::dragPoint->x = evt->pos.x;
				GuiMainWindow::dragPoint->y = evt->pos.y;
				evt->isHandled = true;
				return;
			}
			break;
		}
	case(kGEventMouseUp):
		{
			//DebugPrintLine("STOP DRAG KNOB");
			GuiMainWindow::dragComponent = NULL;
			break;
		}
	default:
		{
			for(int i=0; i<this->SubComponentCount(); i++)
			{
				GuiComponent* gc = GetComponent(i);
				if (!evt->isHandled)
					gc->HandleEvent(evt, true);
			}
			break;
		}
	}
}