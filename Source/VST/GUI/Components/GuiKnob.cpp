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
		glVertex2i(offsetX, offsetY);

		glTexCoord2f(x, y+knobSizeY);
		glVertex2i(offsetX, offsetY+46);

		glTexCoord2f(x+knobSizeX, y+knobSizeY);
		glVertex2i(offsetX+46, offsetY+46);

		glTexCoord2f(x+knobSizeX, y);
		glVertex2i(offsetX+46, offsetY);
		
		glEnd();
	}

	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<subComponents->count; i++)
	{
		GuiComponent* gc = (GuiComponent*)subComponents->items[i];
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}

	dirty = false;
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
			for(int i=0; i<subComponents->count; i++)
			{
				GuiComponent* gc = (GuiComponent*)subComponents->items[i];
				gc->HandleEvent(evt, true);		
			}

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && hottable && width > 0 && height > 0 && (evt->pos.x >= offsetX &&  evt->pos.x <= offsetX + width) && (evt->pos.y >= offsetY &&  evt->pos.y <= offsetY + height))
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
			for(int i=0; i<subComponents->count; i++)
			{
				GuiComponent* gc = (GuiComponent*)subComponents->items[i];
				gc->HandleEvent(evt, true);
				break;				
			}

			if (!evt->isHandled && hottable && width > 0 && height > 0 && (evt->pos.x >= offsetX &&  evt->pos.x <= offsetX + width) && (evt->pos.y >= offsetY &&  evt->pos.y <= offsetY + height))
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
			for(int i=0; i<subComponents->count; i++)
			{
				GuiComponent* gc = (GuiComponent*)subComponents->items[i];
				if (!evt->isHandled)
					gc->HandleEvent(evt, true);
			}
			break;
		}
	}
}