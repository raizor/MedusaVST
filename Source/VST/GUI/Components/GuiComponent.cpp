#include "GuiComponent.h"
#include "GuiMainWindow.h"
#include "GuiKnob.h"

GuiComponent::GuiComponent(int width, int height, int offsetX, int offsetY, int imageId, int spriteId, bool scrollable)
{
	dirty = true;
	scrollable = scrollable;
	scrolloffset = 0;
	this->spriteId = spriteId;
	enabled = true;
	hottable = false;
	this->width = width;
	this->height = height;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	hasImage = imageId !=0;
	type = kGuiComponentTypeGeneric;
	parent = NULL;
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
	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);

	if (hasImage)
	{
		//if (!dirty) return; // doesn't need drawing

		image->bind();
		
		//glColor4f(1,1,1,1);
		glBegin(GL_QUADS);

		if (spriteId !=0)
		{
			// draw sprite
			GSprite* sprite = image->spriteCollection->GetSprite((int)spriteId);
			image->drawSprite(sprite, 0, 0);

		}else{
			// draw whole image
			glTexCoord2f(0,0);
			glVertex2i(0,0);

			glTexCoord2f(0,1);
			glVertex2i(0, 0+height);

			glTexCoord2f(1,1);
			glVertex2i(0+width, 0+height);

			glTexCoord2f(1,0);
			glVertex2i(0+width, 0);
		}
		glEnd();
	}else{
		
		glDisable(GL_TEXTURE_2D);
		switch (type)
		{
		case kGuiComponentTypeSlider:
			{
				glColor4f(1,1,0,0.2f);
				break;
			}

		default:
			{
				glColor4f(1,0,1,0.2f);
				break;
			}

		}
		
		glBegin(GL_QUADS);

		glVertex2i(0,0);

		glVertex2i(0, 0+height);

		glVertex2i(0+width, 0+height);

		glVertex2i(0+width, 0);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glColor4f(1,1,1,1);
	}

	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<this->SubComponentCount(); i++)
	{
		GuiComponent* gc = GetComponent(i);
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}
	glPopMatrix();

	dirty = false;

}

int GuiComponent::GetOffsetX()
{
	int val = this->offsetX;	
	if (parent != NULL)
	{
		val+=parent->GetOffsetX();
	}
	return val;
}

int GuiComponent::GetOffsetY()
{
	int val = this->offsetY;	
	if (parent != NULL)
	{
		val+=parent->GetOffsetY();
	}
	return val;
}

void GuiComponent::HandleEvent(GEvent* evt, bool recursing)
{
	if (evt->isHandled) return;

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
			for(int i=0; i<subComponents.size(); i++)
			{
				GuiComponent* gc = (GuiComponent*)subComponents.at(i);
				gc->HandleEvent(evt, true);		
			}

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && IsHot(evt->pos))
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

			void* xx = this;

			if (!recursing)
			{
				char msg[255];
				sprintf(&msg[0], "x: %d, y: %d", (int)evt->pos.x, (int)evt->pos.y);
				//DebugPrintLine(msg);
			}

			// check children first
			for(int i=0; i<subComponents.size(); i++)
			{
				GuiComponent* gc = (GuiComponent*)subComponents.at(i);
				gc->HandleEvent(evt, true);	

			}

			if (!evt->isHandled && IsHot(evt->pos))
			{
				GuiMainWindow::dragComponent = this;
				GuiMainWindow::dragPoint->x = evt->pos.x;
				GuiMainWindow::dragPoint->y = evt->pos.y;
				evt->isHandled = true;
				Clicked(evt);
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
			for(int i=0; i<subComponents.size(); i++)
			{
				GuiComponent* gc = (GuiComponent*)subComponents.at(i);
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
			for(int i=0; i<subComponents.size(); i++)
			{
				GuiComponent* gc = (GuiComponent*)subComponents.at(i);
				if (!evt->isHandled)
					gc->HandleEvent(evt, true);
			}
			break;
		}
	}
}

 void GuiComponent::Clicked(GEvent* evt)
 {
	 
 }

 void GuiComponent::AddSubComponent(GuiComponent* component)
 {
	 subComponents.push_back(component);
	 component->parent = this;
 }

 int GuiComponent::SubComponentCount()
 {
	 return subComponents.size();
 }

 GuiComponent* GuiComponent::GetComponent(int index)
 {
	 return subComponents.at(index);
 }

 bool GuiComponent::IsHot(GPoint pos, bool onlyCheckY)
 {
	 float offX = GetOffsetX();
	 float offY = GetOffsetY();
	 return (width > 0 && height > 0) && ((pos.x >= offX &&  pos.x <= offX + width) || onlyCheckY) && (pos.y >= offY &&  pos.y <= offY + height);
 }