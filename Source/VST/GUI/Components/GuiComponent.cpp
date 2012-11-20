#include "GuiComponent.h"
#include "GuiMainWindow.h"
#include "GuiKnob.h"

GuiComponent::GuiComponent(int width, int height, int offsetX, int offsetY, int imageId, bool scrollable)
{
	dirty = true;
	scrollable = scrollable;
	scrolloffset = 0;
	enabled = true;
	hottable = false;
	this->width = width;
	this->height = height;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	subComponents = new objectStack(1000);
	hasImage = imageId !=0;
	type = kGuiComponentTypeGeneric;
	if (hasImage)
	{
		image = GuiImageManager::instance->GetImageById(imageId);
		if (width == 0) this->width = image->width;
		if (height == 0) this->height = image->height;
		int xx = 1;
	}
}

GuiComponent::~GuiComponent(void)
{
}

bool GuiComponent::SetImage(int imageId)
{
	image = GuiImageManager::instance->GetImageById(imageId);
	return image > 0;
}

void GuiComponent::draw()
{
	if (hasImage)
	{
		//if (!dirty) return; // doesn't need drawing

		image->bind();
		//glColor4f(1,1,1,1);
		glBegin(GL_QUADS);

		glTexCoord2f(0,0);
		glVertex2i(offsetX,offsetY);

		glTexCoord2f(0,1);
		glVertex2i(offsetX,offsetY+height);

		glTexCoord2f(1,1);
		glVertex2i(offsetX+width,offsetY+height);

		glTexCoord2f(1,0);
		glVertex2i(offsetX+width,offsetY);

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

void GuiComponent::AddComponent(GuiComponent* component)
{
	subComponents->push(component);
}

void GuiComponent::HandleEvent(GEvent* evt, bool recursing)
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

			// check children first
			for(int i=0; i<subComponents->count; i++)
			{
				GuiComponent* gc = (GuiComponent*)subComponents->items[i];
				gc->HandleEvent(evt, true);		
			}

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && hottable && width > 0 && height > 0 && (evt->pos.x >= offsetX &&  evt->pos.x <= offsetX + width) && (evt->pos.y >= offsetY &&  evt->pos.y <= offsetY + height))
			{
				GuiMainWindow::hotComponent = this;
				evt->isHandled = true;
				return;
			}

			// no hot component
			if (!recursing)
			{
				if (!evt->isHandled && GuiMainWindow::dragComponent == NULL)
				{
					GuiMainWindow::hotComponent = NULL;
				}
				
				GuiMainWindow::movePoint->x = evt->pos.x;
				GuiMainWindow::movePoint->y = evt->pos.y;
				//DebugPrintLine("UNHOT COMP");
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
			}

			if (!evt->isHandled && hottable && width > 0 && height > 0 && (evt->pos.x >= offsetX &&  evt->pos.x <= offsetX + width) && (evt->pos.y >= offsetY &&  evt->pos.y <= offsetY + height))
			{
				GuiMainWindow::dragComponent = this;
				GuiMainWindow::dragPoint->x = evt->pos.x;
				GuiMainWindow::dragPoint->y = evt->pos.y;
				evt->isHandled = true;
				return;
			}

			// no hot component
			if (!recursing && !evt->isHandled)
			{
				GuiMainWindow::dragComponent = NULL;
				//DebugPrintLine("STOP DRAG");
			}	
			break;
		}
	case(kGEventMouseUp):
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
			}

			// no hot component
			if (!recursing && !evt->isHandled)
			{
				GuiMainWindow::dragComponent = NULL;
			}	
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
