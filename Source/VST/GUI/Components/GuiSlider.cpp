#include "GuiSlider.h"
#include "GuiMainWindow.h"

// knob

GuiSliderKnob::GuiSliderKnob(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton sliderOn, SpritesButton sliderOff) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	type = kGuiComponentTypeSliderKnob;
	hottable = true;
	value = 0;
	spriteOn = sliderOn;
	spriteOff = sliderOff;
}


void GuiSliderKnob::draw()
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
			sprite = image->spriteCollection->GetSprite((int)spriteOn);
		}else{
			sprite = image->spriteCollection->GetSprite((int)spriteOff);
		}
		
		//glColor4f(1,1,1,1);
		glBegin(GL_QUADS);

		image->drawSprite(sprite, 0, -16-value);

		glEnd();
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


void GuiSliderKnob::HandleDrag(GEvent* evt)
{
	float distance = (evt->pos.y - GuiMainWindow::dragPoint->y);
	char msg[255];
	if (IsHot(evt->pos.Plus(0, value), true))
	{		
		// set value
		float newVal = value - distance;
		if (newVal < 0) newVal = 0;
		if (newVal > 127) newVal = 127;

		value = newVal;

		sprintf(&msg[0], "drag y: %d, %d", (int)distance, value);

		DebugPrintLine(msg);
		GuiMainWindow::dragPoint->y = evt->pos.y;

	}else{
		DebugPrintLine("NOT HOT SK");
	}
}

void GuiSliderKnob::HandleEvent(GEvent* evt, bool recursing) 
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

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && IsHot(evt->pos.Plus(0, value)))
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

			if (!evt->isHandled && IsHot(evt->pos.Plus(0, value)))
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

bool GuiSliderKnob::IsHot(GPoint pos, bool onlyCheckY)
{
	return GuiComponent::IsHot(pos.Plus(0, 20), onlyCheckY);
}

// slider

/*

cursor Y must be same Y as bar for bar to move
bar pos matches Y pos within slider bounds

*/

GuiSlider::GuiSlider(int width, int height, int offsetX, int offsetY, int imageId, SpritesButton sliderOn, SpritesButton sliderOff) : GuiComponent(width, height, offsetX, offsetY, imageId)
{
	hottable = true;
	this->knob = new GuiSliderKnob(38, 33, 0, height, imageId, sliderOn, sliderOff);
	AddSubComponent(this->knob);
	type = kGuiComponentTypeSlider;
}


GuiSlider::~GuiSlider(void)
{
}


void GuiSlider::draw()
{
	float screenOffsetY = this->GetOffsetY();
	glPushMatrix();
	glTranslatef(offsetX, offsetY, 0);
	
	// draw slider background (for testing)
	glColor4f(0, 0, 0, 0.5);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	{
		glVertex2i(0,0);
		glVertex2i(0,0+height);
		glVertex2i(0+width,0+height);
		glVertex2i(0+width,0);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);

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

