#include "GuiSlider.h"
#include "GuiMainWindow.h"

GuiSlider::GuiSlider(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton sliderOn, SpritesButton sliderOff) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	hottable = true;
	value = 0;
	this->sliderOn = sliderOn;
	this->sliderOff = sliderOff;
	type = kGuiComponentTypeSlider;
}


GuiSlider::~GuiSlider(void)
{
}


void GuiSlider::draw()
{

	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);

	if (hasImage)
	{
		//if (!dirty) return; // doesn't need drawing

		image->bind();
		GSprite* sprite;

		if (GuiMainWindow::hotComponent == this)
		{
			sprite = image->spriteCollection->GetSprite((int)sliderOn);
		}else{
			sprite = image->spriteCollection->GetSprite((int)sliderOff);
		}
		

		float pixSizeX = sprite->spriteCollection->pixelSizeX; 
		float pixSizeY = sprite->spriteCollection->pixelSizeY;

		float x1 = pixSizeX * sprite->posX;
		float y1 = pixSizeY * sprite->posY;

		float x2 = x1 + (sprite->width*pixSizeX);
		float y2 = y1 + (sprite->height*pixSizeY);
		
		glColor4f(0,0,0,1);
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);

		glTexCoord2f(x1, y1);
		glVertex2i(0,0);

		glTexCoord2f(x1,y2);
		glVertex2i(0,0+height);

		glTexCoord2f(x2,y2);
		glVertex2i(0+width,0+height);

		glTexCoord2f(x2,y1);
		glVertex2i(0+width,0);

		glEnd();


		// offset for slider button
		printf("%d\n", value);

		float extraY = ((float)value) / 128.0f;
		extraY = height * extraY;

		glEnable(GL_TEXTURE_2D);

		glColor4f(1,1,1,1);
		glBegin(GL_QUADS);
		
		glTexCoord2f(x1, y1);
		glVertex2i(0,0-extraY);

		glTexCoord2f(x1,y2);
		glVertex2i(0,0+sprite->height-extraY);

		glTexCoord2f(x2,y2);
		glVertex2i(0+sprite->width,0+sprite->height-extraY);

		glTexCoord2f(x2,y1);
		glVertex2i(0+sprite->width,0-extraY);

		glEnd();
	}

	// draw sub components last as they likely appear on top of this component
	for(int i=0; i<SubComponentCount(); i++)
	{
		GuiComponent* gc = GetComponent(i);
		gc->dirty = dirty; // mark children as dirty as we're dirty, dirty children!!
		gc->draw();
	}
	glPopMatrix();

	dirty = false;

}


void GuiSlider::HandleDrag(GEvent* evt)
{
	float distance = (evt->pos.y  -GuiMainWindow::dragPoint->y) * 1.00f;
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

void GuiSlider::HandleEvent(GEvent* evt, bool recursing) 
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
					DebugPrintLine("HOT SLIDER");
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