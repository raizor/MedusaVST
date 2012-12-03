#include "GuiKnob.h"
#include "GuiMainWindow.h"

GuiKnob::GuiKnob(int width, int height, int offsetX, int offsetY, int imageId, int min, int max, bool biDirectional, KnobType knobType, char* name ) : GuiComponent(width, height, offsetX, offsetY, imageId, false)
{
	if (name)
	{
		hasName = true;
		sprintf(this->name, name);
	}	
	this->knobType = knobType;
	this->min = min;
	this->max = max;
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

	if (hasImage && enabled)
	{
		//if (!dirty) return; // doesn't need drawing

		image->bind();
		//glColor4f(1,1,1,1);
		
		glBegin(GL_QUADS);
		
		float knobVal = value;
		
		if (synthItem)
		{
			ParamFloat* p  = (ParamFloat*)synthItem->param;
			float mult = 127.0 / max;
			knobVal = p->ValueAsInt() * mult;
		}

		// todo: precalc knob rotation positions

		lit = GuiMainWindow::hotComponent == this || GuiMainWindow::dragComponent == this;

		if (lit)
		{
			knobVal += 128;

			// set item name
			if (hasName)
			{
				GuiMainWindow::panelMaster->SetParamName(&this->name[0]);
			}
			
			// set item value
			if (synthItem)
			{
				ParamFloat* p  = (ParamFloat*)synthItem->param;
				switch(knobType)
				{
				case(kKnobTypeSeconds):
					sprintf(GuiMainWindow::labelText, "%0.3f secs", p->TargetValue);
					break;

				case(kKnobTypeDecimalTwoPlaces):
					// todo percent not working
					sprintf(GuiMainWindow::labelText, "%0.2f%% ", p->TargetValue);
					break;

				case(kKnobTypeDecimalOnePlace):
					// todo percent not working
					sprintf(GuiMainWindow::labelText, "%0.1f%% ", p->TargetValue);
					break;

				case(kKnobTypePan):
					sprintf(GuiMainWindow::labelText, "%0.1f :  %0.1f", 1.0f - p->TargetValue, p->TargetValue);
					break;

				case(kKnobTypeCents):
					// todo percent not working
					sprintf(GuiMainWindow::labelText, "%d cents", (int)p->TargetValue);
					break;

				default:
					sprintf(GuiMainWindow::labelText, " MISS %0.3f%% ", p->TargetValue);
					break;
				}			
				GuiMainWindow::panelMaster->SetParamValue(&GuiMainWindow::labelText[0]);
			}

			
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
	if (!enabled) return;

	float distance = (evt->pos.y  -GuiMainWindow::dragPoint->y) * 1.00f;
	char msg[255];
	sprintf(&msg[0], "drag y: %d", (int)distance);
	//DebugPrintLine(msg);

	// set value
	float newVal = value - distance;

	if (synthItem)
	{
		ParamFloat* p  = (ParamFloat*)synthItem->param;
		newVal = p->ValueAsInt() - distance;
	}

	if (newVal < min) newVal = 0;
	if (newVal > max) newVal = max;

	value = newVal;

	if (synthItem)
	{
		ParamFloat* p  = (ParamFloat*)synthItem->param;
		p->SetValueWithInt((int)newVal);
		sprintf(&msg[0], "knob val: %d", (int)newVal);
		DebugPrintLine(msg);
	}

	GuiMainWindow::dragPoint->y = evt->pos.y;

}

void GuiKnob::HandleEvent(GEvent* evt, bool recursing) 
{
	GuiComponent::HandleEvent(evt);
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

			if (!evt->isHandled && GuiMainWindow::dragComponent == NULL && IsHot(evt->pos) && enabled)
			{
				if (GuiMainWindow::hotComponent  != this)
				{
					DebugPrintLine("HOT KNOB");
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

			if (!evt->isHandled && IsHot(evt->pos) && enabled)
			{
				//DebugPrintLine("START DRAG KNOB");
				GuiMainWindow::dragComponent = this;
				GuiMainWindow::dragPoint->x = evt->pos.x;
				GuiMainWindow::dragPoint->y = evt->pos.y;
				evt->isHandled = true;
				Clicked(evt);
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